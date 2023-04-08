using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DynamicEndpointTestHost;
//-------------------------------------------------------------------------------------------------------
namespace DynamicEndpointTestClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Pripaja sa klasickym sposobom cez PREDDEFINOVANU adresu.
		private static void StaticEndpoint()
		{
			try
			{
				using (ChannelFactory<IToUpper> ChannelFactory=new ChannelFactory<IToUpper>("StaticEndpoint"))
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
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Pripaja sa DYNAMICKY cez DISCOVERY.
		private static void DynamicEndpoint()
		{
			try
			{
				using (ChannelFactory<IToUpper> ChannelFactory=new ChannelFactory<IToUpper>("DynamicEndpoint"))
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
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//StaticEndpoint();
			DynamicEndpoint();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------