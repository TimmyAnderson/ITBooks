//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly ValueTypes {}
.module ValueTypes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace ValueTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!! VALUE TYPES MUSIA byt SEALED.
    .class public auto ansi value sealed CComplexValueType extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
		.field public string 				MValue1
		.field public int32 				MValue2
		.field public static string 		MStaticValue
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CComplexValueType.ctor() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! VALUE TYPES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
			ldarg							0
			call							instance void [mscorlib]System.ValueType::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor(string Value1, int32 Value2) cil managed
		{
			ldstr							"CComplexValueType.ctor(string,int) CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			ldarg.1
			stfld							string ValueTypes.CComplexValueType::MValue1

			ldarg.0
			ldarg.2
			stfld							int32 ValueTypes.CComplexValueType::MValue2

			ret
		}
//-------------------------------------------------------------------------------------------------------
	    .method public instance void InstanceMethod() cil managed
		{
			ldstr							"VALUE TYPE - Name: [{0}], Age [{1}] !"

			ldarg.0
			ldfld							string ValueTypes.CComplexValueType::MValue1

			ldarg.0
			ldfld							int32 ValueTypes.CComplexValueType::MValue2
			box								[mscorlib]System.Int32

			call							string [mscorlib]System.String::Format(string,object,object)

	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	    .method public static void StaticMethod() cil managed
		{
			ldstr							"This is STATIC METHOD !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CValueTypes extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init					(valuetype ValueTypes.CComplexValueType Value)

			ldloca							Value
			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			call							instance void valuetype ValueTypes.CComplexValueType::.ctor(string,int32)

			ldstr							"This is STATIC VARIABLE !"
			stsfld							string ValueTypes.CComplexValueType::MStaticValue

			ldstr							"STATIC FIELD [{0}] !"
			ldsfld							string ValueTypes.CComplexValueType::MStaticValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"FIELD [{0}] !"
			ldloca							Value
			ldfld							string ValueTypes.CComplexValueType::MValue1
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloca							Value
			call							instance void ValueTypes.CComplexValueType::InstanceMethod()

			call							void ValueTypes.CComplexValueType::StaticMethod()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------