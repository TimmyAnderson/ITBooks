using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using StreamingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace StreamingService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection				ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CStreamingService>		Service=new CServiceHostWrapper<CStreamingService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim transfer mod na Streamed.
			TCPBinding.TransferMode=TransferMode.Streamed;

			// Nastavim maximalnu dlzku message.
			TCPBinding.MaxReceivedMessageSize=10*1024*1024;

			Service.AddServiceEndpoint<IStreamingContract>(TCPBinding,"net.tcp://localhost:9001/IStreamingContract");

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