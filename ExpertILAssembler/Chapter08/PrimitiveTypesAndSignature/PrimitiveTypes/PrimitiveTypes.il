//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly PrimitiveTypes {}
.module PrimitiveTypes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace PrimitiveTypes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CPrimitiveTypes extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! COMPILER to akceptuje, ale program OKAMZITE hodi EXCEPTION.
		//.field static int32&				MManagedPointer
		// !!! UNMANAGED FIELDS su povolene.
		.field static int32*				MUnmanagedPointer
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void CallbackMethod(string Param) cil managed
		{
			ldstr							"CALLBACK METHOD CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			.locals init					(int32 Value1, native int Value2)

			ldc.i4							12
			stloc							Value1

			ldc.i8							121212
			stloc							Value2

			ldstr							"TEST1 - VALUE1 is [{0}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"TEST1 - VALUE2 is [{0}] !"
			ldloc							Value2
			// Predpoklada PLATFORM X64.
			box								[mscorlib]System.Int64
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			// Obsahuje UNMANAGED POINTER.
			.locals init					(int32 Value1, int32* PointerValue1)
			// Obsahuje MANAGED POINTER.
			.locals init					(int32 Value2, int32& PointerValue2)
			.locals init					(int32 Value3)
			// !!! Obsahuje MANAGED POINTER na OBJECT REFERENCE.
			.locals init					(string Value4, string& PointerValue4)

			ldc.i4							356
			stloc							Value1

			ldloca							Value1
			conv.u
			stloc							PointerValue1

			ldstr							"TEST2 - VALUE1 is [{0}] !"
			ldloc							PointerValue1
			// !!! Spravi DEREFERENCE POINTER na INT32.
			ldind.i4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							456
			stloc							Value2

			ldloca							Value2
			conv.u
			stloc							PointerValue2

			ldstr							"TEST2 - VALUE2 is [{0}] !"
			ldloc							PointerValue2
			// !!! Spravi DEREFERENCE POINTER na INT32.
			ldind.i4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							556
			stloc							Value3

			ldloca							Value3
			conv.u
			// !!! POINTER je zapisany do FIELD typu UNMANAGED POINTER.
			stsfld							int32* PrimitiveTypes.CPrimitiveTypes::MUnmanagedPointer

			ldstr							"TEST2 - VALUE2 is [{0}] !"
			ldsfld							int32* PrimitiveTypes.CPrimitiveTypes::MUnmanagedPointer
			// !!! Spravi DEREFERENCE POINTER na INT32.
			ldind.i4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"OBJECT REFERENCE !"
			stloc							Value4

			// !!! Ziska sa MANAGED POINTER na OBJECT REFERENCE.
			ldloca							Value4
			conv.u
			stloc							PointerValue4

			ldloc							PointerValue4
			// !!! Spravi DEREFERENCE POINTER na OBJECT REFERENCE.
			ldind.ref 
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			.locals init					(method void * (string) FunctionPointer)

			// !!!!! Ziska sa POINTER na FUNCTION.
			ldftn							void PrimitiveTypes.CPrimitiveTypes::CallbackMethod(string)
			// !!! POINTER na FUNCTION sa ulozi do LOCAL VARIABLE.
			stloc							FunctionPointer

			// !!! PARAMETERS musia byt ako PRVE.
			ldstr							"CALLBACK PARAM !"
			// !!! POINTER na FUNCTION sa nacita z LOCAL VARIABLE.
			ldloc							FunctionPointer
			calli							void (string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			call							void PrimitiveTypes.CPrimitiveTypes::Test1()
			call							void PrimitiveTypes.CPrimitiveTypes::Test2()
			call							void PrimitiveTypes.CPrimitiveTypes::Test3()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------