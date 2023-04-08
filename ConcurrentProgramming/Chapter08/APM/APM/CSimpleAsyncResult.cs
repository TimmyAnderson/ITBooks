using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace APM
{
//------------------------------------------------------------------------------
	public class CSimpleAsyncResult<T> : IAsyncResult
	{
//------------------------------------------------------------------------------
		// Fields potrebne na implementaciu IAsyncResult.
		// Urcuje ci ASYNCHRONNA operacia SKONCILA - 0==not complete, 1==complete.
		private volatile int					MIsCompleted; 
		// Pouziva sa ManualResetEvent, kedze chcem aby PO SKONCENI ASYNCHRONNEJ OPERACIE bol objekt NAVZDY SIGNALIZOVANY.
		private ManualResetEvent				MAsyncWaitHandle;
		// Callback volany pri skonceni ASYNRCHONNEJ OPERACIE.
		private readonly AsyncCallback			MCallback;
		// State object.
		private readonly object					MAsyncState;
//------------------------------------------------------------------------------
		// Field uklada EXCEPTION, ktora sa vyskytne pocas ASYNRCHONNEJ OPERACIE.
		private Exception						MException;
		// Field uklada VYSLEDOK ASYNRCHONNEJ OPERACIE.
		private T								MResult;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CSimpleAsyncResult(Func<T> Work, AsyncCallback Callback, object State)
		{
			MCallback=Callback;
			MAsyncState=State;
			MAsyncWaitHandle=new ManualResetEvent(false);

			RunWorkAsynchronously(Work);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public bool								IsCompleted
		{
			get
			{
				return(MIsCompleted==1);
			}
		}
//------------------------------------------------------------------------------
		// We always queue work asynchronously, so we always return false.
		public bool								CompletedSynchronously
		{
			get
			{ 
				return(false);
			}
		}
//------------------------------------------------------------------------------
		public WaitHandle						AsyncWaitHandle
		{
			get
			{
				return(MAsyncWaitHandle);
			}
		}
//------------------------------------------------------------------------------
		public object							AsyncState
		{
			get
			{
				return(MAsyncState);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Metoda REALIZUJE ASYNCHRONNU OPERACIU pomocou TP.
		private void RunWorkAsynchronously(Func<T> Work)
		{
			// Zaradim pomocnu metodu do TP.
			ThreadPool.QueueUserWorkItem(delegate
			{
				try
				{
					// Pomocna metoda vola operaciu ASYNCHRONNE v threade z TP.
					MResult=Work();
				}
				catch(Exception E)
				{
					// Ak doslo k Exception, tak si ju ulozim.
					MException=E;
				}
				finally
				{
					// Signalizujem koniec ASYNCHRONNEJ OPERACIE.
					MIsCompleted=1;

					// Signaizlujem Event.
					MAsyncWaitHandle.Set();

					// Ak bol uvedeny CALLBACK, tak ho zavolam.
					try
					{
						if (MCallback!=null)
							MCallback(this);
					}
					catch
					{
					}
				}
			});
		}
//------------------------------------------------------------------------------
		// Helper metoda, ktora je pouzivana v EndXXX().
		public T End()
		{
			// Ak este ASYNCHRONNA OPERACIA NESKONCIA, tak vykonam WAIT.
			if (MIsCompleted==0)
			{
				// Realizujem WAIT na MANUAL EVENT.
				MAsyncWaitHandle.WaitOne();
				// Uzatvorim MANUAL EVENT.
				MAsyncWaitHandle.Close();
			}

			// Ak doslo k EXCEPTION, tak ju vyhodim.
			if (MException!=null)
				throw(MException);

			// Vratim vysledok ASYCNHRONNEJ OPERACIE.
			return(MResult);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------