using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using AsynchronousCallsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CAsynchronousCallsService>		Service=new CServiceHostWrapper<CAsynchronousCallsService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding										TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=false;

			Service.AddServiceEndpoint<IAsynchronousCallsContract>(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceDebugBehavior								SDB=Service.Host.Description.Behaviors.OfType<ServiceDebugBehavior>().First();
			
			SDB.IncludeExceptionDetailInFaults=true;

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------