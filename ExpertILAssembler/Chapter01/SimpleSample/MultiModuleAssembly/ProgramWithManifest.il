//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly MultiModuleAssembly { }
//-------------------------------------------------------------------------------------------------------
// !!!!! Kazdy RECORD v METADATA TABLE [ModuleRef] MUSI byt sparovany s METADATA TABLE [File].
.module extern Module1.mod
.module extern Module2.mod
//-------------------------------------------------------------------------------------------------------
// !!!!! Kazdy RECORD v METADATA TABLE [ModuleRef] MUSI byt sparovany s METADATA TABLE [File].
.file Module1.mod
.file Module2.mod
//-------------------------------------------------------------------------------------------------------
.method public static void Exec()
{
	.entrypoint

	call									void [.module Module1.mod]CModule1::SimpleTest()
	call									void [.module Module2.mod]CModule2::SimpleTest()

	ret
}
//-------------------------------------------------------------------------------------------------------