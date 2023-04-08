using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace SimpleSpinWait
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static bool				MTestedMemory=false;
		private static AutoResetEvent	MEvent=new AutoResetEvent(false);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Thread1()
		{
			SSpinWait			SW=new SSpinWait();

			while (MTestedMemory==false)
			{
				if (SW.NextSpinWillYield==true)
				{
					Console.WriteLine("Thread 1 is BLOCKED NOW !");
					MEvent.WaitOne();
				}
				else
					SW.SpinOnce();
			}

			Console.WriteLine("Thread 1 FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Thread2()
		{
			// Pockaj par cyklov;
			for (int i=0;i<50;i++)
				;

			Console.WriteLine("Thread 2 WILL SET EVENT !");

			MTestedMemory=true;
			MEvent.Set();

			Console.WriteLine("Thread 2 FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			Thread			T1=new Thread(Thread1);
			Thread			T2=new Thread(Thread2);

			T1.Start();
			T2.Start();
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