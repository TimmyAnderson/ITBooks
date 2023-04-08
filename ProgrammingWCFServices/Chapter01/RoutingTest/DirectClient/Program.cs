using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using RoutingTestService1;
using RoutingTestService2;
//-------------------------------------------------------------------------------------------------------
namespace DirectClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="DIRECT CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			try
			{
				using (ChannelFactory<IToUpper> ChannelFactory=new ChannelFactory<IToUpper>("ToUpper"))
				{
					ChannelFactory.Open();

					using(IDisposable D=(IDisposable) ChannelFactory.CreateChannel())
					{
						IToUpper				Proxy=(IToUpper) D;
						string					Result=Proxy.ToUpper("Timmy");

						Console.WriteLine(string.Format("Result: [{0}] !",Result));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			try
			{
				using (ChannelFactory<IToLower> ChannelFactory=new ChannelFactory<IToLower>("ToLower"))
				{
					ChannelFactory.Open();

					using(IDisposable D=(IDisposable) ChannelFactory.CreateChannel())
					{
						IToLower				Proxy=(IToLower) D;
						string					Result=Proxy.ToLower("Timmy");

						Console.WriteLine(string.Format("Result: [{0}] !",Result));
					}
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