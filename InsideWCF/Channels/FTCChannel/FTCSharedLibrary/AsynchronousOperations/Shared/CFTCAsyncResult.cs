using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Treida, ktora je predkom pre tiredy inmplementujuce IAsyncResult (u mna ich oznacujem ako Request). Sluzia ako identifikacny objekt prenasany medzi metodami BeginXXX() a EndXXX() na identifikaciu asynchronnej operacie.

	Teoreticky by sa mal implementovat IDisposable, kedze mam AutoResetEvent, ale co som pozeral kody, tak ziaden to neimplementoval.
*/
//-------------------------------------------------------------------------------------------------------
	public abstract class CFTCAsyncResult : IAsyncResult
	{
//-------------------------------------------------------------------------------------------------------
		// Priznak, ci asynchronna operacia skoncila v dosledku ukoncenia napriklad CH, alebo CL.
		private bool											MHasClosed;
		// Priznak, ze Request expiroval.
		private bool											MHasExpired;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected object										MSyn=new object();
		// Referecnia na interny WCF callback, ktory mi WCF zasle cez BeginXXX().
		protected AsyncCallback									MAsyncCallback;
		// Interny stav, ktory mi WCF zasle cez BeginXXX() a vyuziva sa v metodach EndXXX().
		protected object										MAsyncState;
		// WaitHandle - zvolil som typ ManualResetEvent.
		protected ManualResetEvent								MAsyncWaitHandle;
		// Expiracny cas.
		protected TimeSpan?										MTimeout;
		// Cas vytvorenia Request - pre vypocet casu expiracie.
		protected DateTime										MProcessingTime;
		// Udava ci asunchronna operaciu uz skoncila.
		protected bool											MCompleted;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCAsyncResult(AsyncCallback AsyncCallback, object AsyncState, TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MAsyncCallback=AsyncCallback;
			MAsyncState=AsyncState;
			MTimeout=Timeout;

			MAsyncWaitHandle=new ManualResetEvent(false);
			MCompleted=false;
			MHasExpired=false;
			MProcessingTime=DateTime.Now;
			MHasClosed=false;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public object											AsyncState
		{
			get
			{
				return(MAsyncState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public WaitHandle										AsyncWaitHandle
		{
			get
			{
				return(MAsyncWaitHandle);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												CompletedSynchronously
		{
			get
			{
				// Je to OK - tak je to v dokumentacii.
				return(false);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsCompleted
		{
			get
			{
				lock(MSyn)
				{
					return(MCompleted);
				}
			}
			private set
			{
				lock(MSyn)
				{
					MCompleted=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												HasClosed
		{
			get
			{
				lock(MSyn)
				{
					return(MHasClosed);
				}
			}
			protected set
			{
				lock(MSyn)
				{
					MHasClosed=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												HasExpired
		{
			get
			{
				lock(MSyn)
				{
					return(MHasExpired);
				}
			}
			private set
			{
				lock(MSyn)
				{
					MHasExpired=value;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsExpired
		{
			get
			{
				if (MTimeout==null)
					return(false);
				else
				{
					// Vypocet casu expiracie. Kedze WCF zvycajne ako timeout pouziva TimeSpan.MaxValue a ten pri pricitani k DateTime hodi Exception tak som to musel takto osetrit.
					if (MTimeout.Value!=TimeSpan.MaxValue)
						return(MProcessingTime.Add(MTimeout.Value)<=DateTime.Now);
					else
						return(false);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Klucova metoda. Jej ulohou je odpalit interny WCF callback pre dany Request aby ten mohol vola EndXXX().
		public void DoFinishByClose()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			lock(MSyn)
			{
				MHasClosed=true;
				MCompleted=true;
			}

			// Odpalim WaitHandle.
			MAsyncWaitHandle.Set();

			try
			{
				// Zavolam callback.
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
		// Vola sa pri expiracii timeout. Jej ulohou je odpalit interny WCF callback pre dany Request aby ten mohol vola EndXXX().
		public void DoFinishByExpiraiton()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCompleted=true;
			MHasExpired=true;

			// Odpalim WaitHandle.
			MAsyncWaitHandle.Set();

			try
			{
				// Zavolam callback.
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