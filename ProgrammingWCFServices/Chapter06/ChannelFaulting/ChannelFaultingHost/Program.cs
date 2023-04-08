using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace ChannelFaultingHost
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
				using(ServiceHost SH=new ServiceHost(typeof(CFaultTestService)))
				{
					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------