//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly extern UnmanagedCOMServer {}
.assembly UnmanagedCode {}
.module UnmanagedCode.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "Callback.il"
#include "Delegates.il"
//-------------------------------------------------------------------------------------------------------
.namespace UnmanagedCode
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CUnmanagedCode extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 sscanf(string,string) cil managed preservesig {}
		.method public static pinvokeimpl("msvcrt.dll" cdecl) vararg int32 printf(string) cil managed preservesig {}
		// !!! UNMANAGED FUNCTION puts() vyvolana cez PINVOKE.
		.method public static pinvokeimpl("msvcrt.dll" cdecl) int32 puts(string) cil managed preservesig {}
		// !!! UNMANAGED FUNCTION puts() vyvolana cez LOCAL PINVOKE.
		// !!!!! Toto [ILASM.EXE] NEDOKAZE SKOMPILOVAT. METHODS s FLAGS [native] [unmanaged] [ILASM.EXE] NEPODPORUJE.
		//.method public static pinvokeimpl() int32 puts(string) native unmanaged preservesig {}
		.method public static pinvokeimpl("user32.dll" unicode lasterr winapi) int32 MessageBoxW(int32,string,string,int32) cil managed preservesig {}
		.method public static pinvokeimpl("UnmanagedLibrary.dll" cdecl unicode) void PrintMessage(string) cil managed preservesig {}
		.method public static pinvokeimpl("UnmanagedLibrary.dll" cdecl unicode) void ExecuteCallback(class UnmanagedCode.DMyDelegate) preservesig {}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void PrintVectorItem(int32 Index, int32 Value) cil managed
		{
			ldstr							".NET - ITEM[{0}]=[{1}] !"
			ldarg							Index
			box								[mscorlib]System.Int32
			ldarg							Value
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void PINVOKECallback(string MessageFromLibrary, int32 Length) cil managed
		{
			ldstr							".NET - MESSAGE FROM LIBRARY [{0}], LENGTH [{1}] !"
			ldarg							MessageFromLibrary
			ldarg							Length
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Test1() cil managed
		{
            .locals							init (int32 Temp)
            .locals							init (int32 Retval)

        ASK_FOR_NUMBER:
            ldstr							"Enter a number:"
            call							void [mscorlib]System.Console::WriteLine(string)
            call							string [mscorlib]System.Console::ReadLine()

            ldstr							"%d"
            ldloca							Temp
			// !!! VSETKY OPTIONAL PARAMETERS musia byt definovane za [...].
            call							vararg int32 UnmanagedCode.CUnmanagedCode::sscanf(string,string,...,int32*)
			stloc							Retval

            ldloc							Retval
            brfalse							ERROR

            ldloc							Temp
            ldc.i4							1
            and
            brfalse							IT_IS_EVEN

            ldstr							"VALUE is ODD !"
            br								PRINT_AND_RETURN

        IT_IS_EVEN:
            ldstr							"VALUE is EVEN !"
            br								PRINT_AND_RETURN

        ERROR:
            ldstr							"VALUE is INVALID !"

        PRINT_AND_RETURN:
            call							void [mscorlib]System.Console::WriteLine(string)
            ldloc							Retval
            brtrue							ASK_FOR_NUMBER

            ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test2() cil managed
		{
            ldstr							"NAME [%s], AGE [%d] !"
            ldstr							"Timmy Anderson"
            ldc.i4							12
			// !!! VSETKY OPTIONAL PARAMETERS musia byt definovane za [...].
            call							vararg int32 UnmanagedCode.CUnmanagedCode::printf(string,...,string,int32*)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test3() cil managed
		{
            ldc.i4							0
            ldstr							"My name is TIMMY ANDERSON !"
            ldstr							"MESSAGE"
            ldc.i4							0
            call							int32 UnmanagedCode.CUnmanagedCode::MessageBoxW(int32,string,string,int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test4() cil managed
		{
            ldstr							"My name is TIMMY ANDERSON !"
            call							int32 UnmanagedCode.CUnmanagedCode::puts(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test5() cil managed
		{
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass COMObject)

            ldstr							"METHOD BEGIN !"
			call							void [mscorlib]System.Console::WriteLine(string)
			
			newobj							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::.ctor()
			stloc							COMObject

			ldloc							COMObject
			ldstr							"Hello COM !"
			call							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::PrintMessage(string)

			ldnull
			stloc							COMObject

            ldstr							"METHOD END !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test6() cil managed
		{
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass COMObject)
            .locals							init (string Name, int32 Age)

            ldstr							"METHOD BEGIN !"
			call							void [mscorlib]System.Console::WriteLine(string)
			
			newobj							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::.ctor()
			stloc							COMObject

			ldloc							COMObject
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::SaveName(string,int32)

			ldloc							COMObject
			ldloca							Name
			ldloca							Age
			call							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::LoadName(string&,int32&)

			ldstr							"NAME [{0}], AGE [{1}] !"
			ldloc							Name
			ldloc							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldnull
			stloc							COMObject

            ldstr							"METHOD END !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test7() cil managed
		{
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass COMObject)
			// !!! CALLBACK MUSI BYT PINNED, pretoze COM OBJECT si ho uklada do FIELD a pocas doby ked je vo FIELD ulozeny ho NESMIE GC presunut.
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.IUnmanagedCOMServerCallback pinned COMCallback)

            ldstr							"METHOD BEGIN !"
			call							void [mscorlib]System.Console::WriteLine(string)

			newobj							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::.ctor()
			stloc							COMObject

			// !!! Vytvori sa COM CALLBACK OBJECT.
			newobj							instance void UnmanagedCode.CCOMCallback::.ctor()
			castclass						[UnmanagedCOMServer]UnmanagedCOMServer.IUnmanagedCOMServerCallback
			stloc							COMCallback

			// !!! CALLBACK sa zaregistruje v COM OBJECT.
			ldloc							COMObject
			ldloc							COMCallback
			callvirt						instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::RegisterCallback(class [UnmanagedCOMServer]UnmanagedCOMServer.IUnmanagedCOMServerCallback)

			ldloc							COMObject
			ldstr							"Timmy Anderson"
			callvirt						instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::SendMessageToServer(string)

			// !!! CALLBACK sa odregistruje z COM OBJECT.
			ldloc							COMObject
			callvirt						instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::UnRegisterCallback()

			ldnull
			stloc							COMCallback

			ldnull
			stloc							COMObject

            ldstr							"METHOD END !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test8() cil managed
		{
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass COMObject)
            .locals							init (int32& PointerToRawMemory)
            .locals							init (int32& Pointer)
            .locals							init (int32 Index)

            ldstr							"METHOD BEGIN !"
			call							void [mscorlib]System.Console::WriteLine(string)
			
			newobj							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::.ctor()
			stloc							COMObject

			ldc.i4							12
			localloc
			stloc							PointerToRawMemory

			// !!! Naplni sa ARRAY.
			ldloc							PointerToRawMemory
			stloc							Pointer

			ldloc							Pointer
			ldc.i4							11
			stind.i4

			// Inkrementuje sa POINTER.
			ldloc							Pointer
			sizeof							int32
			add
			stloc							Pointer

			ldloc							Pointer
			ldc.i4							22
			stind.i4

			// Inkrementuje sa POINTER.
			ldloc							Pointer
			sizeof							int32
			add
			stloc							Pointer

			ldloc							Pointer
			ldc.i4							33
			stind.i4

			ldloc							PointerToRawMemory
			stloc							Pointer

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_1:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_1

			ldloc							Index
			ldloc							Pointer
			ldind.i4
			call							void UnmanagedCode.CUnmanagedCode::PrintVectorItem(int32,int32)

			// Inkrementuje Pointer.
			ldloc							Pointer
			sizeof							int32
			add
			stloc							Pointer

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_1

		END_FOR_1:

			// !!! Zavola sa COM METHOD.
			ldloc							COMObject
			ldc.i4							3
			ldloc							PointerToRawMemory
			call							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::ArrayTest1(int32,int32&)

			ldloc							PointerToRawMemory
			stloc							Pointer

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_2:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_2

			ldloc							Index
			ldloc							Pointer
			ldind.i4
			call							void UnmanagedCode.CUnmanagedCode::PrintVectorItem(int32,int32)

			// Inkrementuje Pointer.
			ldloc							Pointer
			sizeof							int32
			add
			stloc							Pointer

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_2

		END_FOR_2:

			ldnull
			stloc							COMObject

            ldstr							"METHOD END !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test9() cil managed
		{
            .locals							init (class [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass COMObject)
            .locals							init (int32[] Vector)
            .locals							init (int32 Index)

            ldstr							"METHOD BEGIN !"
			call							void [mscorlib]System.Console::WriteLine(string)
			
			newobj							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::.ctor()
			stloc							COMObject

			// !!! Vytvori sa VECTOR o dlzke 3.
			ldc.i4							3
			newarr							[mscorlib]System.Int32
			stloc							Vector

			ldloc							Vector
			ldc.i4							0
			ldc.i4							11
			stelem.i4

			ldloc							Vector
			ldc.i4							1
			ldc.i4							22
			stelem.i4

			ldloc							Vector
			ldc.i4							2
			ldc.i4							33
			stelem.i4

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_1:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_1

			// 1. PARAMETER METHOD PrintVectorItem().
			ldloc							Index

			// 2. PARAMETER METHOD PrintVectorItem().
			// !!! Nacita hodnotu Vector[Index].
			ldloc							Vector
			ldloc							Index
			ldelem.i4

			call							void UnmanagedCode.CUnmanagedCode::PrintVectorItem(int32,int32)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_1

		END_FOR_1:

			// !!! Zavola sa COM METHOD.
			ldloc							COMObject
			ldloca							Vector
			call							instance void [UnmanagedCOMServer]UnmanagedCOMServer.UnmanagedCOMObjectClass::ArrayTest2(int32[]&)

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_2:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_2

			// 1. PARAMETER METHOD PrintVectorItem().
			ldloc							Index

			// 2. PARAMETER METHOD PrintVectorItem().
			// !!! Nacita hodnotu Vector[Index].
			ldloc							Vector
			ldloc							Index
			ldelem.i4

			call							void UnmanagedCode.CUnmanagedCode::PrintVectorItem(int32,int32)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_2

		END_FOR_2:

			ldnull
			stloc							COMObject

            ldstr							"METHOD END !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test10() cil managed
		{
            ldstr							"Timmy Anderson"
            call							void UnmanagedCode.CUnmanagedCode::PrintMessage(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Test11() cil managed
		{
			.locals							init (class UnmanagedCode.DMyDelegate Delegate)

			ldnull
			ldftn							void UnmanagedCode.CUnmanagedCode::PINVOKECallback(string,int32)
			newobj							instance void UnmanagedCode.DMyDelegate::.ctor(object,native int)
			stloc							Delegate

            ldloc							Delegate
            call							void UnmanagedCode.CUnmanagedCode::ExecuteCallback(class UnmanagedCode.DMyDelegate)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void UnmanagedCode.CUnmanagedCode::Test1()
			//call							void UnmanagedCode.CUnmanagedCode::Test2()
			//call							void UnmanagedCode.CUnmanagedCode::Test3()
			//call							void UnmanagedCode.CUnmanagedCode::Test4()
			//call							void UnmanagedCode.CUnmanagedCode::Test5()
			//call							void UnmanagedCode.CUnmanagedCode::Test6()
			//call							void UnmanagedCode.CUnmanagedCode::Test7()
			//call							void UnmanagedCode.CUnmanagedCode::Test8()
			//call							void UnmanagedCode.CUnmanagedCode::Test9()
			//call							void UnmanagedCode.CUnmanagedCode::Test10()
			call							void UnmanagedCode.CUnmanagedCode::Test11()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------