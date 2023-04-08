using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Routing;
//-------------------------------------------------------------------------------------------------------
namespace MyRoutingService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="ROUTING SERVICE";

			using (ServiceHost SH=new ServiceHost(typeof(RoutingService)))
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