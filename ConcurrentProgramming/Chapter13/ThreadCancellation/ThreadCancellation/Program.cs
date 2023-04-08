using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ThreadCancellation
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------]
		// Sluzi na ukoncenie Threadu, ktory prave vykonava nejaky kod.
		private static bool						MCancelFlag=false;
		// Sluzi na ukoncenie Threadu, ktory prave vykonava nejaky kod.
		private static AutoResetEvent			MCancelEvent=new AutoResetEvent(false);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void CancellationThread()
		{
			try
			{
				while(MCancelFlag==false)
				{
					Console.WriteLine("Worker Thread is running !");

					for (int i=0;i<10;i++)
					{
						// Ak je nastaveny flag, ukoncim thread.
						if (MCancelFlag==true)
						{
							Console.WriteLine("Worker Thread IS FINISHING by FLAG !!!");
							return;
						}

						Thread.Sleep(100);
					}

					if (MCancelEvent.WaitOne(0)==true)
					{
						Console.WriteLine("Worker Thread IS FINISHING by EVENT !!!");
						break;
					}
				}
			}
			finally
			{
				Console.WriteLine("Worker Thread IS FINISHED !");
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Thread			T=new Thread(CancellationThread);

			T.Start();

			Thread.Sleep(5*1000);

			Console.WriteLine("Main Thread IS ASKING for Worker Thread CANCELLATION !!!");

			MCancelFlag=true;

			T.Join();
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Thread			T=new Thread(CancellationThread);

			T.Start();

			Thread.Sleep(5*1000);

			Console.WriteLine("Main Thread IS ASKING for Worker Thread CANCELLATION !!!");

			MCancelEvent.Set();

			T.Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test1();
			//Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------