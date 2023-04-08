using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Constants
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Konstanty su VZDY STATICKE READONLY FIELDS.
		private const int										SOME_NUMBER=100;
		private const string									SOME_STRING="Timmy Anderson";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// !!! Pri referovani na konstantu sa PRIAMO EXTRAHUJE HODNOTA KONSTATNY a nie REFERENCIA na KONSTANTU. Extrahovana hodnota konstanty sa NATVRDO HODI do generovaneho IL kodu a v RUNTIME sa uz pouziva IBA TATO EXTRAHOVANA HODNOTA a ku konstante samotnej sa VOBEC NEPRISTUPUJE.
			// !!! Do Value sa teda NATVRDO ULOZI hodnota 100.
			/*
				// !!! Uklada sa PRIAMO VALUE a NIE referencia na CONSTANT.
				ldc.i4.s										100
				stloc											Value
				ldstr											"Constant [{0}] !"
				ldloc											Value
				box												[mscorlib]System.Int32
				call											string [mscorlib]System.String::Format(string, object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			int													Value=SOME_NUMBER;

			Console.WriteLine(string.Format("Constant [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// !!! Pri referovani na konstantu sa PRIAMO EXTRAHUJE HODNOTA KONSTATNY a nie REFERENCIA na KONSTANTU. Extrahovana hodnota konstanty sa NATVRDO HODI do generovaneho IL kodu a v RUNTIME sa uz pouziva IBA TATO EXTRAHOVANA HODNOTA a ku konstante samotnej sa VOBEC NEPRISTUPUJE.
			// !!! Do Value sa teda NATVRDO ULOZI hodnota "Timmy Anderson".
			/*
				// !!! Uklada sa PRIAMO VALUE a NIE referencia na CONSTANT.
				ldstr											"Timmy Anderson"
				stloc											Value
				ldstr											"Constant [{0}] !"
				ldloc											Value
				call											string [mscorlib]System.String::Format(string,object)
				call											void [mscorlib]System.Console::WriteLine(string)
			*/
			string												Value=SOME_STRING;

			Console.WriteLine(string.Format("Constant [{0}] !",Value));
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