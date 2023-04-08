using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using ContextBindingsSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ContextBindingsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(ChannelFactory<IToUpperContract> CF=new ChannelFactory<IToUpperContract>("Proxy"))
				{
					// Musim pretypovat na IClientChannel, aby som mal pristup ku GetProperty<>().
					using(IClientChannel Channel=(IClientChannel) CF.CreateChannel())
					{
						IContextManager				CM=Channel.GetProperty<IContextManager>();
						IDictionary<string,string>	Context=CM.GetContext();

						Context.Add("FullName","Timmy Anderson");
						
						CM.SetContext(Context);

						Channel.Open();

						IToUpperContract	Contract=(IToUpperContract) Channel;

						Contract.ToUpper("Some string !");

						Channel.Close();
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

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------