using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ManagedAssembly
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CMyClass
	{
//-------------------------------------------------------------------------------------------------------
		private static AutoResetEvent							MEvent=new AutoResetEvent(false);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void CounterThread(object Param)
		{
			for (int Index=0;Index<10;Index++)
			{
				Console.WriteLine(string.Format("Counter: [{0}] !",Index+1));
				Thread.Sleep(1000);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void CounterThreadWithStop(object Param)
		{
			for (int Index=0;Index<10;Index++)
			{
				Console.WriteLine(string.Format("Counter: [{0}] !",Index+1));
				
				if (MEvent.WaitOne(1000)==true)
				{
					Console.WriteLine(string.Format("THREAD was INTERRUPTED !"));
					break;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		// !!!!! METHOD MUSI BYT STATIC, MUSI mat 1 PARAMETER typu STRING a RETURN VALUE MUSI byt typu INT.
		public static int MyMethod1(string Argument)
		{
			Console.WriteLine(string.Format("Hello [{0}] !",Argument));

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		// !!!!! METHOD MUSI BYT STATIC, MUSI mat 1 PARAMETER typu STRING a RETURN VALUE MUSI byt typu INT.
		public static int MyMethod2(string Argument)
		{
			Console.WriteLine(string.Format("Hello [{0}] !",Argument));

			ThreadPool.QueueUserWorkItem(CounterThread,null);

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		// !!!!! METHOD MUSI BYT STATIC, MUSI mat 1 PARAMETER typu STRING a RETURN VALUE MUSI byt typu INT.
		public static int MyMethod3(string Argument)
		{
			Console.WriteLine(string.Format("!!! .NET - WAITING STARTED !"));

			Thread.Sleep(5000);

			Console.WriteLine(string.Format("!!! .NET - WAITING FINISHED !"));

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		// !!!!! METHOD MUSI BYT STATIC, MUSI mat 1 PARAMETER typu STRING a RETURN VALUE MUSI byt typu INT.
		public static int StartThread(string Argument)
		{
			ThreadPool.QueueUserWorkItem(CounterThreadWithStop,null);

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		// !!!!! METHOD MUSI BYT STATIC, MUSI mat 1 PARAMETER typu STRING a RETURN VALUE MUSI byt typu INT.
		public static int StopThread(string Argument)
		{
			MEvent.Set();

			return(0);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------