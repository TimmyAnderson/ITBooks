/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace SimpleSpinWait
{
//------------------------------------------------------------------------------
	class SScalableSpinLock
	{
//------------------------------------------------------------------------------
		private const int								LOCK_AVAILABLE=0;
//------------------------------------------------------------------------------
		private volatile int							MState;
		private volatile Stack<CSpinLockFlag>			MWaiters;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private void SignalOneWaiter()
		{
			CSpinLockFlag		Flag;

			while (GetWaiters().TryPop(out Flag)==true)
			{
				if (Flag.MFlag!=ESpinLockFlagEnum.Done)
				{
					Flag.MFlag=ESpinLockFlagEnum.Set;
					break;
				}
			}
		}
//------------------------------------------------------------------------------
		private Stack<CSpinLockFlag> GetWaiters()
		{
			if (MWaiters==null)
				Interlocked.CompareExchange(ref MWaiters, new Stack<CSpinLockFlag>(), null);

			return(MWaiters);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Enter()
		{
			int				TID=Thread.CurrentThread.ManagedThreadId;

			if (MState==TID)
				throw(new Exception("Recursion not allowed !"));

			Thread.BeginCriticalRegion();

			if (Interlocked.CompareExchange(ref MState, TID, LOCK_AVAILABLE)!=LOCK_AVAILABLE)
			{
				// Enqueue our flag.
				CSpinLockFlag	Flag = new CSpinLockFlag();

				try
				{
					// Spin until it has been set and we succeed.
					SSpinWait	SW=new SSpinWait();

					do
					{
						Flag.MFlag=ESpinLockFlagEnum.Reset;
						GetWaiters().Push(Flag);

						Thread.EndCriticalRegion();

						// So long as it wasnít released before we pushed.
						if (MState!=LOCK_AVAILABLE)
						{
							// Spin until we see the lock available.
							while (Flag.MFlag!=ESpinLockFlagEnum.Set)
								SW.SpinOnce();
						}

						Thread.BeginCriticalRegion();
					}
					while (Interlocked.CompareExchange(ref MState, TID, LOCK_AVAILABLE)!=LOCK_AVAILABLE);

					Flag.MFlag=ESpinLockFlagEnum.Done;
				}
				catch
				{
					// If we've died due to an exception, signal someone.
					// This ensures no lost wake-ups.
					Flag.MFlag=ESpinLockFlagEnum.Done;
					SignalOneWaiter();
					throw;
				}
			}
		}
//------------------------------------------------------------------------------
		public void Exit()
		{
			int				TID=Thread.CurrentThread.ManagedThreadId;

			if (MState!=TID)
				throw(new Exception("Lock not owned by thread !"));

			MState=LOCK_AVAILABLE;
			SignalOneWaiter();

			Thread.EndCriticalRegion();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
*/
//------------------------------------------------------------------------------