using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace IncludeExceptionDetailInFaultsHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// IncludeExceptionDetailInFaults je na FALSE.
		private static void Test1()
		{
			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CFaultTestService)))
				{
					IncludeExceptionDetailInFaults		SDB=SH.Description.Behaviors.Find<ServiceDebugBehavior>();

					SDB.IncludeExceptionDetailInFaults=false;

					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// IncludeExceptionDetailInFaults je na TRUE.
		private static void Test2()
		{
			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CFaultTestService)))
				{
					ServiceDebugBehavior		SDB=SH.Description.Behaviors.Find<ServiceDebugBehavior>();

					SDB.IncludeExceptionDetailInFaults=true;

					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
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
			Console.Title="HOST";

			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------