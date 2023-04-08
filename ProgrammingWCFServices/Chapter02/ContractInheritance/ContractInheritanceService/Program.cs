using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ContractInheritanceLibrary;
//-------------------------------------------------------------------------------------------------------
// Tento service bude vystavovat jeden jediny endpoint a to zdedeny.
// Aj ked som to neskusal asi by bolo mozne aby vystavoval aj 2 nezavisle endpoints.
// Je to znova zavisle od toho co vlastne chcem dosiahnut.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection			ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CCalculatorService>	Service=new CServiceHostWrapper<CCalculatorService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding									TCPBinding=new NetTcpBinding();

			// Dam ibe jeden endpoint.
			Service.AddServiceEndpoint<IScientificCalculatorContract>(TCPBinding,"net.tcp://localhost:9001/IScientificCalculatorContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

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