using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using ChannelFaultingHost;
//-------------------------------------------------------------------------------------------------------
namespace ChannelFaultingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test_TRANSPORT_SESSION_NoFaultContractStandardException()
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
							Proxy.NoFaultContractStandardException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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
		private static void Test_TRANSPORT_SESSION_NoFaultContractFaultException()
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
							Proxy.NoFaultContractFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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
		private static void Test_TRANSPORT_SESSION_NoFaultContractTypedFaultException()
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
							Proxy.NoFaultContractTypedFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractTypedFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractTypedFaultException() - CHANNEL HAS FAILED !");
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
		private static void Test_TRANSPORT_SESSION_WithFaultContractStandardException()
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
							Proxy.WithFaultContractStandardException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractStandardException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractStandardException() - CHANNEL HAS FAILED !");
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
		private static void Test_TRANSPORT_SESSION_WithFaultContractFaultException()
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
							Proxy.WithFaultContractFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractFaultException() - CHANNEL HAS FAILED !");
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
		private static void Test_TRANSPORT_SESSION_WithFaultContractTypedFaultException()
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
							Proxy.WithFaultContractTypedFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractTypedFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractTypedFaultException() - CHANNEL HAS FAILED !");
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
		private static void Test_NO_TRANSPORT_SESSION_NoFaultContractStandardException()
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
							Proxy.NoFaultContractStandardException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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
		private static void Test_NO_TRANSPORT_SESSION_NoFaultContractFaultException()
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
							Proxy.NoFaultContractFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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
		private static void Test_NO_TRANSPORT_SESSION_NoFaultContractTypedFaultException()
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
							Proxy.NoFaultContractTypedFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("NoFaultContractTypedFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("NoFaultContractTypedFaultException() - CHANNEL HAS FAILED !");
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
		private static void Test_NO_TRANSPORT_SESSION_WithFaultContractStandardException()
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
							Proxy.WithFaultContractStandardException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractStandardException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractStandardException() - CHANNEL HAS FAILED !");
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
		private static void Test_NO_TRANSPORT_SESSION_WithFaultContractFaultException()
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
							Proxy.WithFaultContractFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractFaultException() - CHANNEL HAS FAILED !");
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
		private static void Test_NO_TRANSPORT_SESSION_WithFaultContractTypedFaultException()
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
							Proxy.WithFaultContractTypedFaultException();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}

						try
						{
							Proxy.Dummy();

							Console.WriteLine("WithFaultContractTypedFaultException() - CHANNEL IS OK !");
						}
						catch
						{
							Console.WriteLine("WithFaultContractTypedFaultException() - CHANNEL HAS FAILED !");
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

			//Test_TRANSPORT_SESSION_NoFaultContractStandardException();
			//Test_TRANSPORT_SESSION_NoFaultContractFaultException();
			//Test_TRANSPORT_SESSION_NoFaultContractTypedFaultException();
			//Test_TRANSPORT_SESSION_WithFaultContractStandardException();
			//Test_TRANSPORT_SESSION_WithFaultContractFaultException();
			//Test_TRANSPORT_SESSION_WithFaultContractTypedFaultException();

			//Test_NO_TRANSPORT_SESSION_NoFaultContractStandardException();
			//Test_NO_TRANSPORT_SESSION_NoFaultContractFaultException();
			//Test_NO_TRANSPORT_SESSION_NoFaultContractTypedFaultException();
			Test_NO_TRANSPORT_SESSION_WithFaultContractStandardException();
			//Test_NO_TRANSPORT_SESSION_WithFaultContractFaultException();
			//Test_NO_TRANSPORT_SESSION_WithFaultContractTypedFaultException();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------