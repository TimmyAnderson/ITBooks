using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
//------------------------------------------------------------------------------
namespace SimpleSpinWait
{
//------------------------------------------------------------------------------
	public struct SSpinWait
	{
//------------------------------------------------------------------------------
	    [DllImport("kernel32.dll")]
	    internal static extern int SwitchToThread();
//------------------------------------------------------------------------------
		// When to do a true yield.
		internal const int							YIELD_THRESHOLD=25;
		internal const int							SLEEP_0_EVERY_HOW_MANY_TIMES=2;
		internal const int							SLEEP_1_EVERY_HOW_MANY_TIMES=10;
		// Max spin iterations.
		internal const int							MAX_SPIN_INTERVAL=1000;
//------------------------------------------------------------------------------
		private static int							MProcessorCount=Environment.ProcessorCount;
//------------------------------------------------------------------------------
		private int									MCount;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public int									Count
		{
		   get
		   {
			   return(MCount);
		   }
		}
//------------------------------------------------------------------------------
		public bool									NextSpinWillYield
		{
		   get
		   {
			   return(MProcessorCount==1 || MCount>=YIELD_THRESHOLD);
		   }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void SpinOnce()
		{
			if (NextSpinWillYield==true)
			{
				int				YieldsSoFar=((MCount>=YIELD_THRESHOLD) ? (MCount - YIELD_THRESHOLD) : MCount);

				if ((YieldsSoFar % SLEEP_1_EVERY_HOW_MANY_TIMES)==(SLEEP_0_EVERY_HOW_MANY_TIMES-1))
					Thread.Sleep(0);
				else if ((YieldsSoFar % SLEEP_1_EVERY_HOW_MANY_TIMES)==(SLEEP_1_EVERY_HOW_MANY_TIMES-1))
					Thread.Sleep(1);
				else
					SwitchToThread();
			}
			else
				Thread.SpinWait((int)(MCount*((float)MAX_SPIN_INTERVAL/YIELD_THRESHOLD))+1);

			MCount=((MCount==int.MaxValue) ? YIELD_THRESHOLD : MCount+1);
		}
//------------------------------------------------------------------------------
		public void Reset()
		{
			MCount=0;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------