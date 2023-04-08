using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ContractQueriesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ContractQueriesService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CContractQueriesService>	Service=new CServiceHostWrapper<CContractQueriesService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding									TCPBinding1=new NetTcpBinding();
			Binding									TCPBinding2=new NetTcpBinding();

			Service.AddServiceEndpoint<IAddContract>(TCPBinding1,"net.tcp://localhost:9001/IAddContract");
			Service.AddServiceEndpoint<IMultipleContract>(TCPBinding2,"net.tcp://localhost:9001/IMultipleContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------