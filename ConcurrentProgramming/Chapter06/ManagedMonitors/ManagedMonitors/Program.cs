using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.CompilerServices;
//------------------------------------------------------------------------------
namespace ManagedMonitors
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static object					MSyn=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[MethodImpl(MethodImplOptions.Synchronized)]
		private static void ProtectedMethod(string Value)
		{
			Console.WriteLine(string.Format("BEGIN [{0}] !",Value));

			Thread.Sleep(3*1000);

			Console.WriteLine(string.Format("END [{0}] !",Value));
		}
//------------------------------------------------------------------------------
		private static void SynchronizedFunctionThread()
		{
			Thread.Sleep(100);

			Console.WriteLine("Worker thread STARTED !");

			ProtectedMethod("WORKER THREAD CALL");

			Console.WriteLine("Worker thread FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void TestSynchronizedFunction()
		{
			Thread			T=new Thread(SynchronizedFunctionThread);

			T.Start();

			ProtectedMethod("PRIMARY THREAD CALL");

			T.Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void TryEnterThread()
		{
			Thread.Sleep(500);

			Console.WriteLine("Worker thread STARTED !");

			while(Monitor.TryEnter(MSyn,500)==false)
			{
				Console.WriteLine("\tWorker CAN'T ENTER MONITOR !");
			}

			try
			{
				Console.WriteLine("Worker thread ENTERS MONITOR !");

				Thread.Sleep(1*1000);

				Console.WriteLine("Worker thread LEAVES MONITOR !");
			}
			finally
			{
				Monitor.Exit(MSyn);
			}
		}
//------------------------------------------------------------------------------
		private static void TestTryEnter()
		{
			Thread			T=new Thread(TryEnterThread);

			T.Start();

			lock(MSyn)
			{
				Console.WriteLine("Primary thread ENTERS MONITOR !");

				Thread.Sleep(3*1000);

				Console.WriteLine("Primary thread LEAVES MONITOR !");
			}

			T.Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestTryEnter();
			TestSynchronizedFunction();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------