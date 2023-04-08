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
using TestPoisonMessageService;
//-------------------------------------------------------------------------------------------------------
namespace TestPoisonMessageClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			if (MessageQueue.Exists(@".\private$\PoisonTest")==false)
			{
				MessageQueue.Create(@".\private$\PoisonTest",true);
			}

			try
			{
				using(ChannelFactory<IPoisonMessageContract> CF=new ChannelFactory<IPoisonMessageContract>("MS"))
				{
					using(IDisposable D=(CF.CreateChannel() as IDisposable))
					{
						IPoisonMessageContract		Proxy=(IPoisonMessageContract) D;

						try
						{
							Proxy.ThrowException("Timmy Anderson");
							Console.WriteLine("MSMQ MESSAGE SENT to QUEUE !");
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