//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Methods {}
.module Methods.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "StaticNonStatic.il"
#include "VirtualMethods.il"
#include "ValueTypeVirtualMethods.il"
#include "ExplicitMethodOverriding.il"
#include "LocalVariables.il"
#include "StaticConstructors.il"
#include "Finalizers.il"
#include "VariableParametersMethods.il"
#include "Overloading.il"
//-------------------------------------------------------------------------------------------------------
// !!! GLOBAL METHOD.
.method public hidebysig static void GlobalMethod() cil managed
{
	ldstr									"METHOD [GlobalMethod()] CALLED !"
	call									void [mscorlib]System.Console::WriteLine(string)

	ret
}
//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
	// !!! GLOBAL METHOD.
	// !!!!! Na GLOBAL METHODS sa NEAPLIKUJU NAMESPACES.
    .method public hidebysig static void GlobalMethodWithNamespace() cil managed
	{
		ldstr								"METHOD [GlobalMethodWithNamespace()] CALLED !"
		call								void [mscorlib]System.Console::WriteLine(string)

		ret
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CMethods extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			ldstr							"This is PARAM 1 !"
			ldstr							"This is PARAM 2 !"
			call							void Methods.CStaticNonStatic::StaticMethod(string,string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			newobj							instance void Methods.CStaticNonStatic::.ctor()
			ldstr							"This is PARAM 1 !"
			ldstr							"This is PARAM 2 !"
			call							instance void Methods.CStaticNonStatic::NonStaticMethod(string,string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
            .locals							init (class Methods.CDerivedClass Derived, class Methods.CBaseClass Base)

			newobj							instance void Methods.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa NON-VIRTUAL METHOD NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			call							instance void Methods.CDerivedClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			call							instance void Methods.CDerivedClass::NonVirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			call							instance void Methods.CBaseClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			call							instance void Methods.CBaseClass::NonVirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa NON-VIRTUAL METHOD VIRTUALNE. Kedze METHODS su NON-VIRTUAL, tak sa volaju NON-VIRTUAL.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			callvirt						instance void Methods.CDerivedClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			callvirt						instance void Methods.CDerivedClass::NonVirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			callvirt						instance void Methods.CBaseClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			callvirt						instance void Methods.CBaseClass::NonVirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
            .locals							init (class Methods.CDerivedClass Derived, class Methods.CBaseClass Base)

			newobj							instance void Methods.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			call							instance void Methods.CDerivedClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			call							instance void Methods.CDerivedClass::VirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualMethod().
			call							instance void Methods.CBaseClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualMethod().
			call							instance void Methods.CBaseClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa VIRTUAL METHOD VIRTUALNE. Kedze METHODS su VIRTUAL, tak sa volaju VIRTUAL.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualMethod()
			ldloc							Derived
			// !!!!! Zavola sa METHOD CDerivedClass::VirtualMethod(), pretoze METHOD je VIRTUAL.
			callvirt						instance void Methods.CBaseClass::VirtualMethod()
			ldloc							Base
			// !!!!! Zavola sa METHOD CDerivedClass::VirtualMethod(), pretoze METHOD je VIRTUAL.
			callvirt						instance void Methods.CBaseClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
            .locals							init (class Methods.CDerivedClass Derived, class Methods.CBaseClass Base)

			newobj							instance void Methods.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			call							instance void Methods.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			call							instance void Methods.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualNewSlotMethod().
			call							instance void Methods.CBaseClass::VirtualNewSlotMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualNewSlotMethod().
			call							instance void Methods.CBaseClass::VirtualNewSlotMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Aj ked METHOD je VIRTUAL volana VIRTUALNE, kedze na METHOD CDerivedClass::VirtualNewSlotMethod() bol aplikovany FLAG [newslot], METHOD CDerivedClass::VirtualNewSlotMethod() ma VLASTNU ENTRY vo VIRTUAL METHOD TABLE a NIE JE NIJAKO ZVIAZANA s METHOD CBaseClass::VirtualNewSlotMethod().
			ldloc							Derived
			// !!! Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Base
			// !!! Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Derived
			// !!!!! Zavola sa METHOD CBaseClass::VirtualNewSlotMethod(), pretoze METHOD aj ked je VIRTUAL, tak METHOD CDerivedClass::VirtualNewSlotMethod() ma aplikovany FLAG [newslot] a NEVYKONAVA METHOD OVERRIADING METHOD CBaseClass::VirtualNewSlotMethod().
			callvirt						instance void Methods.CBaseClass::VirtualNewSlotMethod()
			ldloc							Base
			// !!!!! Zavola sa METHOD CBaseClass::VirtualNewSlotMethod(), pretoze METHOD aj ked je VIRTUAL, tak METHOD CDerivedClass::VirtualNewSlotMethod() ma aplikovany FLAG [newslot] a NEVYKONAVA METHOD OVERRIADING METHOD CBaseClass::VirtualNewSlotMethod().
			callvirt						instance void Methods.CBaseClass::VirtualNewSlotMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
            .locals							init (class Methods.CDerivedClass Derived, class Methods.CBaseClass Base)

			newobj							instance void Methods.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			call							instance void Methods.CDerivedClass::VirtualFinalMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			call							instance void Methods.CDerivedClass::VirtualFinalMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa VIRTUAL METHOD VIRTUALNE. Kedze vsak CDerivedClass NESMIE mat definovanu FINAL METHOD VirtualFinalMethod(), tak sa vola METHOD CBaseClass::VirtualFinalMethod().
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualFinalMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			callvirt						instance void Methods.CDerivedClass::VirtualFinalMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test7() cil managed
		{
            .locals							init (valuetype Methods.CValueTypeVirtualMethodsClass ValueType, valuetype Methods.CValueTypeVirtualMethodsClass& ValueTypePointer)

			ldloca							ValueType
			stloc							ValueTypePointer

			ldloc							ValueTypePointer
			call							instance void Methods.CValueTypeVirtualMethodsClass::.ctor()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							ValueTypePointer
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void Methods.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueTypePointer
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void Methods.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldloc							ValueTypePointer
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako VIRTUAL METHOD.
			callvirt						instance void Methods.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueTypePointer
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			callvirt						instance void Methods.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							ValueType
			box								valuetype Methods.CValueTypeVirtualMethodsClass
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void Methods.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueType
			box								valuetype Methods.CValueTypeVirtualMethodsClass
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void Methods.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldloc							ValueType
			box								valuetype Methods.CValueTypeVirtualMethodsClass
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako VIRTUAL METHOD.
			callvirt						instance void Methods.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueType
			box								valuetype Methods.CValueTypeVirtualMethodsClass
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			callvirt						instance void Methods.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
            .locals							init (class Methods.CDerived Derived, class Methods.CBase Base)

			newobj							instance void Methods.CDerived::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBase
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod1()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod2()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod3()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod4()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod5()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod6()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
            .locals							init (class Methods.CSuperDerived Derived, class Methods.CBase Base)

			newobj							instance void Methods.CSuperDerived::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class Methods.CBase
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod1()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod2()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod3()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod4()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod5()

			ldloc							Base
			callvirt						instance void Methods.CDerived::VirtualMethod6()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test10() cil managed
		{
            .locals							init (class Methods.CLocalVariables LocalVariables)

			newobj							instance void Methods.CLocalVariables::.ctor()
			stloc							LocalVariables

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							LocalVariables
			call							instance void Methods.CLocalVariables::TestLocalVariables()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test11() cil managed
		{
            .locals							init (class Methods.CLocalVariables LocalVariables)

			newobj							instance void Methods.CLocalVariables::.ctor()
			stloc							LocalVariables

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							LocalVariables
			call							instance void Methods.CLocalVariables::TestNestedLocalVariables()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test12() cil managed
		{
            .locals							init (class Methods.CLocalVariables LocalVariables)

			newobj							instance void Methods.CLocalVariables::.ctor()
			stloc							LocalVariables

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							LocalVariables
			call							instance void Methods.CLocalVariables::TestNestedVariablesWithCustomIndexes()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test13() cil managed
		{
            .locals							init (class Methods.CLocalVariables LocalVariables)

			newobj							instance void Methods.CLocalVariables::.ctor()
			stloc							LocalVariables

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							LocalVariables
			call							instance void Methods.CLocalVariables::TestNestedLocalVariablesWithSameIndexes()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test14() cil managed
		{
            .locals							init (class Methods.CStaticConstructors StaticConstructors)

			newobj							instance void Methods.CStaticConstructors::.ctor()
			stloc							StaticConstructors

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							StaticConstructors
			call							instance void Methods.CStaticConstructors::SomeMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test15() cil managed
		{
            .locals							init (class Methods.CFinalizers Finalizers)

			newobj							instance void Methods.CFinalizers::.ctor()
			stloc							Finalizers

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Finalizers
			call							instance void Methods.CFinalizers::SomeMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test16() cil managed
		{
            .locals							init (class Methods.CVariableParametersMethods VariableParametersMethods)

			newobj							instance void Methods.CVariableParametersMethods::.ctor()
			stloc							VariableParametersMethods

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Volanie METHOD s VARIABLE PARAMETERS BEZ VARIABLE PARAMETERS.
			ldloc							VariableParametersMethods
			ldstr							"Timmy Anderson"
			ldc.i4							12
			// !!! Na METHODS s VARIABLE PARAMETERS MUSI byt pouzity KEYWORD [vararg].
			call							instance vararg void Methods.CVariableParametersMethods::VariableParameters(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Volanie METHOD s VARIABLE PARAMETERS S VARIABLE PARAMETERS.
			ldloc							VariableParametersMethods
			ldstr							"Timmy Anderson"
			ldc.i4							12
			ldstr							"Jenny Thompson"
			ldc.i4							13
			// !!! Na METHODS s VARIABLE PARAMETERS MUSI byt pouzity KEYWORD [vararg].
			// !!!!! Ak METHOD s VARIABLE PARAMETERS ma definovane aj VARIABLE PARAMETERS, tak tieto MUSIA byt oddelene pomocou specialneho PARAMETERS SENTINEL [...].
			call							instance vararg void Methods.CVariableParametersMethods::VariableParameters(string,int32,...,string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test17() cil managed
		{
            .locals							init (class Methods.COverloading Overloading)

			newobj							instance void Methods.COverloading::.ctor()
			stloc							Overloading

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Timmy Anderson"
			// !!! Kedze FIELDS MUSIA mat pri pristupe k nim definovany aj TYPE je mozne vykonat FIELD OVERLOADING na zaklade FIELD TYPE.
			stsfld							string Methods.COverloading::MOverloadedField
			ldc.i4							12
			// !!! Kedze FIELDS MUSIA mat pri pristupe k nim definovany aj TYPE je mozne vykonat FIELD OVERLOADING na zaklade FIELD TYPE.
			stsfld							int32 Methods.COverloading::MOverloadedField

			ldstr							"STATIC FIELDS - [{0}] [{1}] !"
			ldsfld							string Methods.COverloading::MOverloadedField
			ldsfld							int32 Methods.COverloading::MOverloadedField
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Overloading
			ldstr							"Timmy Anderson"
			// !!! Kedze FIELDS MUSIA mat pri pristupe k nim definovany aj TYPE je mozne vykonat FIELD OVERLOADING na zaklade FIELD TYPE.
			stfld							string Methods.COverloading::MNonStaticOverloadedField
			ldloc							Overloading
			ldc.i4							12
			// !!! Kedze FIELDS MUSIA mat pri pristupe k nim definovany aj TYPE je mozne vykonat FIELD OVERLOADING na zaklade FIELD TYPE.
			stfld							int32 Methods.COverloading::MNonStaticOverloadedField

			ldstr							"NON-STATIC FIELDS - [{0}] [{1}] !"
			ldloc							Overloading
			ldfld							string Methods.COverloading::MNonStaticOverloadedField
			ldloc							Overloading
			ldfld							int32 Methods.COverloading::MNonStaticOverloadedField
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			call							void Methods.COverloading::OverloadedMethod()

			ldloc							Overloading
			call							instance void Methods.COverloading::OverloadedMethod()

			call							vararg void Methods.COverloading::OverloadedMethod()

			ldloc							Overloading
			call							instance vararg void Methods.COverloading::OverloadedMethod()

			call							int32 Methods.COverloading::OverloadedMethod()

			ldloc							Overloading
			call							instance int32 Methods.COverloading::OverloadedMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test18() cil managed
		{
			call							void GlobalMethod()

			// !!!!! Na GLOBAL METHODS sa NEAPLIKUJU NAMESPACES a tento CODE hodi COMPILATION ERROR.
			//call							void Methods.GlobalMethodWithNamespace()

			// !!! Tento CODE vsak COMPILER akceptuje.
			call							void GlobalMethodWithNamespace()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void Methods.CMethods::Test1()
			//call							void Methods.CMethods::Test2()
			//call							void Methods.CMethods::Test3()
			//call							void Methods.CMethods::Test4()
			//call							void Methods.CMethods::Test5()
			//call							void Methods.CMethods::Test6()
			//call							void Methods.CMethods::Test7()
			//call							void Methods.CMethods::Test8()
			//call							void Methods.CMethods::Test9()
			//call							void Methods.CMethods::Test10()
			//call							void Methods.CMethods::Test11()
			//call							void Methods.CMethods::Test12()
			//call							void Methods.CMethods::Test13()
			//call							void Methods.CMethods::Test14()
			//call							void Methods.CMethods::Test15()
			//call							void Methods.CMethods::Test16()
			//call							void Methods.CMethods::Test17()
			call							void Methods.CMethods::Test18()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------