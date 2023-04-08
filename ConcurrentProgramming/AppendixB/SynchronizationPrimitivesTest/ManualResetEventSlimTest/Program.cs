using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManualResetEventSlimTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void MyThread(object Param)
		{
			ManualResetEventSlim	MRES=(ManualResetEventSlim) Param;

			Console.WriteLine(string.Format("MyThread - Event IsSet: [{0}] !",MRES.IsSet));

			Thread.Sleep(2000);

			Console.WriteLine("MyThread is GOING to SET EVENT !");

			MRES.Set();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			Thread					T=new Thread(MyThread);
			// Mozem nastavit Spin Count.
			ManualResetEventSlim	MRES=new ManualResetEventSlim(false,1000);

			Console.WriteLine(string.Format("MyThread - Event IsSet: [{0}] !",MRES.IsSet));

			T.Start(MRES);

			Console.WriteLine(string.Format("MainThread - Event IsSet: [{0}] !",MRES.IsSet));

			Console.WriteLine("MainThread - is GOING TO WAIT !");

			MRES.Wait();

			Console.WriteLine("MainThread - WAIT FINISHED !");

			Console.WriteLine(string.Format("MainThread - Event IsSet: [{0}] !",MRES.IsSet));

			Console.WriteLine("WAIT FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------