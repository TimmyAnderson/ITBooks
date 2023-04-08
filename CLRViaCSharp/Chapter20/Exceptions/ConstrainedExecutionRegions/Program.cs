using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.ConstrainedExecution;
using System.Runtime.CompilerServices;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace ConstrainedExecutionRegions
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void CERMethod()
		{
			// !!! Sposobi vyvolanie STATIC CONSTRUCTOR.
			CCER1.SomeStaticMethod();
		}
//-------------------------------------------------------------------------------------------------------
		private static void CERTest()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			// !!!!! Hodi EXCEPTION, pretoze STATIC CONSTRUCTOR CCERWithErrorInStaticConstructor hodi EXCEPTION.
			RuntimeHelpers.PrepareConstrainedRegions();

			// Tu sa ZACINA CER.
			try
			{
				Console.WriteLine("INSIDE TRY !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY 1 !");

				CCERWithErrorInStaticConstructor.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY 2 !");
			}
			// Tu sa KONCI CER.
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			// Vykona sa PREPARATION pre CER co znaci, ze sa vykona JIT COMPILATION KAZDEJ METHOD volanej v TRY, alebo FINALLY BLOCKS.
			// !!!!! Ak by JIT COMPILATION ZLYHALA (alebo sa NENASLA ASSEMBLY obsahujuca CLASS 'CCER', tak by sa ASYNCHRONNE EXCEPTIONS generovali este v tejto METHOD a TRY BLOCK by sa VOBEC NEVYKONAL.
			// !!!!! Cize inak povedane, ak je NUTNE, aby sa FINALLY BLOCK s CO NAJVACSOU PRAVDEPODOBNOSTOU VYKONAL, tak PRED TRY BLOCK je nutne pouzit MEHTOD RuntimeHelpers.PrepareConstrainedRegions(), ktora pripade ASYNCHRONOUS EXCEPTIONS, ktore by pocas vykonavania FINALLY BLOCK mohli nastat nastanu UZ TU POCAS VOLANIA METHOD RuntimeHelpers.PrepareConstrainedRegions().
			// !!!!! Uz pocas volania METHOD RuntimeHelpers.PrepareConstrainedRegions() sa vykona STATIC CONSTUCTOR pre 'CCER'.
			RuntimeHelpers.PrepareConstrainedRegions();

			// Tu sa ZACINA CER.
			try
			{
				Console.WriteLine("INSIDE TRY !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY 1 !");

				// !!!!! STATICKY CONSTRUCTOR pre CNotCER sa VYKONA AZ TU, pretoze METHOD CNotCER.SomeStaticMethod() NIE JE OZNACENA ATTRIBUTE [ReliabilityContract].
				CNotCER.SomeStaticMethod();

				CCER1.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY 2 !");
			}
			// Tu sa KONCI CER.

			// Toto uz NIE JE SUCAST CER.
			CCER2.SomeStaticMethod();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			// !!! METHOD RuntimeHelpers.PrepareConstrainedRegions() MUSI byt vykonana TESNE pred TRY BLOCK.
			// !!! STATIC CONSTRUCTOR pre CLASS 'CCER1' je vyvolany uz tu, kedze sa pouzila METHOD RuntimeHelpers.PrepareConstrainedRegions().
			RuntimeHelpers.PrepareConstrainedRegions();

			// Tu sa ZACINA CER.
			try
			{
				Console.WriteLine("INSIDE TRY 1 !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY A - 1 !");

				// !!!!! STATICKY CONSTRUCTOR pre CNotCER sa VYKONA AZ TU.
				CNotCER.SomeStaticMethod();

				CCER1.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY A - 2 !");
			}
			// Tu sa KONCI CER.

			Console.WriteLine();

			// TOTO NIE JE CER BLOK, lebo som pred nim NEZAVOLALA METHOD RuntimeHelpers.PrepareConstrainedRegions().
			try
			{
				Console.WriteLine("INSIDE TRY 2 !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY B - 1 !");

				// !!! STATIC CONSTRUCTOR pre CLASS 'CCER2' je vyvolany az tu, kedze sa PRED TRY BLOCK NEPOUZILA METHOD RuntimeHelpers.PrepareConstrainedRegions().
				CCER2.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY B - 2 !");
			}
			// Tu sa KONCI CER.
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			// !!!!! STATIC CONSTRUCTOR pre CLASS CCER1 sa UZ TU, pretoze pred TRY BLOCK sa zavolala METHOD RuntimeHelpers.PrepareConstrainedRegions() a METHOD CCER1.SomeStaticMethod() JE OZNACENA ATTRIBUTE [ReliabilityContract].
			// !!!!! STATIC CONSTRUCTOR pre CLASS CCER2 sa UZ TU, pretoze pred TRY BLOCK sa zavolala METHOD RuntimeHelpers.PrepareConstrainedRegions() a METHOD CCER2.SomeStaticMethod() JE OZNACENA ATTRIBUTE [ReliabilityContract].
			RuntimeHelpers.PrepareConstrainedRegions();

			// Tu sa ZACINA CER.
			try
			{
				Console.WriteLine("INSIDE TRY 1 !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY A - 1 !");

				// !!!!! STATIC CONSTUCTOR pre CLASS CNotCER sa VYKONA AZ TU, pretoze METHOD CNotCER.SomeStaticMethod() NIE JE OZNACENA ATTRIBUTE [ReliabilityContract].
				CNotCER.SomeStaticMethod();

				CCER1.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY A - 2 !");
			}
			// Tu sa KONCI CER.

			Console.WriteLine();

			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			RuntimeHelpers.PrepareConstrainedRegions();

			// Tu sa ZACINA NOVY CER.
			try
			{
				Console.WriteLine("INSIDE TRY 2 !");
			}
			finally
			{
				Console.WriteLine("INSIDE FINALLY B - 1 !");

				CCER2.SomeStaticMethod();

				Console.WriteLine("INSIDE FINALLY B - 2 !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			RuntimeHelpers.PrepareConstrainedRegions();

			string												Name="Timmy";

			// BLOCK 'if' NIE JE CER.
			if (Name=="Timmy")
			{
				Console.WriteLine("INSIDE FINALLY 1 !");

				// !!!!! STATIC CONSTRUCTOR pre CNotCER sa VYKONA AZ TU.
				CNotCER.SomeStaticMethod();

				CCER1.SomeStaticMethod();

				Console.WriteLine("AFTER FINALLY 1 !");
			}
			// Tu sa KONCI CER.
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			Console.WriteLine("PrepareConstrainedRegions() CALLING...");

			// !!!!! STATIC CONSTRUCTOR pre CLASS CCER1 sa UZ TU, pretoze pred TRY BLOCK sa zavolala METHOD RuntimeHelpers.PrepareConstrainedRegions() a METHOD CCER1.SomeStaticMethod() JE OZNACENA ATTRIBUTE [ReliabilityContract].
			RuntimeHelpers.PrepareConstrainedRegions();

			string												Name="Timmy";

			// BLOCK 'if' NIE JE CER a preto sa ZIADEN STATIC CONSTRUCTOR NEZAVOLA pred TRY BLOCK.
			if (Name=="Timmy")
			{
				// Tu sa ZACINA CER.
				try
				{
					Console.WriteLine("INSIDE TRY !");
				}
				finally
				{
					Console.WriteLine("INSIDE FINALLY 1 !");

					// !!!!! STATIC CONSTUCTOR pre CLASS CNotCER sa VYKONA AZ TU, pretoze METHOD CNotCER.SomeStaticMethod() NIE JE OZNACENA ATTRIBUTE [ReliabilityContract].
					CNotCER.SomeStaticMethod();

					CCER1.SomeStaticMethod();

					Console.WriteLine("INSIDE FINALLY 2 !");
				}
				// Tu sa KONCI CER.
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Type												ThisType=typeof(Program);
			MethodInfo											Method=ThisType.GetMethod("CERMethod",BindingFlags.Static | BindingFlags.NonPublic);

			Console.WriteLine("BEFORE RuntimeHelpers.PrepareMethod() !");

			// !!! Zavola STATIC CONSTRUCTOR pre CLASS 'CCER1'.
			RuntimeHelpers.PrepareMethod(Method.MethodHandle);

			Console.WriteLine("AFTER RuntimeHelpers.PrepareMethod() !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Action												SomeDelegate=new Action(CERMethod);

			Console.WriteLine("BEFORE RuntimeHelpers.PrepareDelegate() !");

			// !!! Zavola STATIC CONSTRUCTOR pre CLASS 'CCER1'.
			RuntimeHelpers.PrepareDelegate(SomeDelegate);
			
			Console.WriteLine("AFTER RuntimeHelpers.PrepareDelegate() !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Console.WriteLine("Test8() STARTED !");

			try
			{
				CERTest();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E));
			}

			Console.WriteLine("Test8() FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			Test8();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------