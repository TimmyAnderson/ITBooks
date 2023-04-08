using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace FirstWCFService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			CFirstWCFServiceHost	FirstWCFServiceHost=new CFirstWCFServiceHost();

			FirstWCFServiceHost.Start();

			Console.WriteLine("Press any key to STOP !");
			Console.ReadLine();

			FirstWCFServiceHost.Stop();

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------