using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MySynchronizationContextLibrary;
using MySynchronizationContext;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContextService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			// Vytvorim CMySynchronizationContext.
			// Musi byt v 'using' aby sa zastavil jeho thread.
			using(CMySynchronizationContext		MySynchronizationContext=new CMySynchronizationContext())
			{
				// !!! Teraz nastavim SynchronizationContext na CMySynchronizationContext.
				SynchronizationContext.SetSynchronizationContext(MySynchronizationContext);

				CServiceHostWrapperCollection							ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CMySynchronizationContextService>	Service=new CServiceHostWrapper<CMySynchronizationContextService>();

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				NetTcpBinding									TCPBinding=new NetTcpBinding();

				// Nastavim reliability na session.
				TCPBinding.ReliableSession.Enabled=true;

				// !!! Musim nastavit transaction flow.
				TCPBinding.TransactionFlow=true;

				Service.AddServiceEndpoint<IMySynchronizationContextContract>(TCPBinding,"net.tcp://localhost:9001/IMySynchronizationContextContract");

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
}
//-------------------------------------------------------------------------------------------------------