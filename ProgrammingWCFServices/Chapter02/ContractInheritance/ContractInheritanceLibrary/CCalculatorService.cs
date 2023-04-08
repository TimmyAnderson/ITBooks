using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
// V tomto pripade som sa rozhodol, ze obe contracts budu implementovane jednou triedou.
// Ale mohol by som definovat aj 2 triedy, kde by kazda implementovala svoj contract.
// To co je lepsie zavisi od toho ako mi to vyhovuje z hladiska implementacie. Obe moznosti su mozne.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CCalculatorService : IScientificCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCalculatorService()
		{
			Console.WriteLine("CCalculatorService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int Add(int Param1, int Param2)
		{
			Console.WriteLine("CCalculatorService.Add() called !");
			return(Param1+Param2);
		}
//-------------------------------------------------------------------------------------------------------
		public int Multiply(int Param1, int Param2)
		{
			Console.WriteLine("CCalculatorService.Multiply() called !");
			return(Param1*Param2);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------