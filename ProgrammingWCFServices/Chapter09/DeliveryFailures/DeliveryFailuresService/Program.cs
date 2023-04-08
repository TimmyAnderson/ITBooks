using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DeliveryFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DeliveryFailuresService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			string												QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IDeliveryFailuresContract");

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CDeliveryFailuresService>		Service=new CServiceHostWrapper<CDeliveryFailuresService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim TTL.
			TCPBinding.TimeToLive=new TimeSpan(0,1,0);

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			Service.AddServiceEndpoint<IDeliveryFailuresContract>(TCPBinding,QueueName);

			// !!! MEX rozhranie musi vystavit osobitne, pretoze MSMQ ho explicitne nevystavuje.
			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------