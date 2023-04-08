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
	Trieda je zodpovedna za realizovanie asycnhronnej operacie TryReceive na CH.
	Jej ulohou je v threade monitorovat prichadzajuce MESSAGE a END packety a konvertovat ich ma M.
	Ak sa nova M najde potom sa posle WCF.
*/
//-------------------------------------------------------------------------------------------------------
	public class CTryReceiveChannelThread : CThreadHelper
	{
//-------------------------------------------------------------------------------------------------------
		// SessionID CH.
		private CFTCSessionID									MFTCSessionID;
		// Adresar, ktory scanujem na prichod novych packetov.
		private string											MDirectory;
		// Encoder na deserializaciu M - obdrzal som ho z ME BE.
		private MessageEncoder									MMessageEncoder;
		// Notifikacne rozhranie cez ktore CH oznami CL pri volanie Close(), ze sa koreknte ukoncil a teda uz ho CL nemusi pri svojom Close() ukoncovat.
		private IFTCCloseSessionNotification					MCloseSessionNotification;
		// Pattern mena suborov. Treba to, kedze do toho isteho adresara sa kopituju ako BEGIN packety tak aj MESSAGE a END packety vsektych CH a rozlisenie je prave podla mena. Obsahuje SessionID.
		private string											MSearchPattern;
		// Trieda obsahujuca 2 fronty: na TryReceive Requests prisle packety.
		private CTryReceiveQueues								MTryReceiveQueues;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTryReceiveChannelThread(CFTCSessionID FTCSessionID, string Directory, MessageEncoder MessageEncoder, IFTCCloseSessionNotification CloseSessionNotification)
			: base(CDebugHelper.GetIDShortuct(FTCSessionID.SessionID,"TryReceive"),CSettings.TryReceiveThreadExitTimeout,CSettings.TryReceiveThreadCheckTimeout)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MFTCSessionID=FTCSessionID;
			MDirectory=Directory;
			MMessageEncoder=MessageEncoder;
			MCloseSessionNotification=CloseSessionNotification;
			// Pattern ma SessionID.
			MSearchPattern=string.Format("SESSION_{0}*",FTCSessionID.SessionID);
			MTryReceiveQueues=new CTryReceiveQueues();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Kontrolujem ci niektoremu Requst nepretiekol timeout.
		// Kedze WCF mi v prikladoch vracala maximalny cas tak toto nemohlo nikdy pretiect.
		private void CheckTimeouts()
		{
			CFTCTryReceiveAsyncResult		TRAR=null;

			// Ziskam Request, ktoremu expiroval timeout - zaroven sa odstrani z fronty.
			while((TRAR=MTryReceiveQueues.GetNextExpiredRequest())!=null)
				// Volam metodu Request, ktora odpali interny WCF callback a ten zavola EndTryReceive() tejto triedy - cez EndTryReceive() CH.
				TRAR.DoFinishByExpiraiton();
		}
//-------------------------------------------------------------------------------------------------------
		// Jej ulohou je parovat Request a packet.
		private void PairRequestMessage()
		{
			//  Ak mam Request a pride packet tak ich odstrani z front a zaroven spusti jeho metodu, ktora odpali WCF callback a ta spusti moju EndTryReceive().
			MTryReceiveQueues.MakePair();
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda zistuje ci neprisiel packet a ak ano tak ho vycita a vrati v navratovej hodnote.
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
		// Prisly packet zaradi do frotny packetov.
		private void ProcessPacket(CFTCPacket Packet)
		{
			MTryReceiveQueues.AddPacket(Packet);
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
//			Console.WriteLine("S: {0} !",MFTCSessionID.SessionID);

			CheckTimeouts();

			PairRequestMessage();

			CFTCPacket		Packet=CheckForPacket();

			if (Packet==null)
				return;

			ProcessPacket(Packet);
		}
//-------------------------------------------------------------------------------------------------------
		// Pri starte je treba vymazat fronty.
		protected override void Starting()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MTryReceiveQueues.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		protected override void Started()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void Stopping()
		{
			// Tu lock nie je treba, lebo je to volane v ramci lock.

			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Korektne zrusim vsetky Request na TryReceive a to tak, ze sa vyvola WCF callback a ta zas moju EndTryReceive().
			MTryReceiveQueues.ClosePendingRequests();

			// Informujem CL thread o tom, ze koncim aby pri ukoncovani CL uz ten nevolal Close() pre tento CH.
			if (MCloseSessionNotification!=null)
				MCloseSessionNotification.RemoveSession(MFTCSessionID);
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
		// Je to implementnacia BeginTryReceive() CH.
		// Jej ulohou je vytvorit Request - teda objekt typu IAsyncResult, ktory vratim az do WCF a ta ho potom ma ako identifikator Request a ked ten je obsluzeny tak sa vyvola zaregistrovany callback (property tejto triedy) a ten zas vyvola moju EndTryReceive() do ktorej posle prave tento objekt.
		public CFTCAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim Request. Ako vidiet registrujem aj Callback - co je WC interna metoda, ktora sa vyvola ko ukonceni Request a ta zavola moju EndTryReceive().
			CFTCTryReceiveAsyncResult	FTCTryReceiveAsyncResult=new CFTCTryReceiveAsyncResult(Callback,State,Timeout);

			// Zaradim Request do fronty.
			MTryReceiveQueues.AddRequest(FTCTryReceiveAsyncResult);

			return(FTCTryReceiveAsyncResult);
		}
//-------------------------------------------------------------------------------------------------------
		// Je to implementnacia EndTryReceive() CH.
		// Jej ulohou je ukoncit Request a je volana z interneho WCF callback.
		// Cielom je ak dosla M tak ju vratit do WCF aby mohla byt spracovana.
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// !!! Nesmie tu byt volanie metod MTryReceiveQueues, inak nastane DEADLOCK.
			Message=null;

			// Pretypujem objekt, ktory som zaslal v BeginTryReceive().
			CFTCTryReceiveAsyncResult	TRAR=Result as CFTCTryReceiveAsyncResult;

			// Ak pretypovanie zlyhalo tak vratim NULL.
			if (TRAR==null)
			{
				CSettings.Log.Write("Can't CONVERT IAsyncResult to CFTCTryReceiveAsyncResult !",ELogRecordType.E_LRT_MESSAGE);
				return(false);
			}

			// Ak dosiel END PACKET, alebo ak bol CH uzavrety cez Close() potom musim korektne skonci Request a WCF notifikovat, ze CH sa skoncil.
			// O tom, ze CH skoncil informuje nastavenim Message na NULL a vratenim TRUE.
			// Na to WCF zareaguje volanim Close() ale ??? iba ak nedoslo k volanie EndTryReceive() prave v dosledku volanie Close() na CH.
			if (TRAR.HasClosed==true)
			{
				CSettings.Log.Write("TryReceive CLOSED !",ELogRecordType.E_LRT_MESSAGE);
				// !!!!! Musim vratit TRUE, aby sa ukoncil CH. !!!!!
				return(true);
			}

			// Ak Request expiroval potom o tom musim informovat WCF a to tym, ze Message je na NULL a vratim FALSE.
			// Na toto WCF reaguje vyslanim noveho Request co je rozdiel oproti Close() (vtedy vraciam TRUE), kde sa uz BeginTryReceive() nevola.
			if (TRAR.HasExpired==true)
			{
				CSettings.Log.Write("TryReceive EXPIRED !",ELogRecordType.E_LRT_MESSAGE);
				return(false);
			}

			// Iba pomocny test ak by bol packet nekorektny.
			if (TRAR.IsCompleted==false || TRAR.Packet==null || TRAR.Packet.Message==null)
			{
				CSettings.Log.Write("TryReceive CAN'T FIND PACKET for request !",ELogRecordType.E_LRT_MESSAGE);
				return(false);
			}

			// Nastavim Message na tu M co bola nacitane z packetu.
			Message=TRAR.Packet.Message;

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------