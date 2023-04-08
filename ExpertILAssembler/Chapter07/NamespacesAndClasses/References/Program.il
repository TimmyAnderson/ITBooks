//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib { }
.assembly References { }
//-------------------------------------------------------------------------------------------------------
// !!!!! Kazdy RECORD v METADATA TABLE [ModuleRef] MUSI byt sparovany s METADATA TABLE [File].
.module extern Module.mod
//-------------------------------------------------------------------------------------------------------
// !!!!! Kazdy RECORD v METADATA TABLE [ModuleRef] MUSI byt sparovany s METADATA TABLE [File].
.file Module.mod
//-------------------------------------------------------------------------------------------------------
.method public static void Exec()
{
	.entrypoint

	// !!! Referovanie sa na INY MODULE v CURRENT ASSEMBLY.
	call									void [.module Module.mod]CModule::SimpleTest()

	ldstr									"Hello from PRIMARY MODULE !"
	// !!! Referovanie sa na INU ASSEMBLY.
	call									void [mscorlib]System.Console::WriteLine(string)

	ret
}
//-------------------------------------------------------------------------------------------------------