using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DeliveryFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DeliveryFailuresClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CDeliveryFailuresProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IDeliveryFailuresContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim TTL.
			TCPBinding.TimeToLive=new TimeSpan(0,1,0);

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			try
			{
				Client=new CDeliveryFailuresProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				// !!! TREBA SPUSTAS V VYPNUTYM SERVROM a cakat 1 minutu.
				Client.PrintText("PrintText");

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
			CDeliveryFailuresProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IDeliveryFailuresContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim TTL.
			TCPBinding.TimeToLive=new TimeSpan(0,1,0);

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			try
			{
				Client=new CDeliveryFailuresProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Client.ThrowExceptionWithTransaction("ThrowExceptionWithTransaction");

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