//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Names {}
.module Names.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Names
{
//-------------------------------------------------------------------------------------------------------
.field public static string										?StrangeName1
.field public static string										$StrangeName2
.field public static string										@StrangeName3
.field public static string										_StrangeName4
// Nasledujuce NAMES musia byt v ''.
.field public static string										'#StrangeName5'
.field public static string										'123'
.field public static string										'&%!'
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CNames extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"?StrangeName1"
			stsfld							string ?StrangeName1

			ldstr							"$StrangeName2"
			stsfld							string $StrangeName2

			ldstr							"@StrangeName3"
			stsfld							string @StrangeName3

			ldstr							"_StrangeName4"
			stsfld							string _StrangeName4

			ldstr							"#StrangeName5"
			stsfld							string '#StrangeName5'

			ldstr							"123"
			stsfld							string '123'

			ldstr							"&%!"
			stsfld							string '&%!'

			ldsfld							string ?StrangeName1
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string $StrangeName2
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string @StrangeName3
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string _StrangeName4
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string '#StrangeName5'
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string '123'
			call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string '&%!'
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------