//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
// Kombinacia GENERIC ENCLOSING TYPE a GENERIC NESTED TYPE.
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEnclosingGenericGeneric<TParam1> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.class nested public auto ansi CNestedGenericGeneric<TParam2> extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.field private !TParam2								MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
			.method public specialname rtspecialname instance void .ctor() cil managed
			{
				ldstr						"GenericTypes.CEnclosingGenericGeneric<!TParam1>/CNestedGenericGeneric<!TParam2> CONSTRUCTOR CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ldarg						0
				call						instance void [mscorlib]System.Object::.ctor()

				ret
			}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	        .method public hidebysig instance void Test(!TParam2 Param) cil managed
			{
				ldarg						0
				ldarg						Param
				stfld						!TParam2 class GenericTypes.CEnclosingGenericGeneric/CNestedGenericGeneric<!0>::MField

				ldstr						"GenericTypes.CEnclosingGenericGeneric<!TParam1>/CNestedGenericGeneric<!TParam2>::Test() CALLED - MField [{0}] !"
				ldarg						0
				ldfld						!TParam2 class GenericTypes.CEnclosingGenericGeneric/CNestedGenericGeneric<!0>::MField
				box							!TParam2
				call						string [mscorlib]System.String::Format(string,object)
				call						void [mscorlib]System.Console::WriteLine(string)

				ret
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.field private !TParam1									MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"GenericTypes.CEnclosingGenericGeneric<!TParam1> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public hidebysig instance void Test(!TParam1 Param) cil managed
		{
			ldarg							0
			ldarg							Param
			stfld							!TParam1 class GenericTypes.CEnclosingGenericGeneric<!0>::MField

			ldstr							"GenericTypes.CEnclosingGenericGeneric<!TParam1>::Test() CALLED - MField [{0}] !"
			ldarg							0
			ldfld							!TParam1 class GenericTypes.CEnclosingGenericGeneric<!TParam1>::MField
			box								!TParam1
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------