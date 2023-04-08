using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace RoutingTestBackupService2
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="BACKUP SERVICE 2";

			using (ServiceHost SH=new ServiceHost(typeof(CToLower)))
			{
				SH.Open();

				Console.WriteLine("Press any key to STOP !");
				Console.ReadLine();
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------