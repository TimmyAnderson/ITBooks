//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SimpleSample {}
.module SimpleSample.exe
//-------------------------------------------------------------------------------------------------------
.namespace SimpleSample
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSimpleSample extends [mscorlib]System.Object
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

		    .try
			{
	            ldstr						"Enter a number:"
		        call						void [mscorlib]System.Console::WriteLine(string)
			    call						string [mscorlib]System.Console::ReadLine()

				call						int32 [mscorlib]System.Int32::Parse(string)
				stsfld						int32 SimpleSample.CSimpleSample::MValue

				ldstr						"NUMBER is [{0}] !"
				ldsfld						int32 SimpleSample.CSimpleSample::MValue
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object)

		        call						void [mscorlib]System.Console::WriteLine(string)

		        leave.s						Return
			}
			catch [mscorlib]System.Exception
			{
				pop
				ldstr						"EXCEPTION OCCURED !"
				call						void [mscorlib]System.Console::WriteLine(string)
				leave.s						Return
			}

		Return:
			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------