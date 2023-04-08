using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ManagedAssembly
{
//-------------------------------------------------------------------------------------------------------
	public class CMyClass
	{
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		public static int MyMethod1(string Argument)
		{
			Console.WriteLine(string.Format("Hello [{0}] !",Argument));

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda je zavedena z NATIVE PROCESU pomocou CLR HOSTING.
		public static int MyMethod2(string Argument)
		{
			Console.WriteLine(string.Format("Hello [{0}] !",Argument));

			ThreadPool.QueueUserWorkItem(CounterThread,null);

			return(100);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------