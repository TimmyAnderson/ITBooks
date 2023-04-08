using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace SemaphoreSlimTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void MyThread(object Param)
		{
			SemaphoreSlim		SS=(SemaphoreSlim) Param;

			Console.WriteLine(string.Format("MyThread - Count: [{0}] !",SS.CurrentCount));

			Thread.Sleep(2000);

			Console.WriteLine("MyThread is GOING to RELEASE SEMAPHORE !");

			SS.Release();
		}
//------------------------------------------------------------------------------
		private static void CancelThread(object Param)
		{
			SemaphoreSlim		SS=(SemaphoreSlim) Param;

			Thread.Sleep(2000);

			Console.WriteLine("MyThread is GOING to CANCEL WAITING !");

			SS.Cancel();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			Thread					T=new Thread(MyThread);
			SemaphoreSlim			SS=new SemaphoreSlim(3,3);

			Console.WriteLine(string.Format("MyThread - Count: [{0}] !",SS.CurrentCount));

			T.Start(SS);

			for (int i=0;i<4;i++)
			{
				Console.WriteLine(string.Format("MainThread is GOING to WAIT for EVENT [{0}] !",i+1));
				Console.WriteLine(string.Format("MyThread - BEFORE WAIT - Count: [{0}] !",SS.CurrentCount));
				SS.Wait();
				Console.WriteLine(string.Format("MainThread is FINISHED WAITING [{0}] !",i+1));
				Console.WriteLine(string.Format("MyThread - AFTER WAIT - Count: [{0}] !",SS.CurrentCount));
			}

			Console.WriteLine(string.Format("MyThread - Count: [{0}] !",SS.CurrentCount));

			Console.WriteLine("WAIT FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			Thread					T=new Thread(CancelThread);
			// Zablokujem Semaphore.
			SemaphoreSlim			SS=new SemaphoreSlim(0,3);

			Console.WriteLine(string.Format("MyThread - Count: [{0}] !",SS.CurrentCount));

			T.Start(SS);

			try
			{
				Console.WriteLine("MainThread is GOING to WAIT for EVENT !");
				Console.WriteLine(string.Format("MyThread - BEFORE WAIT - Count: [{0}] !",SS.CurrentCount));

				SS.Wait();

				Console.WriteLine("MainThread FINISHED WAITING  !");
				Console.WriteLine(string.Format("MyThread - AFTER WAIT - Count: [{0}] !",SS.CurrentCount));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("MainThread - EXCEPTION: [{0}] !",E.Message));

				Console.WriteLine("MainThread FINISHED WAITING BY EXCEPTION !");
				Console.WriteLine(string.Format("MyThread - AFTER WAIT - Count: [{0}] !",SS.CurrentCount));
			}

			Console.WriteLine(string.Format("MyThread - Count: [{0}] !",SS.CurrentCount));

			Console.WriteLine("WAIT FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------