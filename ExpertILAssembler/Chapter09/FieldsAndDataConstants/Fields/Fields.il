//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Fields {}
.module Fields.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
// Definicia DATA SEGMENTS.
.data															MInt32Segment1=int32(0)
// Hodnota 1122867.
.data															MInt32Segment2=int32(0x112233)
.data															MInt32Segment3=int32(12345678)
// Konvertuje STRING na UNICODE STRING.
.data															MStringSegment=char*("My name is Timmy Anderson !\0")
// Referuje SEGMENT MReferencedSegment na SEGMENT MInt32Segment3.
.data															MReferencedSegment=&(MInt32Segment3)
// SEGMENT, ktory obsahuje BYTE ARRAY.
// !!! Obsahuje hodnotu 0x01010101=16843009.
.data															MArraySegment=int8(1)[4]
//-------------------------------------------------------------------------------------------------------
.field public static string										MGlobalField
//-------------------------------------------------------------------------------------------------------
// STATIC CONSTRUCTOR pre MODULE. Umoznuje inicializaciu GLOBAL FIELDS.
.method public specialname rtspecialname static void .cctor() cil managed
{
	ldstr									"MODULE STATIC CONSTRUCTOR CALLED !"
	call									void [mscorlib]System.Console::WriteLine(string)

	ldstr									"This is GLOBAL FIELD !"
	stsfld									string MGlobalField

	ldstr									"This is GLOBAL FIELD in NAMESPACE !"
	stsfld									string MGlobalFieldInNamespace

	ret
}
//-------------------------------------------------------------------------------------------------------
.namespace Fields
{
//-------------------------------------------------------------------------------------------------------
.field assembly static string									MGlobalFieldInNamespace
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	// !!! Implementacia UNION v MSIL.
    .class public sealed explicit ansi value CUnion extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
        .field [0] public int32									MDWORD
        .field [0] public int16									MWORD1
        .field [2] public int16									MWORD2
        .field [0] public int8									MBYTE1
        .field [1] public int8									MBYTE2
        .field [2] public int8									MBYTE3
        .field [3] public int8									MBYTE4
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg.0
			ldc.i4							0x11
			stfld							int8 Fields.CUnion::MBYTE1
			ldarg.0
			ldc.i4							0x22
			stfld							int8 Fields.CUnion::MBYTE2
			ldarg.0
			ldc.i4							0x33
			stfld							int8 Fields.CUnion::MBYTE3
			ldarg.0
			ldc.i4							0x44
			stfld							int8 Fields.CUnion::MBYTE4

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public sealed explicit ansi CWrongClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! VALUE a REFERENCE TYPES NESMU byt prekryte.
        //.field [0] public int8								MWrongA1
        //.field [0] public string								MWrongA2
		// !!! REFERENCE TYPES NESMU byt NEKOMPLETNE prekryte.
        .field [0] public string								MWrongB1
        .field [2] public string								MWrongB2
		// !!! REFERENCE TYPES MOZU byt KOMPLETNE prekryte.
        .field [0] public string								MOK1
        .field [0] public string								MOK2
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public sealed sequential value ansi CSequentialValueType1 extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! ORDINAL NUMBERS pre FIELDS v SEQUENTIAL TYPE DEFINUJU to v AKOM PORADI budu FIELDS ulozene v MEMORY. NEURCUJU EXPLICITNY OFFSET, ale iba PORADIE. OFFSET je kalkulaovany AUTOMATICKY z PORADIA FIELDS. Vyssie cislo znamena, ze FIELD bude SKOR v MEMORY.
        .field [3] public int8									MField1
		// !!! PRVY v poradi.
        .field [8] public int8									MField2
        .field [1] public int8									MField3
		// !!! POSLEDNY v poradi.
        .field [0] public int8									MField4
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CSequentialValueType1 CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			ldc.i4							0x11
			stfld							int8 Fields.CSequentialValueType1::MField1
			ldarg.0
			ldc.i4							0x22
			stfld							int8 Fields.CSequentialValueType1::MField2
			ldarg.0
			ldc.i4							0x33
			stfld							int8 Fields.CSequentialValueType1::MField3
			ldarg.0
			ldc.i4							0x44
			stfld							int8 Fields.CSequentialValueType1::MField4

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public sealed sequential value ansi CSequentialValueType2 extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
		// ORDINAL NUMBERS pre FIELDS v SEQUENTIAL TYPE DEFINUJU to v AKOM PORADI budu FIELDS ulozene v MEMORY. NEURCUJU EXPLICITNY OFFSET, ale iba PORADIE. OFFSET je kalkulaovany AUTOMATICKY z PORADIA FIELDS. Vyssie cislo znamena, ze FIELD bude SKOR v MEMORY.
		// !!! POSLEDNY v poradi.
        .field [0] public int8									MField1
		// !!! PRVY v poradi.
        .field [8] public int8									MField2
        .field [2] public int8									MField3
        .field [3] public int8									MField4
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CSequentialValueType2 CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			ldc.i4							0x11
			stfld							int8 Fields.CSequentialValueType2::MField1
			ldarg.0
			ldc.i4							0x22
			stfld							int8 Fields.CSequentialValueType2::MField2
			ldarg.0
			ldc.i4							0x33
			stfld							int8 Fields.CSequentialValueType2::MField3
			ldarg.0
			ldc.i4							0x44
			stfld							int8 Fields.CSequentialValueType2::MField4

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public sealed value ansi explicit CExplicitValueType1 extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
        .field [3] public int8									MField1
		// !!! Bude na BYTE 8.
        .field [8] public int8									MField2
        .field [1] public int8									MField3
        .field [0] public int8									MField4
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CExplicitValueType1 CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			ldc.i4							0x11
			stfld							int8 Fields.CExplicitValueType1::MField1
			ldarg.0
			ldc.i4							0x22
			stfld							int8 Fields.CExplicitValueType1::MField2
			ldarg.0
			ldc.i4							0x33
			stfld							int8 Fields.CExplicitValueType1::MField3
			ldarg.0
			ldc.i4							0x44
			stfld							int8 Fields.CExplicitValueType1::MField4

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public sealed value ansi explicit CExplicitValueType2 extends [mscorlib]System.ValueType
	{
//-------------------------------------------------------------------------------------------------------
        .field [0] public int8									MField1
		// !!! Bude na BYTE 8.
        .field [8] public int8									MField2
        .field [2] public int8									MField3
        .field [3] public int8									MField4
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CExplicitValueType2 CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg.0
			ldc.i4							0x11
			stfld							int8 Fields.CExplicitValueType2::MField1
			ldarg.0
			ldc.i4							0x22
			stfld							int8 Fields.CExplicitValueType2::MField2
			ldarg.0
			ldc.i4							0x33
			stfld							int8 Fields.CExplicitValueType2::MField3
			ldarg.0
			ldc.i4							0x44
			stfld							int8 Fields.CExplicitValueType2::MField4

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CFields extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .field public string									MNonStaticValue1
        .field public int32										MNonStaticValue2
//-------------------------------------------------------------------------------------------------------
        .field public static string								MStaticValue1
        .field public static int32								MStaticValue2
//-------------------------------------------------------------------------------------------------------
        .field public static literal string						MStaticLiteralValue1
        .field public static literal int32						MStaticLiteralValue2
//-------------------------------------------------------------------------------------------------------
        .field public static initonly string					MStaticInitOnlyValue1
        .field public static initonly int32						MStaticInitOnlyValue2
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR IGNORUJE CONSTANT INITIALIZERS a preto MNonStaticValueWithDefault1=="" a MNonStaticValueWithDefault2==0.
        .field public string									MNonStaticValueWithDefault1="Timmy Anderson"
        .field public int32										MNonStaticValueWithDefault2=int32(12)
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR IGNORUJE CONSTANT INITIALIZERS a preto MStaticValueWithDefault1=="" a MStaticValueWithDefault2==0.
        .field public static string								MStaticValueWithDefault1="Timmy Anderson"
        .field public static int32								MStaticValueWithDefault2=int32(12)
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR IGNORUJE CONSTANT INITIALIZERS a FIELDS NENASTAVI na DEFAULT VALUES.
        .field public static string								MDefault1="Timmy Anderson"
        .field public static int32								MDefault2=int32(12)
        .field public static bool								MDefault3=bool(true)
        .field public static float32							MDefault4=float32(1.2345)
        .field public static int16								MDefault5=int16(0x1234)
        .field public static object								MDefault6=nullref
		// STRING 'AAA'.
        .field public static string								MDefault7=bytearray(00 03 FF FE 41 00 41 00 41 00 00 00)
		// Specialna SYNTAX pre specialne FLOAT hodnoty.
        .field public static float32							MDefault_PositiveInfinite=float32(0x7F800000)
        .field public static float32							MDefault_NegativeInfinite=float32(0xFF800000)
        .field public static float32							MDefault_NotANumber=float32(0xFFC00000)
//-------------------------------------------------------------------------------------------------------
		// Iba STATIC FIELDS mozu byt MAPPED FIELDS.
        .field public static int32								MMappedField1 at MInt32Segment1
        .field public static int32								MMappedField2 at MInt32Segment1
        .field public static int32								MMappedField3 at MInt32Segment2
		// !!! Bude MAPPED na ZACIATOK UNICODE STRING.
        .field public static char								MMappedField4 at MStringSegment
        .field public static int32								MMappedField5 at MInt32Segment3
        .field public static int32								MMappedField6 at MArraySegment
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// STATIC CONSTRUCTOR.
	    .method public specialname rtspecialname static void .cctor() cil managed
		{
			ldstr							"STATIC CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! CODE SPOSOBUJE ERROR, pretoze CLR NEUMOZNUJE pristup k LITERAL FIELDS.
			/*	
			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							string Fields.CFields::MStaticLiteralValue1
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							int32 Fields.CFields::MStaticLiteralValue2
			*/

			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							string Fields.CFields::MStaticInitOnlyValue1
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							int32 Fields.CFields::MStaticInitOnlyValue2

			ret
		}
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// NON-STATIC METHOD.
        .method public hidebysig void NonStaticMethod() cil managed
		{
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stfld] zapisuje hodnotu zo STACKU do NON-STATIC FIELD.
			stfld							string Fields.CFields::MNonStaticValue1
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			ldc.i4							12
			// !!! INSTRUCTION [stfld] zapisuje hodnotu zo STACKU do NON-STATIC FIELD.
			stfld							int32 Fields.CFields::MNonStaticValue2

			ldstr							"NON-STATIC METHOD - NAME [{0}], AGE [{1}] !"
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			// !!! INSTRUCTION [ldfld] cita hodnotu z NON-STATIC FIELD do STACKU.
			ldfld							string Fields.CFields::MNonStaticValue1
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			// !!! INSTRUCTION [ldfld] cita hodnotu z NON-STATIC FIELD do STACKU.
			ldfld							int32 Fields.CFields::MNonStaticValue2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// STATIC METHOD.
        .method public hidebysig static void StaticMethod() cil managed
		{
			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							string Fields.CFields::MStaticValue1
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							int32 Fields.CFields::MStaticValue2

			ldstr							"STATIC METHOD - NAME [{0}], AGE [{1}] !"
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							string Fields.CFields::MStaticValue1
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MStaticValue2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// STATIC METHOD.
        .method public hidebysig static void StaticMethodForLiterals() cil managed
		{
			// !!!!! MSIL NEUMOZNUJE pristupovat k LITERAL FIELDS a pri pokuse o pristup k tymto FIELDS je generovana EXCEPTION [MissingFieldException].

			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							string Fields.CFields::MStaticLiteralValue1
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							int32 Fields.CFields::MStaticLiteralValue2

			ldstr							"STATIC METHOD for LITERALS - NAME [{0}], AGE [{1}] !"
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							string Fields.CFields::MStaticLiteralValue1
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MStaticLiteralValue2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// STATIC METHOD.
        .method public hidebysig static void StaticMethodForInitOnly() cil managed
		{
			// !!!!! MSIL UMOZNUJE ZAPISOVAT do INITONLY FIELDS aj ked to nie je v sulade s CLR SPECIFICATION.

			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							string Fields.CFields::MStaticInitOnlyValue1
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			stsfld							int32 Fields.CFields::MStaticInitOnlyValue2

			ldstr							"STATIC METHOD for INITONLY - NAME [{0}], AGE [{1}] !"
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							string Fields.CFields::MStaticInitOnlyValue1
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MStaticInitOnlyValue2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// NON-STATIC METHOD.
        .method public hidebysig void NonStaticMethodWithDefaults() cil managed
		{
			// !!!!! CLR IGNORUJE CONSTANT INITIALIZERS a preto MNonStaticValueWithDefault1=="" a MNonStaticValueWithDefault2==0.

			ldstr							"NON-STATIC METHOD with DEFAULTS - NAME [{0}], AGE [{1}] !"
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			// !!! INSTRUCTION [ldfld] cita hodnotu z NON-STATIC FIELD do STACKU.
			ldfld							string Fields.CFields::MNonStaticValueWithDefault1
			// !!! Nacita THIS. Je to NUTNE pretoze FIELD je NON-STATIC.
			ldarg.0
			// !!! INSTRUCTION [ldfld] cita hodnotu z NON-STATIC FIELD do STACKU.
			ldfld							int32 Fields.CFields::MNonStaticValueWithDefault2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// STATIC METHOD.
        .method public hidebysig static void StaticMethodWithDefaults() cil managed
		{
			// !!!!! CLR IGNORUJE CONSTANT INITIALIZERS a preto MStaticValueWithDefault1=="" a MStaticValueWithDefault2==0.

			ldstr							"STATIC METHOD - NAME [{0}], AGE [{1}] !"
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							string Fields.CFields::MStaticValueWithDefault1
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MStaticValueWithDefault2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// STATIC METHOD.
        .method public hidebysig static void MappedFields() cil managed
		{
			ldc.i4							12
			// !!! INSTRUCTION [stsfld] zapisuje hodnotu zo STACKU do STATIC FIELD.
			// !!!!! Kedze OBE FIELDS su MAPPED na TIE ISTE DATA, tak maju SHARED VALUE.
			stsfld							int32 Fields.CFields::MMappedField1

			// !!!!! Kedze OBE FIELDS su MAPPED na TIE ISTE DATA, tak maju SHARED VALUE.
			ldstr							"MAPPED FIELDS - FIELD1 [{0}], FIELD2 [{1}], FIELD3 [{2}] !"
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MMappedField1
			box								[mscorlib]System.Int32
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MMappedField2
			box								[mscorlib]System.Int32
			// !!! INSTRUCTION [ldsfld] cita hodnotu zo STATIC FIELD do STACKU.
			ldsfld							int32 Fields.CFields::MMappedField3
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Nacita sa ADRESA FIELD, ktory bol MAPPED na UNICODE STRING.
			ldsflda							char Fields.CFields::MMappedField4
			// !!! Vykona sa konverzia CHAR* na STRING.
			newobj							instance void [mscorlib]System.String::.ctor(char*)
			// STRING sa vypise na konzolu.
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"REFERENCED MAPPED FIELD [{0}] !"
			ldsfld							int32 Fields.CFields::MMappedField5
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ARRAY MAPPED FIELD [{0}] !"
			ldsfld							int32 Fields.CFields::MMappedField6
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! GENERUJE EXCEPTION.
        .method public hidebysig static void TryWrongType() cil managed
		{
			newobj							instance void Fields.CWrongClass::.ctor()
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			newobj							instance void Fields.CFields::.ctor()
			call							instance void Fields.CFields::NonStaticMethod()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			call							void Fields.CFields::StaticMethod()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			.try
			{
				call						void Fields.CFields::StaticMethodForLiterals()
				leave						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)
				leave						Exit
			}

	    Exit:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
			call							void Fields.CFields::StaticMethodForInitOnly()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
			newobj							instance void Fields.CFields::.ctor()
			call							instance void Fields.CFields::NonStaticMethodWithDefaults()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
			call							void Fields.CFields::StaticMethodWithDefaults()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test7() cil managed
		{
			call							void Fields.CFields::MappedFields()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
            .locals							init (valuetype Fields.CSequentialValueType1 SequentialClass1, valuetype Fields.CSequentialValueType1* Pointer1, int32 Value1)
            .locals							init (valuetype Fields.CSequentialValueType2 SequentialClass2, valuetype Fields.CSequentialValueType2* Pointer2, int32 Value2)

			newobj							instance void Fields.CSequentialValueType1::.ctor()
			stloc							SequentialClass1

			newobj							instance void Fields.CSequentialValueType2::.ctor()
			stloc							SequentialClass2

			ldloca							SequentialClass1
			stloc							Pointer1

			ldloca							SequentialClass2
			stloc							Pointer2

			ldloc							Pointer1
			ldind.i4
			stloc							Value1

			ldloc							Pointer2
			ldind.i4
			stloc							Value2

			ldstr							"SEQUENTIAL - VALUE1 [{0}], VALUE2 [{1}] !"
			ldloc							Value1
			call							string Helpers.CHelpers::ConvertToHex(int32)
			ldloc							Value2
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
            .locals							init (valuetype Fields.CExplicitValueType1 ExplicitClass1, valuetype Fields.CExplicitValueType1* Pointer1, int32 Value1)
            .locals							init (valuetype Fields.CExplicitValueType2 ExplicitClass2, valuetype Fields.CExplicitValueType2* Pointer2, int32 Value2)

			newobj							instance void Fields.CExplicitValueType1::.ctor()
			stloc							ExplicitClass1

			newobj							instance void Fields.CExplicitValueType2::.ctor()
			stloc							ExplicitClass2

			ldloca							ExplicitClass1
			stloc							Pointer1

			ldloca							ExplicitClass2
			stloc							Pointer2

			ldloc							Pointer1
			ldind.i4
			stloc							Value1

			ldloc							Pointer2
			ldind.i4
			stloc							Value2

			ldstr							"EXPLICIT - VALUE1 [{0}], VALUE2 [{1}] !"
			ldloc							Value1
			call							string Helpers.CHelpers::ConvertToHex(int32)
			ldloc							Value2
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! GENERUJE EXCEPTION.
        .method public hidebysig static void Test10() cil managed
		{
			.try
			{
				call						void Fields.CFields::TryWrongType()

				leave						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)
				leave						Exit
			}

	    Exit:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test11() cil managed
		{
            .locals							init (valuetype Fields.CUnion Union)

			newobj							instance void Fields.CUnion::.ctor()
			stloc							Union

			ldstr							"UNION - MBYTE1 [{0}] !"
			ldloc							Union
			ldfld							int8 Fields.CUnion::MBYTE1
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MBYTE2 [{0}] !"
			ldloc							Union
			ldfld							int8 Fields.CUnion::MBYTE2
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MBYTE3 [{0}] !"
			ldloc							Union
			ldfld							int8 Fields.CUnion::MBYTE3
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MBYTE4 [{0}] !"
			ldloc							Union
			ldfld							int8 Fields.CUnion::MBYTE4
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MWORD1 [{0}] !"
			ldloc							Union
			ldfld							int16 Fields.CUnion::MWORD1
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MWORD2 [{0}] !"
			ldloc							Union
			ldfld							int16 Fields.CUnion::MWORD2
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"UNION - MDWORD [{0}] !"
			ldloc							Union
			ldfld							int32 Fields.CUnion::MDWORD
			call							string Helpers.CHelpers::ConvertToHex(int32)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test12() cil managed
		{
			// !!! GLOBAL FIELDS su inicializovane v MODULE STATIC CONSTRUCTOR.

			ldsfld							string MGlobalField
			call							void [mscorlib]System.Console::WriteLine(string)

			/*
			// !!!!! Na GLOBAL FIELDS sa NEAPLIKUJU NAMESPACES a tento CODE hodi COMPILATION ERROR.
			ldsfld							string Fields.MGlobalFieldInNamespace
			call							void [mscorlib]System.Console::WriteLine(string)
			*/

			// !!!!! Na GLOBAL FIELDS sa NEAPLIKUJU NAMESPACES a tento CODE bude korektne COMPILED.
			ldsfld							string MGlobalFieldInNamespace
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			call							void Fields.CFields::Test1()
			call							void Fields.CFields::Test2()
			// !!! CODE SPOSOBUJE ERROR, pretoze CLR NEUMOZNUJE pristup k LITERAL FIELDS.
			//call							void Fields.CFields::Test3()
			call							void Fields.CFields::Test4()
			call							void Fields.CFields::Test5()
			call							void Fields.CFields::Test6()
			call							void Fields.CFields::Test7()
			call							void Fields.CFields::Test8()
			call							void Fields.CFields::Test9()
			// !!! Generuje EXCEPTION.
			//call							void Fields.CFields::Test10()
			call							void Fields.CFields::Test11()
			call							void Fields.CFields::Test12()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------