using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace SpinLockTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		// Zapnem Tracking.
		private static SpinLock							MSL=new SpinLock(true);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void MyThread()
		{
			int				ThreadID=Thread.CurrentThread.ManagedThreadId;
			bool			WasTaken=false;

			Console.WriteLine(string.Format("Thread [{0}] BEFORE LOCK !",ThreadID));

			try
			{
				MSL.ReliableEnter(ref WasTaken);

				Console.WriteLine(string.Format("Thread [{0}] INSIDE LOCK - WasTaken: [{1}], IsHeldByCurrentThread: [{2}] !",ThreadID,WasTaken,MSL.IsHeldByCurrentThread));

				Thread.Sleep(2000);
			}
			finally
			{
				MSL.Exit();
			}

			Console.WriteLine(string.Format("Thread [{0}] AFTER LOCK !",ThreadID));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			Thread[]			T=new Thread[5];

			for (int i=0;i<T.Length;i++)
			{
				T[i]=new Thread(MyThread);
				T[i].Start();
			}

			for (int i=0;i<T.Length;i++)
				T[i].Join();
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