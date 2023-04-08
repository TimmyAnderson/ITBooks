using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MessageContractLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageContractService
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

				CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CMessageContractService>	Service=new CServiceHostWrapper<CMessageContractService>();

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				WSHttpBinding									WSBinding=new WSHttpBinding(SecurityMode.None);

				// Nastavim textovy encoder.
				WSBinding.MessageEncoding=WSMessageEncoding.Text;

				Service.AddServiceEndpoint<IMessageContractContract>(WSBinding,"http://localhost:4000/IMessageContractContract");

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