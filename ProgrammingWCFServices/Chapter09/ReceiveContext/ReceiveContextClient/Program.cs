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
using ReceiveContextService;
//-------------------------------------------------------------------------------------------------------
namespace ReceiveContextClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(ChannelFactory<IReceiveContextContract> CF=new ChannelFactory<IReceiveContextContract>("MS"))
				{
					using(IDisposable D=(CF.CreateChannel() as IDisposable))
					{
						IReceiveContextContract		Proxy=(IReceiveContextContract) D;

						try
						{
							for (int i=0;i<20;i++)
							{
								Proxy.PrintMessage(string.Format("{0}. Timmy Anderson",i+1));
								Console.WriteLine("MSMQ MESSAGE SENT to QUEUE !");
							}
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