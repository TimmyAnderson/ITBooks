using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FaultContractsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FaultContractsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CFaultContractsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFaultContractsProxy(TCPBinding,"net.tcp://localhost:9001/IFaultContractsContract");

				try
				{
					Client.ThrowInvalidOperationException();
				}
				catch(FaultException<InvalidOperationException> E)
				{
					Console.WriteLine(string.Format("FaultException<InvalidOperationException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<ExceptionDetail> E)
				{
					Console.WriteLine(string.Format("FaultException<ExceptionDetail>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
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

				try
				{
					Client.IsAlive();
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
			CFaultContractsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFaultContractsProxy(TCPBinding,"net.tcp://localhost:9001/IFaultContractsContract");

				try
				{
					Client.ThrowFaultException();
				}
				catch(FaultException<InvalidOperationException> E)
				{
					Console.WriteLine(string.Format("FaultException<InvalidOperationException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<ExceptionDetail> E)
				{
					Console.WriteLine(string.Format("FaultException<ExceptionDetail>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
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

				try
				{
					Client.IsAlive();
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
			CFaultContractsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFaultContractsProxy(TCPBinding,"net.tcp://localhost:9001/IFaultContractsContract");

				try
				{
					Client.ThrowInvalidOperationAsFaultException();
				}
				catch(FaultException<InvalidOperationException> E)
				{
					Console.WriteLine(string.Format("FaultException<InvalidOperationException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<ExceptionDetail> E)
				{
					Console.WriteLine(string.Format("FaultException<ExceptionDetail>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
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

				try
				{
					Client.IsAlive();
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
		static void Test4()
		{
			CFaultContractsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFaultContractsProxy(TCPBinding,"net.tcp://localhost:9001/IFaultContractsContract");

				try
				{
					Client.ThrowExceptionDetail();
				}
				catch(FaultException<InvalidOperationException> E)
				{
					Console.WriteLine(string.Format("FaultException<InvalidOperationException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<ExceptionDetail> E)
				{
					Console.WriteLine(string.Format("FaultException<ExceptionDetail>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
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

				try
				{
					Client.IsAlive();
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
		static void Test5()
		{
			CFaultContractsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFaultContractsProxy(TCPBinding,"net.tcp://localhost:9001/IFaultContractsContract");

				try
				{
					Client.ThrowCFaultDetailsException();
				}
				catch(FaultException<InvalidOperationException> E)
				{
					Console.WriteLine(string.Format("FaultException<InvalidOperationException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException<ExceptionDetail> E)
				{
					Console.WriteLine(string.Format("FaultException<ExceptionDetail>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
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

				try
				{
					Client.IsAlive();
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
			//Test2();
			Test3();
			//Test4();
			//Test5();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------