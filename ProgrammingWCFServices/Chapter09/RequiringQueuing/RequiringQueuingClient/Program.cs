using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RequiringQueuingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RequiringQueuingClient
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

			CRequiringQueuingProxy						Client=null;
			string										QueueName;

			// !!! Kontrola MSMQ queue.
			QueueName=CMSMQHelper.VerifyQueue("IRequiringQueuingContract");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetMsmqBinding								TCPBinding=new NetMsmqBinding();

			// Pre private queue MUSI BYT VYPNUTA SECURITY.
			TCPBinding.Security.Mode=NetMsmqSecurityMode.None;

			try
			{
				Client=new CRequiringQueuingProxy(TCPBinding,QueueName);

				// Otvorim kanal aby som zamedzil synchronnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Client.PrintText("HELLO");

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