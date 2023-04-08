//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly WrongException {}
.module WrongException.exe
//-------------------------------------------------------------------------------------------------------
.namespace WrongException
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CWrongException extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init (int32 Retval)

			// !!!!! METHOD STACK MUSI byt EMPTY, ak sa vstupuje do TRY BLOCK, inak PROGRAM ZLYHA hodenim InvalidProgramException.
			//ldc.i4						10

			.try
			{
				ldc.i4						10
				ldc.i4						10
				ldc.i4						10
				ldc.i4						10
				ldc.i4						10

				ldstr						"All OK 1 !"
				call						void [mscorlib]System.Console::WriteLine(string)

				ldc.i4						10
				ldc.i4						10
				ldc.i4						10
				ldc.i4						10
				ldc.i4						10

				// !!!!! Pri ukonceni TRY BLOCK sa METHOD STACK VYPRAZDNI.
				leave.s						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void WrongException.CWrongException::WrongException(class [mscorlib]System.Exception Exception)
				// !!!!! Pri ukonceni CATCH BLOCK sa METHOD STACK VYPRAZDNI.
				leave.s						Exit
			}

	    Exit:
			ldstr							"All OK 2 !"
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void WrongException(class [mscorlib]System.Exception Exception) cil managed
		{
			ldstr							"EXCEPTION [{0}] !"
			ldarg.0
			callvirt						instance string [mscorlib]System.Object::ToString()
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------