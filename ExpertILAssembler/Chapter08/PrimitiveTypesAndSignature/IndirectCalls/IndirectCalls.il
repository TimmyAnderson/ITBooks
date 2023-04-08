//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly IndirectCalls {}
.module IndirectCalls.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace IndirectCalls
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CIndirectCalls extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void IndirectlyCalledMethod(string Param1, int32 Param2) cil managed
		{
			ldstr							"PARAM1 [{0}] !"
			ldarg							Param1
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"PARAM2 [{0}] !"
			ldarg							Param2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"Timmy Anderson"
			ldc.i4							12
			// !!! Ziska sa POINTER na FUNCTION.
			ldftn							void IndirectCalls.CIndirectCalls::IndirectlyCalledMethod(string,int32)
			// !!!!! INSTRUCTION [calli] NEOBSAHUJE METHOD NAME, pretoze poziciu METHOD v MEMORY zisti z FUNCTION POINTER na VRCHOLE STACKU.
			calli							void(string,int32)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------