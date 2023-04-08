using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
#pragma warning disable 0420
//------------------------------------------------------------------------------
namespace ManagedThreadBarrier
{
//------------------------------------------------------------------------------
	public class CBarrier : IDisposable
	{
//------------------------------------------------------------------------------
		private const int						MASK_CURR_SENSE=unchecked((int)0x80000000);
		private const int						MASK_CURR_COUNT=~MASK_CURR_SENSE;
//------------------------------------------------------------------------------
		// Initial count.
		private readonly int					MInitialCount;
		// High order bit 0==even, 1==odd; other bits are count.
		private volatile int					MCurrentCountAndSense;
		// Event for odd phases.
		private ManualResetEvent				MOddEvent;
		// Event for even phases.
		private ManualResetEvent				MEvenEvent;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CBarrier(int InitialCount)
		{
			if (InitialCount<1)
				throw(new ArgumentOutOfRangeException("InitialCount"));

			MInitialCount=InitialCount;
			// Start at even sense.
			MCurrentCountAndSense=InitialCount;
			MOddEvent=new ManualResetEvent(false);
			MEvenEvent=new ManualResetEvent(false);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public int								InitialCount
		{
			get
			{
				return(MInitialCount);
			}
		}
//------------------------------------------------------------------------------
		public int								CurrentCount
		{
			get
			{
				return(MCurrentCountAndSense&MASK_CURR_COUNT);
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		internal void SignalAndWait()
		{
			TrySignalAndWait(Timeout.Infinite);
		}
//------------------------------------------------------------------------------
		internal bool TrySignalAndWait(int TimeoutMilliseconds)
		{
			// Read the sense so we can reverse it later if needed.
			int					Sense=(MCurrentCountAndSense&MASK_CURR_SENSE);

			// We may have to retry in the case of timeouts, hence the loop.
			while (true)
			{
				int				CurrentCountAndSense=MCurrentCountAndSense;

				if ((CurrentCountAndSense & MASK_CURR_COUNT)==1)
				{
					// Last thread, try to reset the barrier state.
					// If CAS failed, retry.
					if (Interlocked.CompareExchange(ref MCurrentCountAndSense, MInitialCount|(~(MCurrentCountAndSense)&MASK_CURR_SENSE), CurrentCountAndSense)!=CurrentCountAndSense)
						continue;

					// Reset old event 1st, ensuring threads that wake up don't race and satisfy the next phase.
					if (Sense==0)
					{
						// Even.
						MOddEvent.Reset();
						MEvenEvent.Set();
					}
					else
					{
						// Odd.
						MEvenEvent.Reset();
						MOddEvent.Set();
					}
				}
				else
				{
					// Not last thread, decrement the count and wait.
					int			NewCount = (CurrentCountAndSense & MASK_CURR_SENSE)|((CurrentCountAndSense & MASK_CURR_COUNT) - 1);

					// If CAS failed, retry.
					if (Interlocked.CompareExchange(ref MCurrentCountAndSense, NewCount, CurrentCountAndSense) != CurrentCountAndSense)
						continue;

					// Wait on the event.
					bool		WaitSuccess;

					if (Sense==0)
						WaitSuccess=MEvenEvent.WaitOne(TimeoutMilliseconds, false);
					else
						WaitSuccess=MOddEvent.WaitOne(TimeoutMilliseconds, false);

					// Timeouts are tricky since we already told other threads we reached the barrier.  Need to consider that they may have already noticed our state updates and hence moved to the next phase. If they did move to the next phase, we will have to return true rather than timing out.  We know this by checking the sense.
					while (WaitSuccess==false)
					{
						CurrentCountAndSense=MCurrentCountAndSense;

						// Sense changed. We are past the point of timing out: return true.
						if ((CurrentCountAndSense & MASK_CURR_SENSE)!=Sense)
							break;

						int		ResetCount=(CurrentCountAndSense&MASK_CURR_SENSE)|((CurrentCountAndSense&MASK_CURR_COUNT)+1);

						// If CAS failed, retry.
						if (Interlocked.CompareExchange(ref MCurrentCountAndSense, ResetCount, CurrentCountAndSense)!=CurrentCountAndSense)
							continue;

						// Timed out and patched up our state changes.
						return(false);
					}
				}

				return true;
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void Dispose()
		{
			MOddEvent.Close();
			MEvenEvent.Close();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------