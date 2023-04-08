using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultEndpointHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				Uri					U1=new Uri("net.tcp://localhost:9005");
				Uri					U2=new Uri("http://localhost:9006");

				using(ServiceHost SH=new ServiceHost(typeof(CService),U1,U2))
				{
					// Pridam DEFAULT ENDPOINTS. Aj ked tuto metodu NEZAVOLAM, tak sa DEFAULT ENDPOINTS pridaju AUTOMATICKY.
					// !!! DEFAULT ENDPOINT pomocou ServiceHost.AddDefaultEndpoints() NIE JE NUTNE VOLAT, ak nepridavam ziadne dalsie ENDPOINTS, pretoze WCF ju zavola AUTOMATICKY. Avsak je ju NUTNE VOLAT, ak pridam pomocou AddServiceEndpoint() aj nejake dalsie ENDPOINTS a zaroven chcem, aby WCF vystavila i DEFAULT ENDPOINTS.
					//SH.AddDefaultEndpoints();

					SH.Open();

					Console.WriteLine("Press any key to STOP service !");
					Console.ReadLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------