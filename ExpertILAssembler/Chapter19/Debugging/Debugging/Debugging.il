//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Debugging {}
.module Debugging.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Debugging
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CDebugging extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			ldstr							"HELLO WORLD !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			ldstr							"BEFORE BREAK !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Sposobi vyhodenie okna, ktore ponuka moznost vykonat DEBUGGING programu a to dokonca i v RELEASE mode. Ak sa stlaci tlacitko NO, tak program OKAMZITE SKONCI.
			break

			ldstr							"AFTER BREAK !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			.try
			{
				ldstr						"BEFORE BREAK !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!! Sposobi vyhodenie okna, ktore ponuka moznost vykonat DEBUGGING programu a to dokonca i v RELEASE mode. Ak sa stlaci tlacitko NO, tak program OKAMZITE SKONCI.
				break

				ldstr						"AFTER BREAK !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			// !!! Ani EXCEPTION nie je generovana ak sa v okne ponukajucom vykonat DEBUGGING programu vyberie NO. Program je skratka OKAMZITE TERMINATED.
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
			// !!! CODE MUSI byt COMPILED v DEBUG mode.
			// !!!!! Ak sa NEPOUZIJU KEYWORDS [.line], tak VISUAL STUDIO zobrazi obsah FILE [Debugging.il].

			// Vyvola BREAKPOINT.
			break

			// !!!!! Pri DEBUGGINGU VISUAL STUDIO zobrazi 1. LINE vo FILE [SOURCE.XXX].
			.line							1,1:1,100 'SOURCE.XXX'

			ldstr							"This is LINE 1 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Pri DEBUGGINGU VISUAL STUDIO zobrazi 2. LINE vo FILE [SOURCE.XXX].
			.line							2,2:1,100 'SOURCE.XXX'

			ldstr							"This is LINE 2 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Pri DEBUGGINGU VISUAL STUDIO zobrazi 3. LINE vo FILE [SOURCE.XXX].
			.line							3,3:1,100 'SOURCE.XXX'

			ldstr							"This is LINE 3 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void Debugging.CDebugging::Test1()
			//call							void Debugging.CDebugging::Test2()
			//call							void Debugging.CDebugging::Test3()
			call							void Debugging.CDebugging::Test4()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------