using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
using WCFSerializationFormatsHost;
//-------------------------------------------------------------------------------------------------------
namespace WCFSerializationFormatsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			string					Address="net.tcp://localhost:8000/Service";
			Binding					B=new NetTcpBinding();

			using(CProxy Proxy=new CProxy(B,Address))
			{
				try
				{
					Proxy.Open();

					CName1			Request=new CName1("Timmy","Anderson",12);
					CName1			Response=Proxy.Method1(Request);

					Console.WriteLine(string.Format("Response: [{0}] !",Response));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("EXCEPTION: {0} - {1} !",E.GetType(),E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			string					Address="net.tcp://localhost:8000/Service";
			Binding					B=new NetTcpBinding();

			using(CProxy Proxy=new CProxy(B,Address))
			{
				try
				{
					Proxy.Open();

					CName2			Request=new CName2("Timmy","Anderson",12);
					CName2			Response=Proxy.Method2(Request);

					Console.WriteLine(string.Format("Response: [{0}] !",Response));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("EXCEPTION: {0} - {1} !",E.GetType(),E.Message));
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
				//Test1();
				Test2();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} - {1} !",E.GetType(),E.Message));
			}

            Console.WriteLine("Press any key to EXIT !");
            Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------