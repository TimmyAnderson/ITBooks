using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerCallMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerCallMSMQService
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
			QueueName=CMSMQHelper.VerifyQueue("IPerCallMSMQContract");

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPerCallMSMQService>			Service=new CServiceHostWrapper<CPerCallMSMQService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			Service.AddServiceEndpoint<IPerCallMSMQContract>(TCPBinding,QueueName);

			// !!! MEX rozhranie musi vystavit osobitne, pretoze MSMQ ho explicitne nevystavuje.
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