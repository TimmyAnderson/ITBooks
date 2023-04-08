//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly GlobalMembers {}
.module GlobalMembers.exe
//-------------------------------------------------------------------------------------------------------
.namespace GlobalMembers
{
//-------------------------------------------------------------------------------------------------------
// GLOBAL VARIABLES.
.field public static string										MGlobalVariableString
.field public static int32										MGlobalVariableInt32
//-------------------------------------------------------------------------------------------------------
// GLOBAL METHOD.
.method public static void GlobalMethodPrintName(string Name, int32 Age) cil managed
{
	ldarg.s									0
	stsfld									string MGlobalVariableString

	ldstr									"NAME is [{0}] !"
	ldsfld									string MGlobalVariableString
	call									string [mscorlib]System.String::Format(string,object)
	call									void [mscorlib]System.Console::WriteLine(string)

	ldarg.s									1
	stsfld									int32 MGlobalVariableInt32

	ldstr									"AGE is [{0}] !"
	ldsfld									int32 MGlobalVariableInt32
	box										[mscorlib]System.Int32
	call									string [mscorlib]System.String::Format(string,object)
	call									void [mscorlib]System.Console::WriteLine(string)

	ret
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGlobalMembers extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"Timmy Anderson"
			stsfld							string MGlobalVariableString

			ldstr							"NAME is [{0}] !"
			ldsfld							string MGlobalVariableString
			call							string [mscorlib]System.String::Format(string,object)
            call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							12
			stsfld							int32 MGlobalVariableInt32

			ldstr							"AGE is [{0}] !"
			ldsfld							int32 MGlobalVariableInt32
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
            call							void [mscorlib]System.Console::WriteLine(string)

			ldsfld							string MGlobalVariableString
			ldsfld							int32 MGlobalVariableInt32
			call							void GlobalMethodPrintName(string,int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------