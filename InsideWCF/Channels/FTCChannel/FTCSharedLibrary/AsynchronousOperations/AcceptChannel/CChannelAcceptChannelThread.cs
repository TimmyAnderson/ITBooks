using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda je zodpovedna za realizovanie asycnhronnej operacie AcceptChannel na CL.
	Jej ulohou je v threade monitorovat prichadzajuce packety a zistovat ci nie su to BEGIN packety.
	Ak ano tak musi vytvorit novy CH.
*/
//-------------------------------------------------------------------------------------------------------
	public class CChannelAcceptChannelThread : CThreadHelper, IFTCCloseSessionNotification
	{
//-------------------------------------------------------------------------------------------------------
		// Adresar, ktory scanujem na prichod novych BEGIN packetov.
		private string											MDirectory;
		// Cas na uzvaretie CH. Vyuziva sa ked uzatvaram vsetky neuzatvorene CH pri uzatvarani CL.
		private TimeSpan										MCloseTimeout;
		// Encoder na deserializaciu M - obdrzal som ho z ME BE.
		private MessageEncoder									MMessageEncoder;
		// Pattern mena suborov. Treba to, kedze do toho isteho adresara sa kopituju ako BEGIN packety tak aj MESSAGE a END packety vsektych CH a rozlisenie je prave podla mena. 
		private string											MSearchPattern;
		// Trieda obsahujuca 2 fronty: na AcceptChannel Requests a SessionID otvorenych CH.
		private CAcceptChannelQueues							MAcceptChannelQueues;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChannelAcceptChannelThread(string Directory, TimeSpan CloseTimeout, MessageEncoder MessageEncoder)
			: base("AcceptChannel",CSettings.AcceptChannelThreadExitTimeout,CSettings.AcceptChannelThreadCheckTimeout)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MDirectory=Directory;
			MCloseTimeout=CloseTimeout;
			MMessageEncoder=MessageEncoder;
			MSearchPattern="PACKET*";
			MAcceptChannelQueues=new CAcceptChannelQueues();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Kontrolujem ci niektoremu Requst nepretiekol timeout.
		// Kedze WCF mi v prikladoch vracala maximalny cas tak toto nemohlo nikdy pretiect.
		private void CheckTimeouts()
		{
			CFTCAcceptChannelAsyncResult	ACAR=null;

			// Ziskam Request, ktoremu expiroval timeout - zaroven sa odstrani z fronty.
			while((ACAR=MAcceptChannelQueues.GetNextExpiredRequest())!=null)
				// Volam metodu Request, ktora odpali interny WCF callback a ten zavola EndAcceptChannel() tejto triedy - cez EndAcceptChannel() CL.
				ACAR.DoFinishByExpiraiton();
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda zistuje ci neprisiel packet a ak ano tak ho vycita a vrati v navratovej hodnote.
		// Mohlo by to byt optimalnejsie a nerobit check na M, ale iba na nazov suboru.
		private CFTCPacket CheckForPacket()
		{
			try
			{
				DirectoryInfo		DI=new DirectoryInfo(MDirectory);
				FileInfo			File=null;
				FileStream			FS=null;

				// Najdem najstarsi subor.
				// Toto by malo zabezpecit, ze M v session budu spracovane v poradi v akom boli vyslane.
				foreach(FileInfo FI in DI.GetFiles(MSearchPattern))
					if (File==null || File.LastAccessTime>FI.LastAccessTime)
						File=FI;

				// Ak subor neexistuje koncim.
				if (File==null)
					return(null);

				CSettings.Log.Write(string.Format("File: {0} is going to be READ !",File.FullName),ELogRecordType.E_LRT_MESSAGE);

				try
				{
					// Nacitam obsah suboru.
					MemoryStream		MS=CFileHelper.ReadFileToStream(File.FullName);

					// Subor bol nacitany a moze byt zmazany.
					File.Delete();

					CSettings.Log.Write(string.Format("File: {0} was SUCCESSFULLY READ !",File.FullName),ELogRecordType.E_LRT_MESSAGE);

					// Vytvorim prazdny packet.
					CFTCPacket			Packet=new CFTCPacket();

					// Deserializujem packet zo obsahu suboru.
					Packet.ReadMessageWithEncoder(MS,MMessageEncoder);

					CSettings.Log.Write(string.Format("Message from file: {0} was SUCCESSFULLY PARSED !",File.FullName),ELogRecordType.E_LRT_MESSAGE);

					return(Packet);
				}
				catch
				{
					CSettings.Log.Write(string.Format("File: {0} FAILED to be READ or PARSE MESSAGE !",File.FullName),ELogRecordType.E_LRT_EXCEPTION);
				}
				finally
				{
					if (FS!=null)
					{
						FS.Close();
						FS=null;
					}
				}
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
			}

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		// Spracuvava dosli packet. Robi testy na typ packetu aj to ci ma zopdovedajuci Request.
		private void ProcessPacket(CFTCPacket Packet)
		{
			// Zavolam metodu, ktora vyhodnoti ci novy packet je BEGIN packet, ci mu zodpoveda Request a teda ci znamena vytvorenie noveho CH.
			ECheckSessionResponse	CSR=MAcceptChannelQueues.CheckSession(Packet);

			// Ak napriklad prisiel MESSAGE packet do neexistujucej session, alebo BEGIN packet do uz existujucej, END packet bez session a tak podobne. Teda logicke chyby.
			if (CSR==ECheckSessionResponse.E_CSR_ERROR)
				return;
			// Prisiel sice BEGIN packet, ale nemam Request na novy CH.
			else if (CSR==ECheckSessionResponse.E_CSR_NO_SESSION_REQUEST)
				return;
			// Poziadavka na novu session.
			// Tu nemusim robit nic, pretoze uz CheckSession() vyssie sposobila zavolanie WCF callback a ten zas vyvolanie mojej metody EndAcceptChannel() nizsie a ta vytvori CH.
			else if (CSR==ECheckSessionResponse.E_CSR_NEW_SESSION)
				return;
			// Prisiel MESSAGE, alebo END pacekt do existujuce session a teda treba vytovrit subor s menom v ktorm bude SessionID, aby ho mohol CH s prislusnym Session ID spracovat.
			else
			{
				// Zapisem obsah pacektu do Streamu.
				MemoryStream	MS=Packet.WriteMessageWithEncoder(MMessageEncoder);
				// Vytvorim jeho meno aby v nom bolo obsiahnute SessionID, lebo iba tak bude vediet ho CH vycitat.
				string			FileName=string.Format(@"{0}\SESSION_{1}_{2}.ftc",MDirectory,Packet.SessionID.SessionID,Packet.FileID);

				try
				{
					// Zapisem do suboru.
					CFileHelper.WriteFileFromStream(FileName,MS);
					CSettings.Log.Write(string.Format("File: {0} was SUCCESSFULLY WRITTEN !",FileName),ELogRecordType.E_LRT_MESSAGE);
				}
				catch
				{
					CSettings.Log.Write(string.Format("File: {0} FAILED to be WRITTEN !",FileName),ELogRecordType.E_LRT_EXCEPTION);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override void Do(int Index)
		{
			DoTimeout();
		}
//-------------------------------------------------------------------------------------------------------
		// Samotna business logika threadu.
		protected override void DoTimeout()
		{
			CheckTimeouts();

			CFTCPacket		Packet=CheckForPacket();

			if (Packet==null)
				return;

			ProcessPacket(Packet);
		}
//-------------------------------------------------------------------------------------------------------
		// Pri starte je treba vymazat fronty a adresar.
		protected override void Starting()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vymazem vsetky Request.
			MAcceptChannelQueues.Clear();

			try
			{
				DirectoryInfo		DI=new DirectoryInfo(MDirectory);
				FileInfo[]			FIArray=DI.GetFiles();

				// Zmazem vsetky subory.
				foreach(FileInfo FI in FIArray)
					FI.Delete();
			}
			catch
			{
				CSettings.Log.Write(string.Format("DELETE FAILED in directory: {0} !",MDirectory),ELogRecordType.E_LRT_EXCEPTION);
			}
		}
//-------------------------------------------------------------------------------------------------------
		protected override void Started()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);
		}
//-------------------------------------------------------------------------------------------------------
		// Pri uzatvarani musim korektne uzavriet vsetky cakajuce Requests a otvorene CH.
		protected override void Stopping()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Korektne zrusim vsetky Request na AcceptChannel a to tak, ze sa vyvola WCF callback a ta zas moju EndAcceptChannel().
			MAcceptChannelQueues.ClosePendingRequests();

			// Zrusim vsetky doteraz otvorene CH volanim Close() na kadzom z nich.
			MAcceptChannelQueues.CloseAllOpenedChannels(MCloseTimeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void Stopped()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Je to implementnacia BeginAcceptChannel() CL.
		// Jej ulohou je vytvorit Request - teda objekt typu IAsyncResult, ktory vratim az do WCF a ta ho potom ma ako identifikator Request a ked ten je obsluzeny tak sa vyvola zaregistrovany callback (property tejto triedy) a ten zas vyvola moju EndAcceptChannel() do ktorej posle prave tento objekt.
		public CFTCAsyncResult BeginAcceptChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim Request. Ako vidiet registrujem aj Callback - co je WC interna metoda, ktora sa vyvola ko ukonceni Request a ta zavola moju EndAcceptChannel().
			CFTCAcceptChannelAsyncResult	FTCAcceptChannelAsyncResult=new CFTCAcceptChannelAsyncResult(Callback,State,Timeout);

			// Zaradim Request do fronty.
			MAcceptChannelQueues.AddRequest(FTCAcceptChannelAsyncResult);

			return(FTCAcceptChannelAsyncResult);
		}
//-------------------------------------------------------------------------------------------------------
		// Je to implementnacia EndAcceptChannel() CL.
		// Jej ulohou je ukoncit Request a je volana z interneho WCF callback.
		// Cielom je vratit bud novy CH, alebo NULL ak je CL ukonceny, alebo pretiekol timeout.
		// !!! Mohol som to implemetnovat aj tak, ze v tejto metode by sa vytvara CH a dokonca ich aj evidovat v koleckii vsetky CH (potrebne pri Close() aby sa uzavreli beziace CH), ale napokon som to urobil separatne.
		public IDuplexSessionChannel EndAcceptChannel(IAsyncResult Result, IFTCDuplexSessionChannelCreator DSCC)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Pretypujem objekt, ktory som zaslal v BeginAcceptChannel().
			CFTCAcceptChannelAsyncResult				ACAR=Result as CFTCAcceptChannelAsyncResult;

			// Ak pretypovanie zlyhalo tak vratim NULL.
			if (ACAR==null)
			{
				CSettings.Log.Write("Can't CONVERT IAsyncResult to CFTCAcceptChannelAsyncResult !",ELogRecordType.E_LRT_MESSAGE);
				return(null);
			}

			// Ak dosla poziadavka na uzatvorenie CL volanim Close() na CH, ktora vyvola meotdu Stop() tohto threadu a ten zas Stopping() vyssie potom vratim NULL aby WCF vedela, ze sa ukoncuje CL.
			if (ACAR.HasClosed==true)
			{
				CSettings.Log.Write("EndAcceptChannel CLOSED !",ELogRecordType.E_LRT_MESSAGE);
				// !!!!! Musim vratit NULL, aby sa ukoncil CL. !!!!!
				return(null);
			}

			// Ak expiroval Request vratim NULL.
			if (ACAR.HasExpired==true)
			{
				CSettings.Log.Write("EndAcceptChannel EXPIRED !",ELogRecordType.E_LRT_MESSAGE);
				// !!!!! Musim vratit null, aby sa ukoncil CL. !!!!!
				return(null);
			}

			// Ma sa vyvorit novy CH.

			// Vytovrim si CH cez pomocnu triedu.
			IDuplexSessionChannel						CH=DSCC.CreateChannel(ACAR.SessionID,ACAR.RemoteAddress);
			CPair<CFTCSessionID, IDuplexSessionChannel>	Pair=new CPair<CFTCSessionID,IDuplexSessionChannel>(ACAR.SessionID,CH);

			// Zaradim ho medzi do fronty zijuich CH aby som vedel zachytavat MESSAGE a END pakety a uzavriet ho pri uzatvarani CL ak tak pred tym neurobil Sender.
			MAcceptChannelQueues.AddSession(Pair);

			return(CH);
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda je volana CH, ked sa ukocnuje a nofifikuje CL, ze CH sa korektne ukoncil a teda ho nie je treba pri Close() CL ukoncovat.
		public void RemoveSession(CFTCSessionID SessionID)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Odstrani SessioID CH z fronty otvorenych CH.
			MAcceptChannelQueues.RemoveSession(SessionID);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------