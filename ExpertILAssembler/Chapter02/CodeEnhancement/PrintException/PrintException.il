//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly PrintException {}
.module PrintException.exe
//-------------------------------------------------------------------------------------------------------
.namespace PrintException
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CPrintException extends [mscorlib]System.Object
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
				call						void PrintException.CPrintException::PrintException(class [mscorlib]System.Exception Exception)
				leave.s						Exit
			}

	    Exit:
            ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void PrintException(class [mscorlib]System.Exception Exception) cil managed
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