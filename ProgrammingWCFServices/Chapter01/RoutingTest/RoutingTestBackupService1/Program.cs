using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace RoutingTestBackupService1
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="BACKUP SERVICE 1";

			using (ServiceHost SH=new ServiceHost(typeof(CToUpper)))
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