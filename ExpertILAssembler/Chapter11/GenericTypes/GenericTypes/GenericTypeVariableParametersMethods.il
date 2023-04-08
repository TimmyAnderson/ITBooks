//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!! GENERIC TYPES NESMU mat METHODS s VARIABLE PARAMETERS, inak je generovana EXCEPTION [TypeLoadException].
    .class public auto ansi CGenericTypeVariableParametersMethods<TParam> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field private !TParam									MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CGenericTypeVariableParametersMethods<TParam> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void SetField(!TParam Param) cil managed
		{
			ldarg							0
			ldarg							Param
			stfld							!0 class GenericTypes.CGenericTypeVariableParametersMethods<!TParam>::MField

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void PrintField() cil managed
		{
			ldstr							"TEST - MField [{0}] !"

			ldarg							0
			ldfld							!0 class GenericTypes.CGenericTypeVariableParametersMethods<!TParam>::MField
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Kedze TYPE ma METHOD s VARIABLE PARAMETERS, tak pri jeho nacitavani je generovana EXCEPTION [TypeLoadException].
        .method public hidebysig instance vararg void VariableParameters(string Param1, int32 Param2) cil managed
		{
			.locals init					(valuetype [mscorlib]System.ArgIterator Iterator, valuetype [mscorlib]System.RuntimeArgumentHandle ArgumentHandle, int32 NumberOfVariableParameters, int32 Index, object VariableParam)

			ldstr							"PARAM1 [{0}], PARAM2 [{1}] !"
			ldarg							Param1
			ldarg							Param2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! INSTRUCTION [arglist] NEPRIJIMA ZIADNE PARAMETERS zo STACK, ale na STACK ulozi POINTER VALUE TYPE [RuntimeArgumentHandle], ktory reprezentuje LIST vsetkych OPTIONAL PARAMETERS.
			arglist
			// !!! VALUE TYPE [RuntimeArgumentHandle], ktoru ulozila INSTRUCTION [arglist] na STACK je mozne ulozit do LOCAL VARIABLE.
			stloc							ArgumentHandle

			// !!! Nacita sa adresa VALUE TYPE [ArgIterator].
			ldloca							Iterator
			// !!! Nacita sa instancia VALUE TYPE [RuntimeArgumentHandle], ktora je PARAMETROM CONSTRUCTOR VALUE TYPE [ArgIterator].
			ldloc							ArgumentHandle
			// !!! Zavola sa CONSTRUCTOR VALUE TYPE [ArgIterator], ktoremu sa ako PARAMETER posle (cez STACK) VALUE TYPE [RuntimeArgumentHandle], ktory vratila INSTRUCTION [arglist].
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

			// !!! Zacina sa enumeracia vsetkych VARIABLE PARAMETERS.
			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=NumberOfVariableParameters.
			ldloc							Index
			ldloc							NumberOfVariableParameters
			bge								END_FOR

			// !!! Ziska sa hodnota VARIABLE PARAM.
			ldloca							Iterator
			// !!!!! METHOD ArgIterator.GetNextArg() uklada na STACK instanciu VALUE TYPE [TypedReference], ktora reprezentuje hodnotu CURRENT OPTIONAL PARAMETER.
			call							instance typedref [mscorlib]System.ArgIterator::GetNextArg()
			// !!! Zavola sa METHOD TypedReference::ToObject(typedref), ktora na STACK ulozi hodnotu OPTIONAL PARAMETER.
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------