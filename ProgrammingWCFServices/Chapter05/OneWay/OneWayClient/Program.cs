using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using OneWayLibrary;
//-------------------------------------------------------------------------------------------------------
namespace OneWayClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// ZAPNUTA SESSION.
		private static void Test1()
		{
			COneWayProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new COneWayProxy(TCPBinding,"net.tcp://localhost:9001/IOneWayContract");

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(3*1000);

				Client.MethodWithException();
				Console.WriteLine("MethodWithException() CALLED !");
				Thread.Sleep(1*1000);

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(12*1000);

				// !!! Pouzivam TRANSPORT SESSION. Tato metoda hodi EXCEPTION, kedze mezitym MethodWithException() dala kanal do FAULTED state.
				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");

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
		// VYPNUTA SESSION, ale kedze pouzivam TCP/IP, tak SESSION je VZDY ZAPNUTA KANALOM.
		private static void Test2()
		{
			COneWayProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nenastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new COneWayProxy(TCPBinding,"net.tcp://localhost:9001/IOneWayContract");

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(3*1000);

				Client.MethodWithException();
				Console.WriteLine("MethodWithException() CALLED !");
				Thread.Sleep(1*1000);

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(12*1000);

				// !!! Pouzivam TRANSPORT SESSION. Tato metoda hodi EXCEPTION, kedze mezitym MethodWithException() dala kanal do FAULTED state.
				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");

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
		// VYPNUTA SESSION. Ozaj sa TRANSPORT SESSION NEPOUZIVA, lebo pouzivam HTTP BIDNING BEZ MESSAGE SECURITY.
		private static void Test3()
		{
			COneWayProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nenastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new COneWayProxy(HTTPBinding,"http://localhost:10001/IOneWayContract");

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(3*1000);

				Client.MethodWithException();
				Console.WriteLine("MethodWithException() CALLED !");
				Thread.Sleep(1*1000);

				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");
				Thread.Sleep(12*1000);

				// !!! NEPOUZIVAM TRANSPORT SESSION. Tato metoda NEHODI EXCEPTION.
				Client.MethodWithoutException();
				Console.WriteLine("MethodWithoutException() CALLED !");

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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test1();
			//Test2();
			//Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------