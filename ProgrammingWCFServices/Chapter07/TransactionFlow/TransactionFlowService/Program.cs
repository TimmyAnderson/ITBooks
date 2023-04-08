using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionFlowLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CTransactionFlowAService>		Service1=new CServiceHostWrapper<CTransactionFlowAService>();
			CServiceHostWrapper<CTransactionFlowBService>		Service2=new CServiceHostWrapper<CTransactionFlowBService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding1=new NetTcpBinding();
			NetTcpBinding									TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding1.TransactionFlow=true;
			TCPBinding2.TransactionFlow=true;

			Service1.AddServiceEndpoint<ITransactionFlowAContract>(TCPBinding1,"net.tcp://localhost:9001/ITransactionFlowAContract");
			Service2.AddServiceEndpoint<ITransactionFlowBContract>(TCPBinding2,"net.tcp://localhost:9002/ITransactionFlowBContract");

			Service1.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");
			Service2.AddTCPMEXEndpoint("net.tcp://localhost:9002/MEX");

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