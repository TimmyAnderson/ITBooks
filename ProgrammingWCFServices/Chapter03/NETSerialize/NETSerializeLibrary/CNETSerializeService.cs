using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CNETSerializeService : INETSerializeContract
	{
//-------------------------------------------------------------------------------------------------------
		public CNETSerializeService()
		{
			Console.WriteLine("CNETSerializeService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSimpleName GetSimpleName()
		{
			Console.WriteLine("CNETSerializeService.GetSimpleName() called !");
			return(new CSimpleName("Timmy","Anderson"));
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintSimpleName(CSimpleName SimpleName)
		{
			Console.WriteLine("CNETSerializeService.PrintSimpleName() called !");
			Console.WriteLine(SimpleName.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress GetNameWithAddress()
		{
			Console.WriteLine("CNETSerializeService.NameWithAddress() called !");
			return(new CNameWithAddress("Timmy","Anderson","Some street",8,"Minneapolis"));
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintNameWithAddress(CNameWithAddress NameWithAddress)
		{
			Console.WriteLine("CNETSerializeService.NameWithAddress() called !");
			Console.WriteLine(NameWithAddress.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------