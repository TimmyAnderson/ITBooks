using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultBindingHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			try
			{
				using(ChannelFactory<IService> CF=new ChannelFactory<IService>("Test1"))
				{
					IService			C=CF.CreateChannel();
					string				Ret=C.ToUpper("Timmy");

					Console.WriteLine(string.Format("Service returned: [{0}] !",Ret));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				using(ChannelFactory<IService> CF=new ChannelFactory<IService>("Test2"))
				{
					// Hodi EXCEPTION, lebo DEFAULT BINDING, ktory tento ENDPOINT POUZIJE NEMA ZAPNUTU SECURITY, ktoru SERVICE VYZADUJE.
					IService			C=CF.CreateChannel();
					string				Ret=C.ToUpper("Timmy");

					Console.WriteLine(string.Format("Service returned: [{0}] !",Ret));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------