using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda sluzi ako base pre triedy realizujuce vlastny thread.
*/
//-------------------------------------------------------------------------------------------------------
	public abstract class CThreadHelper
	{
//-------------------------------------------------------------------------------------------------------
		protected object										MSyn=new object();
		protected string										MThreadName;
		protected int											MExitTimeout;
		protected AutoResetEvent								MExitEvent;
		protected AutoResetEvent[]								MEvents;
		protected int											MTimeout;
		protected Thread										MThread;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CThreadHelper(string ThreadName, int ExitTimeout, AutoResetEvent[] Events)
		{
			MThreadName=ThreadName;
			MExitTimeout=ExitTimeout;
			MExitEvent=new AutoResetEvent(false);
			MEvents=new AutoResetEvent[Events.Length+1];

			MEvents[0]=MExitEvent;

			for(int i=0;i<Events.Length;i++)
				MEvents[i+1]=Events[i];

			MTimeout=Timeout.Infinite;
		}
//-------------------------------------------------------------------------------------------------------
		public CThreadHelper(string ThreadName, int ExitTimeout, int Timeout)
		{
			MThreadName=ThreadName;
			MExitTimeout=ExitTimeout;
			MExitEvent=new AutoResetEvent(false);
			MEvents=new AutoResetEvent[1];
			MEvents[0]=MExitEvent;
			MTimeout=Timeout;
		}
//-------------------------------------------------------------------------------------------------------
		public CThreadHelper(string ThreadName, int ExitTimeout, AutoResetEvent[] Events, int Timeout)
		{
			MThreadName=ThreadName;
			MExitTimeout=ExitTimeout;
			MExitEvent=new AutoResetEvent(false);

			MEvents[0]=MExitEvent;

			for(int i=0;i<Events.Length;i++)
				MEvents[i+1]=Events[i];

			MTimeout=Timeout;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Realizuje Thread metodu.
		private void ThreadMethod()
		{
			try
			{
				CSettings.Log.Write(string.Format("Thread: {0} STARTED !",MThreadName),ELogRecordType.E_LRT_THREAD_LOGS);

				// Ma 3 rezimy prace.

				// 1. Reaguje iba na eventy.
				if (MEvents!=null && MTimeout==Timeout.Infinite)
				{
					DoJustEvents();
				}
				// 2. Reaguje iba na timeout.
				else if (MEvents==null && MTimeout!=Timeout.Infinite)
				{
					DoJustTimeout();
				}
				// 3. Reaguje aj na timeout aj na eventy.
				else
				{
					DoBothEventsAndTimeout();
				}
			}
			catch(Exception E)
			{
				CSettings.Log.Write(string.Format("Thread: {0} FAILED, Exception: {1} !",MThreadName,CDebugHelper.GetExceptionString(E)),ELogRecordType.E_LRT_THREAD_LOGS);
			}
			finally
			{
				CSettings.Log.Write(string.Format("Thread: {0} FINISHED !",CDebugHelper.GetMethodCallString(),MThreadName),ELogRecordType.E_LRT_THREAD_LOGS);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void DoJustEvents()
		{
			while(true)
			{
				int			Index=WaitHandle.WaitAny(MEvents);

				if (Index==0)
					break;

				Do(Index);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void DoJustTimeout()
		{
			while(true)
			{
				int			Index=WaitHandle.WaitAny(MEvents,MTimeout,true);

				if (Index==0)
					break;

				DoTimeout();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private void DoBothEventsAndTimeout()
		{
			while(true)
			{
				int			Index=WaitHandle.WaitAny(MEvents,MTimeout,true);

				if (Index==0)
					break;

				if (Index!=WaitHandle.WaitTimeout)
					Do(Index);
				else
					DoTimeout();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected abstract void Do(int Index);
		protected abstract void DoTimeout();
		// Udalosti, ktore su vyvolavanie pri starte a uzatvoreni threadu.
		protected abstract void Starting();
		protected abstract void Started();
		protected abstract void Stopping();
		protected abstract void Stopped();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public virtual void Start()
		{
			lock(MSyn)
			{
				CSettings.Log.Write(CDebugHelper.GetMethodCallString(1),ELogRecordType.E_LRT_METHOD_CALL);

				// Vyvolavam event.
				Starting();

				if (MThread!=null)
					throw(new InvalidOperationException("Thread is already started !"));

				MThread=new Thread(new ThreadStart(ThreadMethod));
				MThread.Start();

				// Vyvolavam event.
				Started();

				CSettings.Log.Write(CDebugHelper.GetMethodCallString(2),ELogRecordType.E_LRT_METHOD_CALL);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public virtual void Stop()
		{
			lock(MSyn)
			{
				CSettings.Log.Write(CDebugHelper.GetMethodCallString(1),ELogRecordType.E_LRT_METHOD_CALL);

				// Vyvolavam event.
				Stopping();

				if (MThread==null)
					return;

				MExitEvent.Set();

				try
				{
					if (MThread.Join(MExitTimeout)==false)
					{
						MThread.Abort();
						CSettings.Log.Write(string.Format("Thread: {0} ABORTED !",MThreadName),ELogRecordType.E_LRT_THREAD_LOGS);
					}
				}
				catch
				{
					CSettings.Log.Write(string.Format("Thread: {0} FAILED TO ABORT !",MThreadName),ELogRecordType.E_LRT_THREAD_LOGS);
				}

				MThread=null;

				// Vyvolavam event.
				Stopped();

				CSettings.Log.Write(CDebugHelper.GetMethodCallString(2),ELogRecordType.E_LRT_METHOD_CALL);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------