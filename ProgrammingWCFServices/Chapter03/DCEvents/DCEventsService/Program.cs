using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCEventsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCEventsService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CDCEventsService>			Service=new CServiceHostWrapper<CDCEventsService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding											TCPBinding=new NetTcpBinding();

			Service.AddServiceEndpoint<IDCEventsContract>(TCPBinding,"net.tcp://localhost:9001/IDCEventsContract");

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