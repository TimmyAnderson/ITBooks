using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedCSCompareExchange
{
//------------------------------------------------------------------------------
	// !!! Pouzivam 'struct', kvoli vykonnosti ako aj zabrazneniu pouzitia GC nad SExchange.
	public struct SCompareExchange
	{
//------------------------------------------------------------------------------
		private volatile int				MActualThreadWhichOwnsLock;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void EnterCS()
		{
			// Zistim ID threadu.
			int								ID=Thread.CurrentThread.ManagedThreadId;

			// Porovnam aktualny threadu ID a thread ID, ktory MOMENTALNE VLASTNI LOCK CS.
			while (Interlocked.CompareExchange(ref MActualThreadWhichOwnsLock, ID, 0)!=0)
			{
				Console.WriteLine("LOCK WAITING...");

				// Aby som nezabil CPU v cykle.
				Thread.Sleep(100);
			}
		}
//------------------------------------------------------------------------------
		public void ExitCS()
		{
			MActualThreadWhichOwnsLock=0;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------