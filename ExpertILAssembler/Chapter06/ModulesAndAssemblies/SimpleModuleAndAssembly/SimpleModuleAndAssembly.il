//-------------------------------------------------------------------------------------------------------
// Vytvara RECORD v METADATA TABLE [AssemblyRef].
.assembly extern mscorlib {auto}
//-------------------------------------------------------------------------------------------------------
// Vytvara RECORD v METADATA TABLE [Assembly].
.assembly SimpleModuleAndAssembly
{
	// Ak sa definuje PUBLIC KEY, tak MUSI byt definovany KEY FILE v [ILDASM.EXE] FLAG [/KEY=MyKey.key].
	.publickey=(00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF)
	.ver 1:2:3:4
	.hash algorithm 0x00008004
	.locale "en-US"
}
//-------------------------------------------------------------------------------------------------------
// Vytvara RECORD v METADATA TABLE [Module].
.module SimpleModuleAndAssembly.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace SimpleModuleAndAssembly
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSimpleModuleAndAssembly extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"Hello WORLD !"
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------