//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Classes {}
.module Classes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Classes
{
//-------------------------------------------------------------------------------------------------------
	// !!! Ak ma CLASS nastaveny FLAG [sequential], alebo FLAG [explicit], je mozne na CLASS aplikovat KEYWORD [.pack VALUE] a KEYWORD [.size VALUE].
    .class public auto ansi explicit CExplicitClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.pack 4
		.size 1024
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CExplicitClass.ctor() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	// INTERFACES NEMOZU mat BASE CLASS.
    .class public auto ansi interface IInterface
	{
//-------------------------------------------------------------------------------------------------------
		// INTERFACE MOZE mat STATIC FIELDS.
		.field public static string 		MStaticField
//-------------------------------------------------------------------------------------------------------
		// INTERFACE MOZE mat STATIC METHODS.
	    .method public static void StaticInterfaceMethod() cil managed
		{
			ldstr							"IInterface.StaticInterfaceMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	// INTERFACES MOZU mat BASE INTERFACES.
    .class public auto ansi interface IDerivedInterface implements Classes.IInterface
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi interface IOtherInterface
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	// CLASSES mozu implementovat VIACERO INTERFACES.
    .class public auto ansi CClasses extends [mscorlib]System.Object implements Classes.IDerivedInterface, Classes.IOtherInterface
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"Hello WORLD !"
			// !!!!! CLASS NAME System.Console MUSI obsahovat aj RESOLUTION SCOPE 'mscorlib', pretoze je definovana v ASSEMBLY 'mscorlib'.
			call							void [mscorlib]System.Console::WriteLine(string)

			newobj							instance void Classes.CExplicitClass::.ctor()
			// Zahodi sa vytvorena instancia CLASS.
			pop

			// Zavola sa INTERFACE STATIC METHOD.
			call							void Classes.IInterface::StaticInterfaceMethod()

			ldstr							"Hello INTERFACE STATIC FIELD !"
			// Zapise sa STRING do INTERFACE STATIC FIELD.
			stsfld							string Classes.IInterface::MStaticField

			ldsfld							string Classes.IInterface::MStaticField
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------