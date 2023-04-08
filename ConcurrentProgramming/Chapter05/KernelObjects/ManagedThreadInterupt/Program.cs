using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-----------------------------------------------------------------------------
namespace ManagedThreadInterupt
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void SimpleThread()
		{
			using(AutoResetEvent ARE=new AutoResetEvent(false))
			{
				try
				{
					Console.WriteLine("SimpleThread() - Before Wait() !");

					ARE.WaitOne();

					Console.WriteLine("SimpleThread() - After Wait() !");
				}
				catch(ThreadInterruptedException TIE)
				{
					Console.WriteLine(string.Format("SimpleThread() - EXCEPTION: {0} !",TIE.Message));
				}
			}
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Thread		T=new Thread(Program.SimpleThread);

			Console.WriteLine("Main() - Before thread START !");

			T.Start();

			Console.WriteLine("Main() - After thread START !");

			Thread.Sleep(1000);

			Console.WriteLine("Main() - Before Interupt() !");

			T.Interrupt();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------