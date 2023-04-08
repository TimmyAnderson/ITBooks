using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Test
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CTestService)))
				{
					SH.Open();

					ChannelFactory<ITestService>	ChannelFactory=new ChannelFactory<ITestService>("Proxy");
					ITestService					Channel=ChannelFactory.CreateChannel();
					ICommunicationObject			CommunicationObject=(ICommunicationObject) Channel;

					try
					{
						Console.WriteLine("Before NoException() !");

						// Just to be sure that CLIENT and SERVICE are connected.
						Channel.NoException();

						Console.WriteLine("Before ThrowException() !");

						// Operation throws EXCEPTION.
						Channel.ThrowException();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("ThrowException() - EXCEPTION: [{0}] !",E));
					}

					try
					{
						Console.WriteLine("Before CommunicationObject.Close() !");

						// !!!!! Here CPU goes to 100 percent for 1 minute until proxy is closed.
						CommunicationObject.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("Close() - EXCEPTION: [{0}] !",E));
					}

					// !!!!! Here CPU returns back to normal 0 percent.

					Console.WriteLine("Before ChannelFactory.Close() !");

					ChannelFactory.Close();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
				}
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