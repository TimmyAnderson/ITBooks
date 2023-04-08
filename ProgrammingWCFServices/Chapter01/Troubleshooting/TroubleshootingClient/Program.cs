using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TroubleshootingHost;
//-------------------------------------------------------------------------------------------------------
namespace TroubleshootingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
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
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
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
		}
//-------------------------------------------------------------------------------------------------------
		// Kombinacia Test1() a Test2().
		private static void Test3()
		{
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
		}
//-------------------------------------------------------------------------------------------------------
		// !!! UMYSELNA CHYBA. Pokus o pripojenie IToLower na IToUpper ENDPOINT.
		private static void Test4()
		{
			try
			{
				using (ChannelFactory<IToLower> ChannelFactory=new ChannelFactory<IToLower>("ToLower"))
				{
					// Umyselne zmenim adresu aby ukazovala na IToUpper.
					ChannelFactory.Endpoint.Address=new EndpointAddress("net.tcp://localhost:8001/");

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
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------