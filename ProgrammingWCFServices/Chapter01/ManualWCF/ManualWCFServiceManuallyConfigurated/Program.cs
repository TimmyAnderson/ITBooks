using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ManualWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFServiceManuallyConfigurated
{
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ManuallyConfiguratedServices()
		{
			CServiceHostWrapperCollection			ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CHelloWorldService>	Service1=new CServiceHostWrapper<CHelloWorldService>();
			CServiceHostWrapper<CGetSetSetrvice>	Service2=new CServiceHostWrapper<CGetSetSetrvice>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding									TCPBindingS1C1=new NetTcpBinding();
			Binding									TCPBindingS1C2=new NetTcpBinding();
			Binding									TCPBindingS2C1=new NetTcpBinding();
			Binding									TCPBindingS2C2=new NetTcpBinding();

			Service1.AddServiceEndpoint<IHelloWorldContract>(TCPBindingS1C1,"net.tcp://localhost:9001/IHelloWorldContract");
			Service1.AddServiceEndpoint<IThrowExceptionContract>(TCPBindingS1C2,"net.tcp://localhost:9001/IThrowExceptionContract");
			Service2.AddServiceEndpoint<IIntGetSetContract>(TCPBindingS2C1,"net.tcp://localhost:9002/IIntGetSetContract");
			Service2.AddServiceEndpoint<IStringGetSetContract>(TCPBindingS2C2,"net.tcp://localhost:9002/IStringGetSetContract");

			// Musi tu byt cela adresa, lebo som nedeklaroval pri volani konstruktoru HOST zaidnu base adresu.
			Service1.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");
			Service2.AddTCPMEXEndpoint("net.tcp://localhost:9002/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			ManuallyConfiguratedServices();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------