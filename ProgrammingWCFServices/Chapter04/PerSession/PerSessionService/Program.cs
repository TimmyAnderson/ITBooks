using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test1().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa TCP/IP.
		private static void Test1()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			TCPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(TCPBinding,"net.tcp://localhost:9001/IPerSessionContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test2().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa TCP/IP.
		private static void Test2()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			TCPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(TCPBinding,"net.tcp://localhost:9001/IPerSessionContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test3().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa HTTP.
		private static void Test3()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding									HTTPBinding=new WSHttpBinding();

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(HTTPBinding,"http://localhost:10001/IPerSessionContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test4().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa HTTP.
		private static void Test4()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding									HTTPBinding=new WSHttpBinding();

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(HTTPBinding,"http://localhost:10001/IPerSessionContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test5().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa HTTP a NEMA ZAPNUTU SECURITY.
		private static void Test5()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding									HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(HTTPBinding,"http://localhost:10001/IPerSessionContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		// Na CLIENT MUSI BYT SPUSTENY Test6().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa HTTP a NEMA ZAPNUTU SECURITY.
		private static void Test6()
		{
			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerSessionService>			Service=new CServiceHostWrapper<CPerSessionService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding									HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IPerSessionContract>(HTTPBinding,"http://localhost:10001/IPerSessionContract");

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

			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			Test6();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------