using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda ja impelemntaciu rozhrania IAsyncResult (u mna ich oznacujem ako Request) a sluzia ako identifikacny objekt prenasany medzi metodami BeginAcceptChannel() a EndAcceptChannel() na identifikaciu asynchronnej operacie.
*/
//-------------------------------------------------------------------------------------------------------
	internal class CFTCAcceptChannelAsyncResult : CFTCAsyncResult
	{
//-------------------------------------------------------------------------------------------------------
		// SessionID, sluzi pri vytvarani CH, ako parameter jeho konstrukotra.
		private CFTCSessionID									MSession;
		// RemoteAddress, sluzi pri vytvarani CH, ako parameter jeho konstrukotra.
		private Uri												MRemoteAddress;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CFTCAcceptChannelAsyncResult(AsyncCallback AsyncCallback, object AsyncState, TimeSpan Timeout)
			: base(AsyncCallback,AsyncState,Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MSession=null;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CFTCSessionID									SessionID
		{
			get
			{
				lock(MSyn)
				{
					return(MSession);
				}
			}
			private set
			{
				lock(MSyn)
				{
					MSession=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		internal Uri											RemoteAddress
		{
			get
			{
				lock(MSyn)
				{
					return(MRemoteAddress);
				}
			}
			private set
			{
				lock(MSyn)
				{
					MRemoteAddress=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Klucova metoda. Jej ulohou je odpalit interny WCF callback pre dany Request aby ten mohol vola EndAcceptChannel() a skrze jej out parameter dostat objekt typu CFTCDuplexChannel, ktory bol ulozeny v packete.
		public void DoFinish(CFTCSessionID Session, Uri RemoteAddress)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MSession=Session;
				MRemoteAddress=RemoteAddress;
				MCompleted=true;
			}

			// Odpalim WaitHandle.
			MAsyncWaitHandle.Set();

			try
			{
				// Zavolam interny WCF callback, ktory nasledne vyvola moju EndAcceptChannel().
				// !!! Musi tu byt BeginInvoke() - dovody v komentari k funkcii CFTCTryReceiveAsyncResult.DoFinish().
				if (MAsyncCallback!=null)
					MAsyncCallback.BeginInvoke(this,null,null);
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------