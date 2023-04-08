using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ManualWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFServiceConfigConfigurated
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ConfigConfiguratedServices()
		{
			CServiceHostWrapperCollection			ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CHelloWorldService>	Service1=new CServiceHostWrapper<CHelloWorldService>();
			CServiceHostWrapper<CGetSetSetrvice>	Service2=new CServiceHostWrapper<CGetSetSetrvice>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service1);
			ServiceHostWrapperCollection.AddServiceHostWrapper(Service2);

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			ConfigConfiguratedServices();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------