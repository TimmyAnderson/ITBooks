//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGenericClass<TParam> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field private !TParam									MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CGenericClass<TParam> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void SetField(!TParam Param) cil managed
		{
			ldarg							0
			ldarg							Param
			stfld							!0 class GenericTypes.CGenericClass<!TParam>::MField

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void PrintField() cil managed
		{
			ldstr							"TEST - MField [{0}] !"

			ldarg							0
			ldfld							!0 class GenericTypes.CGenericClass<!TParam>::MField
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