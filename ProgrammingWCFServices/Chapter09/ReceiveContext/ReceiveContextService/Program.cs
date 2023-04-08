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
namespace ReceiveContextService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			if (MessageQueue.Exists(@".\private$\ReceiveContext")==false)
			{
				MessageQueue.Create(@".\private$\ReceiveContext",true);
			}

			try
			{
				using(ServiceHost SH1=new ServiceHost(typeof(CReceiveContextContract1)))
				{
					using(ServiceHost SH2=new ServiceHost(typeof(CReceiveContextContract2)))
					{
						try
						{
							SH1.Open();

							Console.WriteLine("SERVICE 1 OPENED !");

							SH2.Open();

							Console.WriteLine("SERVICE 2 OPENED !");

							Console.WriteLine("Press any key to STOP !");
							Console.ReadLine();
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------