//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SimpleSampleStrings {}
.module SimpleSampleStrings.exe
//-------------------------------------------------------------------------------------------------------
.namespace SimpleSampleStrings
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSimpleSampleStrings extends [mscorlib]System.Object
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

			// !!! PINVOKE vykona MARSHALLING UNICODE STRING '%d' do ANSI STRING, ktory potrebuje FUNCTION sscanf().
			ldstr							"%d"
			// Do STACK sa ulozi ADDRESS na STATIC VARIABLE MValue.
            ldsflda							int32 SimpleSampleStrings.CSimpleSampleStrings::MValue
			// Zavola sa UNMANAGED FUNCTION SimpleSampleStrings().
			// !!!!! SYNTAX [...] sluzi na oddelenie OPTIONAL PARAMETERS od MANDATORY PARAMETERS. Ak FUNCTION s VARIABLE PARAMETERS by nebola volana s OPTIONAL PARAMETERS, tak sa SYNTAX [...] NESMIE pouzit.
			// !!! PRVY a DRUHY PARAMETER su STRINGS, aby MARSHALLER vykonal konrektny MARSHALLING z UNICODE do ANSI STRING.
            call							vararg int32 sscanf(string,string,...,int32*)
			// !!! RETURN VALUE UNMANAGED FUNCTION sscanf() obsahuje pocet USPESNE PARSED VALUES. Tato hodnota sa vyberie zo STACK a ulozi do LOCAL VARIABLE Retval.
			stloc.0

			// !!! SHORT VERSION INSTRUCTION 'ldloc'. INSTRUCTION 'ldloc.0' nacita do STACK hodnotu 1. LOCAL PARAMETER.
            ldloc.0
			// Ak RETURN VALUE UNMANAGED FUNCTION SimpleSampleStrings() obsahuje 0, tak ZIADNA VALUE nebola PARSED.
            brfalse.s						Error

            ldsfld							int32 SimpleSampleStrings.CSimpleSampleStrings::MValue
			// !!! SHORT INSTRUCTION 'ldc.i4 1', ktora ma PARAMETER o dlzke iba 1 BYTE, namiesto 4 BYTES pre 'ldc.i4 1'.
            ldc.i4.1
			// OPERATION AND.
            and
			// !!!!! SHORT VERSION INSTRUCTION 'brfalse', ktory vsak umoznuje BRANCHING iba v intervale <-128,127> BYTES.
            brfalse.s						ItsEven

            ldstr							"VALUE is ODD !"
            br.s							PrintAndReturn

        ItsEven:
            ldstr							"VALUE is EVEN !"
            br.s							PrintAndReturn

        Error:
            ldstr							"VALUE is INVALID !"

        PrintAndReturn:
            call							void [mscorlib]System.Console::WriteLine(string)
			ldloc.0
			brtrue.s						AskForNumber
            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Deklaracia MANAGED WRAPPER okolo UNMANAGED FUNCTION sscanf(). Kedze sa jedna o MANAGED WRAPPER je NUTNE pouzit FLAGS 'cil' a 'managed'.
// !!!!! EXTREMNE DOLEZITE je nastavit FLAG 'preservesig', inak FUNCTION nevracala korektne RETURN VALUE.
.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 sscanf(string,string) cil managed preservesig {}
//-------------------------------------------------------------------------------------------------------