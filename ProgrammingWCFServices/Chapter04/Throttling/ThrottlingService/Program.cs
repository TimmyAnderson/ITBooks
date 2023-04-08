using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using ThrottlingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ThrottlingService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CThrottlingService>			Service=new CServiceHostWrapper<CThrottlingService>();
			ServiceThrottlingBehavior						Throttle;

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Throttling.
			Throttle=Service.Host.Description.Behaviors.Find<ServiceThrottlingBehavior>();

			// Nastavujem iba nie je nastaveny v .config subore.
			if(Throttle==null)
			{
				Throttle=new ServiceThrottlingBehavior( );

				// Pre SessionTest().
				//Throttle.MaxConcurrentCalls=2;
				//Throttle.MaxConcurrentSessions=4;
				//Throttle.MaxConcurrentInstances=6;

				// Pre InstanceTest().
				//Throttle.MaxConcurrentCalls=2;
				//Throttle.MaxConcurrentSessions=6;
				//Throttle.MaxConcurrentInstances=3;

				// Pre InstanceTest().
				Throttle.MaxConcurrentCalls=2;
				Throttle.MaxConcurrentSessions=6;
				Throttle.MaxConcurrentInstances=6;
				
				Service.Host.Description.Behaviors.Add(Throttle);
			}

			// Nastavim expiracny timeout na 20 sekund.
			//TCPBinding..ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			Service.AddServiceEndpoint<IThrottlingContract>(TCPBinding,"net.tcp://localhost:9001/IThrottlingContract");

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