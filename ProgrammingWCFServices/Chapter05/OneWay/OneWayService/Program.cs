using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using OneWayLibrary;
//-------------------------------------------------------------------------------------------------------
namespace OneWayService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// ZAPNUTA SESSION.
		private static void Test1()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<COneWayService>				Service=new CServiceHostWrapper<COneWayService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			Service.AddServiceEndpoint<IOneWayContract>(TCPBinding,"net.tcp://localhost:9001/IOneWayContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// VYPNUTA SESSION, ale kedze pouzivam TCP/IP, tak SESSION je VZDY ZAPNUTA KANALOM.
		private static void Test2()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<COneWayService>				Service=new CServiceHostWrapper<COneWayService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nenastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			Service.AddServiceEndpoint<IOneWayContract>(TCPBinding,"net.tcp://localhost:9001/IOneWayContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// VYPNUTA SESSION. Ozaj sa TRANSPORT SESSION NEPOUZIVA, lebo pouzivam HTTP BIDNING BEZ MESSAGE SECURITY.
		private static void Test3()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<COneWayService>				Service=new CServiceHostWrapper<COneWayService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding									HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nenastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			Service.AddServiceEndpoint<IOneWayContract>(HTTPBinding,"http://localhost:10001/IOneWayContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

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
			Console.Title="SERVER";

			Test1();
			//Test2();
			//Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------