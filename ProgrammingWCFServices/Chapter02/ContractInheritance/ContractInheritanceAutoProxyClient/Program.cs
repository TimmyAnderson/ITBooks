using System;
using System.Collections.Generic;
using System.Text;
using ContractInheritanceAutoProxyClient.CalculatorProxy;
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceAutoProxyClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			ScientificCalculatorContractClient	ScientificCalculatorContract=null;

			try
			{
				ScientificCalculatorContract=new ScientificCalculatorContractClient("NetTcpBinding_IScientificCalculatorContract");

				Console.WriteLine(String.Format("Add(): {0} !",ScientificCalculatorContract.Add(5,13)));
				Console.WriteLine(String.Format("Multiply(): {0} !",ScientificCalculatorContract.Multiply(5,13)));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (ScientificCalculatorContract!=null)
				{
					ScientificCalculatorContract.Close();
					ScientificCalculatorContract=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------