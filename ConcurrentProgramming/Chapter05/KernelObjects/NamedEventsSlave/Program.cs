using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Security.AccessControl;
//-----------------------------------------------------------------------------
namespace NamedEventsSlave
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void Test()
		{
			EventWaitHandle		EWH=null;

			while(true)
			{
				try
				{
					EWH=EventWaitHandle.OpenExisting("MyNamedEvent");
					Console.WriteLine("!!! EVENT FOUND !");
					break;
				}
				catch
				{
					Console.WriteLine("EVENT DOESN'T EXIST !");
				}

				Thread.Sleep(500);
			}

			Console.WriteLine("WAITING FOR EVENT !");

			EWH.WaitOne();

			Console.WriteLine("EVENT RECEIVED !");
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SLAVE";

			// !!! Program musi byt spustany spolu s NamedEventsMaster.

			Test();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------