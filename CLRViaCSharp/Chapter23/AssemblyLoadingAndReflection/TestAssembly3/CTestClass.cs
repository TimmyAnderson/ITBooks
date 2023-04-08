using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace TestAssembly3
{
//-------------------------------------------------------------------------------------------------------
	// Tato ASSEMBLY bude NAKOPIROVANA do adresara ASSEMLIES v SOLUTION ADRESARI.
	// !!!!! ASSEMBLY je ZAVISLA na TestAssembly1 a TestAssembly2.
	public static class CTestClass
	{
//-------------------------------------------------------------------------------------------------------
		public static void SomeMethod()
		{
			Console.WriteLine("HELLO TestAssembly 3 !");

			// Zavolam metody ZAVISLYCH ASSEMBLIES.
			TestAssembly1.CTestClass.SomeMethod();
			TestAssembly2.CTestClass.SomeMethod();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------