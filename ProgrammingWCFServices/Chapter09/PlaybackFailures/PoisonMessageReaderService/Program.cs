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
namespace PoisonMessageReaderService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST - POISON READER";

			try
			{
				// READER, ktory cita POISON MESSAGE QUEUE musi mat TEN ISTY CONTRACT, ako POVODNY SERVICE.
				using(ServiceHost SH=new ServiceHost(typeof(CPoisonMessageProcessorService)))
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