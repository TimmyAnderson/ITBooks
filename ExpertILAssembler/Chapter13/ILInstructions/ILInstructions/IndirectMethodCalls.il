//-------------------------------------------------------------------------------------------------------
.namespace ILInstructions
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CIndirectMethodCallsBase extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field famandassem string								MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CIndirectMethodCallsBase CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ldarg							0
			ldstr							"XXX"
			stfld							string ILInstructions.CIndirectMethodCallsBase::MField

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual string VirtualMethod(string Name, int32 Age) cil managed
		{
			ldstr							"BASE - NAME [{0}], AGE [{1}], FIELD [{2}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			ldarg							0
			ldfld							string ILInstructions.CIndirectMethodCallsBase::MField
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vlozi RETURN VALUE do STACK.
			ldstr							"BASE RETURN VALUE"

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance string NonStaticMethod(string Name, int32 Age) cil managed
		{
			ldstr							"NON-STATIC - NAME [{0}], AGE [{1}], FIELD [{2}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			ldarg							0
			ldfld							string ILInstructions.CIndirectMethodCallsBase::MField
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vlozi RETURN VALUE do STACK.
			ldstr							"NON-STACK RETURN VALUE"

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static string StaticMethod(string Name, int32 Age) cil managed
		{
			ldstr							"STATIC - NAME [{0}], AGE [{1}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vlozi RETURN VALUE do STACK.
			ldstr							"STATIC RETURN VALUE"

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CIndirectMethodCallsDerived extends ILInstructions.CIndirectMethodCallsBase
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CIndirectMethodCallsDerived CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void ILInstructions.CIndirectMethodCallsBase::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual string VirtualMethod(string Name, int32 Age) cil managed
		{
			ldstr							"DERIVED - NAME [{0}], AGE [{1}], FIELD [{2}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			ldarg							0
			ldfld							string ILInstructions.CIndirectMethodCallsBase::MField
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vlozi RETURN VALUE do STACK.
			ldstr							"DERIVED RETURN VALUE"

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------