using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace OptionalAndDefault
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ShowName(string Name)
		{
			Console.WriteLine(string.Format("DELEGATE - Name: [{0}] !",Name));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CTestClass											TC=new CTestClass();

			TC.Test1("Jenny","Thompson",13,Guid.NewGuid(),100);

			TC.Test1("Timmy");

			TC.Test1("Timmy",Code:333);

			// Na poradi NAMED parametrov NEZALEZI.
			TC.Test1("Timmy","Anderson",Code:444,Age:15);

			Console.WriteLine(string.Format("INDEXER: [{0}] !",TC["Timmy"]));

			string												ReturnedFullName;

			// !!! Klucove slovo 'out' MUSI i PRI NAMED PARAMETROCH BYT DEFINOVANE.
			TC.Test2("Timmy","Anderson",12,FullName:out ReturnedFullName);

			Console.WriteLine(string.Format("FULL NAME: [{0}] !",ReturnedFullName));

			// NAMED PARAMETERS je mozne pouzit aj ked METHOD NEPOUZIVA DEFAULT VALUES a poradie moze byt LUBOVOLNE.
			TC.Test3(Age:12,FirstName:"Timmy",LastName:"Anderson");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CTestDelegate										TestDelegate=new CTestDelegate(ShowName);

			TestDelegate("Jenny");

			// NAMED PARAMETER.
			TestDelegate(Name:"Atreyu");

			// UPLATNI sa DEFAULT hodnota.
			TestDelegate();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------