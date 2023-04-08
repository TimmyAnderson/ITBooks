//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
// !!!!! ASSEMBLY MUSI byt silne podpisana.
.assembly CCWAssembly {}
.module CCWAssembly.exe
//-------------------------------------------------------------------------------------------------------
.namespace CCWAssembly
{
//-------------------------------------------------------------------------------------------------------
	// COM INTERFACE.
    .class public auto ansi abstract interface ICCWInterface
	{
//-------------------------------------------------------------------------------------------------------
		// CUSTOM ATTRIBUTE [Guid("1B02CECD-4D14-402C-B14A-DA1FD5925E4A")].
		.custom													instance void [mscorlib]System.Runtime.InteropServices.GuidAttribute::.ctor(string) = ( 01 00 24 31 42 30 32 43 45 43 44 2D 34 44 31 34 2D 34 30 32 43 2D 42 31 34 41 2D 44 41 31 46 44 35 39 32 35 45 34 41 00 00 )
		// CUSTOM ATTRIBUTE [InterfaceType(ComInterfaceType.InterfaceIsDual)].
		.custom													instance void [mscorlib]System.Runtime.InteropServices.InterfaceTypeAttribute::.ctor(valuetype [mscorlib]System.Runtime.InteropServices.ComInterfaceType) = ( 01 00 00 00 00 00 00 00 )
		// CUSTOM ATTRIBUTE [ComVisible(true)].
		.custom													instance void [mscorlib]System.Runtime.InteropServices.ComVisibleAttribute::.ctor(bool) = ( 01 00 01 00 00 )
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public abstract virtual instance void PrintString(string Value) cil managed
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CCCWObject extends [mscorlib]System.Object implements CCWAssembly.ICCWInterface
	{
//-------------------------------------------------------------------------------------------------------
		// CUSTOM ATTRIBUTE [Guid("2A8CD9F7-614A-42d9-9FF2-18650FC5C843")].
		.custom								instance void [mscorlib]System.Runtime.InteropServices.GuidAttribute::.ctor(string) = ( 01 00 24 32 41 38 43 44 39 46 37 2D 36 31 34 41 2D 34 32 64 39 2D 39 46 46 32 2D 31 38 36 35 30 46 43 35 43 38 34 33 00 00 )
		// CUSTOM ATTRIBUTE [ProgId("CCWAssembly")].
		.custom								instance void [mscorlib]System.Runtime.InteropServices.ProgIdAttribute::.ctor(string) = ( 01 00 0B 43 43 57 41 73 73 65 6D 62 6C 79 00 00 )
		// CUSTOM ATTRIBUTE [ComVisible(true)].
		.custom								instance void [mscorlib]System.Runtime.InteropServices.ComVisibleAttribute::.ctor(bool) = ( 01 00 01 00 00 )
		// CUSTOM ATTRIBUTE [ClassInterface(ClassInterfaceType.None)].
		.custom								instance void [mscorlib]System.Runtime.InteropServices.ClassInterfaceAttribute::.ctor(valuetype [mscorlib]System.Runtime.InteropServices.ClassInterfaceType) = ( 01 00 00 00 00 00 00 00 )
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public virtual instance void PrintString(string Value) cil managed
		{
			ldarg							Value
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------