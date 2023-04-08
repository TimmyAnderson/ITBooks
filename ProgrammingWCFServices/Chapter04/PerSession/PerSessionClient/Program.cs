using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test1().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa TCP/IP.
		private static void Test1()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			TCPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(TCPBinding,"net.tcp://localhost:9001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test2().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa TCP/IP.
		private static void Test2()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			TCPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(TCPBinding,"net.tcp://localhost:9001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test3().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa HTTP.
		private static void Test3()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						HTTPBinding=new WSHttpBinding();

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(HTTPBinding,"http://localhost:10001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test4().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa HTTP.
		private static void Test4()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						HTTPBinding=new WSHttpBinding();

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(HTTPBinding,"http://localhost:10001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test5().
		// !!! TRANSPORT SESSION je ZAPNUTA.
		// !!! Pouziva sa HTTP a NEMA ZAPNUTU SECURITY.
		private static void Test5()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=true;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(HTTPBinding,"http://localhost:10001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Na HOST MUSI BYT SPUSTENY Test6().
		// !!! TRANSPORT SESSION je VYPNUTA.
		// !!! Pouziva sa HTTP a NEMA ZAPNUTU SECURITY.
		private static void Test6()
		{
			CPerSessionProxy					Client=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						HTTPBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim reliability na session.
			HTTPBinding.ReliableSession.Enabled=false;

			// Nastavim expiracny timeout na 20 sekund.
			// !!! Nejako mi tento timeout ignoruje.
			HTTPBinding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(20);

			try
			{
				Client=new CPerSessionProxy(HTTPBinding,"http://localhost:10001/IPerSessionContract");

				Client.Open();

				Client.SetState(StateIn);
				Console.WriteLine(String.Format("Client send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Press any key to continue or wait 20 seconds and timeout will expire !");
				Console.ReadLine();

				Client.PrintActualState();

				StateOut=Client.GetState();
				Console.WriteLine(String.Format("Server returned StateOut(): {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
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

			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			Test6();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------