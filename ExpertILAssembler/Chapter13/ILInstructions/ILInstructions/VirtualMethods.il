//-------------------------------------------------------------------------------------------------------
.namespace ILInstructions
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CBaseClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CBaseClass CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! DERIVED CLASSES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void NonVirtualMethod() cil managed
		{
			ldstr							"CBaseClass::NonVirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod() cil managed
		{
			ldstr							"CBaseClass::VirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualNewSlotMethod() cil managed
		{
			ldstr							"CBaseClass::VirtualNewSlotMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual final void VirtualFinalMethod() cil managed
		{
			ldstr							"CBaseClass::VirtualFinalMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CDerivedClass extends ILInstructions.CBaseClass
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CDerivedClass CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! DERIVED CLASSES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
			ldarg							0
			call							instance void ILInstructions.CBaseClass::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void NonVirtualMethod() cil managed
		{
			ldstr							"CDerivedClass::NonVirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod() cil managed
		{
			ldstr							"CDerivedClass::VirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Na METHOD je aplikovany FLAG [newslot] a preto NEVYKONA OVERRIDING METHOD CBaseClass::VirtualNewSlotMethod(), ale bude mat vo VIRTUAL METHOD TABLE VLASTNU ENTRY.
        .method public hidebysig virtual newslot void VirtualNewSlotMethod() cil managed
		{
			ldstr							"CDerivedClass::VirtualNewSlotMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------