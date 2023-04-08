using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using HelloWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFManualClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Pouzivam BasicHttpBinding.
		static void Test1()
		{
			CHelloWCFProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			BasicHttpBinding					BasicBinding=new BasicHttpBinding();

			try
			{
				Client=new CHelloWCFProxy(BasicBinding,"http://localhost:4000/IHelloWCFContract");

				// Otvaram kanal.
				Client.Open();

				Client.Say("Hi there WCF");

				Client.SayWith2Params("Hello","World");

				Client.SayPurchaseOrder("Hi !!!",new CPurchaseOrder(100,new CVendorInfo(200,"Hewlett Packard")));

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					try
					{
						Client.Close();
						Console.WriteLine(String.Format("Close() OK"));
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Pouzivam WSHttpBinding.
		static void Test2()
		{
			CHelloWCFProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			// Security nech je zapnuta.
			WSHttpBinding						WSBinding=new WSHttpBinding();

			try
			{
				Client=new CHelloWCFProxy(WSBinding,"http://localhost:4000/IHelloWCFContract");

				// Otvaram kanal.
				Client.Open();

				Client.Say("Hi there WCF");

				Client.SayWith2Params("Hello","World");

				Client.SayPurchaseOrder("Hi !!!",new CPurchaseOrder(100,new CVendorInfo(200,"Hewlett Packard")));

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					try
					{
						Client.Close();
						Console.WriteLine(String.Format("Close() OK"));
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Test1();
			//Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------