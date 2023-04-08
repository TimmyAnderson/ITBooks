//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly IncludeDirective {}
.module IncludeDirective.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace IncludeDirective
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CIncludeDirective extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init (int32 Retval)

			.try
			{
				ldc.i4						10
				ldc.i4						0
				div
				stloc.0

				ldstr						"RESULT is [{0}] !"
				ldloc.0
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object)
				call						void [mscorlib]System.Console::WriteLine(string)

				leave.s						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)
				leave.s						Exit
			}

	    Exit:
            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------