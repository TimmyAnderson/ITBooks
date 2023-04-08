using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace FirstWCFLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CStringOperationsService : IStringOperations1Contract, IStringOperations2Contract
	{
//-------------------------------------------------------------------------------------------------------
		public CStringOperationsService()
		{
			Console.WriteLine("CStringOperationsService.CStringOperationsService() has been hit !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string ConvertToLowerCase(string Input)
		{
			Console.WriteLine("CStringOperationsService.ConvertToLowerCase() has been hit !");
			return(Input.ToLower());
		}
//-------------------------------------------------------------------------------------------------------
		public string ConvertToUpperCase(string Input)
		{
			Console.WriteLine("CStringOperationsService.ConvertToUpperCase() has been hit !");
			return(Input.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------