using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RawMessageSenderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RawMessageSenderService
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

				CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CRawMessageSenderService>	Service=new CServiceHostWrapper<CRawMessageSenderService>();

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				WSHttpBinding									WSBinding=new WSHttpBinding(SecurityMode.None);

				// Nastavim textovy encoder.
				WSBinding.MessageEncoding=WSMessageEncoding.Text;

				Service.AddServiceEndpoint<IRawMessageSenderContract>(WSBinding,"http://localhost:4000/IRawMessageSenderContract");

				Service.AddHTTPMEXEndpoint("http://localhost:4000/MEX");

				ServiceHostWrapperCollection.StartServices();

				Console.WriteLine("Press any key to STOP services !");
				Console.ReadLine();

				ServiceHostWrapperCollection.StopServices();
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