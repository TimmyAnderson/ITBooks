using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-----------------------------------------------------------------------------
namespace NamedEventsMaster
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void Test()
		{
			Thread.Sleep(3000);

			EventWaitHandle		EWH=new EventWaitHandle(false,EventResetMode.AutoReset,"MyNamedEvent");

			Console.WriteLine("EVENT CREATED !");

			Thread.Sleep(3000);

			Console.WriteLine("EVENT SET !");

			EWH.Set();
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="MASTER";

			// !!! Program musi byt spustany spolu s NamedEventsSlave.

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------