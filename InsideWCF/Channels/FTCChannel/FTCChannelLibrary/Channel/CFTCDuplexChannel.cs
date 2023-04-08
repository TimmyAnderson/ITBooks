using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda, ktora impelemtnuje moj Duplex CH.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCDuplexChannel : ChannelBase, IDuplexSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Treida, ktora implementuje asynchronnu operaciu TryReceive.
		private	CTryReceiveChannelThread						MTRCT;
		// Odkaz na CL - kvoli base class, ktora ho potrebuje v konstruktore.
		private ChannelManagerBase								MCMB;
		// SessionID CH.
		private CFTCSessionID									MSessionID;
		// Priznak ci je to CH na strane Sender(FALSE), alebo Receiver (TRUE).
		private bool											MIsListener;
		// Lokalna adresa CH.
		private Uri												MLocalAddress;
		// Vzdialena adresa CH.
		private Uri												MRemoteAddress;
		// Encoder M - pouziva sa pri serializacii a deserializacii M.
		private MessageEncoder									MMessageEncoder;
		// Adresar, ktory scanujem na prichod M (Packetov) - je odvodeny z MLocalAddress.
		private string											MLocalDirectory;
		// Adresar na ktory sa zasiela M (Packet) - je odvodeny z MRemoteAddress.
		private string											MRemoteDirectory;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCDuplexChannel(ChannelManagerBase CMB, CFTCSessionID SessionID, bool IsListener, Uri LocalAddress, Uri RemoteAddress, MessageEncoder MessageEncoder)
			: base(CMB)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCMB=CMB;
			MSessionID=SessionID;
			MIsListener=IsListener;
			MLocalAddress=LocalAddress;
			MRemoteAddress=RemoteAddress;
			MMessageEncoder=MessageEncoder;

			// Adresar zavisi od toho ci som na strane Sender, alebo Listener.
			// !!!!! V FTC vlastne vymena packetov pebieha iba medzi podadresarmi Sedner a Receiver toho isteho parent adresara.
			if (IsListener==true)
			{
				MLocalDirectory=string.Format("{0}/Receiver",MLocalAddress.AbsolutePath);
				MRemoteDirectory=string.Format("{0}/Sender",MRemoteAddress.AbsolutePath);
			}
			else
			{
				MLocalDirectory=string.Format("{0}/Sender",MLocalAddress.AbsolutePath);
				MRemoteDirectory=string.Format("{0}/Receiver",MRemoteAddress.AbsolutePath);
			}

			MTRCT=new CTryReceiveChannelThread(MSessionID,MLocalDirectory,MessageEncoder,(IFTCCloseSessionNotification) MCMB);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IDuplexSession									Session
		{
			get
			{
				// !!!!! Co bolo mimoriadne zaujimave, tak WCF tuto property nikdy necitala.
				// !!!!! Podla mna sluzi iba pre CH vyssie v CS na identifikaciu CH a to tiez iba ak si to tieto CH vyzaduju. Kedze ja som nemal viac CH tak nemal kto SessionID potrebovat.
				CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									LocalAddress
		{
			get
			{
				return(new EndpointAddress(MLocalAddress));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									RemoteAddress
		{
			get
			{
				return(new EndpointAddress(MRemoteAddress));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public Uri												Via
		{
			get
			{
				CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Iba delegujem volanie na CTryReceiveChannelThread, kde je cela logika.
			return(MTRCT.BeginTryReceive(Timeout,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Dvolanie na CTryReceiveChannelThread, kde je cela logika.
			bool		Ret=MTRCT.EndTryReceive(Result,out Message);

			// !!!!! Kedze zdrojova M neobsahovala 'To' (WCF ju tam nepridalo) tak ju doplnam tu.
			// !!! Toto ozaj ma robit TCH - tak to pisu v knihe. Malo by sa o vsak robit IBA ked je property ManualAddressing==false.
			if (Message!=null && Message.Headers.To==null)
				Message.Headers.To=MRemoteAddress;

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message, TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			try
			{
				// Vytovrim FileID - unikatne ID suboru - 6 cislis.
				string				FileID=CDebugHelper.GetIntID(6);
				// Vytvorim packet s M, ktoru chcem poslat.
				CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(MSessionID.SessionID),MLocalAddress.AbsoluteUri,FileID,EMessageType.E_MT_MESSAGE,Message);
				// Serializujem packet do Streamu.
				// !!! Vyuziva sa pri tom Encoder, ktory som ziskal z ME BE.
				MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);
				// Vytorim cestu k suboru kde bude zapisany packet. V mene suboru musi existovat SessionID aby bol packet smerovany priamo do CH.
				// !!! Kedze s jedna o MESSAGE, ktory uz musi byt smeorvany do konkretneho CH, smerujem ho priamo pre dany CH - prihodenim SessionID do mena.
				// !!! Uz to musim smerovat priamo na cielovy adresar. Listener sa tu uz nezapaja.
				string				FileName=string.Format(@"{0}\SESSION_{1}_{2}.ftc",MRemoteDirectory,MSessionID.SessionID,FileID);

				// Zapisem subor (packet) na disk.
				CFileHelper.WriteFileFromStream(FileName,MS);
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
			}
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Ak je to na strane Sendera zaslem BEGIN packet.
			// !!! Tymto packetom vytvorim a spustim CH na strane Receivera.
			if (MIsListener==false)
			{
				// Vytovrim FileID - unikatne ID suboru - 6 cislis.
				string				FileID=CDebugHelper.GetIntID(6);
				// Vytovrim prazdnu M - BEGIN packet nepotrebuje M s telom.
				Message				Message=Message.CreateMessage(CSettings.MessageVersion,"START","START");
				// Vytvorim packet, ktory chcem poslat.
				CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(MSessionID.SessionID),MLocalAddress.AbsoluteUri,FileID,EMessageType.E_MT_START,Message);
				// Serializujem packet do Streamu.
				// !!! Vyuziva sa pri tom Encoder, ktory som ziskal z ME BE.
				MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);
				// !!! Tu mam BEGIN packet a ten je urceny pre CL a preto nedavam SessionID do mena suboru.
				string				FileName=string.Format(@"{0}\PACKET_{1}.ftc",MRemoteDirectory,FileID);

				// Zapisem subor (packet) na disk.
				CFileHelper.WriteFileFromStream(FileName,MS);
			}

			// Spustim monitorovoaci thread na monitoring prichadzajuich packetov.
			MTRCT.Start();

			CSettings.Log.Write(string.Format("CHANNEL WITH SESSION: {0} WAS OPENED !",MSessionID.SessionID),ELogRecordType.E_LRT_CHANNEL);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Ak je to na strane Sendera zaslem END packet.
			// !!! Takto dam sancu CH na strane Receivera sa koreknte ukoncit.
			if (MIsListener==false){
				// Vytovrim FileID - unikatne ID suboru - 6 cislis.
				string				FileID=CDebugHelper.GetIntID(6);
				// Vytovrim prazdnu M - END packet nepotrebuje M s telom.
				Message				Message=Message.CreateMessage(CSettings.MessageVersion,"STOP","STOP");
				// Vytvorim packet, ktory chcem poslat.
				CFTCPacket			PacketOut=new CFTCPacket(DateTime.Now,new CFTCSessionID(MSessionID.SessionID),MLocalAddress.AbsoluteUri,FileID,EMessageType.E_MT_STOP,Message);
				// Serializujem packet do Streamu.
				// !!! Vyuziva sa pri tom Encoder, ktory som ziskal z ME BE.
				MemoryStream		MS=PacketOut.WriteMessageWithEncoder(MMessageEncoder);
				// !!! Tu mam END packet. Aj ked by som ho mohol poslat priamo do CH - tym, ze by som prihodil SessionID tam som to neurobil. CL to urobi za mna a zaroven otestuje ci takyto CH so SessionID existuje a ked nie tak ho zmaze.
				string				FileName=string.Format(@"{0}\PACKET_{1}.fct",MRemoteDirectory,FileID);

				// Zapisem subor (packet) na disk.
				CFileHelper.WriteFileFromStream(FileName,MS);
			}

			// Zastavim CH, tym ze zastavim monitorovaci thread a zaroven !!! sa korektne zastavia aj vsetky Requests na TryReceive.
			MTRCT.Stop();

			CSettings.Log.Write(string.Format("CHANNEL WITH SESSION: {0} WAS CLOSED !",MSessionID.SessionID),ELogRecordType.E_LRT_CHANNEL);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Iba volam Close().
			Close(TimeSpan.Zero);
		}
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);
			
			// Implemtnujem svoj vlastny FaultConverter.
			// !!! Dokumentacia pise, ze by som mal v TCH pozuivat coverter vrateny z FaultConverter.GetDefaultFaultConverter(), co aj robim a moja treida iba doplna logovanie.
			if (typeof(T)==typeof(FaultConverter))
				return(new CFTCFaultConverter(MMessageEncoder.MessageVersion) as T);

			return(base.GetProperty<T>());
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndClose(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginWaitForMessage(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message EndReceive(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndWaitForMessage(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive(TimeSpan Timeout)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive()
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool TryReceive(TimeSpan Timeout, out Message Message)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public bool WaitForMessage(TimeSpan Timeout)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message message,TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message message,AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSend(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------