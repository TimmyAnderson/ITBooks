using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.ServiceModel;
using System.ServiceModel.Channels;
using UseSynchronizationContextLibrary;
//-------------------------------------------------------------------------------------------------------
namespace UseSynchronizationContextService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection							ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CUseSynchronizationContextService>	Service=new CServiceHostWrapper<CUseSynchronizationContextService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			Service.AddServiceEndpoint<IUseSynchronizationContextContract>(TCPBinding,"net.tcp://localhost:9001/IUseSynchronizationContextContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			// Startujem WinForm.
			Application.Run(new CMyForm(ServiceHostWrapperCollection));

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------