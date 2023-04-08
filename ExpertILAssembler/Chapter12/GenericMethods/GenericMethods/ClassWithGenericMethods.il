//-------------------------------------------------------------------------------------------------------
.namespace GenericMethods
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CClassWithGenericMethods extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CClassWithGenericMethods CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void StaticGenericMethod<TParam>(!!TParam Param) cil managed
		{
			ldstr							"StaticGenericMethod<TParam>() CALLED - PARAM [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void NonStaticGenericMethod<TParam>(!!TParam Param) cil managed
		{
			ldstr							"NonStaticGenericMethod<TParam>() CALLED - PARAM [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------