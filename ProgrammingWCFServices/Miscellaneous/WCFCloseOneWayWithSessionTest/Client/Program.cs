using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.Threading;
using WCFCloseOneWayWithSessionTest;
//-------------------------------------------------------------------------------------------------------
namespace Client
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

			try
			{
				ChannelFactory<ITestService>	ChannelFactory=new ChannelFactory<ITestService>("Proxy");
				ITestService					Channel=ChannelFactory.CreateChannel();
				ICommunicationObject			CommunicationObject=(ICommunicationObject) Channel;

				try
				{
					Console.WriteLine("Before Open() !");

					CommunicationObject.Open();

					Console.WriteLine("Before ThrowException() !");

					Channel.ThrowException();
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("ThrowException() - EXCEPTION: [{0}] !",E));
				}

				try
				{
					Console.WriteLine("Before CommunicationObject.Close() !");

					CommunicationObject.Close();
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Close() - EXCEPTION: [{0}] !",E));
				}

				try
				{
					Console.WriteLine("Before ChannelFactory.Close() !");

					ChannelFactory.Close();
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Close() - EXCEPTION: [{0}] !",E));
				}

				Console.WriteLine("Press any key to STOP !");
				Console.ReadLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------