using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.ConstrainedExecution;
using System.Runtime.CompilerServices;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace SimpleSpinWait
{
//------------------------------------------------------------------------------
	public struct SSpinLock
	{
//------------------------------------------------------------------------------
		private volatile int						MState;
		private const int							LOCK_AVAILABLE=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Enter()
		{
			int				TID=Thread.CurrentThread.ManagedThreadId;

			if (MState==TID)
				throw(new Exception("Recursion not allowed !"));

			Thread.BeginCriticalRegion();

			if (Interlocked.CompareExchange(ref MState, TID, LOCK_AVAILABLE) != LOCK_AVAILABLE)
			{
				SSpinWait	SW=new SSpinWait();

				do
				{
					Thread.EndCriticalRegion();

					// Spin until we see the lock available.
					do
					{
						SW.SpinOnce();
					}
					while (MState != 0);

					Thread.BeginCriticalRegion();
				}
				while (Interlocked.CompareExchange(ref MState, TID, LOCK_AVAILABLE)!=LOCK_AVAILABLE);
			}
		}
//------------------------------------------------------------------------------
		public void Exit()
		{
			Exit(false);
		}
//------------------------------------------------------------------------------
		public void Exit(bool FlushCacheWithRelease)
		{
			if (MState!=Thread.CurrentThread.ManagedThreadId)
				throw(new Exception("Lock not owned by thread !"));

			if (FlushCacheWithRelease==true)
				Interlocked.Exchange(ref MState, LOCK_AVAILABLE);
			else
				MState=LOCK_AVAILABLE;

			Thread.EndCriticalRegion();
		}
//------------------------------------------------------------------------------
		[ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
		public void ReliableEnter(ref bool Taken)
		{
			int				TID=Thread.CurrentThread.ManagedThreadId;

			if (MState==TID)
				throw(new Exception("Recursion not allowed !"));

			SSpinWait		SW=new SSpinWait();

			while (true)
			{
				if (MState==LOCK_AVAILABLE)
				{
					Thread.BeginCriticalRegion();

					RuntimeHelpers.PrepareConstrainedRegions();

					try
					{
						// Intentionally blank.
					}
					finally
					{
						if (Interlocked.CompareExchange(ref MState, TID, LOCK_AVAILABLE)==LOCK_AVAILABLE)
						{
							Taken=true;
						}
					}

					// Lock acquired, leave.
					if (Taken==true)
						break; 

					Thread.EndCriticalRegion();
				}

				SW.SpinOnce();
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------