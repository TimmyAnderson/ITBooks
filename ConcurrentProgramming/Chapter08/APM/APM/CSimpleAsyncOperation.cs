using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace APM
{
//------------------------------------------------------------------------------
	public class CSimpleAsyncOperation
	{
//------------------------------------------------------------------------------
		// Tato operacia sa bude vykonavat asynchronne.
		private int Work(int SleepyTime)
		{
			Console.WriteLine(string.Format("Work() - TID: {0} - BEFORE SLEEP !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(SleepyTime);

			Console.WriteLine(string.Format("Work() - TID: {0} - END SLEEP !",Thread.CurrentThread.ManagedThreadId));

			return(new Random().Next());
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public IAsyncResult BeginWork(int SleepyTime, AsyncCallback Callback, object State)
		{
			// Pouzijem CUSTOM CSimpleAsyncResult ako implementaciu IAsyncResult.
			return(new CSimpleAsyncResult<int>(() => Work(SleepyTime),Callback,State));
		}
//------------------------------------------------------------------------------
		public int EndWork(IAsyncResult AsyncResult)
		{
			CSimpleAsyncResult<int>			SimpleResult=AsyncResult as CSimpleAsyncResult<int>;

			if (SimpleResult==null)
				throw(new ArgumentException("Bad async result."));

			// Pouzijem pomocou metodu End() CUSTOM CSimpleAsyncResult.
			int								Ret=SimpleResult.End();

			return(Ret);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------