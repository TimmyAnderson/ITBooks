using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AutoCompleteSessionCloseLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace AutoCompleteSessionCloseClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CAutoCompleteSessionCloseProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CAutoCompleteSessionCloseProxy(TCPBinding,"net.tcp://localhost:9001/IAutoCompleteSessionCloseContract");

				Client.DoTransaction("XXX");

				Console.WriteLine("Press any key to finish transaction ! Pause must be shoter than 60 seconds otherwise rollback will be realized. \n");
				Console.ReadLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						// !!! Az teraz sa urobi Commit/Rollback transakcie.
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
		static void Test2()
		{
			CAutoCompleteSessionCloseProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CAutoCompleteSessionCloseProxy(TCPBinding,"net.tcp://localhost:9001/IAutoCompleteSessionCloseContract");

				Client.DoTransaction("YYY");

				try
				{
					Client.ThrowException();
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				Console.WriteLine("Press any key to continue. \n");
				Console.ReadLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						// !!! Az teraz sa urobi Commit/Rollback transakcie.
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
		static void Test3()
		{
			CAutoCompleteSessionCloseProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CAutoCompleteSessionCloseProxy(TCPBinding,"net.tcp://localhost:9001/IAutoCompleteSessionCloseContract");

				Client.DoTransaction("AAA");
				// Ukonci transakciu.
				Client.FinishTransaction("BBB");

				// Rozbehne novu - ta uz skonci cez autocomplete.
				Client.DoTransaction("CCC");

				Console.WriteLine("Press any key to continue. \n");
				Console.ReadLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						// !!! Az teraz sa urobi Commit/Rollback transakcie.
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
		static void Test4()
		{
			CAutoCompleteSessionCloseProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CAutoCompleteSessionCloseProxy(TCPBinding,"net.tcp://localhost:9001/IAutoCompleteSessionCloseContract");

				Client.DoTransaction("AAA");

				// Transakcia zlyha, lebo pretecie timeout.
				Thread.Sleep(65*1000);
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						// !!! Az teraz sa urobi Commit/Rollback transakcie.
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

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

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