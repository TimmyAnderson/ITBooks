using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using BehaviorsConfigurationHost;
//-------------------------------------------------------------------------------------------------------
namespace BehaviorsConfigurationClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				ChannelFactory<IConfiguredByAttribute>	CFByAttribute=new ChannelFactory<IConfiguredByAttribute>("ClientByAttribute");
				ChannelFactory<IConfiguredByCode>		CFByCode=new ChannelFactory<IConfiguredByCode>("ClientByCode");
				ChannelFactory<IConfiguredByConfigFile>	CFByConfigFile=new ChannelFactory<IConfiguredByConfigFile>("ClientByConfigFile");

				try
				{
					using(IDisposable ByAttribute=(CFByAttribute.CreateChannel() as IDisposable))
					{
						try
						{
							IConfiguredByAttribute			Proxy=ByAttribute as IConfiguredByAttribute;

							Proxy.ThrowException("BY ATTRIBUTE");
						}
						catch(Exception E)
						{
							if (E.Message=="BY ATTRIBUTE")
								Console.WriteLine("BY ATTRIBUTE - IncludeExceptionDetailInFaults is set to TRUE !");
							else
								Console.WriteLine("BY ATTRIBUTE - IncludeExceptionDetailInFaults is set to FALSE !");
						}
					}
				}
				catch
				{
				}

				try
				{
					using(IDisposable ByCode=(CFByCode.CreateChannel() as IDisposable))
					{
						try
						{
							IConfiguredByCode				Proxy=ByCode as IConfiguredByCode;

							Proxy.ThrowException("BY CODE");
						}
						catch(Exception E)
						{
							if (E.Message=="BY CODE")
								Console.WriteLine("BY CODE - IncludeExceptionDetailInFaults is set to TRUE !");
							else
								Console.WriteLine("BY CODE - IncludeExceptionDetailInFaults is set to FALSE !");
						}
					}
				}
				catch
				{
				}

				try
				{
					using(IDisposable ByConfigFile=(CFByConfigFile.CreateChannel() as IDisposable))
					{
						try
						{
							IConfiguredByConfigFile			Proxy=ByConfigFile as IConfiguredByConfigFile;

							Proxy.ThrowException("BY CONFIG FILE");
						}
						catch(Exception E)
						{
							if (E.Message=="BY CONFIG FILE")
								Console.WriteLine("BY CONFIG FILE - IncludeExceptionDetailInFaults is set to TRUE !");
							else
								Console.WriteLine("BY CONFIG FILE - IncludeExceptionDetailInFaults is set to FALSE !");
						}
					}
				}
				catch
				{
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

			Test();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------