//-------------------------------------------------------------------------------------------------------
//#define USE_MAPPED_FIELD
//#define BLOW_UP
//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SimpleSampleCodeDirectives {}
.module SimpleSampleCodeDirectives.exe
//-------------------------------------------------------------------------------------------------------
.typedef									[mscorlib]System.Console as TTY
.typedef									method void TTY::WriteLine(string) as PrintLine
//-------------------------------------------------------------------------------------------------------
.namespace SimpleSampleCodeDirectives
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSimpleSampleCodeDirectives extends [mscorlib]System.Object
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
		    call							PrintLine

			.try
			{
				call						string TTY::ReadLine()

//-------------------------------------------------------------------------------------------------------
#ifdef BLOW_UP
//-------------------------------------------------------------------------------------------------------
				pop
				ldnull
//-------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------
#ifdef USE_MAPPED_FIELD
//-------------------------------------------------------------------------------------------------------
				// Do STACK sa ulozi ADDRESS na GLOBAL VARIABLE MFormat.
				ldsflda						valuetype CharArray8 MFormat
				// Do STACK sa ulozi ADDRESS na STATIC VARIABLE MValue.
				ldsflda						int32 SimpleSampleCodeDirectives.CSimpleSampleCodeDirectives::MValue
				// Zavola sa UNMANAGED FUNCTION sscanf().
				// !!!!! SYNTAX [...] sluzi na oddelenie OPTIONAL PARAMETERS od MANDATORY PARAMETERS. Ak FUNCTION s VARIABLE PARAMETERS by nebola volana s OPTIONAL PARAMETERS, tak sa SYNTAX [...] NESMIE pouzit.
				call						vararg int32 sscanf(string,int8*,...,int32*)
//-------------------------------------------------------------------------------------------------------
#else
//-------------------------------------------------------------------------------------------------------
				ldstr						"%d"
				// Do STACK sa ulozi ADDRESS na STATIC VARIABLE MValue.
				ldsflda						int32 SimpleSampleCodeDirectives.CSimpleSampleCodeDirectives::MValue
				// Zavola sa UNMANAGED FUNCTION SimpleSampleCodeDirectives().
				// !!!!! SYNTAX [...] sluzi na oddelenie OPTIONAL PARAMETERS od MANDATORY PARAMETERS. Ak FUNCTION s VARIABLE PARAMETERS by nebola volana s OPTIONAL PARAMETERS, tak sa SYNTAX [...] NESMIE pouzit.
				call						vararg int32 sscanf(string,string,...,int32*)
//-------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------

				// !!! RETURN VALUE UNMANAGED FUNCTION sscanf() obsahuje pocet USPESNE PARSED VALUES. Tato hodnota sa vyberie zo STACK a ulozi do LOCAL VARIABLE Retval.
				stloc.0

				leave.s						DidntBlowUp
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						PrintLine
				leave.s						Return
			}

	    DidntBlowUp:
            ldloc.0
			// Ak RETURN VALUE UNMANAGED FUNCTION SimpleSampleCodeDirectives() obsahuje 0, tak ZIADNA VALUE nebola PARSED.
            brfalse.s						Error

            ldsfld							int32 SimpleSampleCodeDirectives.CSimpleSampleCodeDirectives::MValue
            ldc.i4.1
			// OPERATION AND.
            and
            brfalse.s						ItsEven

            ldstr							"VALUE is ODD !"
            br.s							PrintAndReturn

        ItsEven:
            ldstr							"VALUE is EVEN !"
            br.s							PrintAndReturn

        Error:
            ldstr							"VALUE is INVALID !"

        PrintAndReturn:
		    call							PrintLine
			ldloc.0
			brtrue.s						AskForNumber

		Return:
            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#ifdef USE_MAPPED_FIELD
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
#else
//-------------------------------------------------------------------------------------------------------
// !!! Deklaracia MANAGED WRAPPER okolo UNMANAGED FUNCTION sscanf(). Kedze sa jedna o MANAGED WRAPPER je NUTNE pouzit FLAGS 'cil' a 'managed'.
// !!!!! EXTREMNE DOLEZITE je nastavit FLAG 'preservesig', inak FUNCTION nevracala korektne RETURN VALUE.
.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 sscanf(string,string) cil managed preservesig {}
//-------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------