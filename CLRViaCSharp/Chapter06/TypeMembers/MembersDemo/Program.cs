using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MembersDemo
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			COuterClass											OuterClass=new COuterClass("Timmy Anderson");
			COuterClass.CInnerClass								InnerClass=new COuterClass.CInnerClass(OuterClass);

			Console.WriteLine(string.Format("VALUE [{0}] !",OuterClass.Value));

			InnerClass.ChangeValue("Jenny Thompson");

			Console.WriteLine(string.Format("VALUE [{0}] !",OuterClass.Value));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CNewNestedClassBase									Base=new CNewNestedClassBase();
			CNewNestedClassBase.CNestedClass					BaseNested=Base.CreateNestedClassInstanceInBase();

			Console.WriteLine("BaseNested [{0}] !",BaseNested.Field);

			CNewNestedClassDerived								Derived=new CNewNestedClassDerived();
			CNewNestedClassBase.CNestedClass					DerivedNested1=Derived.CreateNestedClassInstanceInBase();
			CNewNestedClassDerived.CNestedClass					DerivedNested2=Derived.CreateNestedClassInstanceInDerived();

			Console.WriteLine("DerivedNested1 [{0}] !",DerivedNested1.Field);
			Console.WriteLine("DerivedNested2 [{0}] !",DerivedNested2.Field);
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