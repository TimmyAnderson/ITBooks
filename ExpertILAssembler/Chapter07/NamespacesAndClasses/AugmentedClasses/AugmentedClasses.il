//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly AugmentedClasses {}
.module AugmentedClasses.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace AugmentedClasses
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi auto CAugmentedClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Method1() cil managed
		{
			ldstr							"CAugmentedClass.Method1() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	// Dalsi SEGMENT tej iste CLASS.
    .class CAugmentedClass
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Method2() cil managed
		{
			ldstr							"CAugmentedClass.Method2() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CAugmentedClasses extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			call							void AugmentedClasses.CAugmentedClass::Method1()
			call							void AugmentedClasses.CAugmentedClass::Method2()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------