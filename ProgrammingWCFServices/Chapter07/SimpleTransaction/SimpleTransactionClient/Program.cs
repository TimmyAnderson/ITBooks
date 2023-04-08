using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleTransactionLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace SimpleTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_1);
			CTransactionHelper.DeleteAll(EDBID.E_DI_DB_2);

			CSimpleTransactionProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CSimpleTransactionProxy(TCPBinding,"net.tcp://localhost:9001/ISimpleTransactionContract");

				try
				{
					Client.OneDBTwoTables("OneDBTwoTables");
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

				try
				{
					Client.TwoDBOneTableInEach("TwoDBOneTableInEach");
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

				try
				{
					Client.TwoDBOneTableInEachExcplicitVoting("TwoDBOneTableInEachExcplicitVoting");
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

				try
				{
					Client.TwoDBOneTableInEachExcplicitVotingWithException("TwoDBOneTableInEachExcplicitVotingWithException");
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

				try
				{
					Client.TwoDBOneTableInEachWithException("TwoDBOneTableInEachWithException");
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------