using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AsynchroCallbackTransactionLibrary;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace AsynchroCallbackTransactionClient
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

			int										ID=new Random().Next(100,999);
			string									ClientName="C_" + ID;
			CAsynchroCallbackTransactionProxy		Client=null;
			IAsynchroCallbackTransactionCallback	CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding							TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// !!! Musim nastavit transaction flow.
			TCPBinding.TransactionFlow=true;

			try
			{
				CallBack=new CAsynchroCallbackTransactionCatcher();

				Client=new CAsynchroCallbackTransactionProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/IAsynchroCallbackTransactionContract");

				Client.Connect(ClientName);

				Client.DoTransaction("HELLO CALLBACK " + ID,5*1000);

				Console.WriteLine("ALL OK !\n");

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");

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