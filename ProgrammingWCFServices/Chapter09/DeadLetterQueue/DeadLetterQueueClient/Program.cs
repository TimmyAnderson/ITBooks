using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace DeadLetterQueueClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			// !!!!! Voci tomuto Clientovi NIE JE POSTAVENY ZIADNY SERVICE, ABY SA MESSAGE HODILA DO DEAD LETTER QUEUE.

			// TENTO CLIENT SLUZI IBA NA VYGENEROVANIE MSMQ MESSAGE, KTORA po 10 SEKUNDACH skonci v DEAD LETTER QUEUE.

			if (MessageQueue.Exists(@".\private$\DLQTestQueue")==false)
				MessageQueue.Create(@".\private$\DLQTestQueue",false);

			try
			{
				using(ChannelFactory<IDLQTest> CF=new ChannelFactory<IDLQTest>("MS"))
				{
					using(IDisposable D=(CF.CreateChannel() as IDisposable))
					{
						IDLQTest		Proxy=(IDLQTest) D;

						try
						{
							Proxy.SomeMethod("Timmy Anderson");
							Console.WriteLine("MSMQ MESSAGE SENT to QUEUE and WILL BE RESEND TO DEAD LETTER QUEUE IN 10 SECONDS !");
						}
						catch(Exception E)
						{
							Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
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

			try
			{
				Test();
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------