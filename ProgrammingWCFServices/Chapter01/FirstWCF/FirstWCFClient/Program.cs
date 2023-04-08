using System;
using System.Collections.Generic;
using System.Text;
using FirstWCFClient.StringOperationsService;
using FirstWCFClient.MathOperationsService;
//-------------------------------------------------------------------------------------------------------
namespace FirstWCFClient
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

			string								Input="Hello Wolrd !";
			int									Input1=12;
			int									Input2=9;
			StringOperations1ContractClient		StringOperations1Contract=null;
			StringOperations2ContractClient		StringOperations2Contract=null;
			MathOperations1ContractClient		MathOperations1Contract=null;
			MathOperations2ContractClient		MathOperations2Contract=null;

			try
			{
				StringOperations1Contract=new StringOperations1ContractClient("NetTcpBinding_IStringOperations1Contract");
				StringOperations2Contract=new StringOperations2ContractClient("NetTcpBinding_IStringOperations2Contract");
				MathOperations1Contract=new MathOperations1ContractClient("NetTcpBinding_IMathOperations1Contract");
				MathOperations2Contract=new MathOperations2ContractClient("NetTcpBinding_IMathOperations2Contract");

				Console.WriteLine(String.Format("ConvertToLowerCase() - Input: {0}, Output: {1} !",Input,StringOperations1Contract.ConvertToLowerCase(Input)));
				Console.WriteLine(String.Format("ConvertToUpperCase() - Input: {0}, Output: {1} !",Input,StringOperations2Contract.ConvertToUpperCase(Input)));
				Console.WriteLine(String.Format("Add() - Input1: {0}, Input2: {1}, Output: {2} !",Input1,Input2,MathOperations1Contract.Add(Input1,Input2)));
				Console.WriteLine(String.Format("Subtract() - Input1: {0}, Input2: {1}, Output: {2} !",Input1,Input2,MathOperations2Contract.Subtract(Input1,Input2)));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (StringOperations1Contract!=null)
				{
					StringOperations1Contract.Close();
					StringOperations1Contract=null;
				}

				if (StringOperations2Contract!=null)
				{
					StringOperations2Contract.Close();
					StringOperations2Contract=null;
				}

				if (MathOperations1Contract!=null)
				{
					MathOperations1Contract.Close();
					MathOperations1Contract=null;
				}

				if (MathOperations2Contract!=null)
				{
					MathOperations2Contract.Close();
					MathOperations2Contract=null;
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