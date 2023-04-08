//-------------------------------------------------------------------------------------------------------
// !!!!! Kedze ASSEMBLY External1 aj ASSEMBLY External2 maju v TOM ISTOM NAMESPACE 'External' TEN ISTY TYPE 'CClass', je NUTNE pouzit EXTERNAL ALIAS.
// !!!!! Na to, aby to fungovalo, MUSI byt v projekte na References->Externa1->Aliases nastavena hodnota 'EXT1'.
extern alias EXT1;
// !!!!! Na to, aby to fungovalo, MUSI byt v projekte na References->Externa2->Aliases nastavena hodnota 'EXT2'.
extern alias EXT2;
//-------------------------------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
// INTERNAL ALIAS.
using CMyStringList=System.Collections.Generic.List<string>;
//-------------------------------------------------------------------------------------------------------
namespace TypeFundamentals
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CName												Name1=new CName("Timmy","Anderson",12);
			CName												Name2=new CName("Timmy","Anderson",12);
			CName												Name3=new CName("Jenny","Thompson",13);

			Console.WriteLine(string.Format("GetHashCode() - Name1: [{0}] !",Name1.GetHashCode()));
			Console.WriteLine(string.Format("GetHashCode() - Name2: [{0}] !",Name2.GetHashCode()));
			Console.WriteLine(string.Format("GetHashCode() - Name3: [{0}] !",Name3.GetHashCode()));
			Console.WriteLine();

			Console.WriteLine(string.Format("ToString() - Name1: [{0}] !",Name1.ToString()));
			Console.WriteLine(string.Format("ToString() - Name2: [{0}] !",Name2.ToString()));
			Console.WriteLine(string.Format("ToString() - Name3: [{0}] !",Name3.ToString()));
			Console.WriteLine();

			Console.WriteLine(string.Format("Name1.Equals(Name2): [{0}] !",Name1.Equals(Name2)));
			Console.WriteLine(string.Format("Name1.Equals(Name3): [{0}] !",Name1.Equals(Name3)));
			Console.WriteLine(string.Format("Name2.Equals(Name3): [{0}] !",Name2.Equals(Name3)));
			Console.WriteLine();

			DateTime											Start;
			TimeSpan											Diff;

			CDerivedName										DerivedName=new CDerivedName("Timmy","Anderson",12);
			CName												Name=DerivedName;
			CName												TempName;
			CDerivedName										TempDerivedName;

			Start=DateTime.Now;

			for(int Index=0;Index<int.MaxValue;Index++)
			{
				TempName=DerivedName;
			}

			Diff=DateTime.Now-Start;

			Console.WriteLine("Implicit casting - time: [{0}] !",Diff.TotalMilliseconds);

			Start=DateTime.Now;

			for(int Index=0;Index<int.MaxValue;Index++)
			{
				// Pouzije sa 'DerivedName'.
				TempDerivedName=(CDerivedName) DerivedName;
			}

			Diff=DateTime.Now-Start;

			Console.WriteLine("Explicit casting TRY 1 - time: [{0}] !",Diff.TotalMilliseconds);

			Start=DateTime.Now;

			for(int Index=0;Index<int.MaxValue;Index++)
			{
				// Pouzije sa 'Name'.
				TempDerivedName=(CDerivedName) Name;
			}

			Diff=DateTime.Now-Start;

			Console.WriteLine("Explicit casting TRY 2 - time: [{0}] !",Diff.TotalMilliseconds);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CName												Name1=new CName("Timmy","Anderson",12);
			CName												Name2=Name1.CreateClone();

			Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			Console.WriteLine(string.Format("Name2: [{0}] !",Name2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CMutableClass										MutableClass1=new CMutableClass("Timmy Anderson");
			CMutableClass										MutableClass2=new CMutableClass("Jenny Thompson");
			CClassUsingMutableClass								ClassUsingMutableClass1=new CClassUsingMutableClass(MutableClass1);
			CClassUsingMutableClass								ClassUsingMutableClass2=ClassUsingMutableClass1.CreateClone();
			CClassUsingMutableClass								ClassUsingMutableClass3=ClassUsingMutableClass1.CreateClone();
			CClassUsingMutableClass								ClassUsingMutableClass4=ClassUsingMutableClass1.CreateClone();

			Console.WriteLine("-------------------------------------------------------------------------------");

			Console.WriteLine(string.Format("ClassUsingMutableClass1: [{0}] !",ClassUsingMutableClass1));
			Console.WriteLine(string.Format("ClassUsingMutableClass2: [{0}] !",ClassUsingMutableClass2));
			Console.WriteLine(string.Format("ClassUsingMutableClass3: [{0}] !",ClassUsingMutableClass3));
			Console.WriteLine(string.Format("ClassUsingMutableClass4: [{0}] !",ClassUsingMutableClass4));

			Console.WriteLine("-------------------------------------------------------------------------------");
			
			ClassUsingMutableClass2.MutableClass=MutableClass2;

			Console.WriteLine(string.Format("ClassUsingMutableClass1: [{0}] !",ClassUsingMutableClass1));
			Console.WriteLine(string.Format("ClassUsingMutableClass2: [{0}] !",ClassUsingMutableClass2));
			Console.WriteLine(string.Format("ClassUsingMutableClass3: [{0}] !",ClassUsingMutableClass3));
			Console.WriteLine(string.Format("ClassUsingMutableClass4: [{0}] !",ClassUsingMutableClass4));
			
			Console.WriteLine("-------------------------------------------------------------------------------");

			// !!! Zmeni hodnotu v INNER CLASS, ktora sa pouziva v 3 CLONED OBJECTS.
			MutableClass1.Text="Atreyu";

			Console.WriteLine(string.Format("ClassUsingMutableClass1: [{0}] !",ClassUsingMutableClass1));
			Console.WriteLine(string.Format("ClassUsingMutableClass2: [{0}] !",ClassUsingMutableClass2));
			Console.WriteLine(string.Format("ClassUsingMutableClass3: [{0}] !",ClassUsingMutableClass3));
			Console.WriteLine(string.Format("ClassUsingMutableClass4: [{0}] !",ClassUsingMutableClass4));

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			OuterNamespace.InnerNamespace.CMultiNamespacesClass.WriteName();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			EXT1.External.CClass.PrintMessage();
			EXT2.External.CClass.PrintMessage();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CMyStringList										MyStringList=new CMyStringList();

			MyStringList.Add("Timmy Anderson");
			MyStringList.Add("Jenny Thompson");

			foreach(string Value in MyStringList)
			{
				Console.WriteLine(string.Format("VALUE: [{0}] !",Value));
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
			//Test4();
			//Test5();
			Test6();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------