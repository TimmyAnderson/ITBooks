using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace CountdownEventTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static int				THREAD_COUNT=10;
		// Nastavim pociatocnu hodnotu CountdownEvent.
		private static CountdownEvent	CDE=new CountdownEvent(THREAD_COUNT);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void MyThread(object Param)
		{
			int				Value=(int) Param;

			Thread.Sleep(Value);
			Console.WriteLine(string.Format("Thread {0} is FINISHING !",Value));

			CDE.Decrement();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			for (int i=0;i<THREAD_COUNT;i++)
			{
				Thread			T=new Thread(MyThread);

				T.Start(i*1000);
			}

			Console.WriteLine("MAIN Thread is WAITING !");

			CDE.Wait();

			Console.WriteLine("!!! MAIN Thread FINISHED WAITING !");
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