using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ErrorHandlingExtensionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ErrorHandlingExtensionsService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection							ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CErrorHandlingExtensionsService>	Service=new CServiceHostWrapper<CErrorHandlingExtensionsService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding											TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			Service.AddServiceEndpoint<IErrorHandlingExtensionsContract>(TCPBinding,"net.tcp://localhost:9001/IErrorHandlingExtensionsContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------