using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InheritanceTwoServices_Client
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(SimpleService.SimpleTextOperationsClient SS=new InheritanceTwoServices_Client.SimpleService.SimpleTextOperationsClient("WSHttpBinding_ISimpleTextOperations"))
				{
					string			Ret=SS.ToUpper("Timmy");

					Console.WriteLine(string.Format("SimpleService - ToUpper(): [{0}] !",Ret));
				}

				using(ComplexService.ComplexTextContractClient CS=new InheritanceTwoServices_Client.ComplexService.ComplexTextContractClient("WSHttpBinding_IComplexTextContract"))
				{
					string			Ret1=CS.ToUpper("Timmy");

					Console.WriteLine(string.Format("ComplexService - ToUpper(): [{0}] !",Ret1));

					string			Ret2=CS.ToLower("Timmy");

					Console.WriteLine(string.Format("ComplexService - ToLower(): [{0}] !",Ret2));
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