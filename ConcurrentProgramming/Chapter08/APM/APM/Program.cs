using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace APM
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void MyCallback(IAsyncResult AR)
		{
			CSimpleAsyncOperation		AO=(CSimpleAsyncOperation) AR;
			int							Value=AO.EndWork(AR);

			Console.WriteLine(string.Format("MyCallback() - TID: {0} - CALLBACK RETURNED: {1} !",Thread.CurrentThread.ManagedThreadId,Value));
		}
//------------------------------------------------------------------------------
		private static void Test()
		{
			CSimpleAsyncOperation		AO=new CSimpleAsyncOperation();

			Console.WriteLine(string.Format("Test() - TID: {0} - BEFORE BeginWork() !",Thread.CurrentThread.ManagedThreadId));

			IAsyncResult				AR=AO.BeginWork(5*1000,MyCallback,AO);

			Console.WriteLine(string.Format("Test() - TID: {0} - AFTER BeginWork() !",Thread.CurrentThread.ManagedThreadId));

			while(true)
			{
				Thread.Sleep(1000);

				if (AR.IsCompleted==false)
					Console.WriteLine(string.Format("Test() - TID: {0} - WAITING !",Thread.CurrentThread.ManagedThreadId));
				else
					break;
			}

			Console.WriteLine(string.Format("Test() - TID: {0} - CALLBACK COMPLETED !",Thread.CurrentThread.ManagedThreadId));
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