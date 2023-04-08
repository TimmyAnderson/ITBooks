using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using ReliableSession_FaultEvent_Shared;
//-----------------------------------------------------------------------------------------------------------
namespace ReliableSession_FaultEvent_Client
{
//-----------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------
		private static void CO_Opened(object Sender, EventArgs E)
		{
			Console.WriteLine(string.Format("!!!!! PROXY received OPENED STATE - [{0}] !!!!!",DateTime.Now.ToLongTimeString()));
		}
//-----------------------------------------------------------------------------------------------------------
		private static void CO_Faulted(object Sender, EventArgs E)
		{
			Console.WriteLine(string.Format("!!!!! PROXY received FAULTED STATE - [{0}] !!!!!",DateTime.Now.ToLongTimeString()));
		}
//-----------------------------------------------------------------------------------------------------------
		private static void CO_Closed(object Sender, EventArgs E)
		{
			Console.WriteLine(string.Format("!!!!! PROXY received CLOSED STATE - [{0}] !!!!!",DateTime.Now.ToLongTimeString()));
		}
//-----------------------------------------------------------------------------------------------------------
		private static void WaitCallback(object State)
		{
			while(true)
			{
				Thread.Sleep(60*1000);
				Console.WriteLine(string.Format("Time [{0}] !",DateTime.Now.ToLongTimeString()));
			}
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			try
			{
				using (ChannelFactory<ISimpleTestInterface> CF=new ChannelFactory<ISimpleTestInterface>("Test"))
				{
					try
					{
						ISimpleTestInterface		STI=CF.CreateChannel();
						ICommunicationObject		CO=(ICommunicationObject) STI;

						CO.Opened+=new EventHandler(CO_Opened);
						CO.Faulted+=new EventHandler(CO_Faulted);
						CO.Closed+=new EventHandler(CO_Closed);

						ThreadPool.QueueUserWorkItem(WaitCallback);

						CO.Open();

						STI.ToUpper("Timmy");

						Console.WriteLine("Now wait MAX(receiveTimeout,inactivityTimeout) when RELIABLE SESSION is ENABLED, or 10 minutes when RELIABLE SESSION is DISABLED to check if FAULTED EVENT occurs. If RELIABLE SESSION is ENABLED, than FAULTED EVENT should COME, otherwise NOT !");
						Console.WriteLine();
						Console.WriteLine("Press any key to SEND another MESSAGE !");
						Console.ReadLine();

						STI.ToUpper("Timmy");

						CO.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------