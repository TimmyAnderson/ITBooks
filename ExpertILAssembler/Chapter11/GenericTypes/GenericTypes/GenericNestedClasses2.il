//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
// Kombinacia GENERIC ENCLOSING TYPE a NON-GENERIC NESTED TYPE.
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEnclosingGenericNonGeneric<TParam> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.class nested public auto ansi CNestedGenericNonGeneric extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.method public specialname rtspecialname instance void .ctor() cil managed
			{
				ldstr						"GenericTypes.CEnclosingGenericNonGeneric<!TParam>/CNestedGenericNonGeneric CONSTRUCTOR CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ldarg						0
				call						instance void [mscorlib]System.Object::.ctor()

				ret
			}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
			.method public hidebysig instance void Test() cil managed
			{
				ldstr						"GenericTypes.CEnclosingGenericNonGeneric<!TParam>/CNestedGenericNonGeneric::Test() CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ret
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.field private !TParam									MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"GenericTypes.CEnclosingGenericNonGeneric<TParam> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public hidebysig instance void Test(!TParam Param) cil managed
		{
			ldarg							0
			ldarg							Param
			stfld							!TParam class GenericTypes.CEnclosingGenericNonGeneric<!0>::MField

			ldstr							"GenericTypes.CEnclosingGenericNonGeneric<!TParam>::Test() CALLED - MField [{0}] !"
			ldarg							0
			ldfld							!TParam class GenericTypes.CEnclosingGenericNonGeneric<!0>::MField
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------