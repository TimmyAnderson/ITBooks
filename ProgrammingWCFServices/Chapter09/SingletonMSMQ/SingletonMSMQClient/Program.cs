using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionHelper;
using SingletonMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SingletonMSMQClient
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

			CSingletonMSMQProxy					Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ISingletonMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CSingletonMSMQProxy(TCPBinding,QueueName);

				try
				{
					// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
					Client.Open();

					Client.DoTransaction("DoTransaction1");
					Client.NonTransaction("NonTransaction");
					Client.DoTransaction("DoTransaction2");
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Console.WriteLine("ALL OK !\n");
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