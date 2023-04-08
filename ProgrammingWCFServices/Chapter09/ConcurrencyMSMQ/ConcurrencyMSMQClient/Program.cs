using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThread(object Param)
		{
			CPair<CConcurrencyMSMQProxy,string>		Pair=(CPair<CConcurrencyMSMQProxy,string>) Param;

			Console.WriteLine(string.Format("ExecutionThread: {0} 1 !",Pair.Second));
			
			Pair.First.PrintText(Pair.Second);

			Console.WriteLine(string.Format("ExecutionThread: {0} 2 !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Test()
		{
			CConcurrencyMSMQProxy				Client=null;
			string								QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IConcurrencyMSMQContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding										TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CConcurrencyMSMQProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Thread										T1=new Thread(Program.ExecutionThread);
				Thread										T2=new Thread(Program.ExecutionThread);
				CPair<CConcurrencyMSMQProxy,string>			P1=new CPair<CConcurrencyMSMQProxy,string>(Client,"HELLO 1");
				CPair<CConcurrencyMSMQProxy,string>			P2=new CPair<CConcurrencyMSMQProxy,string>(Client,"HELLO 2");

				// Pri testovani treba experimentovant s nastavenim ConcurrencyMode raz na Sigle a raz na Multiple.

				T1.Start(P1);
				T2.Start(P2);

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

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------