using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CallbackFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CCallbackFaultsProxy				Client=null;
			CCallbackFaultsCatcher				Catcher=new CCallbackFaultsCatcher();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CCallbackFaultsProxy(Catcher,TCPBinding,"net.tcp://localhost:9001/ICallbackFaultsContract");

				Client.Connect("SynchroNonFault");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.SynchroNonFaultException("HELLO",1000);
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(CommunicationException E)
				{
					Console.WriteLine(string.Format("CommunicationException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					// Volanie ZLYHA, lebo ak CALLBACK vrati NON-FaultException, tak TRANSPORT CHANNEL je vo FAULTED STATE.
					Client.Disconnect();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Disconnect() - Exception: {0} !",E.Message));
				}

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CCallbackFaultsProxy				Client=null;
			CCallbackFaultsCatcher				Catcher=new CCallbackFaultsCatcher();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CCallbackFaultsProxy(Catcher,TCPBinding,"net.tcp://localhost:9001/ICallbackFaultsContract");

				Client.Connect("AsynchroNonFault");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.AsynchroNonFaultException("HELLO",1000);

					Console.WriteLine("Press any key to continue !");
					Console.ReadLine();
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(CommunicationException E)
				{
					Console.WriteLine(string.Format("CommunicationException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					// Volanie ZLYHA, lebo ak CALLBACK vrati NON-FaultException, tak TRANSPORT CHANNEL je vo FAULTED STATE.
					Client.Disconnect();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Disconnect() - Exception: {0} !",E.Message));
				}

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			CCallbackFaultsProxy				Client=null;
			CCallbackFaultsCatcher				Catcher=new CCallbackFaultsCatcher();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CCallbackFaultsProxy(Catcher,TCPBinding,"net.tcp://localhost:9001/ICallbackFaultsContract");

				Client.Connect("SynchroFault");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.SynchroFaultException("HELLO",1000);
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(CommunicationException E)
				{
					Console.WriteLine(string.Format("CommunicationException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					// Volanie prebehne OK, lebo ak CALLBACK vrati FaultException, tak TRANSPORT CHANNEL je STALE OK.
					Client.Disconnect();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Disconnect() - Exception: {0} !",E.Message));
				}

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			CCallbackFaultsProxy				Client=null;
			CCallbackFaultsCatcher				Catcher=new CCallbackFaultsCatcher();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CCallbackFaultsProxy(Catcher,TCPBinding,"net.tcp://localhost:9001/ICallbackFaultsContract");

				Client.Connect("AsynchroFault");

				try
				{
					Client.AsynchroFaultException("HELLO",1000);

					Console.WriteLine("Press any key to continue !");
					Console.ReadLine();
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(CommunicationException E)
				{
					Console.WriteLine(string.Format("CommunicationException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					// Volanie prebehne OK, lebo ak CALLBACK vrati FaultException, tak TRANSPORT CHANNEL je STALE OK.
					Client.Disconnect();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Disconnect() - Exception: {0} !",E.Message));
				}

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
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
			//Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------