using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFaultsService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CSimpleFaultsPerCallService>	Service1=new CServiceHostWrapper<CSimpleFaultsPerCallService>();
			CServiceHostWrapper<CSimpleFaultsPerSessionService>	Service2=new CServiceHostWrapper<CSimpleFaultsPerSessionService>();
			CServiceHostWrapper<CSimpleFaultsSingletonService>	Service3=new CServiceHostWrapper<CSimpleFaultsSingletonService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service3);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding1=new NetTcpBinding();
			NetTcpBinding									TCPBinding2=new NetTcpBinding();
			NetTcpBinding									TCPBinding3=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;

			Service1.AddServiceEndpoint<ISimpleFaultsPerCallContract>(TCPBinding1,"net.tcp://localhost:9001/ISimpleFaultsPerCallContract");
			Service2.AddServiceEndpoint<ISimpleFaultsPerSessionContract>(TCPBinding2,"net.tcp://localhost:9002/ISimpleFaultsPerSessionContract");
			Service3.AddServiceEndpoint<ISimpleFaultsSingletonContract>(TCPBinding3,"net.tcp://localhost:9003/ISimpleFaultsSingletonContract");

			Service1.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");
			Service2.AddTCPMEXEndpoint("net.tcp://localhost:9002/MEX");
			Service3.AddTCPMEXEndpoint("net.tcp://localhost:9003/MEX");

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