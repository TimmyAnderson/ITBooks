using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------
namespace SimpleManagedThreads
{
//------------------------------------------------------------------------
	public class MainClass
	{
//------------------------------------------------------------------------
		private static void MyThreadFunction(object Obj)
		{
			Console.WriteLine("{0}: Running: {1} !", Thread.CurrentThread.ManagedThreadId, Obj);
		}
//------------------------------------------------------------------------
		private static void Test()
		{
			Thread			NewThread=new Thread(new ParameterizedThreadStart(MyThreadFunction));

			Console.WriteLine("{0}: Created thread (ID {1}) !", Thread.CurrentThread.ManagedThreadId, NewThread.ManagedThreadId);

			NewThread.Start("Hello World");

			 // Wait for the thread to finish.
			NewThread.Join();

			Console.WriteLine("{0}: Thread exited !", Thread.CurrentThread.ManagedThreadId);
		}
//------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------