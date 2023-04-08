using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace TroubleshootingHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			using (ServiceHost SH1=new ServiceHost(typeof(CToUpper)))
			{
				SH1.Open();

				using (ServiceHost SH2=new ServiceHost(typeof(CToLower)))
				{
					SH2.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------