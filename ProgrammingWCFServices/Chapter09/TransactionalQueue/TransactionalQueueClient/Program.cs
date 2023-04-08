using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionHelper;
using TransactionalQueueLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalQueueClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Service nepouzje transakciu - funkcia skonci bez Exception.
		static void Test1()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST1 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				Client.PrintText(Message);

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
		}
//-------------------------------------------------------------------------------------------------------
		// Service nepouzije transakciu - funkcia skonci s Exception.
		static void Test2()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST2 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				Client.ThrowException(Message);

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
		}
//-------------------------------------------------------------------------------------------------------
		// Service pouzije transakciu - funkcia skonci bez Exception.
		static void Test3()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST3 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				Client.PrintTextWithTransaction(Message);

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
		}
//-------------------------------------------------------------------------------------------------------
		// Service pouzije transakciu - funkcia skonci s Exception.
		static void Test4()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST4 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				Client.ThrowExceptionWithTransaction(Message);

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
		}
//-------------------------------------------------------------------------------------------------------
		// Simulacia klientskej transakcie s pouzitim abientnej transakcie. Transakcia skonci COMMIT.
		static void Test5()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST5 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				using(TransactionScope T=new TransactionScope())
				{
					// Service nebude pouzivat ranakcie ale na tom nezalezi.
					Client.PrintText(Message);

					// Urobim commit a tym padom sa volanie zaradi do Queue.
					T.Complete();
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
		}
//-------------------------------------------------------------------------------------------------------
		// Simulacia klientskej transakcie s pouzitim abientnej transakcie. Transakcia skonci COMMIT.
		static void Test6()
		{
			CTransactionalQueueProxy			Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("TEST4 - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ITransactionalQueueContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CTransactionalQueueProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				using(TransactionScope T=new TransactionScope())
				{
					// Service nebude pouzivat ranakcie ale na tom nezalezi.
					Client.PrintText(Message);

					// Neurobim commit mam ROLLBACK a tym padom sa volanie nezaradi do Queue.
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
			//Test5();
			//Test6();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------