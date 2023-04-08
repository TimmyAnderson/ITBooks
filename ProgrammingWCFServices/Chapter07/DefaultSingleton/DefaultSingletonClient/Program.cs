using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DefaultSingletonLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------		
namespace DefaultSingletonClient
{
//-------------------------------------------------------------------------------------------------------		
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CDefaultSingletonProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CDefaultSingletonProxy(TCPBinding,"net.tcp://localhost:9001/IDefaultSingletonContract");

				Client.DoTransaction("AAA");
				Client.NonTransaction();
				Client.DoTransaction("BBB");
				Client.NonTransaction();
				Client.DoTransaction("CCC");
				Client.DoTransaction("DDD");
				Client.DoTransaction("EEE");
				Client.DoTransaction("FFF");

				Console.WriteLine("ALL OK !\n");
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
			CDefaultSingletonProxy				Client1=null;
			CDefaultSingletonProxy				Client2=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding1.TransactionFlow=true;
			TCPBinding2.TransactionFlow=true;

			try
			{
				Client1=new CDefaultSingletonProxy(TCPBinding1,"net.tcp://localhost:9001/IDefaultSingletonContract");
				Client2=new CDefaultSingletonProxy(TCPBinding2,"net.tcp://localhost:9001/IDefaultSingletonContract");

				Client1.DoTransaction("AAA");
				Client2.DoTransaction("BBB");

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client1!=null)
				{
					try
					{
						// !!! Az teraz sa urobi Commit/Rollback transakcie.
						Client1.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client1=null;
				}

				if (Client2!=null)
				{
					try
					{
						Client2.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client2=null;
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

			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------		
	}
//-------------------------------------------------------------------------------------------------------		
}
//-------------------------------------------------------------------------------------------------------