using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CSCCallbackWithoutSCService>	Service1=new CServiceHostWrapper<CSCCallbackWithoutSCService>();
			CServiceHostWrapper<CSCCallbackWithSCService>		Service2=new CServiceHostWrapper<CSCCallbackWithSCService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding1=new NetTcpBinding();
			NetTcpBinding									TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			Service1.AddServiceEndpoint<ISCCallbackWithoutSCContract>(TCPBinding1,"net.tcp://localhost:9001/ISCCallbackWithoutSCContract");
			Service2.AddServiceEndpoint<ISCCallbackWithSCContract>(TCPBinding2,"net.tcp://localhost:9002/ISCCallbackWithSCContract");

			Service1.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");
			Service2.AddTCPMEXEndpoint("net.tcp://localhost:9002/MEX");

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