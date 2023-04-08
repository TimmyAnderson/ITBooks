using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Messaging;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace TestPoisonMessageService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			if (MessageQueue.Exists(@".\private$\PoisonTest")==false)
			{
				MessageQueue.Create(@".\private$\PoisonTest",true);
			}

			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CPoisonMessageService)))
				{
					try
					{
						SH.Open();

						Console.WriteLine("Press any key to STOP !");
						Console.ReadLine();
					}
					catch(Exception E)
					{
						Console.WriteLine("EXCEPTION: [{0}] !",E.Message);
					}
				}
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