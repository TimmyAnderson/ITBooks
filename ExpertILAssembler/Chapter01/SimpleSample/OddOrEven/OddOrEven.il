//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly OddOrEven {}
.module OddOrEven.exe
//-------------------------------------------------------------------------------------------------------
.namespace OddOrEqual
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi COddOrEven extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .field public static int32								MValue
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
            .locals							init (int32 Retval)
        
		    .try
			{
				// Nacita STRING do STACK.
	            ldstr						"Enter a number:"
				// Zavola METHOD Console.WriteLine().
		        call						void [mscorlib]System.Console::WriteLine(string)
				// Zavola METHOD Console.ReadLine().
				// METHOD Console.ReadLine() vlozi na STACK nacitany STRING.
			    call						string [mscorlib]System.Console::ReadLine()

				// Zavola METHOD Int32.Parse() nad nacitanym STRING.
				// METHOD Int32.Parse() vlozi na STACK bud PARSED INT, alebo hodi EXCEPTION.
				call						int32 [mscorlib]System.Int32::Parse(string)
				// Ulozi hodnotu zo STACK do STATIC VARIABLE.
				stsfld						int32 OddOrEqual.COddOrEven::MValue

				ldstr						"NUMBER is [{0}] !"
				ldsfld						int32 OddOrEqual.COddOrEven::MValue
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object)

		        call						void [mscorlib]System.Console::WriteLine(string)

				ldsfld						int32 OddOrEqual.COddOrEven::MValue
				ldc.i4						1
				and
				brfalse						Even

	            ldstr						"VALUE is ODD !"
		        call						void [mscorlib]System.Console::WriteLine(string)

				leave.s						Return

		Even:
	            ldstr						"VALUE is EVEN !"
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