using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContext
{
//-------------------------------------------------------------------------------------------------------
	public class CTest
	{
//-------------------------------------------------------------------------------------------------------
		private static CMySynchronizationContext				MMySynchronizationContext;
//-------------------------------------------------------------------------------------------------------
		static void Method1(object Param)
		{
			string			Value=(string) Param;

			Console.WriteLine(string.Format("Method1(): {0} 1 !",Value));

			Thread.Sleep(3*1000);

			Console.WriteLine(string.Format("Method1(): {0} 2 !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		static void Method2(object Param)
		{
			string			Value=(string) Param;

			Console.WriteLine(string.Format("Method2(): {0} 1 !",Value));

			Thread.Sleep(3*1000);

			Console.WriteLine(string.Format("Method2(): {0} 2 !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		static void Thread1()
		{
			Console.WriteLine("Thread1(): 1 !");

			// Send() je blokovana funkcia.
			//MMySynchronizationContext.Send(new SendOrPostCallback(CTest.Method1),"11111");

			// Post() je neblokovana funkcia.
			MMySynchronizationContext.Post(new SendOrPostCallback(CTest.Method1),"11111");

			Console.WriteLine("Thread1(): 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		static void Thread2()
		{
			Console.WriteLine("Thread2(): 1 !");

			// Send() je blokovana funkcia.
			//MMySynchronizationContext.Send(new SendOrPostCallback(CTest.Method1),"22222");

			// Post() je neblokovana funkcia.
			MMySynchronizationContext.Post(new SendOrPostCallback(CTest.Method1),"22222");

			Console.WriteLine("Thread2(): 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			MMySynchronizationContext=new CMySynchronizationContext();

			Thread						T1=new Thread(new ThreadStart(CTest.Thread1));
			Thread						T2=new Thread(new ThreadStart(CTest.Thread2));

			T1.Start();
			T2.Start();

			Console.WriteLine("Press any key to STOP !");
			Console.ReadLine();

			MMySynchronizationContext.Dispose();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------