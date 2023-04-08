using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using MyDataContractResolver;
using DataContractResolversService;
using SharedLibrary1;
using SharedLibrary2;
using SharedLibrary3;
//-------------------------------------------------------------------------------------------------------
namespace DataContractResolversClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("Client"))
			{
				CMyDataContractResolver						Resolver=new CMyDataContractResolver(true,false);

				// Pridam Contract BH.
				CMyDataContractResolverContractBehavior		DCRCB=new CMyDataContractResolverContractBehavior(Resolver);

				CF.Endpoint.Contract.Behaviors.Add(DCRCB);

				using(IDisposable D=(IDisposable) CF.CreateChannel())
				{
					ITestService							Proxy=(ITestService) D;

					Proxy.ConnectionTest();

					// RECEIVE NON-GENERIC DATA from SERVICE.

					CNameBase								Name1=Proxy.ReceiveName(1);

					Console.WriteLine(string.Format("Name1: [{0}] !",Name1));

					CNameBase								Name2=Proxy.ReceiveName(2);

					Console.WriteLine(string.Format("Name2: [{0}] !",Name2));

					CNameBase								Name3=Proxy.ReceiveName(3);

					Console.WriteLine(string.Format("Name3: [{0}] !",Name3));

					// RECEIVE GENERIC DATA from SERVICE.

					CNameBaseGenerics<string>				GenericName1=Proxy.ReceiveGenericsName(1);

					Console.WriteLine(string.Format("GenericName1: [{0}] !",GenericName1));

					CNameBaseGenerics<string>				GenericName2=Proxy.ReceiveGenericsName(2);

					Console.WriteLine(string.Format("GenericName2: [{0}] !",GenericName2));

					CNameBaseGenerics<string>				GenericName3=Proxy.ReceiveGenericsName(3);

					Console.WriteLine(string.Format("GenericName3: [{0}] !",GenericName3));

					// SEND NON-GENERIC DATA to SERVICE.

					CNameBase								SendName1=new CNameBase("Timmy");

					Proxy.SendName(SendName1);
					Console.WriteLine(string.Format("Name [{0}] SENT to SERVICE !",SendName1));

					CName									SendName2=new CName("Timmy","Anderson");

					Proxy.SendName(SendName2);
					Console.WriteLine(string.Format("Name [{0}] SENT to SERVICE !",SendName2));

					CNameInfo								SendName3=new CNameInfo("Timmy","Anderson",12);

					Proxy.SendName(SendName3);
					Console.WriteLine(string.Format("Name [{0}] SENT to SERVICE !",SendName3));

					// SEND GENERIC DATA to SERVICE.

					CNameBaseGenerics<string>				SendGenericName1=new CNameBaseGenerics<string>("Timmy");

					Proxy.SendGenericsName(SendGenericName1);
					Console.WriteLine(string.Format("Generic name [{0}] SENT to SERVICE !",SendGenericName1));

					CNameGenerics<string,string>			SendGenericName2=new CNameGenerics<string,string>("Timmy","Anderson");

					Proxy.SendGenericsName(SendGenericName2);
					Console.WriteLine(string.Format("Generic name [{0}] SENT to SERVICE !",SendGenericName2));

					CNameInfoGenerics<string,string,int>	SendGenericName3=new CNameInfoGenerics<string,string,int>("Timmy","Anderson",12);

					Proxy.SendGenericsName(SendGenericName3);
					Console.WriteLine(string.Format("Generic name [{0}] SENT to SERVICE !",SendGenericName3));
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
				Test();
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