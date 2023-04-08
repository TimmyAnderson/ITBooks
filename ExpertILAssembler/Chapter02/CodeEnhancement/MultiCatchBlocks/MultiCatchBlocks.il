//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly MultiCatchBlocks {}
.module MultiCatchBlocks.exe
//-------------------------------------------------------------------------------------------------------
.namespace MultiCatchBlocks
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CMultiCatchBlocks extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init (int32 Retval)

			.try
			{
				ldc.i4						10
				ldc.i4						5
				div
				stloc.0

				ldstr						"RESULT is [{0}] !"
				ldloc.0
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object)
	            call						void [mscorlib]System.Console::WriteLine(string)

				leave.s						Exit1
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit1
			}

	    Exit1:

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

				leave.s						Exit2
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit2
			}

	    Exit2:

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

				leave.s						Exit3
			}
			catch [mscorlib]System.DivideByZeroException
			{
				pop 
				ldstr						"DIVIDE BY ZERO EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit3
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit3
			}

	    Exit3:

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

				leave.s						Exit4
			}
			// !!!!! Ak sa BASE EXCEPTION CLASS da ako PRVA v poradi, tak NESKORSIE CATCH BLOCKS BUDU IGNOROVANE, ale MSIL COMPILER NEHODI ERROR.
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit4
			}
			catch [mscorlib]System.DivideByZeroException
			{
				pop 
				ldstr						"DIVIDE BY ZERO EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit4
			}

	    Exit4:
            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------