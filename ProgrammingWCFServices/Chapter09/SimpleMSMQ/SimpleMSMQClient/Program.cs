using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CSimpleMSMQProxy					Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("Hello WORLD - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ISimpleMSMQLibraryContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CSimpleMSMQProxy(TCPBinding,QueueName);

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
		static void Test2()
		{
			CSimpleMSMQProxy					Client=null;
			Random								RND=new Random();
			string								QueueName;
			string								Message=string.Format("Hello WORLD - {0}",RND.Next(100,999));

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("ISimpleMSMQLibraryContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CSimpleMSMQProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Console.WriteLine(string.Format("MESSAGE: {0}",Message));

				// Volam metodu, ktora hodi vynimku.
				Client.ThrowException(Message);

				// Pockam na spracovanie.
				Thread.Sleep(10*1000);

				// Overim ci zije kanal.
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test1();
			//Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------