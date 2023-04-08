using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using NETSerializeLibrary;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CNETSerializeService>		Service=new CServiceHostWrapper<CNETSerializeService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding									TCPBinding=new NetTcpBinding();

			Service.AddServiceEndpoint<INETSerializeContract>(TCPBinding,"net.tcp://localhost:9001/INETSerializeContract");

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