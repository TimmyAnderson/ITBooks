//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly NestedClasses {}
.module NestedClasses.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace NestedClasses
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEnclosingType extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.class nested public auto ansi CNestedClass1 extends [mscorlib]System.Object
		{
//-------------------------------------------------------------------------------------------------------
			.class nested public auto ansi CNestedClass2 extends [mscorlib]System.Object
			{
//-------------------------------------------------------------------------------------------------------
				.method public static void InNestedClass2() cil managed
				{
					ldstr					"Hello from InNestedClass2() !"
					call					void [mscorlib]System.Console::WriteLine(string)

					ret
				}
//-------------------------------------------------------------------------------------------------------
			}
//-------------------------------------------------------------------------------------------------------
			.method public static void InNestedClass1() cil managed
			{
				ldstr						"Hello from InNestedClass1() !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ret
			}
//-------------------------------------------------------------------------------------------------------
		}
//-------------------------------------------------------------------------------------------------------
		.method public static void InEnclosingType() cil managed
		{
			ldstr						"Hello from EnclosingType() !"
			call						void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CNestedClasses extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			call							void NestedClasses.CEnclosingType::InEnclosingType()
			// Pristup k NESTED TYPES je cez OPERATOR [/].
			call							void NestedClasses.CEnclosingType/CNestedClass1::InNestedClass1()
			call							void NestedClasses.CEnclosingType/CNestedClass1/CNestedClass2::InNestedClass2()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------