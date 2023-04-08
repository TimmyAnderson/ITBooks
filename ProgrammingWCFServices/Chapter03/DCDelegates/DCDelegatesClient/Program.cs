using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using DCDelegatesSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCDelegatesClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("Client"))
			{
				using(IDisposable D=(IDisposable) CF.CreateChannel())
				{
					ITestService							Proxy=(ITestService) D;

					Proxy.ConnectionTest();

					DMyDelegate								Delegate=Proxy.ReceiveEmptyDelegate();

					if (Delegate!=null)
					{
						Delegate("Timmy Anderson");
					}
					else
					{
						Console.WriteLine("DELEGATE was EMPTY !");
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("Client"))
			{
				using(IDisposable D=(IDisposable) CF.CreateChannel())
				{
					ITestService							Proxy=(ITestService) D;

					Proxy.ConnectionTest();

					DMyDelegate								Delegate=Proxy.ReceiveDelegateToStaticMethod();

					if (Delegate!=null)
					{
						Delegate("Timmy Anderson");
					}
					else
					{
						Console.WriteLine("DELEGATE was EMPTY !");
					}
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("Client"))
			{
				using(IDisposable D=(IDisposable) CF.CreateChannel())
				{
					ITestService							Proxy=(ITestService) D;

					Proxy.ConnectionTest();

					DMyDelegate								Delegate=Proxy.ReceiveDelegateToInstanceMethod();

					if (Delegate!=null)
					{
						Delegate("Timmy Anderson");
					}
					else
					{
						Console.WriteLine("DELEGATE was EMPTY !");
					}
				}
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

			try
			{
				Test1();
				//Test2();
				//Test3();
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