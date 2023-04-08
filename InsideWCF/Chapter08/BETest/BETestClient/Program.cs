using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using BETestLibrary;
//-------------------------------------------------------------------------------------------------------
namespace BETestClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test(Binding B)
		{
			CBETestProxy						Client=null;

			try
			{
				Client=new CBETestProxy(B,"net.tcp://localhost:9001/IBETestContract");

				Client.Open();

				string Response=Client.SomeMethod("Hello World");

				Console.WriteLine(string.Format("Response from SERVICE: {0} !",Response));

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
			}
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
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//DoTest1();
			//DoTest2();
			//DoTest3();
			//DoTest4();
			DoTest5();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------