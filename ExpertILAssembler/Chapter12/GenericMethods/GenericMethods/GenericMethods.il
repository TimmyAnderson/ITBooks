//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly GenericMethods {}
.module GenericMethods.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "ClassWithGenericMethods.il"
#include "GenericClassWithGenericMethods.il"
#include "GenericMethodInheritance.il"
#include "GenericConstructor.il"
//-------------------------------------------------------------------------------------------------------
.namespace GenericMethods
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGenericMethods extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.method private hidebysig static void MethodWithGenericConstrain<(class [mscorlib]System.IEquatable`1<!!TParam>) TParam>(!!TParam Value) cil managed
		{
			ldstr							"METHOD - Value [{0}] !"
			ldarg							Value
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig static !!TParam3 GenericMethod<TParam1,TParam2,TParam3>(!!TParam1 Param1, !!TParam2 Param2, !!TParam3 Param3) cil managed
		{
            .locals							init (!!TParam1 Value1, !!TParam2 Value2, !!TParam3 Value3)

			ldarg							Param1
			stloc							Value1

			ldarg							Param2
			stloc							Value2

			ldarg							Param3
			stloc							Value3

			ldstr							"METHOD - Value1 [{0}], Value2 [{1}], Value3 [{2}] !"

			ldloc							Value1
			box								!!TParam1
			ldloc							Value2
			box								!!TParam2
			ldloc							Value3
			box								!!TParam3

			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Nastavi sa RETURN VALUE.
			ldloc							Value3

			ret
	}		
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig static void GenericMethodWithConstraints<([mscorlib]System.ICloneable) TParam1,([mscorlib]System.IFormattable) TParam2>(!!TParam1 Param1, !!TParam2 Param2) cil managed
		{
            .locals							init (!!TParam1 Value1, !!TParam2 Value2)

			ldarg							Param1
			stloc							Value1

			ldarg							Param2
			stloc							Value2

			ldstr							"METHOD - Value1 [{0}], Value2 [{1}] !"

			ldloc							Value1
			box								!!TParam1
			ldloc							Value2
			box								!!TParam2

			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
            .locals							init (float32 Value)

			ldstr							"Timmy Anderson"
			ldc.i4							12
			ldc.r4							123.456
			call							!!2 GenericMethods.CGenericMethods::GenericMethod<string,int32,float32>(!!0,!!1,!!2)
			// Ulozi sa RETURN VALUE.
			stloc							Value

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							Value
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
            .locals							init (class GenericMethods.CClassWithGenericMethods Object)

			newobj							instance void class GenericMethods.CClassWithGenericMethods::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericMethods.CClassWithGenericMethods::NonStaticGenericMethod<string>(!!0)

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericMethods.CClassWithGenericMethods::NonStaticGenericMethod<int32>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			ldstr							"Timmy Anderson"
			call							void class GenericMethods.CClassWithGenericMethods::StaticGenericMethod<string>(!!0)

			ldc.i4							12
			call							void class GenericMethods.CClassWithGenericMethods::StaticGenericMethod<int32>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
			// !!! GENERIC CLASS ma INY TYPE PARAMETER ako jeho MEMBER GENERIC METHOD.
            .locals							init (class GenericMethods.CGenericClassWithGenericMethods<float64> Object)

			newobj							instance void class GenericMethods.CGenericClassWithGenericMethods<float64>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericMethods.CGenericClassWithGenericMethods<float64>::NonStaticGenericMethod<string>(!!0)

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericMethods.CGenericClassWithGenericMethods<float64>::NonStaticGenericMethod<int32>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
			// !!! GENERIC CLASS ma INY TYPE PARAMETER ako jeho MEMBER GENERIC METHOD.
			ldstr							"Timmy Anderson"
			call							void class GenericMethods.CGenericClassWithGenericMethods<float64>::StaticGenericMethod<string>(!!0)

			ldc.i4							12
			call							void class GenericMethods.CGenericClassWithGenericMethods<float64>::StaticGenericMethod<int32>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							void GenericMethods.CGenericMethods::GenericMethodWithConstraints<string,int32>(!!0,!!1)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test7() cil managed
		{
            .locals							init (method void *(string,int32) GenericMethodPointer)

			// !!! Demonstruje ziskanie POINTER na GENERIC METHOD.
			ldftn							void GenericMethods.CGenericMethods::GenericMethodWithConstraints<string,int32>(!!0,!!1)
			stloc							GenericMethodPointer

			ldstr							"Timmy Anderson"
			ldc.i4							12
			ldloc							GenericMethodPointer
			// !!! Demonstruje volanie GENERIC METHOD cez POINTER na METHOD.
			calli							void(string,int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
            .locals							init (class GenericMethods.CDerivedClass Object, class GenericMethods.IInterface Interface)

			newobj							instance void class GenericMethods.CDerivedClass::.ctor()
			stloc							Object

			ldloc							Object
			castclass						class GenericMethods.IInterface
			stloc							Interface

			ldloc							Interface
			ldstr							"Timmy Anderson"
			callvirt						instance void GenericMethods.IInterface::Print1<string>(!!0)

			ldloc							Interface
			ldc.i4							12
			callvirt						instance void GenericMethods.IInterface::Print1<int32>(!!0)

			ldloc							Interface
			ldstr							"Timmy Anderson"
			callvirt						instance void GenericMethods.IInterface::Print2<string>(!!0)

			ldloc							Interface
			ldc.i4							12
			callvirt						instance void GenericMethods.IInterface::Print2<int32>(!!0)

			ldloc							Interface
			ldstr							"Timmy Anderson"
			callvirt						instance void GenericMethods.IInterface::Print3<string>(!!0)

			ldloc							Interface
			ldc.i4							12
			callvirt						instance void GenericMethods.IInterface::Print3<int32>(!!0)

			ldloc							Interface
			ldstr							"Timmy Anderson"
			ldc.i4							12
			callvirt						instance void GenericMethods.IInterface::Print4<string,int32>(!!0,!!1)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
            .locals							init (class GenericMethods.CGenericConstructor Object)

			ldstr							"Timmy Anderson"
			newobj							instance void class GenericMethods.CGenericConstructor::.ctor<string>(!!0)
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			callvirt						instance void GenericMethods.CGenericConstructor::Print<string>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test10() cil managed
		{
			ldstr							"Timmy Anderson"
			call							void GenericMethods.CGenericMethods::MethodWithGenericConstrain<string>(!!0)

			ldc.i4							12
			call							void GenericMethods.CGenericMethods::MethodWithGenericConstrain<int32>(!!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void GenericMethods.CGenericMethods::Test1()
			//call							void GenericMethods.CGenericMethods::Test2()
			//call							void GenericMethods.CGenericMethods::Test3()
			//call							void GenericMethods.CGenericMethods::Test4()
			//call							void GenericMethods.CGenericMethods::Test5()
			//call							void GenericMethods.CGenericMethods::Test6()
			//call							void GenericMethods.CGenericMethods::Test7()
			//call							void GenericMethods.CGenericMethods::Test8()
			//call							void GenericMethods.CGenericMethods::Test9()
			call							void GenericMethods.CGenericMethods::Test10()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------