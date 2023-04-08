using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Timers
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void MyTimerCallback(object Param)
		{
			Console.WriteLine(string.Format("CALLBACK START: [{0}] !",Param));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("CALLBACK END: [{0}] !",Param));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Timer												T=new Timer(MyTimerCallback,"Timmy Anderson",5*1000,2*1000);

			Console.WriteLine("\nPress any key to STOP CALLBACK !");
			Console.ReadLine();

			T.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Timer												T=new Timer(MyTimerCallback,"Timmy Anderson",5*1000,2*1000);

			Console.WriteLine("Press any key to STOP CALLBACK !");
			Console.ReadLine();

			WaitHandle											WH=new ManualResetEvent(false);

			T.Dispose(WH);

			Console.WriteLine("Waiting for CALLBACK to FINISH !");

			WH.WaitOne();

			Console.WriteLine("CALLBACK FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test1();
			//Test2();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------