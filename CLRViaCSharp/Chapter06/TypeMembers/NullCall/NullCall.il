//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly NullCall {}
.module NullCall.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace NullCall
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CNullCall extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void NonVirtualMethod() cil managed
		{
			ldstr							"CNullCall::NonVirtualMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Aj ked METHOD je INSTANCE METHOD, tak kedze nepouziva THIS PARAMETER, tak je ju mozne volat aj ked OBJECT pre ktory je volany ma NULL VALUE.
			ldnull							
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			call							instance void NullCall.CNullCall::NonVirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			call							void NullCall.CNullCall::Test()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------