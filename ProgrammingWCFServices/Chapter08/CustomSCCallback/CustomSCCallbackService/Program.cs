using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CustomSCCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CCustomSCCallbackService>		Service=new CServiceHostWrapper<CCustomSCCallbackService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			Service.AddServiceEndpoint<ICustomSCCallbackContract>(TCPBinding,"net.tcp://localhost:9001/ICustomSCCallbackContract");

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