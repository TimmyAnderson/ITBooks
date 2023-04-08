//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Modifiers {}
.module Modifiers.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Modifiers
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CModifiers extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Modifiers(string Value) cil managed
		{
			ldstr							"METHOD Modifiers() WITH NO MODIFIERS CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Kedze METHOD SIGNATURES sa lisia v aplikovani MODIFIER [modreq()], tak CLR generuje 2 NEZAVISLE METHODS, aj ked METHODS maju ROVNAKE PARAMETERS a RETURN VALUES.
		// !!! Ako MODIFIER TYPE moze byt pouzity LUBOVOLNY TYPE.
        .method public hidebysig static void Modifiers(string modreq([mscorlib]System.Int32) Value) cil managed
		{
			ldstr							"METHOD Modifiers() WITH MODIFIER [modreq()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Kedze METHOD SIGNATURES sa lisia v aplikovani MODIFIER [modopt()], tak CLR generuje 2 NEZAVISLE METHODS, aj ked METHODS maju ROVNAKE PARAMETERS a RETURN VALUES.
		// !!! Ako MODIFIER TYPE moze byt pouzity LUBOVOLNY TYPE.
        .method public hidebysig static void Modifiers(string modopt([mscorlib]System.Int32) Value) cil managed
		{
			ldstr							"METHOD Modifiers() WITH MODIFIER [modopt()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! V METHOD DEFINITION sa NESMIE pouzit MODIFIER [...]. Ten sa pouziva IBA v METHOD CALL.
        .method public hidebysig static vararg void VariableParameters(string Param1, int32 Param2) cil managed
		{
			.locals init					(valuetype [mscorlib]System.ArgIterator Iterator, int32 NumberOfVariableParameters, int32 Index, object VariableParam)

			ldstr							"PARAM1 [{0}], PARAM2 [{1}] !"
			ldarg							Param1
			ldarg							Param2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vytvori sa ARGUMENT ITERATOR.
			ldloca							Iterator
			arglist
			call							instance void [mscorlib]System.ArgIterator::.ctor(valuetype [mscorlib]System.RuntimeArgumentHandle)

			// !!! Nacita sa pocet VARIABLE PARAMETERS.
			ldloca							Iterator
			call							instance int32 [mscorlib]System.ArgIterator::GetRemainingCount()
			stloc							NumberOfVariableParameters

			ldstr							"NUMBER of VARIABLE PARAMETERS [{0}] !"
			ldloc							NumberOfVariableParameters
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zacina sa enumeracia vsetkych VARIABLE PARAMETERS.
			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=NumberOfVariableParameters.
			ldloc							Index
			ldloc							NumberOfVariableParameters
			bge								END_FOR

			// !!! Ziska sa hodnota VARIABLE PARAM.
			ldloca							Iterator
			call							instance typedref [mscorlib]System.ArgIterator::GetNextArg()
			call							object [mscorlib]System.TypedReference::ToObject(typedref)
			stloc							VariableParam

			// Vypise hodnotu VARIABLE PARAM.
			ldstr							"VARIABLE PARAM [{0}]: [{1}] !"
			ldloc							Index
			box								[mscorlib]System.Int32
			ldloc							VariableParam
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR

		END_FOR:

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// MODIFIER [pinned] je mozne aplikovat IBA na LOCAL VARIABLES.
        .method public hidebysig static void PinnedVariables() cil managed
		{
			.locals init					(int32 Variable1, int32 pinned *PointerVariable1)
			.locals init					(string Variable2, string pinned *PointerVariable2)

			ldc.i4							100
			stloc							Variable1

			ldstr							"VARIABLE1 [{0}] !"
			ldloc							Variable1
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// Ziska PINNED POINTER.
			ldloca							Variable1
			stloc							PointerVariable1

			ldloc							PointerVariable1
			ldc.i4							200
			stind.i4

			ldstr							"VARIABLE1 [{0}] !"
			ldloc							Variable1
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Timmy Anderson"
			stloc							Variable2

			ldstr							"VARIABLE2 [{0}] !"
			ldloc							Variable2
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// Ziska PINNED POINTER.
			ldloca							Variable2
			stloc							PointerVariable2

			ldloc							PointerVariable2
			ldstr							"Jenny Thompson"
			stind.ref

			ldstr							"VARIABLE2 [{0}] !"
			ldloc							Variable2
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			ldstr							"Some PARAM !"
			call							void Modifiers.CModifiers::Modifiers(string Value)

			ldstr							"Some PARAM !"
			// Vola sa METHOD s MODIFIER [modreq()].
			call							void Modifiers.CModifiers::Modifiers(string modreq([mscorlib]System.Int32) Value)

			ldstr							"Some PARAM !"
			// Vola sa METHOD s MODIFIER [modopt()].
			call							void Modifiers.CModifiers::Modifiers(string modopt([mscorlib]System.Int32) Value)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			ldstr							"Timmy Anderson"
			ldc.i4							12
			// !!! Ak sa METHOD s VARIABLE PARAMETERS vola BEZ VARIABLE PARAMETERS, tak sa MODIFIER [...] NESMIE pouzit.
			call							vararg void Modifiers.CModifiers::VariableParameters(string,int32)

			ldstr							"Timmy Anderson"
			ldc.i4							12
			ldstr							"Jenny Thompson"
			ldc.i4							13
			// !!! METHOD je volana s 2 VARIABLE PARAMETERS.
			call							vararg void Modifiers.CModifiers::VariableParameters(string,int32,...,string,int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			call							void Modifiers.CModifiers::PinnedVariables()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void Modifiers.CModifiers::Test1()
			//call							void Modifiers.CModifiers::Test2()
			call							void Modifiers.CModifiers::Test3()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------