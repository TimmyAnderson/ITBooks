using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InheritanceTwoServices_Service
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			try
			{
				using (ServiceHost SH1=new ServiceHost(typeof(CSimpleTextService)))
				{
					SH1.Open();

					using (ServiceHost SH2=new ServiceHost(typeof(CComplexTextService)))
					{
						SH2.Open();

						Console.WriteLine("Press any key to STOP !");
						Console.ReadLine();
						
						SH2.Close();
					}
					
					SH1.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------