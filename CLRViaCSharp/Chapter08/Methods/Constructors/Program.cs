using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace Constructors
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! Ked je tato METHOD kompilovana pomocou JIT COMPILER, STATIC CONSTRUCTORS pre CBeforeFieldInit a CPrecise MUSIA BYT ZAVOLANE, lebo ESTE NEBOLI VOLANE. A preto JIT GENERUJE NATIVE CODE, ktory vola STATIC CONSTRUCTORS.
		private static void PerfTest1(int Iterations, bool Skip)
		{
			Console.WriteLine("METHOD PerfTest1() CALLED !");

			if (Skip==true)
			{
				return;
			}

			Stopwatch											SW=Stopwatch.StartNew();

			for (int Index=0;Index<Iterations;Index++)
			{
				// !!! Kedze CBeforeFieldInit ma nastaveny FLAG BeforeFieldInit tak jej STATICKY KONSTRUKTOR je volany PRED CYKLOM na ZACIATKU CELEJ METODY.
				CBeforeFieldInit.X=1;
			}

			Console.WriteLine(string.Format("PerfTest1(): [{0}] BeforeFieldInit !", SW.Elapsed));

			SW=Stopwatch.StartNew();

			for (int Index=0;Index<Iterations;Index++)
			{
				// !!! Kedze CPrecise NEMA nastaveny FLAG BeforeFieldInit tak jej STATICKY KONSTRUKTOR je volany AZ PRED PRVYM PRISTUPOM k FIELDU z CPrecise a teda AZ V CYKLE. To sposobi POMALSIE VYKONAVANIE CELEHO CYKLU.
				CPrecise.X=1;
			}

			Console.WriteLine(string.Format("PerfTest1(): [{0}] Precise !", SW.Elapsed));
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Ked je tato METHOD kompilovana pomocou JIT COMPILER, STATIC CONSTRUCTORS pre CBeforeFieldInit a CPrecise UZ BOLI ZAVOLANE a preto JIT COMPILER uz NEMUSI PRIDAVAT do vygenerovaneho NATIVE CODE volania STATIC CONSTRUCTORS a CODE BEZI RYCHLEJSIE.
		private static void PerfTest2(Int32 Iterations)
		{
			Console.WriteLine("METHOD PerfTest2() CALLED !");

			Stopwatch											SW=Stopwatch.StartNew();

			for (int Index=0;Index<Iterations; Index++)
			{
				CBeforeFieldInit.X=1;
			}

			Console.WriteLine(string.Format("PerfTest2(): [{0}] BeforeFieldInit !", SW.Elapsed));

			SW=Stopwatch.StartNew();

			for (int Index=0;Index<Iterations; Index++)
			{
				CPrecise.X=1;
			}

			Console.WriteLine(string.Format("PerfTest2(): [{0}] Precise !", SW.Elapsed));
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda bude prelozena JIT COMPILER ako PRVA a preto bude obsahovat i VOLANIE STATICKEHO KONSTUKTORA CBase.
		private static void JIT1()
		{
			CJIT												JIT=new CJIT();

			JIT.VirtualMethod();
		}
//-------------------------------------------------------------------------------------------------------
		// Tato metoda bude prelozena JIT COMPILER AZ PO VOLANI JIT1(), ktory ZAVOLAL STATICKY KONSTURKTOR pre CBase a preto sa tu uz STATICKY KONSTRUKTOR NEVOLA.
		private static void JIT2()
		{
			CJIT												JIT=new CJIT();

			JIT.VirtualMethod();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			CDerived											Derived=new CDerived();

			Derived.ShowValues();

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Nevola sa ZIADEN KONSTURKTOR.
			SStruct												Struct1=new SStruct();

			Struct1.ShowValues();

			Console.WriteLine("-------------------------------------------------------------------------------");

			// Vola sa PARAMETRICKY KONSTRUKTOR.
			SStruct												Struct2=new SStruct(10,20);

			Struct2.ShowValues();

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CClassWithValueType									ClassWithValueType=new CClassWithValueType();

			ClassWithValueType.ShowValues();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			SStructReset										StructReset=new SStructReset(100,200);

			StructReset.ShowValues();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine("STEP 1 !!!");

			SStaticConstructorNotCalled[]						StaticConstructorNotCalledArray=new SStaticConstructorNotCalled[5];

			Console.WriteLine("STEP 2 !!!");

			for(int Index=0;Index<StaticConstructorNotCalledArray.Length;Index++)
			{
				Console.WriteLine("STEP 3 !!!");

				// !!!!! STATIC CONSTRUCTOR sa NEVOLA, aj ked sa zapisuje do FIELD daneho VALUE TYPE.
				StaticConstructorNotCalledArray[Index].MText=(Index+100).ToString();

				Console.WriteLine("STEP 4 !!!");

				// !!!!! Az TU sa zavola STATIC CONSTRUCTOR.
				StaticConstructorNotCalledArray[Index].Do();

				Console.WriteLine("STEP 5 !!!");
			}

			Console.WriteLine("STEP 6 !!!");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			JIT1();
			JIT2();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			//CStaticConstructor1.Print();
			//CStaticConstructor2.Print();

			CStaticConstructor2.Print();
			CStaticConstructor1.Print();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			const int											ITERATIONS=1000*1000*1000;

			PerfTest1(ITERATIONS,false);
			PerfTest2(ITERATIONS);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			const int											ITERATIONS=1000*1000*1000;

			// Zavola sa metoda, ktora sa PREKOMPILUJE cez JIT a ktora GENERUJE VOLANIE STATICKYCH KONSTRUKTOROV v NATIVE KODE, ale STATICKE KONSTRUKTORY sa NEZAVOLAJU.
			PerfTest1(ITERATIONS,true);

			// Zavola sa metoda, ktora sa PREKOMPILUJE cez JIT a ktora ZNOVA GENERUJE VOLANIE STATICKYCH KONSTRUKTOROV v NATIVE KODE, pretoze PerfTest1() ich NEVOLALA. Teraz vsak metoda STATICKE KONSTRUKTORY uz ZAVOLA.
			PerfTest2(ITERATIONS);

			// !!!!! Teraz uz PREKOMPILOVANA METODA v NATIVE KODE ma v NATIVE KODE zapisanu KONTORLU a pripadne VOLANIE STATICKYCH KONSTRUKTOROV, co sa NEGATIVNE ODRAZI na VYKONNOSTI volania STATICKEHO KONSTUKTORA pre CPrecise TYP.
			PerfTest1(ITERATIONS,false);
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