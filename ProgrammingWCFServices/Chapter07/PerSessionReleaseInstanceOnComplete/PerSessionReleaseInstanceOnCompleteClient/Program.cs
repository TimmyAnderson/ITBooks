using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionReleaseInstanceOnCompleteLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteClient
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

			CPerSessionReleaseInstanceOnCompleteProxy	Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding								TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				Client=new CPerSessionReleaseInstanceOnCompleteProxy(TCPBinding,"net.tcp://localhost:9001/IPerSessionReleaseInstanceOnCompleteContract");

				Client.PrintSessionID();

				Client.NoTransaction("111");

				Client.DoTransaction("222");

				// Session stale zije.
				Client.PrintSessionID();

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