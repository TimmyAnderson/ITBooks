using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TCPIBBindingStressTestHost;
//-------------------------------------------------------------------------------------------------------
namespace TCPIBBindingStressTestClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test(object Param)
		{
			try
			{
				string									ProxyName=Param.ToString();

				for(int i=0;i<1000000;i++)
				{
					ChannelFactory<IToUpperService>		CF;
					IToUpperService						Proxy;
					ICommunicationObject				CO;
					IDisposable							D;

					CF=new ChannelFactory<IToUpperService>(ProxyName);
					CF.Open();

					Proxy=CF.CreateChannel();

					CO=Proxy as ICommunicationObject;
					D=Proxy as IDisposable;

					CO.Open();

					using(D)
					{
						string				Ret=Proxy.ToUpper("Timmy");

						//Console.WriteLine(string.Format("Value: [{0}] !",Ret));

						if ((i % 100)==0)
						{
							Console.WriteLine(string.Format("{0} - [{1}] !",Param,i));
						}

						CO.Close();
					}

					CF.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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

			ThreadPool.QueueUserWorkItem(Test,"Proxy1");

			ThreadPool.QueueUserWorkItem(Test,"Proxy2");

			ThreadPool.QueueUserWorkItem(Test,"Proxy3");

			ThreadPool.QueueUserWorkItem(Test,"Proxy4");

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------