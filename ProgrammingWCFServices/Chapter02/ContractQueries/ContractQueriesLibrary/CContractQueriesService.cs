using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ContractQueriesLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CContractQueriesService : IAddContract, IMultipleContract
	{
//-------------------------------------------------------------------------------------------------------
		public CContractQueriesService()
		{
			Console.WriteLine("CContractQueriesService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int Add(int Param1, int Param2)
		{
			Console.WriteLine("CContractQueriesService.Add() called !");
			return(Param1+Param2);
		}
//-------------------------------------------------------------------------------------------------------
		public int Multiple(int Param1, int Param2)
		{
			Console.WriteLine("CContractQueriesService.Multiple() called !");
			return(Param1*Param2);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------