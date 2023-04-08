using System;
using System.Collections.Generic;
using System.Text;
using ManualWCFLibrary;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ConfigConfiguratedServices()
		{
			CServiceHostWrapperCollection			ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CHelloWorldService>	Service1=new CServiceHostWrapper<CHelloWorldService>();
			CServiceHostWrapper<CGetSetSetrvice>	Service2=new CServiceHostWrapper<CGetSetSetrvice>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		static void ManuallyConfiguratedServices()
		{
			CServiceHostWrapperCollection			ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CHelloWorldService>	Service1=new CServiceHostWrapper<CHelloWorldService>();
			CServiceHostWrapper<CGetSetSetrvice>	Service2=new CServiceHostWrapper<CGetSetSetrvice>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding									TCPBinding=new NetTcpBinding();

			Service1.AddServiceEndpoint<IHelloWorldContract>(TCPBinding,"net.tcp://localhost:9001/IHelloWorldContract");
			Service1.AddServiceEndpoint<IThrowExceptionContract>(TCPBinding,"net.tcp://localhost:9001/IThrowExceptionContract");
			Service2.AddServiceEndpoint<IIntGetSetContract>(TCPBinding,"net.tcp://localhost:9002/IIntGetSetContract");
			Service2.AddServiceEndpoint<IStringGetSetContract>(TCPBinding,"net.tcp://localhost:9002/IStringGetSetContract");

			// Musi tu byt cela adresa, lebo som nedeklaroval pri volani konstruktoru HOST zaidnu base adresu.
			Service1.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");
			Service2.AddTCPMEXEndpoint("net.tcp://localhost:9002/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			ConfigConfiguratedServices();

			// !!! Aby toto fungovalo, musim zakomentovat app.config, inak budu MANUALNE KONFIGUROVANY WCF SERVICE v KOLIZII v WCF SERVICE definovanom v app.config.
			//ManuallyConfiguratedServices();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------