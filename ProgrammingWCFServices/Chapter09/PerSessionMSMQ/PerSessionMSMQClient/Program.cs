using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionHelper;
using PerSessionMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CPerSessionMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPerSessionMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CPerSessionMSMQProxy(TCPBinding,QueueName);

				try
				{
					using(TransactionScope T=new TransactionScope())
					{
						// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
						Client.Open();

						Client.TransactionStart("TransactionStart");
						Client.TransactionFinishAuto("TransactionFinishAuto");

						// !!! Kedze by som tu neuzavrel Proxy tak mam vynimku pri opustani TransactionScope s tym, ze transakcia bola ROLLBACK.

						// Ani toto nepomoze. Proxy musi byt uzavrete.
						T.Complete();
					}
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
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CPerSessionMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPerSessionMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CPerSessionMSMQProxy(TCPBinding,QueueName);

				try
				{
					using(TransactionScope T=new TransactionScope())
					{
						// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
						Client.Open();

						Client.TransactionStart("TransactionStart");
						Client.TransactionFinishAuto("TransactionFinishAuto");

						// !!! Musim uzavriet proxy a este pred Complete().
						Client.Close();
						Client=null;

						// !!! A az teraz mozem COMMITNUT transakciu.
						T.Complete();
					}
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
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			CPerSessionMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPerSessionMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CPerSessionMSMQProxy(TCPBinding,QueueName);

				try
				{
					using(TransactionScope T=new TransactionScope())
					{
						// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
						Client.Open();

						Client.TransactionStart("TransactionStart");
						Client.TransactionFinishManual("TransactionFinishManual");

						// !!! Musim uzavriet proxy a este pred Complete().
						Client.Close();
						Client=null;

						// !!! A az teraz mozem COMMITNUT transakciu.
						T.Complete();
					}
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
		}
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			CPerSessionMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPerSessionMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CPerSessionMSMQProxy(TCPBinding,QueueName);

				try
				{
					using(TransactionScope T=new TransactionScope())
					{
						// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
						Client.Open();

						Client.TransactionStart("TransactionStart");

						// Zavloam netransakcnu metodu.
						// !!! Ak pri realizacii transakcie niekde zvolam metou, ktrora nepuziva transakcie, teda TransactionScopeRequired=false potom dochadza k tomu, ze transakcia zlyha a WCF sa ju pokusi zopakovat, no ale kedze sa zopakuje aj volanie netransakcnej metody tak volanie VZDY ZLYHA.
						// !!! Sposobi PERMANENTNY ROLLBACK, KDE KAZDE OPAKOVANIE TRANSAKCIE Z MSMQ hodi VZDY ROLLBACK.
						Client.NonTransaction("NonTransaction");

						Client.TransactionFinishManual("TransactionFinishManual");

						// !!! Musim uzavriet proxy a este pred Complete().
						Client.Close();
						Client=null;

						// !!! A az teraz mozem COMMITNUT transakciu.
						T.Complete();
					}
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
		}
//-------------------------------------------------------------------------------------------------------
		static void Test5()
		{
			CPerSessionMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPerSessionMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding						TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CPerSessionMSMQProxy(TCPBinding,QueueName);

				try
				{
					using(TransactionScope T=new TransactionScope())
					{
						// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
						Client.Open();

						Client.TransactionStart("TransactionStart");

						// Zavloam metodu, ktora na prve 3 pokusy hodi exception. WCF JU VSAK OPAKUJE a na 4. pokus PREJDE.
						Client.FailTransaction("FailTransaction");

						Client.TransactionFinishManual("TransactionFinishManual");

						// !!! Musim uzavriet proxy a este pred Complete().
						Client.Close();
						Client=null;

						// !!! A az teraz mozem COMMITNUT transakciu.
						T.Complete();
					}
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
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------