using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace TestServiceMetadataEndpoint
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					ServiceMetadataBehavior		SMB=new ServiceMetadataBehavior();

					// Pridam do Behaviors ServiceMetadataBehavior.
					SH.Description.Behaviors.Add(SMB);

					Binding						B=MetadataExchangeBindings.CreateMexTcpBinding();

					// Vytvorim MEX ENDPOINT pomocou triedy ServiceMetadataEndpoint.
					ServiceMetadataEndpoint		SME=new ServiceMetadataEndpoint(B,new EndpointAddress("net.tcp://localhost:8001/MEX"));

					// Vytvorim MEX Endpoint - pouzijem relativnu adresu.
					SH.AddServiceEndpoint(SME);

					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
					
					SH.Close();
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