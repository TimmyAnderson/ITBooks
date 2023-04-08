using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace MonitorWaitPulseTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static object				MTestLock=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Thread_1(object Param)
		{
			string			ThreadName="111";
			int				Pause=(int) Param;

			Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"BEFORE LOCK"));

			Thread.Sleep(Pause);

			lock(MTestLock)
			{
				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"LOCK ACQUIRED"));

				Thread.Sleep(1*1000);

				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"Wait() IS CALLING"));

				if (Monitor.Wait(MTestLock,5*1000)==true)
					Console.WriteLine("Wait(): LOCK REACQUIRED !");
				else
					Console.WriteLine("Wait(): TIMEOUT ELAPSED !");

				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"Wait() FINISHED"));

				Thread.Sleep(1*1000);
			}

			Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"AFTER LOCK"));
		}
//------------------------------------------------------------------------------
		private static void Thread_2(object Param)
		{
			string			ThreadName="222";
			int				Pause=(int) Param;

			Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"BEFORE LOCK"));

			Thread.Sleep(Pause);

			lock(MTestLock)
			{
				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"LOCK ACQUIRED"));

				Thread.Sleep(1*1000);

				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"Pause() IS CALLING"));

				Monitor.Pulse(MTestLock);

				Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"Pause() FINISHED"));

				Thread.Sleep(1*1000);
			}

			Console.WriteLine(string.Format("{0} {1} {2} !",DateTime.Now.ToString("HH:mm:dd.fff"),ThreadName,"AFTER LOCK"));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				object				Obj=new object();

				// Monitor.Wait() a Monitor.Pulse() je mozne volat IBA AK je objekt LOCKED. Inak hodi Exception.
				//Monitor.Wait(Obj);
				Monitor.Pulse(Obj);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				object				Obj=new object();

				lock(Obj)
				{
					if (Monitor.Wait(Obj,5*1000)==true)
						Console.WriteLine("LOCK REACQUIRED !");
					else
						Console.WriteLine("TIMEOUT ELAPSED !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			try
			{
				Thread		T1=new Thread(Thread_1);
				Thread		T2=new Thread(Thread_2);

				T1.Start(0);
				T2.Start(1000);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				Thread		T1=new Thread(Thread_1);
				Thread		T2=new Thread(Thread_2);

				T1.Start(1000);
				T2.Start(0);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test1();
			//Test2();
			//Test3();
			//Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------