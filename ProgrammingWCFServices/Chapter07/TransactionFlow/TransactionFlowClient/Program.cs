using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionFlowLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFAllowed("TFAllowed");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFNotAllowed("TFNotAllowed");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFMandatory("TFMandatory");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFImplicitVoting("TFImplicitVoting");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFImplicitVotingWithException("TFImplicitVotingWithException");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				// Zbehne aj ked sa vyvola FaultException a nie FaultException<Exception>.
				Client.Dummy();
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFExplicitVoting("TFExplicitVoting");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFExplicitVotingWithEnd("TFExplicitVotingWithEnd");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			CTransactionFlowAProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CTransactionFlowAProxy(TCPBinding,"net.tcp://localhost:9001/ITransactionFlowAContract");

				try
				{
					Client.TFExplicitVotingStartTransaction("TFExplicitVotingStartTransaction");
					Client.TFExplicitVotingEndTransaction("TFExplicitVotingEndTransaction");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(FaultException E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
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

			// Zmaz DB.
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

			Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------