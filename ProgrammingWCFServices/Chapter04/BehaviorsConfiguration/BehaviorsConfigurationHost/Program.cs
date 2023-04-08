using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace BehaviorsConfigurationHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			try
			{
				using(ServiceHost HostByAttribute=new ServiceHost(typeof(CConfiguredByAttribute)))
				{
					using(ServiceHost HostByCode=new ServiceHost(typeof(CConfiguredByCode)))
					{
						ServiceDebugBehavior	SB;

						SB=(ServiceDebugBehavior) HostByCode.Description.Behaviors.Where(I => (I.GetType()==typeof(ServiceDebugBehavior))).FirstOrDefault();

						if (SB==null)
						{
							SB=new ServiceDebugBehavior();
							HostByCode.Description.Behaviors.Add(SB);
						}

						SB.IncludeExceptionDetailInFaults=true;

						using(ServiceHost HostByConfigFile=new ServiceHost(typeof(CConfiguredByConfigFile)))
						{
							HostByConfigFile.Open();
							HostByCode.Open();
							HostByAttribute.Open();

							Console.WriteLine("Press any key to STOP !");
							Console.ReadLine();
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------