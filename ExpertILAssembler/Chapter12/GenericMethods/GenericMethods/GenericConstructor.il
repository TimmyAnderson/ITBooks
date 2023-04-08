//-------------------------------------------------------------------------------------------------------
.namespace GenericMethods
{
//-------------------------------------------------------------------------------------------------------
	.class public auto ansi CGenericConstructor extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor<TParam>(!!TParam Param) cil managed
		{
			ldstr							"CGenericConstructor<TParam> CONSTRUCTOR CALLED - [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD IMPLICITNE pretazuje METHOD z INTERFACE IInterface.
        .method public hidebysig virtual instance void Print<TParam>(!!TParam Param) cil managed
		{
			ldstr							"Print(!!TParam Param) - [{0}] !"
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