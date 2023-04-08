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
namespace CustomDeadLetterQueueClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			// !!!!! Voci tomuto Clientovi NIE JE POSTAVENY ZIADNY SERVICE, ABY SA MESSAGE HODILA DO DEAD LETTER QUEUE.

			// TENTO CLIENT SLUZI IBA NA VYGENEROVANIE MSMQ MESSAGE, KTORA po 10 SEKUNDACH skonci v DEAD LETTER QUEUE.

			if (MessageQueue.Exists(@".\private$\CustomDLQTestQueue")==false)
			{
				MessageQueue.Create(@".\private$\CustomDLQTestQueue",true);
			}

			if (MessageQueue.Exists(@".\private$\CustomDLQ")==false)
			{
				MessageQueue.Create(@".\private$\CustomDLQ",true);
			}

			try
			{
				using(ChannelFactory<ICustomDLQTest> CF=new ChannelFactory<ICustomDLQTest>("MS"))
				{
					using(IDisposable D=(CF.CreateChannel() as IDisposable))
					{
						ICustomDLQTest		Proxy=(ICustomDLQTest) D;

						try
						{
							Proxy.SomeMethod1("Timmy Anderson");
							Console.WriteLine("MSMQ MESSAGE SENT to QUEUE and WILL BE RESEND TO DEAD LETTER QUEUE IN 10 SECONDS !");

							Proxy.SomeMethod2("Jenny Thompson");
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