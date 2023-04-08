using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using BETestLibrary;
//-------------------------------------------------------------------------------------------------------
namespace BETestService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test(Binding B)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CBETestService>				Service=new CServiceHostWrapper<CBETestService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			Service.AddServiceEndpoint<IBETestContract>(B,"net.tcp://localhost:9001/IBETestContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoTest1()
		{
			// Pouzijem tuto konfiguraciu B.
			// 1. TcpTransportBindingElement.
			CustomBinding		CB=new CustomBinding(new BindingElement[] {new TcpTransportBindingElement()});

			Test(CB);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoTest2()
		{
			// Pouzijem tuto konfiguraciu B.
			// 1. BinaryMessageEncodingBindingElement.
			// 2. TcpTransportBindingElement.
			CustomBinding		CB=new CustomBinding(new BindingElement[] {new BinaryMessageEncodingBindingElement(), new TcpTransportBindingElement()});

			Test(CB);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoTest3()
		{
			// Pouzijem tuto konfiguraciu B.
			// 1. TransactionFlowBindingElement.
			// 2. BinaryMessageEncodingBindingElement.
			// 3. TcpTransportBindingElement.
			CustomBinding		CB=new CustomBinding(new BindingElement[] {new TransactionFlowBindingElement(), new BinaryMessageEncodingBindingElement(), new TcpTransportBindingElement()});

			Test(CB);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoTest4()
		{
			// Pouzijem tuto konfiguraciu B.
			// 1. TransactionFlowBindingElement.
			// 2. ReliableSessionBindingElement
			// 3. BinaryMessageEncodingBindingElement.
			// 4. TcpTransportBindingElement.
			CustomBinding		CB=new CustomBinding(new BindingElement[] {new TransactionFlowBindingElement(), new BinaryMessageEncodingBindingElement(), new TcpTransportBindingElement()});

			Test(CB);
		}
//-------------------------------------------------------------------------------------------------------
		private static void DoTest5()
		{
			// Pouzijem tuto konfiguraciu B.
			// 1. TransactionFlowBindingElement.
			// 2. ReliableSessionBindingElement
			// 3. BinaryMessageEncodingBindingElement.
			// 4. WindowsStreamSecurityBindingElement.
			// 5. TcpTransportBindingElement.
			CustomBinding		CB=new CustomBinding(new BindingElement[] {new TransactionFlowBindingElement(), new BinaryMessageEncodingBindingElement(), new WindowsStreamSecurityBindingElement(), new TcpTransportBindingElement()});

			Test(CB);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			//DoTest1();
			//DoTest2();
			//DoTest3();
			//DoTest4();
			DoTest5();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------