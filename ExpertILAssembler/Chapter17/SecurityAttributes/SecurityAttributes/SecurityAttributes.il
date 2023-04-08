//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly SecurityAttributes {}
.module SecurityAttributes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace SecurityAttributes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CSecurityAttributes extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// Nema aplikovany PERMISSION.
		.method private hidebysig static void CreateAndWriteFile1() cil managed
		{
			.locals							init (class [mscorlib]System.IO.StreamWriter Writer)

			ldstr							"C:\\Text.!!!"
			newobj							instance void [mscorlib]System.IO.StreamWriter::.ctor(string)
			stloc							Writer

			ldloc							Writer
			ldstr							"My name is Timmy Anderson !"
			callvirt						instance void [mscorlib]System.IO.TextWriter::WriteLine(string)

			ldloc							Writer
			callvirt						instance void [mscorlib]System.IO.TextWriter::Close()
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Bohuzial, ked som aplikoval KEYWORD [.permission], MSIL COMPILER sa pri kompilacii ZRUTIL.
		// Ma aplikovany PERMISSION.
		.method private hidebysig static void CreateAndWriteFile2() cil managed
		{
			//.permission					demand [mscorlib]System.Security.Permissions.FileIOPermissionAttribute ("Write"="C:\\Text.!!!")

			.locals							init (class [mscorlib]System.IO.StreamWriter Writer)

			ldstr							"C:\\Text.!!!"
			newobj							instance void [mscorlib]System.IO.StreamWriter::.ctor(string)
			stloc							Writer

			ldloc							Writer
			ldstr							"My name is Timmy Anderson !"
			callvirt						instance void [mscorlib]System.IO.TextWriter::WriteLine(string)

			ldloc							Writer
			callvirt						instance void [mscorlib]System.IO.TextWriter::Close()
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
		// Ma aplikovany PERMISSION SET.
		.method private hidebysig static void CreateAndWriteFile3() cil managed
		{
			.permissionset					demand={[mscorlib]System.Security.Permissions.FileIOPermissionAttribute = {property string 'Write' = string('C:\\Text.!!!')}}

			.locals							init (class [mscorlib]System.IO.StreamWriter Writer)

			ldstr							"C:\\Text.!!!"
			newobj							instance void [mscorlib]System.IO.StreamWriter::.ctor(string)
			stloc							Writer

			ldloc							Writer
			ldstr							"My name is Timmy Anderson !"
			callvirt						instance void [mscorlib]System.IO.TextWriter::WriteLine(string)

			ldloc							Writer
			callvirt						instance void [mscorlib]System.IO.TextWriter::Close()
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! HODI EXCEPTION, pretoze DENY ACTION je OBSOLETE.
        .method public hidebysig static void DenyTest() cil managed
		{
			// !!! DENY ACTION je OBSOLETE.
			.permissionset					deny={[mscorlib]System.Security.Permissions.FileIOPermissionAttribute = {property string 'Write' = string('C:\\Text.!!!')}}

			call							void SecurityAttributes.CSecurityAttributes::CreateAndWriteFile3()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			.try
			{
				call						void SecurityAttributes.CSecurityAttributes::CreateAndWriteFile1()

				ldstr						"FILE SUCCESSFULLY WRITTEN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			.try
			{
				call						void SecurityAttributes.CSecurityAttributes::CreateAndWriteFile2()

				ldstr						"FILE SUCCESSFULLY WRITTEN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			.try
			{
				call						void SecurityAttributes.CSecurityAttributes::CreateAndWriteFile3()

				ldstr						"FILE SUCCESSFULLY WRITTEN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
			.try
			{
				call						void SecurityAttributes.CSecurityAttributes::DenyTest()

				ldstr						"FILE SUCCESSFULLY WRITTEN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void SecurityAttributes.CSecurityAttributes::Test1()
			//call							void SecurityAttributes.CSecurityAttributes::Test2()
			//call							void SecurityAttributes.CSecurityAttributes::Test3()
			// !!!!! Hodi UNHANDLED EXCEPTION. Vyzera to, ze ak sa pouziva OBSOLETE PERMISSION DENY, tak takuto [NotSupportedException] NIE JE MOZNE ZACHYTIT.
			call							void SecurityAttributes.CSecurityAttributes::Test4()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------