//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje VALUE TYPE s VIRTUAL METHODS.
    .class public auto ansi value sealed CValueTypeVirtualMethodsClass extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CValueTypeVirtualMethodsClass CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! DERIVED CLASSES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
			ldarg							0
			call							instance void [mscorlib]System.ValueType::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void NonVirtualMethod() cil managed
		{
			ldstr							"CValueTypeVirtualMethodsClass::NonVirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod() cil managed
		{
			ldstr							"CValueTypeVirtualMethodsClass::VirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------