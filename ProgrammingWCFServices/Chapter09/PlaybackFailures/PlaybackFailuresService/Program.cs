using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PlaybackFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PlaybackFailuresService
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
			QueueName=CMSMQHelper.VerifyQueue("IPlaybackFailuresContract");

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CPlaybackFailuresService>		Service=new CServiceHostWrapper<CPlaybackFailuresService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			// Nastavim vlastnosti zotavenia.
			TCPBinding.ReceiveRetryCount=3;
			TCPBinding.MaxRetryCycles=6;
			TCPBinding.ReceiveTimeout=new TimeSpan(0,0,15);
			TCPBinding.ReceiveErrorHandling=ReceiveErrorHandling.Fault;

			Service.AddServiceEndpoint<IPlaybackFailuresContract>(TCPBinding,QueueName);

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