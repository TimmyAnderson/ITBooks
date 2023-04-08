//-------------------------------------------------------------------------------------------------------
.namespace ILInstructions
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
			stfld							string ILInstructions.CComplexValueType::MValue1

			ldarg.0
			ldarg.2
			stfld							int32 ILInstructions.CComplexValueType::MValue2

			ret
		}
//-------------------------------------------------------------------------------------------------------
	    .method public instance void InstanceMethod(string Prefix) cil managed
		{
			ldstr							"VALUE TYPE [{0}] - Name: [{1}], Age [{2}] !"

			ldarg							Prefix

			ldarg.0
			ldfld							string ILInstructions.CComplexValueType::MValue1

			ldarg.0
			ldfld							int32 ILInstructions.CComplexValueType::MValue2
			box								[mscorlib]System.Int32

			call							string [mscorlib]System.String::Format(string,object,object,object)

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
}
//-------------------------------------------------------------------------------------------------------