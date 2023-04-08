using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PlaybackFailuresLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PlaybackFailuresClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CPlaybackFailuresProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPlaybackFailuresContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			// Nastavim vlastnosti zotavenia.
			TCPBinding.ReceiveRetryCount=3;
			TCPBinding.MaxRetryCycles=6;
			TCPBinding.ReceiveTimeout=new TimeSpan(0,0,15);
			TCPBinding.ReceiveErrorHandling=ReceiveErrorHandling.Fault;

			try
			{
				Client=new CPlaybackFailuresProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Client.ThrowExceptionWithTransaction1("ThrowExceptionWithTransaction1");

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
			CPlaybackFailuresProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IPlaybackFailuresContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			// Nastavim Dead Letter Queue.
			TCPBinding.DeadLetterQueue=DeadLetterQueue.System;

			// Nastavim vlastnosti zotavenia.
			TCPBinding.ReceiveRetryCount=3;
			TCPBinding.MaxRetryCycles=6;
			TCPBinding.ReceiveTimeout=new TimeSpan(0,0,15);
			TCPBinding.ReceiveErrorHandling=ReceiveErrorHandling.Fault;

			try
			{
				Client=new CPlaybackFailuresProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Client.ThrowExceptionWithTransaction2("ThrowExceptionWithTransaction2");

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