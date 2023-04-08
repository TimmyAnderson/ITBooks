//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Enums {}
.module Enums.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Enums
{
//-------------------------------------------------------------------------------------------------------
	.class public auto ansi sealed enum EMyEnum extends [mscorlib]System.Enum
	{
//-------------------------------------------------------------------------------------------------------
		// !!! FIELD reprezentujuci ENUM TYPE.
		.field public specialname rtspecialname int32	value__
//-------------------------------------------------------------------------------------------------------
		// ENUM CONSTANTS MUSIA byt LITERALS.
		.field public static literal valuetype Enums.EMyEnum E_VALUE_1 = int32(0x00000001)
		.field public static literal valuetype Enums.EMyEnum E_VALUE_2 = int32(0x00000002)
		.field public static literal valuetype Enums.EMyEnum E_VALUE_3 = int32(0x00000003)
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEnums extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
			.locals init					(valuetype Enums.EMyEnum MyEnum)

			ldstr							"ENUM: [{0}] !"

			ldc.i4							2
			stloc.0

			ldloc.0
			box								[mscorlib]System.Int32

			call							string [mscorlib]System.String::Format(string,object)

	        call							void [mscorlib]System.Console::WriteLine(string)

			ret

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------