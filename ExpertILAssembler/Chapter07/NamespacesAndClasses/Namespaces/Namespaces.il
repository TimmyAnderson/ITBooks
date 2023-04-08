//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Namespaces {}
.module Namespaces.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Namespaces
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CClass1 extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field public static string								MField
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	.namespace NestedNamespace
	{
//-------------------------------------------------------------------------------------------------------
		.class public auto ansi CClass2 extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.field public static string								MField
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
		// CLASS NAME obsahuje definiciu NAMESPACE 'InnerNestedNamespace'.
		.class public auto ansi InnerNestedNamespace.CClass3 extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.field public static string								MField
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CNamespaces extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"Value1"
			stsfld							string Namespaces.CClass1::MField

			ldstr							"Value2"
			stsfld							string Namespaces.NestedNamespace.CClass2::MField

			ldstr							"Value3"
			stsfld							string Namespaces.NestedNamespace.InnerNestedNamespace.CClass3::MField

			ldsfld							string Namespaces.CClass1::MField
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string Namespaces.NestedNamespace.CClass2::MField
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string Namespaces.NestedNamespace.InnerNestedNamespace.CClass3::MField
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------