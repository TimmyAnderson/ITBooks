//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Arrays {}
.module Arrays.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Arrays
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CArrays extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void PrintVectorItem(int32 Index, int32 Value) cil managed
		{
			ldstr							"ITEM[{0}]=[{1}] !"
			ldarg							Index
			box								[mscorlib]System.Int32
			ldarg							Value
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void PrintVectorItem(int32 Index, string Value) cil managed
		{
			ldstr							"ITEM[{0}]=[{1}] !"
			ldarg							Index
			box								[mscorlib]System.Int32
			ldarg							Value
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Print2DimensionalArrayItem(int32 Index1, int32 Index2, int32 Value) cil managed
		{
			ldstr							"ITEM[{0},{1}]=[{2}] !"
			ldarg							Index1
			box								[mscorlib]System.Int32
			ldarg							Index2
			box								[mscorlib]System.Int32
			ldarg							Value
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			.locals init					(int32[] Vector, int32 Index)

			// !!! Vytvori sa VECTOR o dlzke 3.
			ldc.i4							3
			newarr							[mscorlib]System.Int32
			stloc							Vector

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_1:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_1

			// Vykona operaciu Vector[Index]=(Index+10).
			ldloc							Vector
			ldloc							Index
			// Ulozi hodnotu (Index+10), ktora ma byt ulozena do Vector[Index].
			ldloc							Index
			ldc.i4							10
			add
			// !!! Na STACK musi byt ARRAY, INDEX a VALUE, ktora sa ma do ARRAY[INDEX] ulozit.
			stelem.i4

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_1

		END_FOR_1:

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

			call							void Arrays.CArrays::PrintVectorItem(int32,int32)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_2

		END_FOR_2:

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			.locals init					(int32[0...3,0...4] MultiArray, int32 Index1, int32 Index2)

			// !!! Vytvori sa MULTI DIMENSIONS ARRAYS o dlzke 3.
			ldc.i4							3
			ldc.i4							4
			newobj							instance void int32[0...3,0...4]::.ctor(int32,int32)
			stloc							MultiArray

			ldc.i4							0
			stloc							Index1

		BEGIN_FOR_INDEX1_1:
			// !!! Ukonci cyklus, ak Index1>=3.
			ldloc							Index1
			ldc.i4							3
			bge								END_FOR_INDEX1_1

			ldc.i4							0
			stloc							Index2

		BEGIN_FOR_INDEX2_1:
			// !!! Ukonci cyklus, ak Index2>=4.
			ldloc							Index2
			ldc.i4							4
			bge								END_FOR_INDEX2_1
			
			// Vykona operaciu MultiArray[Index1,Index2]=(Index1*10+Index2).
			ldloc							MultiArray
			ldloc							Index1
			ldloc							Index2
			// Ulozi hodnotu (Index1*10+Index2), ktora ma byt ulozena do MultiArray[Index1,Index2].
			ldloc							Index1
			ldc.i4							10
			mul
			ldloc							Index2
			add
			// !!! Na STACK musi byt ARRAY, INDEX1, INDEX2 a VALUE, ktora sa ma do ARRAY[INDEX1,INDEX2] ulozit.
			call							instance void int32[0...3,0...4]::Set(int32,int32,int32)

			// Inkrementuje Index2.
			ldloc							Index2
			ldc.i4							1
			add
			stloc							Index2

			br								BEGIN_FOR_INDEX2_1

		END_FOR_INDEX2_1:

			// Inkrementuje Index1.
			ldloc							Index1
			ldc.i4							1
			add
			stloc							Index1

			br								BEGIN_FOR_INDEX1_1

		END_FOR_INDEX1_1:

			ldc.i4							0
			stloc							Index1

		BEGIN_FOR_INDEX1_2:
			// !!! Ukonci cyklus, ak Index1>=3.
			ldloc							Index1
			ldc.i4							3
			bge								END_FOR_INDEX1_2

			ldc.i4							0
			stloc							Index2

		BEGIN_FOR_INDEX2_2:
			// !!! Ukonci cyklus, ak Index2>=4.
			ldloc							Index2
			ldc.i4							4
			bge								END_FOR_INDEX2_2

			// 1. PARAMETER METHOD Print2DimensionalArrayItem().
			ldloc							Index1
			// 2. PARAMETER METHOD Print2DimensionalArrayItem().
			ldloc							Index2

			// 3. PARAMETER METHOD Print2DimensionalArrayItem().
			// !!! Nacita hodnotu MultiArray[Index1,Index2].
			ldloc							MultiArray
			ldloc							Index1
			ldloc							Index2
			call							instance int32 int32[0...3,0...4]::Get(int32,int32)

			call							void Arrays.CArrays::Print2DimensionalArrayItem(int32,int32,int32)

			// Inkrementuje Index2.
			ldloc							Index2
			ldc.i4							1
			add
			stloc							Index2

			br								BEGIN_FOR_INDEX2_2

		END_FOR_INDEX2_2:

			// Inkrementuje Index1.
			ldloc							Index1
			ldc.i4							1
			add
			stloc							Index1

			br								BEGIN_FOR_INDEX1_2

		END_FOR_INDEX1_2:

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			.locals init					(string[] Vector, int32 Index, int32 Temp)

			// !!! Vytvori sa VECTOR o dlzke 3.
			ldc.i4							3
			newarr							[mscorlib]System.String
			stloc							Vector

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_1:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldc.i4							3
			bge								END_FOR_1

			// Vykona operaciu Vector[Index]="(Index+10)".
			ldloc							Vector
			ldloc							Index
			// Ulozi hodnotu (Index+10), ktora ma byt ulozena do Vector[Index].
			ldloc							Index
			ldc.i4							10
			add
			stloc							Temp
			ldloca							Temp
			call							instance string [mscorlib]System.Int32::ToString()

			// !!! Na STACK musi byt ARRAY, INDEX a VALUE, ktora sa ma do ARRAY[INDEX] ulozit.
			stelem.ref

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_1

		END_FOR_1:

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
			ldelem.ref

			call							void Arrays.CArrays::PrintVectorItem(int32,string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_2

		END_FOR_2:

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void Arrays.CArrays::Test1()
			//call							void Arrays.CArrays::Test2()
			call							void Arrays.CArrays::Test3()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------