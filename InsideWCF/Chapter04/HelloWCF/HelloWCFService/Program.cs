using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using HelloWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Pouzivam BasicHttpBinding.
		static void Test1()
		{
			try
			{
				CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CHelloWCFService>			Service=new CServiceHostWrapper<CHelloWCFService>();

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				BasicHttpBinding								BasicBinding=new BasicHttpBinding();

				Service.AddServiceEndpoint<IHelloWCFContract>(BasicBinding,"http://localhost:4000/IHelloWCFContract");

				ServiceHostWrapperCollection.StartServices();

				Console.WriteLine("Press any key to STOP services !");
				Console.ReadLine();

				ServiceHostWrapperCollection.StopServices();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pouzivam WSHttpBinding.
		static void Test2()
		{
			try
			{
				CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				CServiceHostWrapper<CHelloWCFService>			Service=new CServiceHostWrapper<CHelloWCFService>();

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				// Security nech je zapnuta.
				WSHttpBinding									WSBinding=new WSHttpBinding();

				Service.AddServiceEndpoint<IHelloWCFContract>(WSBinding,"http://localhost:4000/IHelloWCFContract");

				ServiceHostWrapperCollection.StartServices();

				Console.WriteLine("Press any key to STOP services !");
				Console.ReadLine();

				ServiceHostWrapperCollection.StopServices();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pouzivam BasicHttpBinding.
		static void Test3()
		{
			try
			{
				Uri												BaseAddress=new Uri("http://localhost:4000/IHelloWCFContract");

				CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
				// Musim prida base address.
				CServiceHostWrapper<CHelloWCFService>			Service=new CServiceHostWrapper<CHelloWCFService>(BaseAddress);

				ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

				// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
				BasicHttpBinding								BasicBinding=new BasicHttpBinding();

				Service.AddServiceEndpoint<IHelloWCFContract>(BasicBinding,BaseAddress.AbsoluteUri);

				// Metadata.

				// Metadata cez HttpGet.
				// Vytvorim Behavior.
				ServiceMetadataBehavior							MetadataBehavior=new ServiceMetadataBehavior();

				// Nastavim ho na HttpGet.
				MetadataBehavior.HttpGetEnabled=true;

				// Pridam Behavior do collection.
				Service.Host.Description.Behaviors.Add(MetadataBehavior);
				
				// Metadata cez MEX endpoint.
				// 1. Vytvorim si MEX adresu - TCP.
				Uri												MEXAddress=new Uri("net.tcp://localhost:5000/IHelloWCFContract/MEX");

				// 2. Vytvorim si MEX binding - pouzijem TCP.
				Binding											MEXBinding=MetadataExchangeBindings.CreateMexTcpBinding();

				// Pridam MEX endpoint.
				// 3. Contract==IMetadataExchange.
				Service.Host.AddServiceEndpoint(typeof(IMetadataExchange), MEXBinding, MEXAddress);

				// Spustim service.
				ServiceHostWrapperCollection.StartServices();

				Console.WriteLine("Press any key to STOP services !");
				Console.ReadLine();

				ServiceHostWrapperCollection.StopServices();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CInsideWCFHelper.ClearMessageDirectory();

			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------