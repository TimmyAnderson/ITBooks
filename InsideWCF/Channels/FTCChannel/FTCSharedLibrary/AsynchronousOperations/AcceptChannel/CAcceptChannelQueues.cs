using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using CSessionPair=FTCSharedLibrary.CPair<FTCSharedLibrary.CFTCSessionID, System.ServiceModel.Channels.IDuplexSessionChannel>;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Triedu pouziva CChannelAcceptChannelThread na ukladanie Requests na AcceptChannel a SessionID otvorenych kanalov.
	Pouziva sa na parovanie Request a prchadzajucih BEGIN packet ako aj pri uzatvarani neuzatvorenych CH ked sa konci CL.
*/
//-------------------------------------------------------------------------------------------------------
	internal class CAcceptChannelQueues
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn=new object();
		// Fronta pre Requests.
		// Moze byt viacero Request - lepsie pouzit Dictionary.
		private List<CFTCAcceptChannelAsyncResult>				MRequests;
		// Fronta pre SessionID.
		// Pair obsahujuci SessionID a Duplex CH.
		private List<CSessionPair>								MSessions;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CAcceptChannelQueues()
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MRequests=new List<CFTCAcceptChannelAsyncResult>();
			MSessions=new List<CSessionPair>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Pridam novy Request.
		internal void AddRequest(CFTCAcceptChannelAsyncResult FTCAcceptChannelAsyncResult)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MRequests.Add(FTCAcceptChannelAsyncResult);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pridam novy SessionID - ked sa vytvori CH - takto mam registrovane otvrene CH.
		internal void AddSession(CSessionPair SessionPair)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MSessions.Add(SessionPair);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Odoberiem SessionID - ked sa uzatvori CH - takto mam registrovane otvrene CH.
		internal void RemoveSession(CFTCSessionID FTCSessionID)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				for (int i=0;i<MSessions.Count;i++)
					if (MSessions[i].First.CompareTo(FTCSessionID)==true)
					{
						MSessions.RemoveAt(i);
						break;
					}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Zmazem obe fronty.
		internal void Clear()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MRequests.Clear();
				MSessions.Clear();
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Kontroluje prichodzi packet ci je BEGIN, MESSAGE, alebo END, sktornuje ci logicky sedi (teda END moze prist iba ak je CH s danym SessionID) a ak ma aj Request na BEGIN PACKET tak odpali WCF callback aby ten volal moju EndAcceptChannel.
		// Mohlo by to byt optimalnejsie a nerobit check na M, ale iba na nazov suboru.
		internal ECheckSessionResponse CheckSession(CFTCPacket Packet)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				bool		SessionExists=false;

				// Zistim ci existuje session s rovnakym SessionID pre dany packet.
				for (int i=0;i<MSessions.Count;i++)
					if (MSessions[i].First.CompareTo(Packet.SessionID)==true)
					{
						SessionExists=true;
						break;
					}

				// Ak neexistuje session.
				if (SessionExists==false)
				{
					// BEGIN packet.
					if (Packet.MessageType==EMessageType.E_MT_START)
					{
						// Nemam Request - zahodim packet.
						if (MRequests.Count==0)
						{
							CSettings.Log.Write(string.Format("START PACKET - NO REQUEST FOR SESSION - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
							return(ECheckSessionResponse.E_CSR_NO_SESSION_REQUEST);
						}
						// Mam Request - zacinam novu session.
						else
						{
							CSettings.Log.Write(string.Format("START PACKET !!! OK !!! - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);

							CFTCAcceptChannelAsyncResult	Request;

							Request=MRequests[0];
							// Odstranim request z fronty, lebo bude obsluzeny.
							MRequests.RemoveAt(0);

							// Zavolam metodu, ktora spusti interny WCF callback a ta zas moju EndAcceptChannel() a ta vytvori novy CH.
							Request.DoFinish(Packet.SessionID,new Uri(Packet.SourceAddress));
							return(ECheckSessionResponse.E_CSR_NEW_SESSION);
						}
					}
					// Ak prisiel END packet potom chyba.
					else if (Packet.MessageType==EMessageType.E_MT_STOP)
					{
						CSettings.Log.Write(string.Format("STOP PACKET - Session NOT STARTED YET - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_ERROR);
					}
					// Ak prisiel MESSAGE packet potom chyba.
					else if (Packet.MessageType==EMessageType.E_MT_MESSAGE)
					{
						CSettings.Log.Write(string.Format("MESSAGE PACKET - Session NOT STARTED YET - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_ERROR);
					}
					// Ak mam neznamy typ packetu potom chyba.
					else
					{
						CSettings.Log.Write(string.Format("UNKNOWN MessageType for FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_ERROR);
					}
				}
				// Mam session.
				else
				{
					// Ak prisiel BEGIN packet potom chyba.
					if (Packet.MessageType==EMessageType.E_MT_START)
					{
						CSettings.Log.Write(string.Format("START PACKET - Session ALREADY STARTED - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_ERROR);
					}
					// Ak prisiel END packet preposlem na spracovanie do CH.
					else if (Packet.MessageType==EMessageType.E_MT_STOP)
					{
						CSettings.Log.Write(string.Format("STOP PACKET !!! OK !!! - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_EXISTING_SESSION);
					}
					// Ak prisiel MESSAGE packet preposlem na spracovanie do CH.
					else if (Packet.MessageType==EMessageType.E_MT_MESSAGE)
					{
						CSettings.Log.Write(string.Format("MESSAGE PACKET !!! OK !!! - FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_EXISTING_SESSION);
					}
					// Ak mam neznamy typ packetu potom chyba.
					else
					{
						CSettings.Log.Write(string.Format("UNKNOWN MessageType for FileID: {0} !",Packet.FileID),ELogRecordType.E_LRT_PACKET);
						return(ECheckSessionResponse.E_CSR_ERROR);
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vrati nasledujuci Request, ktory expiroval.
		internal CFTCAcceptChannelAsyncResult GetNextExpiredRequest()
		{
			lock(MSyn)
			{
				for(int i=0;i<MRequests.Count;i++)
					if (MRequests[i].IsExpired==true)
					{
						CFTCAcceptChannelAsyncResult	FTCAsyncResult=MRequests[i];

						MRequests.RemoveAt(i);
						return(FTCAsyncResult);
					}

				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Korektne uzatvori, vskety Requests, ktore este neboi uzatvorene - vola sa pri Close() CL.
		internal void ClosePendingRequests()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				// Zavola sa meotda, ktora nastavi priznak, ze Reqeust bol 'obsluzeny' lebo CL sa ma ukoncit. Tat metoda odpali WCF callback a ta zas zavola moju EndAcceptChannel(). Ta nasledne vrati NULL a tym WCF vie, ze sa CL ukoncuje.
				for(int i=0;i<MRequests.Count;i++)
					MRequests[i].DoFinishByClose();

				MRequests.Clear();
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pri Close() CL uzatvara vsetky otvorene CH, teda tie, ktore neboli korektne ukoncene.
		internal void CloseAllOpenedChannels(TimeSpan CloseTimeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				// Musim vytvorit kopiu, pretoze MSessions[i].Second.Close(CloseTimeout) maze kolekciu.
				CSessionPair[]		Array=MSessions.ToArray();

				// Zavolam Close() pre kazdy CH.
				for(int i=0;i<Array.Length;i++)
					Array[i].Second.Close(CloseTimeout);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------