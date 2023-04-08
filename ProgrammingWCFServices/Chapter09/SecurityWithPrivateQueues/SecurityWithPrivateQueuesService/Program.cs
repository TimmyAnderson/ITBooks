using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace SecurityWithPrivateQueuesService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				string			QueueName=@".\private$\PrintService";

				if (MessageQueue.Exists(QueueName)==false)
					MessageQueue.Create(QueueName,true);

				using (ServiceHost SH=new ServiceHost(typeof(CPrintService)))
				{
					try
					{
						SH.Open();

						Console.WriteLine("Press any key to STOP !");
						Console.ReadLine();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------