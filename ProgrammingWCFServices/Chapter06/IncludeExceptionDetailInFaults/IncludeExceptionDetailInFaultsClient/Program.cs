using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using IncludeExceptionDetailInFaultsHost;
//-------------------------------------------------------------------------------------------------------
namespace IncludeExceptionDetailInFaultsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test_TRANSPORT_SESSION_ThrowNonFaultException()
		{
			try
			{
				using(ChannelFactory<IFaultTestService> CF=new ChannelFactory<IFaultTestService>("TransportSessionEnabled"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IFaultTestService		Proxy=Disp as IFaultTestService;

						try
						{
							Proxy.ThrowNonFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractStandardException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractStandardException() - CHANNEL HAS FAILED !");
						}
					}
				}
			}
			catch
			{
				// Ignorujem.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test_TRANSPORT_SESSION_ThrowFaultException()
		{
			try
			{
				using(ChannelFactory<IFaultTestService> CF=new ChannelFactory<IFaultTestService>("TransportSessionEnabled"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IFaultTestService		Proxy=Disp as IFaultTestService;

						try
						{
							Proxy.ThrowFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractFaultException() - CHANNEL HAS FAILED !");
						}
					}
				}
			}
			catch
			{
				// Ignorujem.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test_NO_TRANSPORT_SESSION_ThrowNonFaultException()
		{
			try
			{
				using(ChannelFactory<IFaultTestService> CF=new ChannelFactory<IFaultTestService>("TransportSessionDisabled"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IFaultTestService		Proxy=Disp as IFaultTestService;

						try
						{
							Proxy.ThrowNonFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractStandardException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractStandardException() - CHANNEL HAS FAILED !");
						}
					}
				}
			}
			catch
			{
				// Ignorujem.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test_NO_TRANSPORT_SESSION_ThrowFaultException()
		{
			try
			{
				using(ChannelFactory<IFaultTestService> CF=new ChannelFactory<IFaultTestService>("TransportSessionDisabled"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IFaultTestService		Proxy=Disp as IFaultTestService;

						try
						{
							Proxy.ThrowFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractFaultException() - CHANNEL HAS FAILED !");
						}
					}
				}
			}
			catch
			{
				// Ignorujem.
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

			Test_TRANSPORT_SESSION_ThrowNonFaultException();
			//Test_TRANSPORT_SESSION_ThrowFaultException();

			//Test_NO_TRANSPORT_SESSION_ThrowNonFaultException();
			//Test_NO_TRANSPORT_SESSION_ThrowFaultException();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------