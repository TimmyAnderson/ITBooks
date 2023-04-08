using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using CustomHeadersInConfigHost;
//-------------------------------------------------------------------------------------------------------
namespace CustomHeadersInConfigClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void TestEndpointHeaders()
		{
			try
			{
				using(ChannelFactory<IService> CF=new ChannelFactory<IService>("SE"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							IService				Service=Disp as IService;
							string					Ret=Service.ToUpperEndpointHeader("Timmy");

							Console.WriteLine(string.Format("Response: [{0}] !", Ret));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestAddressHeaders()
		{
			try
			{
				using(ChannelFactory<IService> CF=new ChannelFactory<IService>("SE"))
				{
					// Vytvorim AddressHeader.
					AddressHeader		AH=AddressHeader.CreateAddressHeader("MyAddressHeader","MyNamespace","Timmy");
					// Ulozim ho do EndpointAddress.
					EndpointAddress		EA=new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),AH);

					using(IDisposable Disp=(CF.CreateChannel(EA) as IDisposable))
					{
						try
						{
							IService				Service=Disp as IService;
							string					Ret=Service.ToUpperAddressHeader("Timmy");

							Console.WriteLine(string.Format("Response: [{0}] !", Ret));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
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

			//TestEndpointHeaders();
			TestAddressHeaders();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------