using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedTPTimers
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void MyCallback(object State, bool TimedOut)
		{
			string				Param=(string) State;

			Console.WriteLine(string.Format("{0} - BEGIN TIMER: [{1}], TimedOut: [{2}] !",DateTime.Now,Param,TimedOut));

			Thread.Sleep(2*1000);

			Console.WriteLine(string.Format("{0} - END TIMER: [{1}], TimedOut: [{2}] !",DateTime.Now,Param,TimedOut));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			AutoResetEvent				Event=new AutoResetEvent(false);
			AutoResetEvent				FinishEvent=new AutoResetEvent(false);
			RegisteredWaitHandle		RWH;

			// Nastavim aby bol Event ZNOVA REGISTROVANY a TIMEOUT JE 5 sekund.
			RWH=ThreadPool.RegisterWaitForSingleObject(Event,MyCallback,"Hello World",5*1000,false);

			Console.WriteLine("Press any key to FIRE EVENT - or wait 5 seconds to timeout !");
			Console.ReadLine();

			Console.WriteLine("EVENT IS GOING TO BE FIRED !");

			Event.Set();

			Console.WriteLine("Press any key to UNREGISTER !");
			Console.ReadLine();
			
			RWH.Unregister(FinishEvent);

			Console.WriteLine(string.Format("{0} - Waiting for FinishEvent !",DateTime.Now));

			FinishEvent.WaitOne();

			Console.WriteLine(string.Format("{0} - FinishEvent SIGNALIZED !",DateTime.Now));
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