using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
using System.Configuration;
using FTCSharedLibrary;
using FTCChannelLibrary;
using TestLibrary;
//-------------------------------------------------------------------------------------------------------
// !!!!! Aby to bezalo musim mat ADRESAR v ktorom budu dve podadresare !Packets1 a !Packets2 a kazdy z nich podadresare Receiver a Sender.
// Tento ADRESAR je cestou - parameter MAddressBase.
//-------------------------------------------------------------------------------------------------------
namespace TestService
{
//-------------------------------------------------------------------------------------------------------
	class Service
	{
//-------------------------------------------------------------------------------------------------------
		// Cesta k directory, ktory bude mat subdirectory Sender a Receiver.
		// !!! Cesta nesmie obsahovat znaky, ktore nevie Uri parsovat, napriklad '#'.
		private static string									MAddressBase=ConfigurationManager.AppSettings["Path"];
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			try
			{
				Console.Title="Service1";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				using(ServiceHost Svc=new ServiceHost(typeof(CTestFTCContract)))
				{
					Svc.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address);

					Console.WriteLine("Press any key to START SERVICE !");
					Console.ReadLine();

					Svc.Open();

					Console.WriteLine("Press any key to CLOSE SERVICE !");
					Console.ReadLine();

					Svc.Close();
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			try
			{
				Console.Title="Service2";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				using(ServiceHost Svc=new ServiceHost(typeof(CTestFTCContract)))
				{
					Svc.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address);

					Console.WriteLine("Press any key to START SERVICE !");
					Console.ReadLine();

					Svc.Open();

					Console.WriteLine("Press any key to CLOSE SERVICE !");
					Console.ReadLine();

					Svc.Close();
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			try
			{
				Console.Title="Service3";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address1=new Uri(MAddressBase + @"/!Packets1");
				Uri						Address2=new Uri(MAddressBase + @"/!Packets2");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				using(ServiceHost Svc=new ServiceHost(typeof(CTestFTCContract)))
				{
					Svc.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address1);
					Svc.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address2);

					Console.WriteLine("Press any key to START SERVICE !");
					Console.ReadLine();

					Svc.Open();

					Console.WriteLine("Press any key to CLOSE SERVICE !");
					Console.ReadLine();

					Svc.Close();
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			try
			{
				Console.Title="Service4";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address1=new Uri(MAddressBase + @"/!Packets1");
				Uri						Address2=new Uri(MAddressBase + @"/!Packets2");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				using(ServiceHost Svc1=new ServiceHost(typeof(CTestFTCContract)))
				{
					using(ServiceHost Svc2=new ServiceHost(typeof(CTestFTCContract)))
					{
						Svc1.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address1);
						Svc2.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address2);

						Console.WriteLine("Press any key to START SERVICE !");
						Console.ReadLine();

						Svc1.Open();
						Svc2.Open();

						Console.WriteLine("Press any key to CLOSE SERVICE !");
						Console.ReadLine();

						Svc1.Close();
						Svc2.Close();
					}
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test5()
		{
			try
			{
				Console.Title="Service5";

				Console.WriteLine(CDebugHelper.GetMethodCallString(1));
		        
				Uri						Address=new Uri(MAddressBase + @"/!Packets1");
				CFTCBinding				Binding=new CFTCBinding(CSettings.MessageVersion);

				using(ServiceHost Svc=new ServiceHost(typeof(CTestFTCContract)))
				{
					Svc.AddServiceEndpoint(typeof(ITestFTCContract), Binding, Address);

					Console.WriteLine("Press any key to START SERVICE !");
					Console.ReadLine();

					Svc.Open();

					Console.WriteLine("Press any key to CLOSE SERVICE !");
					Console.ReadLine();

					Svc.Close();
				}

				Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();
			//Test5();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------