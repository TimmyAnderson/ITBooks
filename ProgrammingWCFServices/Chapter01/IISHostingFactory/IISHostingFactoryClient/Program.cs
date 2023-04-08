using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using IISHostingFactoryService;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace IISHostingFactoryClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				WSHttpBinding		Binding=new WSHttpBinding();
				IMySimpleService	Proxy=ChannelFactory<IMySimpleService>.CreateChannel(Binding,new EndpointAddress("http://localhost:9999/MySimpleService.svc"));

				string				Ret=Proxy.ToUpper("Timmy");

				Console.WriteLine(string.Format("Value: [{0}] !",Ret));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------