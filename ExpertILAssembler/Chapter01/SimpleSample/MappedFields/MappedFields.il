//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly MappedFields {}
.module MappedFields.exe
//-------------------------------------------------------------------------------------------------------
.namespace MappedFields
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CMappedFields extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .field public static int32								MInt32LocalVariable at MInt32Segment
		// !!! STRING FIELD NIE JE mozne definovat ako MAPPED FIELD. RUNTIME hodi EXCEPTION TypeLoadExecption.
        //.field public static string							MStringLocalVariable at MStringSegment
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"GLOBAL VARIABLE is [{0}] !"
			ldsfld							int32 MInt32GlobalVariable
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"LOCAL VARIABLE is [{0}] !"
			ldsfld							int32 MappedFields.CMappedFields::MInt32LocalVariable
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							337
			// !!!!! Kedze MInt32GlobalVariable aj MInt32LocalVariable su OBE MAPPED na TEN ISTY DATA SEGMENT, tak pri zmene jednej z nich sa zmenia OBIDVE.
			stsfld							int32 MappedFields.CMappedFields::MInt32LocalVariable

			ldstr							"GLOBAL VARIABLE is [{0}] !"
			ldsfld							int32 MInt32GlobalVariable
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"LOCAL VARIABLE is [{0}] !"
			ldsfld							int32 MappedFields.CMappedFields::MInt32LocalVariable
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
.field public static int32										MInt32GlobalVariable at MInt32Segment
// !!! STRING FIELD NIE JE mozne definovat ako MAPPED FIELD. RUNTIME hodi EXCEPTION TypeLoadExecption.
//.field public static string									MStringGlobalVariable at MStringSegment
//-------------------------------------------------------------------------------------------------------
// Definicia DATA SEGMENTS.
.data															MInt32Segment=int32(530)
.data															MStringSegment=bytearray(4D 00 79 00 20 00 6E 00 61 00 6D 00 65 00 20 00 69 00 73 00 20 00 54 00 69 00 6D 00 6D 00 79 00 20 00 41 00 6E 00 64 00 65 00 72 00 73 00 6F 00 6E 00 20 00 21 00)
//-------------------------------------------------------------------------------------------------------