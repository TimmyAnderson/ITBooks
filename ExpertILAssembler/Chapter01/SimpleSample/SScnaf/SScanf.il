//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SScanf {}
.module SScanf.exe
//-------------------------------------------------------------------------------------------------------
.namespace SScanf
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSScanf extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .field public static int32								MValue
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init (int32 Retval)

        AskForNumber:
            ldstr							"Enter a number:"
            call							void [mscorlib]System.Console::WriteLine(string)
            call							string [mscorlib]System.Console::ReadLine()

			// Do STACK sa ulozi ADDRESS na GLOBAL VARIABLE MFormat.
            ldsflda							valuetype CharArray8 MFormat
			// Do STACK sa ulozi ADDRESS na STATIC VARIABLE MValue.
            ldsflda							int32 SScanf.CSScanf::MValue
			// Zavola sa UNMANAGED FUNCTION sscanf().
			// !!!!! SYNTAX [...] sluzi na oddelenie OPTIONAL PARAMETERS od MANDATORY PARAMETERS. Ak FUNCTION s VARIABLE PARAMETERS by nebola volana s OPTIONAL PARAMETERS, tak sa SYNTAX [...] NESMIE pouzit.
            call							vararg int32 sscanf(string,int8*,...,int32*)
			// !!! RETURN VALUE UNMANAGED FUNCTION sscanf() obsahuje pocet USPESNE PARSED VALUES. Tato hodnota sa vyberie zo STACK a ulozi do LOCAL VARIABLE Retval.
			stloc							Retval

            ldloc							Retval
			// Ak RETURN VALUE UNMANAGED FUNCTION sscanf() obsahuje 0, tak ZIADNA VALUE nebola PARSED.
            brfalse							Error

            ldsfld							int32 SScanf.CSScanf::MValue
            ldc.i4							1
			// OPERATION AND.
            and
            brfalse							ItsEven

            ldstr							"VALUE is ODD !"
            br								PrintAndReturn

        ItsEven:
            ldstr							"VALUE is EVEN !"
            br								PrintAndReturn

        Error:
            ldstr							"VALUE is INVALID !"

        PrintAndReturn:
            call							void [mscorlib]System.Console::WriteLine(string)
            ldloc							Retval
            brtrue							AskForNumber
            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Definicia GLOBAL FIELD. FIELD je MAPPED FIELD, pretoze je MAPPED (inicializovany) na DATA SEGMENT 'MFormatData'.
.field public static valuetype CharArray8						MFormat at MFormatData
//-------------------------------------------------------------------------------------------------------
// Definicia DATA SEGMENT MFormatData o dlzke 8 BYTES.
// Obsahuje hodnotu '%d'.
.data															MFormatData=bytearray(25 64 00 00 00 00 00 00)
//-------------------------------------------------------------------------------------------------------
// Definicia VALUE TYPE CharArray8.
.class sealed public explicit CharArray8 extends [mscorlib]System.ValueType
{
	// !!! VALUE TYPE CharArray8 NEMA ZIADNE MEMBERS, pretoze jeho vnutorna struktura nie je podstatna. Ma definovanu iba VELKOST, ktora je 8 BYTES.
	.size														8
}
//-------------------------------------------------------------------------------------------------------
// !!! Deklaracia MANAGED WRAPPER okolo UNMANAGED FUNCTION sscanf(). Kedze sa jedna o MANAGED WRAPPER je NUTNE pouzit FLAGS 'cil' a 'managed'.
// !!!!! EXTREMNE DOLEZITE je nastavit FLAG 'preservesig', inak FUNCTION nevracala korektne RETURN VALUE.
.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 sscanf(string,int8*) cil managed preservesig {}
//-------------------------------------------------------------------------------------------------------