using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace AssemblyLoading
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static Assembly CurrentDomain_AssemblyResolve(object Sender, ResolveEventArgs Args)
		{
			Console.WriteLine(string.Format("AssemblyResolve() CALLED - Assembly: [{0}] !",Args.Name));

			// !!! Iba TestAssembly2.DLL nevie CLR NAJST, lebo NIE JE V ROVANKOM ADRESARI ako EXE subor a nie je aplikovana ani ziadna POLICY, ktora by prinutila CLR aby hladal ASSEMBLY aj v inych adresaroch.
			if (Args.Name.StartsWith("TestAssembly2")==true)
			{
				Assembly										A=Assembly.LoadFrom("..\\..\\..\\!ASSEMLIES\\TestAssembly2.dll");

				return(A);
			}
			else
			{
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static Assembly CurrentDomain_ReflectionOnlyAssemblyResolve(object Sender, ResolveEventArgs Args)
		{
			Console.WriteLine(string.Format("ReflectionOnlyAssemblyResolve() CALLED - Assembly: [{0}] !",Args.Name));

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				// ASSEMBLY musi byt v adresari, kde ju CLR cez mechanizmus vyhladavania dokazal najst.
				Assembly										A=Assembly.Load("TestAssembly1");

				Console.WriteLine("ASSEMBLY LOADED !");

				Type											T=A.GetType("TestAssembly1.CTestClass");
				MethodInfo										MI=T.GetMethod("SomeMethod");

				Console.WriteLine("METHOD FOUND !");

				// Vyvolam metodu v dynamicky nacitanej ASSEMBLY.
				MI.Invoke(null,null);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				// ASSEMBLY musi byt v adresari na ktory ukazuje PATH.
				Assembly										A=Assembly.LoadFrom("..\\..\\..\\!ASSEMLIES\\TestAssembly2.dll");

				Console.WriteLine("ASSEMBLY LOADED !");

				Type											T=A.GetType("TestAssembly2.CTestClass");
				MethodInfo										MI=T.GetMethod("SomeMethod");

				Console.WriteLine("METHOD FOUND !");

				// Vyvolam metodu v dynamicky nacitanej ASSEMBLY.
				MI.Invoke(null,null);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			try
			{
				// Ak by nahodou ASSEMBLY bola zavisla na inych ASSEMBLIES tak by som v HANDLER tohto EVENT mohol riesit DEPENDENCIES.
				AppDomain.CurrentDomain.ReflectionOnlyAssemblyResolve+=new ResolveEventHandler(CurrentDomain_ReflectionOnlyAssemblyResolve);

				// ASSEMBLY musi byt v adresari, kde ju CLR cez mechanizmus vyhladavania dokaze najst.
				// Pri pouziti ReflectionOnlyLoad() NIE JE MOZNE VYVOLAVAT JEDNOTLIVE TYPY, ani MEMBERS, iba prechadzat cez MEMBERS pomocou REFLECTION.
				Assembly										A=Assembly.ReflectionOnlyLoad("TestAssembly1");

				Console.WriteLine("ASSEMBLY LOADED !");

				Type											T=A.GetType("TestAssembly1.CTestClass");
				MethodInfo										MI=T.GetMethod("SomeMethod");

				Console.WriteLine("METHOD FOUND !");

				// Vyvolam metodu v dynamicky nacitanej ASSEMBLY.
				// !!!!! Hodi EXCEPTION, lebo na nacitanie ASSEMBLY som pouzil ReflectionOnlyLoad().
				MI.Invoke(null,null);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				// !!! Kedze ASSEMBLY je zavisla na inych ASSEMBLIES tak v HANDLER tohto EVENT riesim DEPENDENCIES - nacitanie DEPENDENT ASSEMBLIES.
				AppDomain.CurrentDomain.AssemblyResolve+=new ResolveEventHandler(CurrentDomain_AssemblyResolve);

				// ASSEMBLY musi byt v adresari, kde ju CLR cez mechanizmus vyhladavania dokaza najst.
				Assembly										A=Assembly.Load("TestAssembly3");

				Console.WriteLine("ASSEMBLY LOADED !");

				Type											T=A.GetType("TestAssembly3.CTestClass");
				MethodInfo										MI=T.GetMethod("SomeMethod");

				Console.WriteLine("METHOD FOUND !");

				// Vyvolam metodu v dynamicky nacitanej ASSEMBLY.
				MI.Invoke(null,null);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------