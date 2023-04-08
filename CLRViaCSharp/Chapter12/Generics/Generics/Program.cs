using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
using CUsingIntList=System.Collections.Generic.List<int>;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void GenericOverriden<TType>(TType Parameter)
		{
			Console.WriteLine(string.Format("GENERIC GenericOverriden<TType>() METHOD CALLED with GENERICS PARAMETER: [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void GenericOverriden(string Parameter)
		{
			Console.WriteLine(string.Format("NON-GENERIC GenericOverriden() METHOD CALLED with GENERICS PARAMETER: [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void SameParams<TType>(TType Parameter1, TType Parameter2)
		{
			Console.WriteLine(string.Format("SameParams<TType>() METHOD CALLED with GENERICS PARAMETERS: [{0}] and [{1}] !",Parameter1,Parameter2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void GenericDelegateHandler(int Parameter)
		{
			Console.WriteLine(string.Format("Generics DELEGATE HANDLER CALLED with GENERICS parameter: [{0}] !",Parameter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void GenericMethod<TType>(TType Parameter)
		{
			Console.WriteLine(string.Format("GenericMethod<TType>() DELEGATE METHOD CALLED with GENERICS parameter: [{0}], Type: [{1}] !",Parameter,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Definujem CONSTRAIN medzi 2 TYPOVYMI PARAMETRAMI.
		private static void GenericMethodWithConstrain<TType1, TType2>(TType1 Parameter1, TType2 Parameter2) where TType2 : TType1
		{
			Console.WriteLine(string.Format("GenericMethodWithConstrain<TType>() CLASS METHOD CALLED with GENERICS Parameter1: [{0}], Type1: [{1}], Parameter2: [{2}], Type1: [{3}] !",Parameter1,typeof(TType1).Name,Parameter2,typeof(TType2).Name));
		}
//-------------------------------------------------------------------------------------------------------
		private static void OpeatrorsEqualAndNotEqualTest<TType>(TType Parameter)
		{
			// !!! Kompilator porovnanie SKOMPILUJE a pre VALUE TYPES je hodnota vyrazu VZDY FALSE>
			if (Parameter==null)
			{
				Console.WriteLine("Operator == returned TRUE !");
			}
			else
			{
				Console.WriteLine("Operator == returned FALSE !");
			}

			if (Parameter!=null)
			{
				Console.WriteLine("Operator != returned TRUE !");
			}
			else
			{
				Console.WriteLine("Operator != returned FALSE !");
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			IGenericInterface<int>								GCI=new CGenericClass<int>();

			GCI.InterfaceMethod(7);

			IGenericInterface<int>								GSI=new SGenericStruct<int>();

			GSI.InterfaceMethod(2);

			SGenericStruct<int>									GS=new SGenericStruct<int>();

			GS.StructMethod(8);

			DGenericDelegate<int>								GD=new DGenericDelegate<int>(GenericDelegateHandler);

			GD(3);

			// Kompilator zisti podla typu parametru aky je GENERIC parameter.
			GenericMethod(9);
			GenericMethod((byte) 4);

			// Explicitne zadam TYPE PARAMETER pre GENERIC METHOD.
			GenericMethod<long>(1);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// OPENED type.
			Type												T1=typeof(Dictionary<,>);

			Console.WriteLine(string.Format("T1: [{0}] !",T1));

			// OPENED type.
			Type												T2=typeof(SGenericStruct<>);

			Console.WriteLine(string.Format("T2: [{0}] !",T2));

			// CLOSED type.
			Type												T3=typeof(Dictionary<int,string>);

			Console.WriteLine(string.Format("T3: [{0}] !",T3));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CGenericClass<int>.MStaticValue=10;
			CGenericClass<float>.MStaticValue=999;

			Console.WriteLine(string.Format("CGenericClass<int>.MStaticValue [{0}] !",CGenericClass<int>.MStaticValue));
			Console.WriteLine(string.Format("CGenericClass<float>.MStaticValue [{0}] !",CGenericClass<float>.MStaticValue));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				CGenericStaticConstructor<int>					GSC=new CGenericStaticConstructor<int>();

				GSC.ClassMethod(100);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				// Tento typ staticky konstruktor nepovoli vytvorit.
				CGenericStaticConstructor<string>				GSC=new CGenericStaticConstructor<string>();

				GSC.ClassMethod("Timmy");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			// Testovanie porovnania (Value==null) a (Value!=null) pre VALUE TYPES.
			OpeatrorsEqualAndNotEqualTest<int>(10);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine(string.Format("typeof(CIntList)==typeof(List<int>): [{0}] !",typeof(CIntList)==typeof(List<int>)));

			// Kedze sa pouzil KEYWORD [using], TYPES su ZHODNE.
			Console.WriteLine(string.Format("typeof(CUsingIntList)==typeof(List<int>): [{0}] !",typeof(CUsingIntList)==typeof(List<int>)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			IGenericInterface<int>								GCI=new CGenericClass<int>();

			GCI.InterfaceMethod(7);

			IGenericInterface<int>								GSI=new SGenericStruct<int>();

			GSI.InterfaceMethod(2);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			DGenericDelegate<int>								GD=new DGenericDelegate<int>(GenericDelegateHandler);

			GD(3);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			CGenericClass<int>									GC=new CGenericClass<int>();

			// NON-GENERIC METHOD v GENERIC CLASS.
			GC.ClassMethod(6);

			// !!! GENERIC METHOD v GENERIC CLASS.
			GC.GenericMethod<string>("Timmy",12);

			// TYPE PARAMETER je INFERRED kompilatorom.
			GC.GenericMethod("Jenny",13);

			GenericMethod<string>("Timmy");

			// TYPE PARAMETER je INFERRED kompilatorom.
			GenericMethod("Timmy");

			// TYPE PARAMETERS su INFERRED kompilatorom.
			SameParams("Timmy","Anderson");

			string												Param1="Timmy";
			object												Param2="Anderson";

			// TYPE PARAMETERS su INFERRED kompilatorom.
			SameParams(Param1,Param2);

			// !!!!! REFERENCE TYPES su povazovane za IDENTICKE TYPES a preto aj ked sa do METHOD NEZASIELAJU ROVNAKE TYPES (aj ked METHOD to predpoklada), tak kedze OBE su REFERENCE TYPES, tak C# ich povazuje za IDENTICKE.
			SameParams(Param1,new object());

			// !!! TYPE PARAMETERS NEMOZU byt INFERRED kompilatorom, pretoze su NEROVNAKE.
			//SameParams(Param1,12);

			object												ParameterObject="Timmy Anderson";
			string												ParameterString="Timmy Anderson";

			// !!! Zavola sa GENERIC OVERRIDEN METHOD.
			GenericOverriden(ParameterObject);

			// !!! Zavola sa NON-GENERIC OVERRIDEN METHOD, ktora ma String ako PARAMETER.
			GenericOverriden(ParameterString);

			// !!! Zavola sa GENERIC OVERRIDEN METHOD, lebo sa EXPLICITNE vola GENERIC METHOD.
			GenericOverriden<string>(ParameterString);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			CBaseClass											BC=new CBaseClass(10);
			CDerivedClass										DC=new CDerivedClass(20);

			GenericMethodWithConstrain<CBaseClass,CDerivedClass>(BC,DC);

			// !!! Toto sa neprekompiluje, lebo nie je splneny CONSTRAINT medzi TYPOVYMI PARAMETRAMI.
			//GenericMethodWithConstrain<CDerivedClass,CBaseClass>(DC,BC);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			CConstrainsDerivedClass<int>						Class=new CConstrainsDerivedClass<int>();

			Class.VirtualMethod<string>();

			Class.Overloaded();

			Class.Overloaded<int>();

			Class.Overloaded<int,int>();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			CDerivedClass										Object=new CDerivedClass(100);

			// PRIMARY CONSTRAINT obsahuje TYPE CBaseClass.
			CPrimaryConstraintReferenceType<CBaseClass>			Object1=new CPrimaryConstraintReferenceType<CBaseClass>();

			Object1.PrintType(Object);

			// PRIMARY CONSTRAINT moze obsahovat aj TYPES, ktore su DERIVED z TYPE CBaseClass.
			CPrimaryConstraintReferenceType<CDerivedClass>		Object2=new CPrimaryConstraintReferenceType<CDerivedClass>();

			Object2.PrintType(Object);

			// !!! Hodi COMPILATION ERROR, lebo String NIE JE DERIVED z CBaseClass.
			/*
			CPrimaryConstraintReferenceType<String>				Object3=new CPrimaryConstraintReferenceType<String>();

			Object3.PrintType(Object);
			*/

			// !!! Hodi COMPILATION ERROR, lebo Int32 je VALUE TYPE.
			/*
			CPrimaryConstraintReferenceType<int>				Object4=new CPrimaryConstraintReferenceType<int>();

			Object4.PrintType(Object);
			*/
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			// PRIMARY CONSTRAINT obsahuje CLASS a CBaseClass je REFERENCE TYPE.
			CPrimaryConstraintClass<CBaseClass>					Object1=new CPrimaryConstraintClass<CBaseClass>();

			Object1.PrintType();

			// PRIMARY CONSTRAINT obsahuje CLASS a CBaseClass je REFERENCE TYPE.
			CPrimaryConstraintClass<CDerivedClass>				Object2=new CPrimaryConstraintClass<CDerivedClass>();

			Object2.PrintType();

			// !!! PRIMARY CONSTRAINT obsahuje CLASS  a String je REFERENCE TYPE.
			CPrimaryConstraintClass<String>						Object3=new CPrimaryConstraintClass<String>();

			Object3.PrintType();

			// !!! Hodi COMPILATION ERROR, lebo Int32 je VALUE TYPE a nie REFERENCE TYPE.
			/*
			CPrimaryConstraintClass<int>						Object4=new CPrimaryConstraintClass<int>();

			Object4.PrintType();
			*/
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			// !!! PRIMARY CONSTRAINT obsahuje STRUCT a CBaseClass je REFERENCE TYPE, takze COMPILER hodi ERROR.
			/*
			CPrimaryConstraintStruct<CBaseClass>				Object1=new CPrimaryConstraintStruct<CBaseClass>();

			Object1.PrintType();
			*/

			// !!! PRIMARY CONSTRAINT obsahuje STRUCT a String je REFERENCE TYPE, takze COMPILER hodi ERROR.
			/*
			CPrimaryConstraintStruct<String>					Object2=new CPrimaryConstraintStruct<String>();

			Object2.PrintType();
			*/

			// PRIMARY CONSTRAINT je STRUCT a Int32 je VALUE TYPE.
			CPrimaryConstraintStruct<int>						Object3=new CPrimaryConstraintStruct<int>();

			Object3.PrintType();

			// PRIMARY CONSTRAINT je STRUCT a EEnum je VALUE TYPE.
			CPrimaryConstraintStruct<EEnum>						Object4=new CPrimaryConstraintStruct<EEnum>();

			Object4.PrintType();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			// PRIMARY CONSTRAINT obsahuje TYPE CBaseClass.
			SPrimaryConstraintOnValueType<CBaseClass>			Object1=new SPrimaryConstraintOnValueType<CBaseClass>();

			Object1.PrintType();

			// PRIMARY CONSTRAINT moze obsahovat aj TYPES, ktore su DERIVED z TYPE CBaseClass.
			SPrimaryConstraintOnValueType<CDerivedClass>		Object2=new SPrimaryConstraintOnValueType<CDerivedClass>();

			Object2.PrintType();

			// !!! Hodi COMPILATION ERROR, lebo String NIE JE DERIVED z CBaseClass.
			/*
			SPrimaryConstraintOnValueType<String>				Object3=new SPrimaryConstraintOnValueType<String>();

			Object3.PrintType();
			*/

			// !!! Hodi COMPILATION ERROR, lebo Int32 je VALUE TYPE.
			/*
			SPrimaryConstraintOnValueType<int>					Object4=new SPrimaryConstraintOnValueType<int>();

			Object4.PrintType();
			*/
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			// TYPE Int32 implementuje VSETKY INTERFACES IFormattable, IComparable, IComparable<TParam>.
			CSecondaryConstraint<int>							Object1=new CSecondaryConstraint<int>();

			Object1.PrintType();

			// !!!! Kedze EEnum NEIMPLEMENTUJE IComparable<TParam>, tak COMPILER hodi ERROR.
			/*
			CSecondaryConstraint<EEnum>							Object2=new CSecondaryConstraint<EEnum>();

			Object2.PrintType();
			*/

			// TYPE DateTime implementuje VSETKY INTERFACES IFormattable, IComparable, IComparable<TParam>.
			CSecondaryConstraint<DateTime>						Object3=new CSecondaryConstraint<DateTime>();

			Object3.PrintType();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			// TYPE Int32 implementuje VSETKY INTERFACES IFormattable, IComparable, IComparable<TParam>.
			SSecondaryConstraint<int>							Object1=new SSecondaryConstraint<int>();

			Object1.PrintType();

			// !!!! Kedze EEnum NEIMPLEMENTUJE IComparable<TParam>, tak COMPILER hodi ERROR.
			/*
			SSecondaryConstraint<EEnum>							Object2=new SSecondaryConstraint<EEnum>();

			Object2.PrintType();
			*/

			// TYPE DateTime implementuje VSETKY INTERFACES IFormattable, IComparable, IComparable<TParam>.
			SSecondaryConstraint<DateTime>						Object3=new SSecondaryConstraint<DateTime>();

			Object3.PrintType();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			// !!! Kedze CDerivedClass je DERIVED z CBaseClass NAKED TYPE PARAMETER CONSTRAINT je splneny.
			CNakedTypeParameterConstraint<CBaseClass,CDerivedClass>	Object1=new CNakedTypeParameterConstraint<CBaseClass,CDerivedClass>();

			Object1.PrintType();

			// !!! Kedze String je DERIVED z Object NAKED TYPE PARAMETER CONSTRAINT je splneny.
			CNakedTypeParameterConstraint<object,string>		Object2=new CNakedTypeParameterConstraint<object,string>();

			Object2.PrintType();

			// !!! Kedze Object NIE je DERIVED zo String NAKED TYPE PARAMETER CONSTRAINT NIE je splneny a COMPILER hodi ERROR.
			/*
			CNakedTypeParameterConstraint<string,object>		Object3=new CNakedTypeParameterConstraint<string,object>();

			Object3.PrintType();
			*/

			// !!!!! C# tento CODE AKCEPTUJE, aj ked String NIE JE DERIVED zo String, no kedze su TYPES IDENTICKE, tak CONSTRAINT povazuje za splneny.
			CNakedTypeParameterConstraint<string,string>		Object4=new CNakedTypeParameterConstraint<string,string>();

			Object4.PrintType();

			// !!!!! C# tento CODE AKCEPTUJE pretoze String IMPLEMENTUJE INTERFACE IComparable.
			CNakedTypeParameterConstraint<IComparable,string>	Object5=new CNakedTypeParameterConstraint<IComparable,string>();

			Object5.PrintType();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			CConstructorConstraint<int>							Object1=new CConstructorConstraint<int>();

			Console.WriteLine(string.Format("Object1 [{0}] !",Object1.CreateType()));
			
			CConstructorConstraint<EEnum>						Object2=new CConstructorConstraint<EEnum>();

			Console.WriteLine(string.Format("Object2 [{0}] !",Object2.CreateType()));

			// Hodi COMPILATION ERROR, pretoze CLASS CBaseClass NEMA DEFAULT CONSTRUCTOR.
			/*
			CConstructorConstraint<CBaseClass>					Object3=new CConstructorConstraint<CBaseClass>();

			Console.WriteLine(string.Format("Object3 [{0}] !",Object3.CreateType()));
			*/
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			CDerivedClass										DerivedClass=new CDerivedClass(100);

			CConversionSamples.Sample1<CBaseClass,CDerivedClass>(DerivedClass);

			List<int>											List=new CUsingIntList();

			CConversionSamples.Sample2<List<int>,int>(List);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			// !!! CLR robi VYNIMKU a v GENERIC CONSTRUCTS UMOZNUJE porovnat aj VALUE TYPES s NULL.
			COperators.Test1<int>(100);

			// !!! CLR robi VYNIMKU a v GENERIC CONSTRUCTS UMOZNUJE porovnat aj VALUE TYPES s NULL.
			COperators.Test2<int>(100);

			COperators.Test1<string>("Timmy Anderson");

			COperators.Test2<string>("Timmy Anderson");

			COperators.Test1<string>(null);

			COperators.Test2<string>(null);
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
			//Test11();
			//Test12();
			//Test13();
			//Test14();
			//Test15();
			//Test16();
			//Test17();
			//Test18();
			//Test19();
			//Test20();
			Test21();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------