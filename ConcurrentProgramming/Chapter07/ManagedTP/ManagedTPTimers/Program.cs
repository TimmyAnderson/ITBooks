using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedTPTimers
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void MyTimerCallback(object State)
		{
			string				Param=(string) State;

			Console.WriteLine(string.Format("{0} - BEGIN TIMER: [{1}] !",DateTime.Now,Param));

			Thread.Sleep(2*1000);

			Console.WriteLine(string.Format("{0} - END TIMER: [{1}] !",DateTime.Now,Param));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Timer			T=new Timer(MyTimerCallback,"Hello World",1*1000,5*1000);

			Console.WriteLine("Press any key to STOP !");
			Console.ReadLine();

			// Timer zastavim, no jeho instancia je aktivna.
			T.Change(-1,0);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Timer			T=new Timer(MyTimerCallback,"Hello World",1*1000,5*1000);

			Console.WriteLine("Press any key to STOP !");
			Console.ReadLine();

			// Necakam na koniec Callback.
			T.Dispose();
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			Timer			T=new Timer(MyTimerCallback,"Hello World",1*1000,5*1000);

			Console.WriteLine("Press any key to STOP !");
			Console.ReadLine();

			AutoResetEvent	E=new AutoResetEvent(false);

			T.Dispose(E);

			Console.WriteLine(string.Format("{0} - Waiting for Event !",DateTime.Now));

			E.WaitOne();

			Console.WriteLine(string.Format("{0} - Event SIGNALIZED !",DateTime.Now));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------