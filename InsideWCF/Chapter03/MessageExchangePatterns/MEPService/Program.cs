using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MEPLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MEPService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				Console.Title="SERVER";

				CInsideWCFHelper.ClearMessageDirectory();

				NetTcpBinding									TCPBinding=new NetTcpBinding();

				CServiceHostWrapperCollection					ServiceHostWrapperCollection1=new CServiceHostWrapperCollection();
				CServiceHostWrapper<COneWayService>				Service1=new CServiceHostWrapper<COneWayService>();

				CServiceHostWrapperCollection					ServiceHostWrapperCollection2=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CRequestResponseService>	Service2=new CServiceHostWrapper<CRequestResponseService>();

				CServiceHostWrapperCollection					ServiceHostWrapperCollection3=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CDuplexService>				Service3=new CServiceHostWrapper<CDuplexService>();

				ServiceHostWrapperCollection1.AddServiceHostWrapper(Service1);
				ServiceHostWrapperCollection2.AddServiceHostWrapper(Service2);
				ServiceHostWrapperCollection3.AddServiceHostWrapper(Service3);

				Service1.AddServiceEndpoint<IOneWayContract>(TCPBinding,"net.tcp://localhost:5000/");
				Service2.AddServiceEndpoint<IRequestResponseContract>(TCPBinding,"net.tcp://localhost:6000/");
				Service3.AddServiceEndpoint<IDuplexContract>(TCPBinding,"net.tcp://localhost:7000/");

				ServiceHostWrapperCollection1.StartServices();
				ServiceHostWrapperCollection2.StartServices();
				ServiceHostWrapperCollection3.StartServices();

				Console.WriteLine("Press any key to STOP services !");
				Console.ReadLine();

				ServiceHostWrapperCollection1.StopServices();
				ServiceHostWrapperCollection2.StopServices();
				ServiceHostWrapperCollection3.StopServices();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------