//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CBase extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CBase CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod1() cil managed
		{
			ldstr							"CBase::VirtualMethod1() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod2() cil managed
		{
			ldstr							"CBase::VirtualMethod2() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod3() cil managed
		{
			ldstr							"CBase::VirtualMethod3() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod4() cil managed
		{
			ldstr							"CBase::VirtualMethod4() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod5() cil managed
		{
			ldstr							"CBase::VirtualMethod5() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void VirtualMethod6() cil managed
		{
			ldstr							"CBase::VirtualMethod6() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CDerived extends Methods.CBase
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CDerived CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void Methods.CBase::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Kedze sa pouziva EXPLICIT METHOD OVERRIDING, tak OVERRIDDEN METHOD moze mat ODLISNY NAME.
        .method public hidebysig virtual void DerivedVirtualMethod1() cil managed
		{
			// !!! EXPLICIT METHOD OVERRIDING je definovany v METHOD BODY.
			.override						Methods.CBase::VirtualMethod1

			ldstr							"CDerived::DerivedVirtualMethod1() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void DerivedVirtualMethod2And3And4() cil managed
		{
			// !!! Jedna METHOD moze vykonat EXPLICIT METHOD OVERRIDING pre VIACERO METHODS z BASE CLASS.
			.override						Methods.CBase::VirtualMethod2
			.override						Methods.CBase::VirtualMethod3
			.override						Methods.CBase::VirtualMethod4

			ldstr							"CDerived::DerivedVirtualMethod2And3And4() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! EXPLICIT METHOD OVERRIDING je definovane na CLASS LEVEL.
        .method public hidebysig virtual void DerivedVirtualMethod5() cil managed
		{
			ldstr							"CDerived::DerivedVirtualMethod5() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! EXPLICIT METHOD OVERRIDING moze byt definovany aj v CLASS BODY.
		.override							Methods.CBase::VirtualMethod5 with instance void Methods.CDerived::DerivedVirtualMethod5()
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSuperDerived extends Methods.CDerived
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CSuperDerived CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void Methods.CDerived::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void SuperDerivedVirtualMethod1() cil managed
		{
			// !!! Vykonava sa EXPLICIT METHOD OVERRIDING pre METHOD CDerived::DerivedVirtualMethod1().
			.override						Methods.CDerived::DerivedVirtualMethod1

			ldstr							"CSuperDerived::SuperDerivedVirtualMethod1() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void SuperDerivedVirtualMethod3() cil managed
		{
			// !!! Vykonava sa EXPLICIT METHOD OVERRIDING pre METHOD CBase::VirtualMethod3().
			.override						Methods.CBase::VirtualMethod3

			ldstr							"CSuperDerived::SuperDerivedVirtualMethod3() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! EXPLICIT METHOD OVERRIDING je definovane na CLASS LEVEL.
        .method public hidebysig virtual void SuperDerivedVirtualMethod5() cil managed
		{
			ldstr							"CSuperDerived::SuperDerivedVirtualMethod5() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig virtual void SuperDerivedVirtualMethod6() cil managed
		{
			// !!! Vykonava sa EXPLICIT METHOD OVERRIDING pre METHOD CDerived::VirtualMethod6().
			.override						Methods.CDerived::VirtualMethod6
			// !!! Alternativna SYNTAX s vyuzitim KEYWORD [.base].
			//.override						.base::VirtualMethod6

			ldstr							"CSuperDerived::SuperDerivedVirtualMethod6() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! EXPLICIT METHOD OVERRIDING moze byt definovany aj v CLASS BODY.
		.override							Methods.CDerived::VirtualMethod5 with instance void Methods.CSuperDerived::SuperDerivedVirtualMethod5()
		// !!! Alternativna SYNTAX s vyuzitim KEYWORD [.base].
		//.override							.base::VirtualMethod5 with instance void Methods.CSuperDerived::SuperDerivedVirtualMethod5()
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------