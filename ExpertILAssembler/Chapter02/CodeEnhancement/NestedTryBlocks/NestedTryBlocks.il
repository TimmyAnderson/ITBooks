//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly NestedTryBlocks {}
.module NestedTryBlocks.exe
//-------------------------------------------------------------------------------------------------------
.namespace NestedTryBlocks
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CNestedTryBlocks extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals init (int32 Retval)

			.try
			{
				.try
				{
					ldc.i4					10
					ldc.i4					0
					div
					stloc.0

					ldstr					"RESULT is [{0}] !"
					ldloc.0
					box						[mscorlib]System.Int32
					call					string [mscorlib]System.String::Format(string,object)
					call					void [mscorlib]System.Console::WriteLine(string)

					leave.s					Exit1
				}
				catch [mscorlib]System.Exception
				{
					pop 
					ldstr					"INNER EXCEPTION OCCURED !"
					call					void [mscorlib]System.Console::WriteLine(string)
					leave.s					Exit1
				}

		Exit1:
					leave.s					Exit2
			}
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"OUTER EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Exit2
			}

	    Exit2:

			.try
			{
				.try
				{
					ldc.i4					10
					ldc.i4					0
					div
					stloc.0

					ldstr					"RESULT is [{0}] !"
					ldloc.0
					box						[mscorlib]System.Int32
					call					string [mscorlib]System.String::Format(string,object)
					call					void [mscorlib]System.Console::WriteLine(string)

					leave.s					Exit3
				}
				catch [mscorlib]System.Exception
				{
					pop 
					ldstr					"INNER EXCEPTION OCCURED !"
					call					void [mscorlib]System.Console::WriteLine(string)
					leave.s					Exit3
				}

		Exit3:
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
			catch [mscorlib]System.Exception
			{
				pop 
				ldstr						"OUTER EXCEPTION OCCURED !"
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