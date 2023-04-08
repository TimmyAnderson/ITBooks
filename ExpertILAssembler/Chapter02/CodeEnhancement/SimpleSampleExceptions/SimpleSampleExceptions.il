//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SimpleSampleExceptions {}
.module SimpleSampleExceptions.exe
//-------------------------------------------------------------------------------------------------------
.namespace SimpleSampleExceptions
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSimpleSampleExceptions extends [mscorlib]System.Object
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

			.try
			{
				call						string [mscorlib]System.Console::ReadLine()

				ldstr						"%d"
				// Do STACK sa ulozi ADDRESS na STATIC VARIABLE MValue.
				ldsflda						int32 SimpleSampleExceptions.CSimpleSampleExceptions::MValue
				// Zavola sa UNMANAGED FUNCTION SimpleSampleExceptions().
				// !!!!! SYNTAX [...] sluzi na oddelenie OPTIONAL PARAMETERS od MANDATORY PARAMETERS. Ak FUNCTION s VARIABLE PARAMETERS by nebola volana s OPTIONAL PARAMETERS, tak sa SYNTAX [...] NESMIE pouzit.
				call						vararg int32 sscanf(string,string,...,int32*)
				// !!! RETURN VALUE UNMANAGED FUNCTION sscanf() obsahuje pocet USPESNE PARSED VALUES. Tato hodnota sa vyberie zo STACK a ulozi do LOCAL VARIABLE Retval.
				stloc.0

				leave.s						DidntBlowUp
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Return
			}

	    DidntBlowUp:
            ldloc.0
			// Ak RETURN VALUE UNMANAGED FUNCTION SimpleSampleExceptions() obsahuje 0, tak ZIADNA VALUE nebola PARSED.
            brfalse.s						Error

            ldsfld							int32 SimpleSampleExceptions.CSimpleSampleExceptions::MValue
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
            call							void [mscorlib]System.Console::WriteLine(string)
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
// !!! Deklaracia MANAGED WRAPPER okolo UNMANAGED FUNCTION sscanf(). Kedze sa jedna o MANAGED WRAPPER je NUTNE pouzit FLAGS 'cil' a 'managed'.
// !!!!! EXTREMNE DOLEZITE je nastavit FLAG 'preservesig', inak FUNCTION nevracala korektne RETURN VALUE.
.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 sscanf(string,string) cil managed preservesig {}
//-------------------------------------------------------------------------------------------------------