//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly StackUnwind {}
.module StackUnwind.exe
//-------------------------------------------------------------------------------------------------------
.namespace StackUnwind
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CStackUnwind extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void ThrowException() cil managed
		{
            .locals init (int32 Retval)

			ldc.i4							10
			ldc.i4							0
			div
			stloc.0

			ldstr							"RESULT is [{0}] !"
			ldloc.0
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			.try
			{
				call						void StackUnwind.CStackUnwind::ThrowException()
				leave.s						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void StackUnwind.CStackUnwind::StackUnwind(class [mscorlib]System.Exception Exception)
				leave.s						Exit
			}

	    Exit:
            ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void StackUnwind(class [mscorlib]System.Exception Exception) cil managed
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