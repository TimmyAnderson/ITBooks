using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleFaultsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CSimpleFaultsPerCallProxy			Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CSimpleFaultsPerCallProxy(TCPBinding,"net.tcp://localhost:9001/ISimpleFaultsPerCallContract");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowCMyFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy JE MRTVE.
					Client.ThrowSimpleException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Chodi CommunicationException, kedze proxy je mrtve.
					Client.IsAlive();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
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
			CSimpleFaultsPerSessionProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CSimpleFaultsPerSessionProxy(TCPBinding,"net.tcp://localhost:9002/ISimpleFaultsPerSessionContract");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowCMyFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy JE MRTVE.
					Client.ThrowSimpleException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Chodi CommunicationException, kedze proxy je mrtve.
					Client.IsAlive();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
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
			CSimpleFaultsSingletonProxy			Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CSimpleFaultsSingletonProxy(TCPBinding,"net.tcp://localhost:9003/ISimpleFaultsSingletonContract");

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy prezije.
					Client.ThrowCMyFaultException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vrati sa ako FaultException<CFaultDetails>.
					// Proxy JE MRTVE.
					Client.ThrowSimpleException();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Chodi CommunicationException, kedze proxy je mrtve.
					Client.IsAlive();
				}
				catch(CMyFaultException E)
				{
					Console.WriteLine(string.Format("CMyFaultException: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<CFaultDetails> E)
				{
					Console.WriteLine(string.Format("FaultException<CFaultDetails>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
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

			//Test1();
			Test2();
			//Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------