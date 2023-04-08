//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
// Kombinacia NON-GENERIC ENCLOSING TYPE a GENERIC NESTED TYPE.
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEnclosingNonGenericGeneric extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.class nested public auto ansi CNestedNonGenericGeneric<TParam> extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.field private !TParam								MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
			.method public specialname rtspecialname instance void .ctor() cil managed
			{
				ldstr						"GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<!TParam> CONSTRUCTOR CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ldarg						0
				call						instance void [mscorlib]System.Object::.ctor()

				ret
			}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	        .method public hidebysig instance void Test(!TParam Param) cil managed
			{
				ldarg						0
				ldarg						Param
				stfld						!TParam class GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<!0>::MField

				ldstr						"GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<!TParam>::Test() CALLED - MField [{0}] !"
				ldarg						0
				ldfld						!TParam class GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<!0>::MField
				box							!TParam
				call						string [mscorlib]System.String::Format(string,object)
				call						void [mscorlib]System.Console::WriteLine(string)

				ret
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"GenericTypes.CEnclosingNonGenericGeneric CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig instance void Test() cil managed
		{
			ldstr							"GenericTypes.CEnclosingNonGenericGeneric::Test() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------