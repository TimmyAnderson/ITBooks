using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using MetadataImporterService;
//-------------------------------------------------------------------------------------------------------
namespace MetadataImporterClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("Client"))
			{
				using(IDisposable D=(IDisposable) CF.CreateChannel())
				{
					ITestService							Proxy=(ITestService) D;

					Proxy.ConnectionTest();

					Uri										MetadataAddress=new Uri("net.tcp://localhost:8000/Service/MEX");
					MetadataExchangeClient					Client=new MetadataExchangeClient(MetadataAddress,MetadataExchangeClientMode.MetadataExchange);
					
					// Ziskam RAW metadata.
					MetadataSet								RawMetadada=Client.GetMetadata();

					WsdlImporter							Importer=new WsdlImporter(RawMetadada);

					// Vykonam PARSING METADAT.
					ServiceEndpointCollection				ServiceEndpoints=Importer.ImportAllEndpoints();

					foreach(ServiceEndpoint ServiceEndpoint in ServiceEndpoints)
					{
						Console.WriteLine(string.Format("Address: [{0}] !",ServiceEndpoint.Address));
						Console.WriteLine(string.Format("Contract.Name: [{0}] !",ServiceEndpoint.Contract.Name));
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

            Console.WriteLine("Press any key to START !");
            Console.ReadLine();

			try
			{
				Test();
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