using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Transactions;
using ClientTransactionLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace ClientTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CClientTransactionProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CClientTransactionProxy(TCPBinding,"net.tcp://localhost:9001/IClientTransactionContract");

				try
				{
					using(TransactionScope Scope=new TransactionScope())
					{
						Transaction					T=Transaction.Current;

						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						Client.TFAllowed("TFAllowed");

						Console.WriteLine(CDebugHelper.GetTransactionString(T));
						CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"TFAllowed",T);
						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						// Ak by som nezavolal Complete() cela transakcia - aj service cast bude rollbacknuta.
						Scope.Complete();
					}
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
			CClientTransactionProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CClientTransactionProxy(TCPBinding,"net.tcp://localhost:9001/IClientTransactionContract");

				try
				{
					using(TransactionScope Scope=new TransactionScope())
					{
						Transaction					T=Transaction.Current;

						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						Client.TFNotAllowed("TFNotAllowed");

						Console.WriteLine(CDebugHelper.GetTransactionString(T));
						CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"TFNotAllowed",T);
						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						// Ak by som nezavolal Complete() cela transakcia - aj service cast bude rollbacknuta.
						Scope.Complete();
					}
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
			CClientTransactionProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CClientTransactionProxy(TCPBinding,"net.tcp://localhost:9001/IClientTransactionContract");

				try
				{
					using(TransactionScope Scope=new TransactionScope())
					{
						Transaction					T=Transaction.Current;

						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						Client.TFMandatory("TFMandatory");

						Console.WriteLine(CDebugHelper.GetTransactionString(T));
						CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,"TFMandatory",T);
						Console.WriteLine(CDebugHelper.GetTransactionString(T));

						// Ak by som nezavolal Complete() cela transakcia - aj service cast bude rollbacknuta.
						Scope.Complete();
					}
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
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			// Zmaz DB.
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

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