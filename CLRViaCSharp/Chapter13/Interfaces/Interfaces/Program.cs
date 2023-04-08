using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Interfaces
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CBase												Base=new CBase();
			CDerived											Derived=new CDerived();
			CBase												DerivedAsBase=Derived;

			Console.WriteLine("-------------------------------------------------------------------------------");
			Base.NonVirtualMethod();
			Base.VirtualMethod();
			Base.VirtualMethodWithNew();
			Console.WriteLine("-------------------------------------------------------------------------------");
			Derived.NonVirtualMethod();
			Derived.VirtualMethod();
			Derived.VirtualMethodWithNew();
			Console.WriteLine("-------------------------------------------------------------------------------");
			DerivedAsBase.NonVirtualMethod();
			DerivedAsBase.VirtualMethod();
			DerivedAsBase.VirtualMethodWithNew();
			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CNestedInterface.IInnerInterface					Interface=new CNestedInterface.CNestedClass();

			Interface.Print();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			IGenericInterface<string>							GenericClass=new CGenericClass();

			GenericClass.Print("Timmy Anderson");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			IInterfaceWithGenericMethods						InterfaceWithGenericMethods=new CInterfaceWithGenericMethods();

			InterfaceWithGenericMethods.GenericMethod<string>("Timmy Anderson");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CBaseWithInterface									Base=new CBaseWithInterface();
			CDerivedWithInterface								Derived=new CDerivedWithInterface();
			CBaseWithInterface									DerivedAsBase=Derived;

			Console.WriteLine("-------------------------------------------------------------------------------");
			Base.Print1();
			Base.Print2();
			((IInterface)Base).Print1();
			((IInterface)Base).Print2();
			Console.WriteLine("-------------------------------------------------------------------------------");
			Derived.Print1();
			Derived.Print2();
			((IInterface)Derived).Print1();
			((IInterface)Derived).Print2();
			Console.WriteLine("-------------------------------------------------------------------------------");
			DerivedAsBase.Print1();
			DerivedAsBase.Print2();
			((IInterface)DerivedAsBase).Print1();
			((IInterface)DerivedAsBase).Print2();
			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CNameStruct											NameAsStruct=new CNameStruct("Timmy","Anderson",12);

			Console.WriteLine(string.Format("NameAsSturct: [{0}] !",NameAsStruct));

			// !!! Teraz sa robi BOXING.
			/*
				ldloc											NameAsStruct
				box												Interfaces.CNameStruct
				stloc											StructAsInterface
			*/
			IChangeStruct										StructAsInterface=NameAsStruct;

			Console.WriteLine(string.Format("StructAsInterface: [{0}] !",StructAsInterface));

			// !!!!! Teraz ked zmenim StructAsInterface tak sa NameAsStruct NEZMENI - lebo su to 2 NEZAVISLE OBJEKTY. Avsak StructAsInterface sa samozrejme zmeni.
			StructAsInterface.Change("Jenny","Thompson",13);

			Console.WriteLine(string.Format("NameAsSturct: [{0}] !",NameAsStruct));
			Console.WriteLine(string.Format("StructAsInterface: [{0}] !",StructAsInterface));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			CVirtualMethodTable1								VMT1=new CVirtualMethodTable1();
			IDummy												Dummy1=VMT1;

			Console.WriteLine("-------------------------------------------------------------------------------");

			// !!!!! Kedze IDummy.DoSomething() i CVirtualMethodTable1.DoSomething() maju v METADATA REFERENCIU na TEN ISTY CODE, tak sa VOLA pre obe volania TEN ISTY CODE v 2 de-facto ROZLICNYCH METODACH.

			// Volam CVirtualMethodTable1.DoSomething().
			VMT1.DoSomething();
			// Volam sa IDummy.DoSomething(), ktora odkazuje na TEN ISTY CODE ako volanie METHOD VMT1.DoSomething().
			Dummy1.DoSomething();

			Console.WriteLine("-------------------------------------------------------------------------------");

			CVirtualMethodTable2								VMT2=new CVirtualMethodTable2();
			IDummy												Dummy2=VMT2;
			
			// !!!!! Kedze IDummy.DoSomething() pouziva EXPLICIT OVERRIDING, CVirtualMethodTable2.DoSomething() a IDummy.DoSomething() odkazuju na INY CODE - na vlastne implementacie svojich METHODS.

			// Volam CVirtualMethodTable2.DoSomething().
			VMT2.DoSomething();
			// !!! Volam sa IDummy.DoSomething(), ktora NEMA IDENTICKY CODE ako CVirtualMethodTable2.DoSomething().
			Dummy2.DoSomething();

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			// Bez VARIANCE.
			IVariantInterface<object,string>					I1=new CObjectVariantClass();

			Console.WriteLine(string.Format("I1: [{0}] !",I1.Do("XXX")));

			// !!! S vyuzitim VARIANCE.
			// !!!!! Aj ked je pozadovany IVariantInterface<string,object> a CStringVariantClass implementuje IVariantInterface<string,object>, tak IMPLICITNA KONVERZIA PREBEHNE, pretoze sa pouzila COVARIANCE a CONTRAVARIANCE.
			IVariantInterface<string,object>					I2=new CStringVariantClass();

			Console.WriteLine(string.Format("I2: [{0}] !",I2.Do("YYY")));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			CInterfaceConstraint								InterfaceConstraint=new CInterfaceConstraint();

			Console.WriteLine("-------------------------------------------------------------------------------");

			InterfaceConstraint.DoTestWithConstraints<CComparableEquatableClass>(new CComparableEquatableClass(10),new CComparableEquatableClass(22));

			Console.WriteLine("-------------------------------------------------------------------------------");

			InterfaceConstraint.DoTestWithConstraints<int>(10,2);

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Console.WriteLine("-------------------------------------------------------------------------------");

			CSameNamedMethodInMultipleInterfaces1				SNMIMI1=new CSameNamedMethodInMultipleInterfaces1();
			IInterface1											I11=SNMIMI1;
			IInterface2											I12=SNMIMI1;

			SNMIMI1.SameNamedMethod();
			I11.SameNamedMethod();
			I12.SameNamedMethod();

			Console.WriteLine("-------------------------------------------------------------------------------");

			CSameNamedMethodInMultipleInterfaces2				SNMIMI2=new CSameNamedMethodInMultipleInterfaces2();
			IInterface1											I21=SNMIMI2;
			IInterface2											I22=SNMIMI2;

			SNMIMI2.SameNamedMethod();
			I21.SameNamedMethod();
			I22.SameNamedMethod();

			Console.WriteLine("-------------------------------------------------------------------------------");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			CExplicitlyImplementedInterface						EII=new CExplicitlyImplementedInterface();
			IComparable											C=EII;

			// !!! Toto sa NEPREKOMPILUJE, pretoze CompareTo(object Obj) je SKRYTA.
			//EII.CompareTo(C);

			// Vola METHOD NON-GENERICS INTERFACE.
			C.CompareTo(C);

			// Vola TYPOVO BEZPECNU METHOD.
			EII.CompareTo(EII);
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
			//Test8();
			//Test9();
			//Test10();
			Test11();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------