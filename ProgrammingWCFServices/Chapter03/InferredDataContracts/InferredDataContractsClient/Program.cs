using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using InferredDataContractsClient.MyNamespace;
//-------------------------------------------------------------------------------------------------------
namespace InferredDataContractsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(FullNameServiceClient Proxy=new FullNameServiceClient())
				{
					Proxy.Open();

					Console.WriteLine("Proxy OPENED !");

					CInferredFullName			FN=Proxy.GetFullName("Timmy","Anderson",12);

					Console.WriteLine(string.Format("Name: {0} {1}, Age: {2} !",FN.FirstName,FN.LastName,FN.Age));
				}

				using(FullNameServiceClient Proxy=new FullNameServiceClient())
				{
					Proxy.Open();

					Console.WriteLine("Proxy OPENED !");

					CInferredFullNameDerived	FN=Proxy.GetFullNameDerived("Timmy","Anderson",12,"Some INFO");

					Console.WriteLine(string.Format("Name: {0} {1}, Age: {2}, SomeInfo: {3} !",FN.FirstName,FN.LastName,FN.Age,FN.SomeInfo));
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

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------