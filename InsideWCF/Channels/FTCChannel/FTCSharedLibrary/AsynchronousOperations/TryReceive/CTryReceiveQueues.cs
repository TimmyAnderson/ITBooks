using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Triedu pouziva CTryReceiveChannelThread na ukladanie Requests na TryReceive a prichodzich packetov.
	Pouziva sa na parovanie Request a pri ich uzatvarani.
*/
//-------------------------------------------------------------------------------------------------------
	internal class CTryReceiveQueues
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn=new object();
		// Fronta pre packety.
		// Pakety sa budu bufferovat - lepsie pouzit Queue.
		private List<CFTCPacket>								MPackets;
		// Fronta pre Requests.
		// Moze byt viacero Request - lepsie pouzit Dictionary.
		private List<CFTCTryReceiveAsyncResult>					MRequests;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CTryReceiveQueues()
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MPackets=new List<CFTCPacket>();
			MRequests=new List<CFTCTryReceiveAsyncResult>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Pridam novy packet.
		internal void AddPacket(CFTCPacket FTCPacket)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MPackets.Add(FTCPacket);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pridam novy Request.
		internal void AddRequest(CFTCTryReceiveAsyncResult FTCTryReceiveAsyncResult)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MRequests.Add(FTCTryReceiveAsyncResult);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Zmazem obe fronty.
		internal void Clear()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MPackets.Clear();
				MRequests.Clear();
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Klucova metoda triedy, ktora sluzi na parovanie Request a packet.
		internal void MakePair()
		{
			lock(MSyn)
			{
				CFTCTryReceiveAsyncResult	Request=null;
				CFTCPacket					Packet=null;

				if (MRequests.Count==0 || MPackets.Count==0)
					return;

				// Vyhadzujem ako packet tak aj Request z fronty.
				Packet=MPackets[0];
				MPackets.RemoveAt(0);
				Request=MRequests[0];
				MRequests.RemoveAt(0);

				// Tu sa vyvola interny WCF callback, ktory nasledne vyvola EndTryReceive(), ktora vrati Message obsaihnuty v packete.
				// Message sa prenasa tak, ze DoFinish() ho ulozi do property Request (CFTCTryReceiveAsyncResult) a tento objekt WCF internal callback zasle do EndTryReceive() odkial ho iba poslem von v out parametre typu Message.
				Request.DoFinish(Packet);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vrati nasledujuci Request, ktory expiroval.
		internal CFTCTryReceiveAsyncResult GetNextExpiredRequest()
		{
			lock(MSyn)
			{
				for(int i=0;i<MRequests.Count;i++)
					if (MRequests[i].IsExpired==true)
					{
						CFTCTryReceiveAsyncResult	FTCAsyncResult=MRequests[i];

						MRequests.RemoveAt(i);
						return(FTCAsyncResult);
					}

				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Vola sa pri Close() CH. Korektne ukoncuje vsetky neukoncene Requests tym, ze nastavi priznak ukonecnia (HasClosed), odpali WCF callback a ten vyvola EndTryReceive(), ktora navratovou hodnotu TRUE a vratenim NULL ako out Message oznami WCF, ze CH sa ukoncuje.
		internal void ClosePendingRequests()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				// Korektne ukoncuje vsetky neukoncene Requests tym, ze nastavi priznak ukonecnia (HasClosed), odpali WCF callback a ten vyvola EndTryReceive(), ktora navratovou hodnotu TRUE a vratenim NULL ako out Message oznami WCF, ze CH sa ukoncuje.
				for(int i=0;i<MRequests.Count;i++)
					MRequests[i].DoFinishByClose();

				MRequests.Clear();
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------