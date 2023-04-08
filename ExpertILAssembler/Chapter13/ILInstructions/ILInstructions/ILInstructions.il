//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly ILInstructions {}
.module ILInstructions.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "Class.il"
#include "VirtualMethods.il"
#include "ValueTypeVirtualMethods.il"
#include "ExplicitMethodOverriding.il"
#include "IndirectMethodCalls.il"
#include "ValueTypes.il"
//-------------------------------------------------------------------------------------------------------
.namespace ILInstructions
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CILInstructions extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void ThrowException() cil managed
		{
			ldstr						"Some EXCEPTION !"
			// !!! Pred hodenim EXCEPTION MUSI byt na STACK ulozena instancia CLASS Exception.
			newobj						instance void class [mscorlib]System.Exception::.ctor(string)
			// !!! Hodi EXCEPTION.
			throw

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void RethrowException() cil managed
		{
			.try
			{
				call						void ILInstructions.CILInstructions::ThrowException()

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!! INSTRACTION spravi RETHROW aktualnej EXCEPTION. Na STACKU nepotrebuje mat nic.
				rethrow

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:
			ret
		}
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
		.method private hidebysig static void ConstrainedCall<TParam>(!!TParam Value) cil managed
		{
            .locals							init (string Result)

			ldarga							Value
			// !!! Ak by METHOD mala PARAMETERS, tak by boli na tomto mieste, az za INSTRUCTION [ldarga].
			// !!!!! Kedze je nutne vyvolavat MEMBER METHOD GENERIC PARAMETER bez INTRUCTION [constrained.] by METHOD NEDOKAZALA urcit ci GENERIC PARMETER je VALUE TYPE (kedy potrebuje MANAGED POINTER ziskavany cez INSTRUCTION [ldarga]), alebo REFERENCE TYPE (kedy potrebuje OBJECT REFERENCE ziskavany cez [ldloc]).
			constrained.					!!TParam
			callvirt						instance string [mscorlib]System.Object::ToString()
			stloc							Result

			ldstr							"CONSTRAINED CALL - VALUE [{0}] !"
			ldloc							Result
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD funguje IBA pre REFERENCE TYPES. Pre VALUE TYPES hodi EXCEPTION.
		.method private hidebysig static void UnconstrainedCallForReferenceTypes<TParam>(!!TParam Value) cil managed
		{
            .locals							init (string Result)

			// !!!!! Pre REFERENCE TYPES je NUTNE pouzit INSTRUCTION [ldarg].
			ldarg							Value
			callvirt						instance string [mscorlib]System.Object::ToString()
			stloc							Result

			ldstr							"UNCONSTRAINED CALL for REFERENCE TYPES - VALUE [{0}] !"
			ldloc							Result
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD funguje IBA pre VALUE TYPES. Pre REFERENCE TYPES hodi EXCEPTION.
		.method private hidebysig static void UnconstrainedCallForValueTypes1<TParam>(!!TParam Value) cil managed
		{
            .locals							init (string Result)

			// !!!!! Pre VALUE TYPES je NUTNE pouzit INSTRUCTION [ldarga].
			ldarga							Value
			// !!!!! VALUE TYPE pri tomto volani MUSI PRIAMO IMPLEMENTOVAT METHOD ToString().
			callvirt						instance string [mscorlib]System.Object::ToString()
			stloc							Result

			ldstr							"CONSTRAINED CALL for VALUE TYPES - VALUE [{0}] !"
			ldloc							Result
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD funguje IBA pre VALUE TYPES. Pre REFERENCE TYPES hodi EXCEPTION.
		.method private hidebysig static void UnconstrainedCallForValueTypes2<TParam>(!!TParam Value) cil managed
		{
            .locals							init (string Result)

			// !!!!! Pre VALUE TYPES je NUTNE pouzit INSTRUCTION [ldarga].
			ldarga							Value
			// !!!!! Ak VALUE TYPE NEIMPLEMENTUJE ToString(), je NUTNE vykonat DEREFERENCOVANIE MANAGED POINTER a vykonat BOXING.
			ldind.i
			box								!!TParam
			callvirt						instance string [mscorlib]System.Object::ToString()
			stloc							Result

			ldstr							"CONSTRAINED CALL for VALUE TYPES - VALUE [{0}] !"
			ldloc							Result
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD, ktora je volana cez TAIL CALL moze mat ODLISNU SIGNATURU, ale MUSI mat ROVNAKU RETURN VALUE.
        .method public hidebysig static string TailCalledMethod(int32 Identifier, string Name) cil managed
		{
			ldstr							"TailCalledMethod() - IDENTIFIER [{0}], NAME [{1}] !"
			ldarg							Identifier
			box								[mscorlib]System.Int32
			ldarg							Name
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! RETURN VALUE TailCalledMethod() sa stane RETURN VALUE TailCallTest(), ktora ju zavolala cez INSTRUCTION [tail. call].
			ldstr							"TAIL CALLED METHOD"

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static string TailCallTest(int32 Identifier, string Name, int32 Age) cil managed
		{
            .locals							init (string ReturnValue)

			ldstr							"TailCallTest() - IDENTIFIER [{0}], NAME [{1}], AGE [{2}] !"
			ldarg							Identifier
			box								[mscorlib]System.Int32
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			ldarg							Identifier
			bne.un							JUMP

			ldstr							"NO TAIL CALL"
			stloc							ReturnValue
			br								EXIT

		JUMP:
			ldc.i4							2
			ldarg							Identifier
			bne.un							DEFAULT

			ldstr							"BEFORE TAIL CALL !!!"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Pri pouzivani INSTRUCTION [tail. call] je NUTNE vlozit vsetky PARAMETERS na STACK.
			ldc.i4							100
			ldstr							"Jenny Thompson"
			// !!! PREFIX INSTRUCTION.
			tail.
			// !!! Samotna INSTRUCTION.
			call							string ILInstructions.CILInstructions::TailCalledMethod(int32,string)

			// !!!!! Za TAIL CALL musi VZDY OKAMZITE nasledovat INSTRUCTION [ret], inak CLR hodi EXCEPTION. Ak ma METHOD RETURN VALUE, tak RETURN VALUE TAIL CALLED METHOD bude dosadena za RETURN VALUE CURRENT METHOD.
			ret

		DEFAULT:
			ldstr							"DEFAULT"
			stloc							ReturnValue

		EXIT:
			ldloc							ReturnValue

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static string JumpedMethod(int32 Identifier, string Name, int32 Age) cil managed
		{
			ldstr							"JumpedMethod() - IDENTIFIER [{0}], NAME [{1}], AGE [{2}] !"
			ldarg							Identifier
			box								[mscorlib]System.Int32
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! RETURN VALUE JumpedMethod() sa stane RETURN VALUE JumpTest(), ktora ju zavolala cez INSTRUCTION [jmp].
			ldstr							"JUMPED METHOD"

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static string JumpTest(int32 Identifier, string Name, int32 Age) cil managed
		{
            .locals							init (string ReturnValue)

			ldstr							"JumpTest() - IDENTIFIER [{0}], NAME [{1}], AGE [{2}] !"
			ldarg							Identifier
			box								[mscorlib]System.Int32
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			ldarg							Identifier
			bne.un							JUMP

			ldstr							"NO JUMP"
			stloc							ReturnValue
			br								EXIT

		JUMP:
			ldc.i4							2
			ldarg							Identifier
			bne.un							DEFAULT

			ldstr							"BEFORE JUMP !!!"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Modifikujem hodnoty PARAMETERS, aby bolo vidiet, ze ich JUMP prenesie do JUMPED METHOD.
			ldstr							"Jenny Thompson"
			starg							Name
			ldc.i4							13
			starg							Age

			// !!! Vykona sa SKOK na METHOD, ktora MUSI MAT ROVNAKU SIGNATURE.
			jmp								string ILInstructions.CILInstructions::JumpedMethod(int32,string,int32)

			// !!!!! Tento CODE sa NIKDY NEVYKONA, pretoze INSTRUCTION [jmp] UKONCUJE CURRENT METHOD a RETURN VALUE JUMPED METHOD zoberie ako RETURN VALUE CURRENT METHOD.
			ldstr							"AFTER JUMP !!!"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"JUMP"
			stloc							ReturnValue
			br								EXIT

		DEFAULT:
			ldstr							"DEFAULT"
			stloc							ReturnValue

		EXIT:
			ldloc							ReturnValue

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static string SimplePrint(string Value) cil managed
		{
			ldarg							Value
			// Duplikuje sa VALUE, ktora bude sluzit ako RETURN VALUE.
			dup
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void SwitchInstruction(unsigned int32 Value) cil managed
		{
			ldstr							"SwitchInstruction() VALUE [{0}] !"
			ldarg							Value
			box								[mscorlib]System.UInt32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! SWITCH VALUE musi byt ulozena na STACKU.
			ldarg							Value

			switch							(CASE_0,CASE_1,CASE_2)

			// !!! DEFAULT CASE.
			ldstr							"DEFAULT CASE !"
			call							void [mscorlib]System.Console::WriteLine(string)

			br								EXIT
		CASE_0:
			ldstr							"CASE 0 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			br								EXIT
		CASE_1:
			ldstr							"CASE 1 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			br								EXIT
		CASE_2:
			ldstr							"CASE 2 !"
			call							void [mscorlib]System.Console::WriteLine(string)

			br								EXIT

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void GenerateException1(int32 Value) cil managed
		{
			.try
			{
				ldarg						Value
				brfalse						LEAVE_EXIT

				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			LEAVE_EXIT:
				ldstr						"NO EXCEPTION THROWN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void GenerateException2(int32 Value) cil managed
		{
			.try
			{
				ldarg						Value
				brfalse						LEAVE_EXIT

				ldstr						"LEAVE 1 !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Kedze INSTRUCTION [leave] urcuje LOGICKY a NIE LEXIKALNY koniec TRY (CATCH) BLOCK, tak sa moze nachadzat aj v TELE TRY (CATCH) BLOCKS.
				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT

			LEAVE_EXIT:
				ldstr						"LEAVE 2 !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void GenerateException3WithFinally(int32 Value) cil managed
		{
			.try
			{
				.try
				{
					ldarg					Value
					brfalse					LEAVE_EXIT

					ldstr					"Some EXCEPTION !"
					newobj					instance void class [mscorlib]System.Exception::.ctor(string)
					throw

				LEAVE_EXIT:
					ldstr					"NO EXCEPTION THROWN !"
					call					void [mscorlib]System.Console::WriteLine(string)

					// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
					leave					LOCAL_EXIT
				}
				catch [mscorlib]System.Exception
				{
					call					void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

					// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
					leave					LOCAL_EXIT
				}

			LOCAL_EXIT:
				leave						EXIT
			}
			finally
			{
				ldstr						"FINALLY BLOCK CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! LEXICAL SCOPE FINALLY BLOCK MUSI VZDY koncit INSTRUCTION [endfinally].
				endfinally
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FaultBlockTest(int32 Value) cil managed
		{
			.try
			{
				ldarg						Value
				ldc.i4						1
				bne.un						CASE_NO_EXCEPTION

				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.ArgumentException::.ctor(string)
				throw

			CASE_NO_EXCEPTION:
				ldstr						"NO EXCEPTION is THROWN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			fault
			{
				ldstr						"FAULT BLOCK was EXECUTED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! FAULT BLOCK musi VZDY LEXIKALNE koncit INSTRUCTION [endfault], ktora je IDENTICKA s INSTRUCTION [endfinally].
				endfault
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void EndFilter(int32 Value) cil managed
		{
			.try
			{
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			filter
			{
				ldarg						Value
				ldc.i4						1
				beq							FILTER_SUCCEEDED_1

				ldstr						"FILTER 1 CALLED but FAILED to PROCESS EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
				ldc.i4						0
				br							EXIT_FILTER_1

			FILTER_SUCCEEDED_1:
				ldstr						"FILTER 1 CALLED and PROCEEDED EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
				ldc.i4						1

			EXIT_FILTER_1:
				// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
				endfilter
			}
			{
				ldstr						"CATCH BLOCK 1 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			filter
			{
				ldarg						Value
				ldc.i4						2
				beq							FILTER_SUCCEEDED_2

				ldstr						"FILTER 2 CALLED but FAILED to PROCESS EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
				ldc.i4						0
				br							EXIT_FILTER_2

			FILTER_SUCCEEDED_2:
				ldstr						"FILTER 2 CALLED and PROCEEDED EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
				ldc.i4						1

			EXIT_FILTER_2:
				// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
				endfilter
			}
			{
				ldstr						"CATCH BLOCK 2 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			filter
			{
				ldstr						"DEFAULT FILTER CALLED and PROCEEDED EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
				ldc.i4						1
				// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
				endfilter
			}
			{
				ldstr						"DEFAULT CATCH BLOCK CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static int32 ReturnValue(int32 Value) cil managed
		{
			ldarg						Value
			brfalse						FALSE

			ldstr						"VALUE is TRUE !"
			call						void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Do EVALUATION STACK sa ulozi RETURN VALUE.
			ldarg						Value
			// !!! METHOD sa UKONCI.
			ret

		FALSE:
			ldstr						"VALUE is FALSE !"
			call						void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Do EVALUATION STACK sa ulozi RETURN VALUE.
			ldarg						Value
			// !!! METHOD sa UKONCI.
			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! V METHOD DEFINITION sa NESMIE pouzit MODIFIER [...]. Ten sa pouziva IBA v METHOD CALL.
        .method public hidebysig static vararg void VariableParameters(string Param1, int32 Param2) cil managed
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
			ldc.i4							0
			// CONDITIONAL JUMP.
			brtrue							TRUE

			ldstr							"VALUE is FALSE !"
			call							void [mscorlib]System.Console::WriteLine(string)
			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		TRUE:
			ldstr							"VALUE is TRUE !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
			ldc.i4							100
			// CONDITIONAL JUMP.
			brtrue							TRUE

			ldstr							"VALUE is FALSE !"
			call							void [mscorlib]System.Console::WriteLine(string)
			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		TRUE:
			ldstr							"VALUE is TRUE !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
            .locals							init (int32 Value1)
            .locals							init (int32 Value2)

			ldc.i4							90
			stloc							Value1
			ldc.i4							100
			stloc							Value2

			ldloc							Value1			
			ldloc							Value2
			blt								LOWER

			ldstr							"COMPARISION [{0}]>=[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		LOWER:
			ldstr							"COMPARISION [{0}]<[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
            .locals							init (int32 Value1)
            .locals							init (int32 Value2)

			ldc.i4							110
			stloc							Value1
			ldc.i4							100
			stloc							Value2

			ldloc							Value1			
			ldloc							Value2
			blt								LOWER

			ldstr							"COMPARISION [{0}]>=[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		LOWER:
			ldstr							"COMPARISION [{0}]<[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
            .locals							init (float32 Value1)
            .locals							init (float32 Value2)

			ldc.r4							100.456
			stloc							Value1
			ldc.r4							100.200
			stloc							Value2

			ldloc							Value1			
			ldloc							Value2
			blt								LOWER

			ldstr							"COMPARISION [{0}]>=[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		LOWER:
			ldstr							"COMPARISION [{0}]<[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
            .locals							init (float32 Value1)
            .locals							init (float32 Value2)

			ldc.r4							100.256
			stloc							Value1
			ldc.r4							100.400
			stloc							Value2

			ldloc							Value1			
			ldloc							Value2
			blt								LOWER

			ldstr							"COMPARISION [{0}]>=[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// UNCONDITIONAL JUMP.
			br								EXIT

			// LABEL.
		LOWER:
			ldstr							"COMPARISION [{0}]<[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// LABEL.
		EXIT:
			ret			
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test7() cil managed
		{
			ldc.i4							0
			call							void ILInstructions.CILInstructions::SwitchInstruction(unsigned int32)

			ldc.i4							1
			call							void ILInstructions.CILInstructions::SwitchInstruction(unsigned int32)

			ldc.i4							2
			call							void ILInstructions.CILInstructions::SwitchInstruction(unsigned int32)

			ldc.i4							3
			call							void ILInstructions.CILInstructions::SwitchInstruction(unsigned int32)

			ldc.i4							4
			call							void ILInstructions.CILInstructions::SwitchInstruction(unsigned int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
			ldstr							"BEFORE BREAK !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Vlozi BREAKPOINT do CODE.
			break

			ldstr							"AFTER BREAK !"
			call							void [mscorlib]System.Console::WriteLine(string)
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
			ldc.i4							0
			call							void ILInstructions.CILInstructions::GenerateException1(int32)

			ldc.i4							1
			call							void ILInstructions.CILInstructions::GenerateException1(int32)

			ldc.i4							0
			call							void ILInstructions.CILInstructions::GenerateException2(int32)

			ldc.i4							1
			call							void ILInstructions.CILInstructions::GenerateException2(int32)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test10() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							1
			call							void ILInstructions.CILInstructions::EndFilter(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							2
			call							void ILInstructions.CILInstructions::EndFilter(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							3
			call							void ILInstructions.CILInstructions::EndFilter(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							4
			call							void ILInstructions.CILInstructions::EndFilter(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test11() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							0
			call							void ILInstructions.CILInstructions::GenerateException3WithFinally(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							1
			call							void ILInstructions.CILInstructions::GenerateException3WithFinally(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test12() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						0
				call						void ILInstructions.CILInstructions::FaultBlockTest(int32)

				leave						CONTINUE
			}
			catch [mscorlib]System.Exception
			{
				ldstr						"Exception was CAUGHT !"
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						CONTINUE
			}

		CONTINUE:
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						1
				call						void ILInstructions.CILInstructions::FaultBlockTest(int32)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				ldstr						"Exception was CAUGHT !"
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				leave						EXIT
			}

		EXIT:
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test13() cil managed
		{
            .locals							init (int32 ReturnValue)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							0
			call							int32 ILInstructions.CILInstructions::ReturnValue(int32)
			// !!! RETURN VALUE sa ulozi do TEMPORARY VARIABLE.
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							100
			call							int32 ILInstructions.CILInstructions::ReturnValue(int32)
			// !!! RETURN VALUE sa ulozi do TEMPORARY VARIABLE.
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test14() cil managed
		{
            .locals							init (int32 ReturnValue)

			ldstr							"My name is Timmy Anderson !"
			// Skopiruje sa vrchol STACKU.
			dup

			// Operacia NEROBI NIC.
			nop
			nop
			nop

			call							string ILInstructions.CILInstructions::SimplePrint(string)
			// Vymaze sa RETURN VALUE.
			pop
			
			call							string ILInstructions.CILInstructions::SimplePrint(string)
			// Ulozi sa RETURN VALUE.
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test15() cil managed
		{
			ldstr							"INT32 VALUE [{0}] !"
			ldc.i4							123
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"INT64 VALUE [{0}] !"
			ldc.i8							1234567890123456
			box								[mscorlib]System.Int64
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"SINGLE VALUE [{0}] !"
			ldc.r4							123.456
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DOUBLE VALUE [{0}] !"
			ldc.r8							123.456789123456
			box								[mscorlib]System.Double
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"HEXA VALUE [{0}] !"
			ldc.i4							0x123
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DOUBLE VALUE as INTEGER [{0}] !"
			ldc.r8							(01 02 03 04 05 06 07 08)
			box								[mscorlib]System.Double
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DOUBLE VALUE as NAN [{0}] !"
			ldc.r8							(FF FF FF FF FF FF FF FF)
			box								[mscorlib]System.Double
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test16() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, int32 Temp, int32& PointerToValue1, int32& PointerToValue2)

			ldc.i4							123
			stloc							Value1

			ldstr							"VALUE 1 [{0}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// Ziska POINTER na Value1.
			ldloca							Value1
			stloc							PointerToValue1

			// Ziska POINTER na Value1.
			ldloca							Value2
			stloc							PointerToValue2

			ldloc							PointerToValue1
			// Nacita VALUE z PointerToValue1.
			ldind.i4
			stloc							Temp

			ldstr							"TEMP [{0}] !"
			ldloc							Temp
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// POINTER na ktory sa ma VALUE ulozit.
			ldloc							PointerToValue2
			// VALUE, ktora sa ma ulozit.
			ldloc							Temp
			// Ulozi VALUE z PointerToValue2.
			stind.i4

			ldloc							Value2

			ldstr							"VALUE 2 [{0}] !"
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test17() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, int32 Result)

			ldc.i4							12
			stloc							Value1
			ldc.i4							4
			stloc							Value2

			ldloc							Value1
			ldloc							Value2
			add
			stloc							Result

			ldstr							"[{0}]+[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			sub
			stloc							Result

			ldstr							"[{0}]-[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			mul
			stloc							Result

			ldstr							"[{0}]*[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			div
			stloc							Result

			ldstr							"[{0}]/[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test18() cil managed
		{
            .locals							init (float32 Value1, float32 Value2, float32 Result)

			ldc.r4							12.4
			stloc							Value1
			ldc.r4							4.3
			stloc							Value2

			ldloc							Value1
			ldloc							Value2
			add
			stloc							Result

			ldstr							"[{0}]+[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			ldloc							Result
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			sub
			stloc							Result

			ldstr							"[{0}]-[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			ldloc							Result
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			mul
			stloc							Result

			ldstr							"[{0}]*[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			ldloc							Result
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			div
			stloc							Result

			ldstr							"[{0}]/[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Single
			ldloc							Value2
			box								[mscorlib]System.Single
			ldloc							Result
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test19() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, int32 Result)

			ldc.i4							0x73
			stloc							Value1
			ldc.i4							0x29
			stloc							Value2

			ldloc							Value1
			ldloc							Value2
			and
			stloc							Result

			ldstr							"[{0}] AND [{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			or
			stloc							Result

			ldstr							"[{0}] OR [{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			xor
			stloc							Result

			ldstr							"[{0}] XOR [{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			not
			stloc							Result

			ldstr							"NOT [{0}]=[{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test20() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, int32 Result)

			ldc.i4							0x0C
			stloc							Value1
			ldc.i4							0x02
			stloc							Value2

			ldloc							Value1
			ldloc							Value2
			shl
			stloc							Result

			ldstr							"[{0}] SHL [{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			shr
			stloc							Result

			ldstr							"[{0}] SHR [{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test21() cil managed
		{
            .locals							init (float32 Value, int32 Result)

			ldc.r4							123.456
			stloc							Value

			ldloc							Value
			conv.i4
			stloc							Result

			ldstr							"ORIGINAL VALUE [{0}], CONVERTED VALUE [{1}] !"
			ldloc							Value
			box								[mscorlib]System.Single
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test22() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, float64 Value3, float64 Value4, int32 Result, float64 FloatResult)

			ldc.i4							7
			stloc							Value1
			ldc.i4							10
			stloc							Value2
			// NAN hodnota.
			ldc.r8							123.456
			stloc							Value3
			// NAN hodnota.
			ldc.r8							(FF FF FF FF FF FF FF FF)
			stloc							Value4

			ldloc							Value1
			ldloc							Value2
			cgt
			stloc							Result

			ldstr							"[{0}]>[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value1
			ldloc							Value2
			clt
			stloc							Result

			ldstr							"[{0}]<[{1}]=[{2}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			ldloc							Result
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Value3
			ckfinite
			stloc							FloatResult

			ldstr							"CKFINITE [{0}]=[{1}] !"
			ldloc							Value3
			box								[mscorlib]System.Double
			ldloc							FloatResult
			box								[mscorlib]System.Double
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldloc						Value4
				// !!! Hodi EXCEPTION OverflowException.
				ckfinite
				stloc						FloatResult

				ldstr						"CKFINITE [{0}]=[{1}] !"
				ldloc						Value4
				box							[mscorlib]System.Double
				ldloc						FloatResult
				box							[mscorlib]System.Double
				call						string [mscorlib]System.String::Format(string,object,object)
				call						void [mscorlib]System.Console::WriteLine(string)
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test23() cil managed
		{
            .locals							init (int32 Value1, int32 Value2, int32& PointerToValue1, int32& PointerToValue2)

			ldc.i4							1234567890
			stloc							Value1
			ldc.i4							0
			stloc							Value2

			ldloca							Value1
			stloc							PointerToValue1

			ldloca							Value2
			stloc							PointerToValue2

			// DESTINATION POINTER.
			ldloc							PointerToValue2
			// SOURCE POINTER.
			ldloc							PointerToValue1
			// POCET BYTES, ktore maju byt skopirovane.
			ldc.i4							4
			// !!! Skopiruje obsah BYTES Value1 do MEMORY obsadenej Value2.
			cpblk

			ldstr							"VALUE1 [{0}], VALUE2 [{1}] !"
			ldloc							Value1
			box								[mscorlib]System.Int32
			ldloc							Value2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test24() cil managed
		{
            .locals							init (int32 Value, int32& PointerToValue)

			ldc.i4							0
			stloc							Value

			ldloca							Value
			stloc							PointerToValue

			ldstr							"ORIGINAL VALUE [{0}]"
			ldloc							Value
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// DESTINATION POINTER.
			ldloc							PointerToValue
			// INICIALIZANCA VALUE.
			ldc.i4							2
			// POCET BYTES, ktore maju byt inicializovane.
			ldc.i4							4
			// !!! Inicializuje obsah BYTES Value, ktora bude obsahovat 0x02020202=33686018.
			initblk

			ldstr							"INITIALIZED VALUE [{0}] !"
			ldloc							Value
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test25() cil managed
		{
            .locals							init (class ILInstructions.CClass Object)

			newobj							instance void ILInstructions.CClass::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"XXX"
			ldstr							"YYY"
			call							instance void ILInstructions.CClass::TestMethod1(string,string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test26() cil managed
		{
            .locals							init (class ILInstructions.CClass Object)

			newobj							instance void ILInstructions.CClass::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderon"
			call							instance void ILInstructions.CClass::TestMethod2(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test27() cil managed
		{
            .locals							init (string Value, string& PointerToValue)

			ldstr							"Timmy Anderson"
			stloc							Value

			ldstr							"LOCAL VARIABLE BEFORE CHANGE [{0}] !"
			ldloc							Value
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska POINTER na LOCAL VARIABLE.
			ldloca							Value
			stloc							PointerToValue

			ldloc							PointerToValue
			ldstr							"Jenny Thompson"
			// !!! Ulozi hodnotu do ARGUMENT.
			stind.i4

			ldstr							"LOCAL VARIABLE AFTER CHANGE [{0}] !"
			ldloc							Value
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test28() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Volanie METHOD s VARIABLE PARAMETERS BEZ VARIABLE PARAMETERS.
			ldstr							"Timmy Anderson"
			ldc.i4							12
			// !!! Na METHODS s VARIABLE PARAMETERS MUSI byt pouzity KEYWORD [vararg].
			call							vararg void ILInstructions.CILInstructions::VariableParameters(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Volanie METHOD s VARIABLE PARAMETERS S VARIABLE PARAMETERS.
			ldstr							"Timmy Anderson"
			ldc.i4							12
			ldstr							"Jenny Thompson"
			ldc.i4							13
			// !!! Na METHODS s VARIABLE PARAMETERS MUSI byt pouzity KEYWORD [vararg].
			// !!!!! Ak METHOD s VARIABLE PARAMETERS ma definovane aj VARIABLE PARAMETERS, tak tieto MUSIA byt oddelene pomocou specialneho PARAMETERS SENTINEL [...].
			call							vararg void ILInstructions.CILInstructions::VariableParameters(string,int32,...,string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test29() cil managed
		{
            .locals							init (int32& PointerToRawMemory)
			
			ldc.i4							4
			// !!! Alokuje 4 BYTES na STACK.
			localloc
			// !!! POINTER na MEMORY BLOCK je ulozeny do LOCAL VARIABLE.
			stloc							PointerToRawMemory

			ldloc							PointerToRawMemory
			ldc.i4							1234567890
			stind.i4

			ldstr							"VALUE [{0}] !"
			ldloc							PointerToRawMemory
			ldind.i4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test30() cil managed
		{
            .locals							init (class ILInstructions.CClass Object)

			newobj							instance void ILInstructions.CClass::.ctor()
			stloc							Object

			ldloc							Object
			call							instance void ILInstructions.CClass::TestMethod3()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test31() cil managed
		{
            .locals							init (class ILInstructions.CDerivedClass Derived, class ILInstructions.CBaseClass Base)

			newobj							instance void ILInstructions.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa NON-VIRTUAL METHOD NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			call							instance void ILInstructions.CDerivedClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			call							instance void ILInstructions.CDerivedClass::NonVirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			call							instance void ILInstructions.CBaseClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			call							instance void ILInstructions.CBaseClass::NonVirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa NON-VIRTUAL METHOD VIRTUALNE. Kedze METHODS su NON-VIRTUAL, tak sa volaju NON-VIRTUAL.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			callvirt						instance void ILInstructions.CDerivedClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::NonVirtualMethod().
			callvirt						instance void ILInstructions.CDerivedClass::NonVirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			callvirt						instance void ILInstructions.CBaseClass::NonVirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::NonVirtualMethod().
			callvirt						instance void ILInstructions.CBaseClass::NonVirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test32() cil managed
		{
            .locals							init (class ILInstructions.CDerivedClass Derived, class ILInstructions.CBaseClass Base)

			newobj							instance void ILInstructions.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualMethod().
			call							instance void ILInstructions.CBaseClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualMethod().
			call							instance void ILInstructions.CBaseClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa VIRTUAL METHOD VIRTUALNE. Kedze METHODS su VIRTUAL, tak sa volaju VIRTUAL.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualMethod()
			ldloc							Derived
			// !!!!! Zavola sa METHOD CDerivedClass::VirtualMethod(), pretoze METHOD je VIRTUAL.
			callvirt						instance void ILInstructions.CBaseClass::VirtualMethod()
			ldloc							Base
			// !!!!! Zavola sa METHOD CDerivedClass::VirtualMethod(), pretoze METHOD je VIRTUAL.
			callvirt						instance void ILInstructions.CBaseClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test33() cil managed
		{
            .locals							init (class ILInstructions.CDerivedClass Derived, class ILInstructions.CBaseClass Base)

			newobj							instance void ILInstructions.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Base
			// Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualNewSlotMethod().
			call							instance void ILInstructions.CBaseClass::VirtualNewSlotMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualNewSlotMethod().
			call							instance void ILInstructions.CBaseClass::VirtualNewSlotMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Aj ked METHOD je VIRTUAL volana VIRTUALNE, kedze na METHOD CDerivedClass::VirtualNewSlotMethod() bol aplikovany FLAG [newslot], METHOD CDerivedClass::VirtualNewSlotMethod() ma VLASTNU ENTRY vo VIRTUAL METHOD TABLE a NIE JE NIJAKO ZVIAZANA s METHOD CBaseClass::VirtualNewSlotMethod().
			ldloc							Derived
			// !!! Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Base
			// !!! Zavola sa METHOD CDerivedClass::VirtualNewSlotMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualNewSlotMethod()
			ldloc							Derived
			// !!!!! Zavola sa METHOD CBaseClass::VirtualNewSlotMethod(), pretoze METHOD aj ked je VIRTUAL, tak METHOD CDerivedClass::VirtualNewSlotMethod() ma aplikovany FLAG [newslot] a NEVYKONAVA METHOD OVERRIADING METHOD CBaseClass::VirtualNewSlotMethod().
			callvirt						instance void ILInstructions.CBaseClass::VirtualNewSlotMethod()
			ldloc							Base
			// !!!!! Zavola sa METHOD CBaseClass::VirtualNewSlotMethod(), pretoze METHOD aj ked je VIRTUAL, tak METHOD CDerivedClass::VirtualNewSlotMethod() ma aplikovany FLAG [newslot] a NEVYKONAVA METHOD OVERRIADING METHOD CBaseClass::VirtualNewSlotMethod().
			callvirt						instance void ILInstructions.CBaseClass::VirtualNewSlotMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test34() cil managed
		{
            .locals							init (class ILInstructions.CDerivedClass Derived, class ILInstructions.CBaseClass Base)

			newobj							instance void ILInstructions.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBaseClass
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Zavola sa VIRTUAL METHOD NEVIRTUALNE.
			// !!!!! Aj ked METHODS su VIRUAL, tak sa budu volat NEVIRTUALNE.
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualFinalMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			call							instance void ILInstructions.CDerivedClass::VirtualFinalMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Zavola sa VIRTUAL METHOD VIRTUALNE. Kedze vsak CDerivedClass NESMIE mat definovanu FINAL METHOD VirtualFinalMethod(), tak sa vola METHOD CBaseClass::VirtualFinalMethod().
			ldloc							Derived
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualFinalMethod()
			ldloc							Base
			// Zavola sa METHOD CBaseClass::VirtualFinalMethod(), pretoze CDerivedClass NESMIE mat definovanu METHOD VirtualFinalMethod().
			callvirt						instance void ILInstructions.CDerivedClass::VirtualFinalMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test35() cil managed
		{
            .locals							init (valuetype ILInstructions.CValueTypeVirtualMethodsClass ValueType, valuetype ILInstructions.CValueTypeVirtualMethodsClass& ValueTypePointer)

			ldloca							ValueType
			stloc							ValueTypePointer

			ldloc							ValueTypePointer
			call							instance void ILInstructions.CValueTypeVirtualMethodsClass::.ctor()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							ValueTypePointer
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void ILInstructions.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueTypePointer
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void ILInstructions.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldloc							ValueTypePointer
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako VIRTUAL METHOD.
			callvirt						instance void ILInstructions.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueTypePointer
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			callvirt						instance void ILInstructions.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							ValueType
			box								valuetype ILInstructions.CValueTypeVirtualMethodsClass
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void ILInstructions.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueType
			box								valuetype ILInstructions.CValueTypeVirtualMethodsClass
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			call							instance void ILInstructions.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldloc							ValueType
			box								valuetype ILInstructions.CValueTypeVirtualMethodsClass
			// !!! NON-VIRTUAL METHOD CValueTypeVirtualMethodsClass::NonVirtualMethod() je volana ako VIRTUAL METHOD.
			callvirt						instance void ILInstructions.CValueTypeVirtualMethodsClass::NonVirtualMethod()

			ldloc							ValueType
			box								valuetype ILInstructions.CValueTypeVirtualMethodsClass
			// !!! VIRTUAL METHOD CValueTypeVirtualMethodsClass::VirtualMethod() je volana ako NON-VIRTUAL METHOD.
			callvirt						instance void ILInstructions.CValueTypeVirtualMethodsClass::VirtualMethod()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test36() cil managed
		{
            .locals							init (class ILInstructions.CDerived Derived, class ILInstructions.CBase Base)

			newobj							instance void ILInstructions.CDerived::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBase
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod1()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod2()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod3()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod4()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod5()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod6()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test37() cil managed
		{
            .locals							init (class ILInstructions.CSuperDerived Derived, class ILInstructions.CBase Base)

			newobj							instance void ILInstructions.CSuperDerived::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBase
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod1()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod2()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod3()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod4()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod5()

			ldloc							Base
			callvirt						instance void ILInstructions.CDerived::VirtualMethod6()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test38() cil managed
		{
            .locals							init (class ILInstructions.CIndirectMethodCallsDerived Derived, class ILInstructions.CIndirectMethodCallsBase Base)
			.locals							init (method string * (string,int32) CallbackFunctionPointerToVirtualNonStaticMethod)
			.locals							init (method string * (string,int32) CallbackFunctionPointerToNonStaticMethod)
			.locals							init (method string * (string,int32) CallbackFunctionPointerToStaticMethod)
            .locals							init (string ReturnValue)

			newobj							instance void ILInstructions.CIndirectMethodCallsDerived::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CIndirectMethodCallsBase
			stloc							Base

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"DIRECT CALLS !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			ldstr							"Timmy Anderson"
			ldc.i4							12
			callvirt						instance string ILInstructions.CIndirectMethodCallsBase::VirtualMethod(string Name, int32 Age)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			ldstr							"Timmy Anderson"
			ldc.i4							12
			callvirt						instance string ILInstructions.CIndirectMethodCallsBase::NonStaticMethod(string Name, int32 Age)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"VIRTUAL INDIRECT CALL of NON-STATIC METHOD !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			// !!! Ziska POINTER na NON-STATIC METHOD, ktora ma byt volana VIRTUALNE.
			ldvirtftn						instance string ILInstructions.CIndirectMethodCallsBase::VirtualMethod(string,int32)
			stloc							CallbackFunctionPointerToVirtualNonStaticMethod

			// !!!!! Kedze sa vola NON-STATIC METHOD, je NUTNE vlozit THIS POINTER.
			ldloc							Base
			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			// !!! Na VRCHOLE STACK, MUSI byt POINTER na METHOD.
			ldloc							CallbackFunctionPointerToVirtualNonStaticMethod
			// !!!!! NON-STATIC VITRTUAL METHOD sa zavola INDIRECTLY.
			// !!!!! Kedze na ziskanie POINTER sa pouzila INSTRUCTION [ldvirtftn], volanie bude VIRTUALNE.
			calli							instance string(string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"NON-VIRTUAL INDIRECT CALL of NON-STATIC METHOD !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska POINTER na NON-STATIC METHOD.
			ldftn							instance string ILInstructions.CIndirectMethodCallsBase::VirtualMethod(string,int32)
			stloc							CallbackFunctionPointerToNonStaticMethod

			// !!!!! Kedze sa vola NON-STATIC METHOD, je NUTNE vlozit THIS POINTER.
			ldloc							Base
			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			// !!! Na VRCHOLE STACK, MUSI byt POINTER na METHOD.
			ldloc							CallbackFunctionPointerToNonStaticMethod
			// !!!!! NON-STATIC VITRTUAL METHOD sa zavola INDIRECTLY a NEVIRTUALNE, pretoze sa NEPOUZILA INSTRUCTION [ldvirtftn].
			calli							instance string(string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldstr							"INDIRECT CALL of STATIC METHOD !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska POINTER na STATIC METHOD.
			ldftn							string ILInstructions.CIndirectMethodCallsBase::StaticMethod(string,int32)
			stloc							CallbackFunctionPointerToStaticMethod

			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			// !!! Na VRCHOLE STACK, MUSI byt POINTER na METHOD.
			ldloc							CallbackFunctionPointerToStaticMethod
			// !!!!! STATIC METHOD sa zavola INDIRECTLY.
			calli							string(string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test39() cil managed
		{
            .locals							init (string ReturnValue)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							0
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::JumpTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::JumpTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::JumpTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test40() cil managed
		{
            .locals							init (string ReturnValue)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							0
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::TailCallTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::TailCallTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							string ILInstructions.CILInstructions::TailCallTest(int32,string,int32)
			stloc							ReturnValue

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							ReturnValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test41() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Timmy Anderson"
			call							void ILInstructions.CILInstructions::ConstrainedCall<string>(!!0)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							12
			call							void ILInstructions.CILInstructions::ConstrainedCall<int32>(!!0)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Timmy Anderson"
			call							void ILInstructions.CILInstructions::UnconstrainedCallForReferenceTypes<string>(!!0)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			/*
			// !!!!! HODI EXCEPTION.
			ldc.i4							12
			call							void ILInstructions.CILInstructions::UnconstrainedCallForReferenceTypes<int32>(!!0)
			*/

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			/*
			// !!!!! HODI EXCEPTION.
			ldstr							"Timmy Anderson"
			call							void ILInstructions.CILInstructions::UnconstrainedCallForValueTypes1<string>(!!0)
			*/

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			/*
			// !!!!! Aj toto HODI EXCEPTION, pretoze Int32 NEIMPLEMENTUJE ToString().
			ldc.i4							12
			call							void ILInstructions.CILInstructions::UnconstrainedCallForValueTypes1<int32>(!!0)
			*/

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! ZBEHNE KOREKTNE.
			ldstr							"Timmy Anderson"
			call							void ILInstructions.CILInstructions::UnconstrainedCallForValueTypes2<string>(!!0)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! ZBEHNE KOREKTNE.
			ldc.i4							12
			call							void ILInstructions.CILInstructions::UnconstrainedCallForValueTypes2<int32>(!!0)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test42() cil managed
		{
			.locals init					(int32[] Vector, int32 Index, int32 VectorLength)

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

			ldloc							Vector
			// Nacita velkost ARRAY.
			ldlen
			stloc							VectorLength

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_2:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldloc							VectorLength
			bge								END_FOR_2

			// 1. PARAMETER METHOD PrintVectorItem().
			ldloc							Index

			// 2. PARAMETER METHOD PrintVectorItem().
			// !!! Nacita hodnotu Vector[Index].
			ldloc							Vector
			ldloc							Index
			ldelem.i4

			call							void ILInstructions.CILInstructions::PrintVectorItem(int32,int32)

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
        .method public hidebysig static void Test43() cil managed
		{
			.locals init					(string[] Vector, int32 Index, int32 Temp, int32 VectorLength)

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
			ldc.i4							20
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

			ldloc							Vector
			// Nacita velkost ARRAY.
			ldlen
			stloc							VectorLength

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_2:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldloc							VectorLength
			bge								END_FOR_2

			// 1. PARAMETER METHOD PrintVectorItem().
			ldloc							Index

			// 2. PARAMETER METHOD PrintVectorItem().
			// !!! Nacita hodnotu Vector[Index].
			ldloc							Vector
			ldloc							Index
			ldelem.ref

			call							void ILInstructions.CILInstructions::PrintVectorItem(int32,string)

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
        .method public hidebysig static void Test44() cil managed
		{
			.locals init					(int32[] Vector, int32 Index, int32& PointerToValue, int32 VectorLength)

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
			// !!! Ziska POINTER na ARRAY ITEM.
			ldelema							[mscorlib]System.Int32
			// POINTER na ARRAY ITEM ulozi do LOCAL VARIABLE.
			stloc							PointerToValue

			ldloc							PointerToValue
			// Ulozi hodnotu (Index+10), ktora ma byt ulozena do Vector[Index].
			ldloc							Index
			ldc.i4							30
			add
			// !!! Ulozi cez POINTER hodnotu do ARRAY[INDEX].
			stind.i4

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index

			br								BEGIN_FOR_1

		END_FOR_1:

			ldloc							Vector
			// Nacita velkost ARRAY.
			ldlen
			stloc							VectorLength

			ldc.i4							0
			stloc							Index

		BEGIN_FOR_2:
			// !!! Ukonci cyklus, ak Index>=3.
			ldloc							Index
			ldloc							VectorLength
			bge								END_FOR_2

			// 1. PARAMETER METHOD PrintVectorItem().
			ldloc							Index

			// 2. PARAMETER METHOD PrintVectorItem().
			// !!! Nacita hodnotu Vector[Index].
			ldloc							Vector
			ldloc							Index
			ldelem.i4

			call							void ILInstructions.CILInstructions::PrintVectorItem(int32,int32)

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
        .method public hidebysig static void Test45() cil managed
		{
            .locals init					(valuetype ILInstructions.CComplexValueType Value)
            .locals init					(valuetype ILInstructions.CComplexValueType CopiedValue1)
            .locals init					(valuetype ILInstructions.CComplexValueType CopiedValue2)
            .locals init					(valuetype ILInstructions.CComplexValueType CopiedValue3)
            .locals init					(valuetype ILInstructions.CComplexValueType& PointerToValue)
            .locals init					(valuetype ILInstructions.CComplexValueType& PointerToCopiedValue1)
            .locals init					(valuetype ILInstructions.CComplexValueType& PointerToCopiedValue2)
            .locals init					(valuetype ILInstructions.CComplexValueType& PointerToCopiedValue3)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// Nacita sa POINTER na VALUE TYPE.
			ldloca							Value
			stloc							PointerToValue

			// Nacita sa POINTER na VALUE TYPE.
			ldloca							CopiedValue1
			stloc							PointerToCopiedValue1

			// Nacita sa POINTER na VALUE TYPE.
			ldloca							CopiedValue2
			stloc							PointerToCopiedValue2

			// Nacita sa POINTER na VALUE TYPE.
			ldloca							CopiedValue3
			stloc							PointerToCopiedValue3

			// !!! Pri volani CONSTRUCTORS VALUE TYPES je NUTNE ako 1. PARAMETER dat POINTER na VALUE TYPE.
			ldloc							PointerToValue
			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			call							instance void valuetype ILInstructions.CComplexValueType::.ctor(string,int32)

			// !!! Pri volani METHODS VALUE TYPES je NUTNE ako 1. PARAMETER dat POINTER na VALUE TYPE.
			ldloc							PointerToValue
			ldstr							"Value"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// VALUE TYPE CopiedValue1 je PRAZDNY.
			ldloc							PointerToCopiedValue1
			ldstr							"CopiedValue1"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// VALUE TYPE CopiedValue2 je PRAZDNY.
			ldloc							PointerToCopiedValue2
			ldstr							"CopiedValue2"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// VALUE TYPE CopiedValue3 je PRAZDNY.
			ldloc							PointerToCopiedValue3
			ldstr							"CopiedValue3"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Nacita VALUE TYPE na STACK.
			ldloc							PointerToValue
			// !!! INSTRUCTION vyzaduje mat na STACKU POINTER na VALUE TYPE. Na STACK uklada hodnotu VALUE TYPE.
			ldobj							ILInstructions.CComplexValueType
			stloc							CopiedValue1

			// Teraz uz CopiedValue1 bude obsahovat nastavenu hodnotu.
			ldloc							PointerToCopiedValue1
			ldstr							"CopiedValue1"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// !!! POINTER na VALUE TYPE do ktoreho sa ulozi hodnota VALUE TYPE.
			ldloc							PointerToCopiedValue2
			// !!! Hodnota VALUE TYPE, ktora sa ma ulozit do dereferencovaneho POINTER na VALUE TYPE (PointerToCopiedValue2).
			ldloc							Value
			// !!! INTRUCTION ulozi hodnotu VALUE TYPE do dereferencovaneho PointerToCopiedValue2. Na STACKU musi mat INSTRUCTION ulozeny POINTER na VALUE TYPE do ktoreho sa bude hodnota VALUE TYPE ukladat a samotnyu hodnotu VALUE TYPE.
			stobj							ILInstructions.CComplexValueType

			// Teraz uz CopiedValue2 bude obsahovat nastavenu hodnotu.
			ldloc							PointerToCopiedValue2
			ldstr							"CopiedValue2"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// !!! Nacita POINTER na VALUE TYPE do ktoreho sa ma hodnota VALUE TYPE ulozit.
			ldloc							PointerToCopiedValue3
			// !!! Nacita POINTER na VALUE TYPE z ktoreho sa ma hodnota VALUE TYPE nacitat.
			ldloc							PointerToValue
			// !!! Skopiruje hodnotu VALUE TYPE urcenu POINTER na VALUE TYPE do ineho VALUE TYPE urceneho POINTER na VALUE TYPE.
			cpobj							ILInstructions.CComplexValueType

			// Teraz uz CopiedValue3 bude obsahovat nastavenu hodnotu.
			ldloc							PointerToCopiedValue3
			ldstr							"CopiedValue3"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			// Vymaze obsah VALUE TYPE.
			ldloc							PointerToValue
			// Ako PARAMETER na STACKU potrebuje mat ulozeny POINTER na VALUE TYPE.
			initobj							ILInstructions.CComplexValueType

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							PointerToValue
			ldstr							"Value"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			ldloc							PointerToCopiedValue1
			ldstr							"CopiedValue1"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			ldloc							PointerToCopiedValue2
			ldstr							"CopiedValue2"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			ldloc							PointerToCopiedValue3
			ldstr							"CopiedValue3"
			call							instance void ILInstructions.CComplexValueType::InstanceMethod(string Prefix)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test46() cil managed
		{
			ldstr							"STRING [{0}] !"
			ldstr							"Timmy Anderson"
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"STRING [{0}] !"
			// !!! INSTRUCTION NEROBI AUTOMATICKY konverziu na UNICODE a BYTES MUSIA zodpovedat UNICODE.
			ldstr							bytearray(41 00 42 00 43 00)
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test47() cil managed
		{
            .locals							init (class ILInstructions.CDerivedClass Derived, class ILInstructions.CBaseClass Base)
			.locals							init (object ConversionResult)

			newobj							instance void ILInstructions.CDerivedClass::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class ILInstructions.CBaseClass
			stloc							Base

			ldloc							Derived
			// !!! Zistuje ci CDerivedClass je CBaseClass.
			isinst							ILInstructions.CBaseClass
			// Na STACK sa ulozi konvertovany TYPE, alebo NULL, ak sa konverzia neda vykonat.
			stloc							ConversionResult

			ldstr							"DERIVED is BASE [{0}] !"
			ldloc							ConversionResult
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			// !!! Zistuje ci CBaseClass je CDerivedClass.
			isinst							ILInstructions.CDerivedClass
			// Na STACK sa ulozi konvertovany TYPE, alebo NULL, ak sa konverzia neda vykonat.
			stloc							ConversionResult

			ldstr							"BASE is DERIVED [{0}] !"
			ldloc							ConversionResult
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Base
			// !!! Zistuje ci CBaseClass je String.
			isinst							string
			// Na STACK sa ulozi konvertovany TYPE, alebo NULL, ak sa konverzia neda vykonat.
			stloc							ConversionResult

			ldstr							"BASE is STRING [{0}] !"
			ldloc							ConversionResult
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							100
			box								[mscorlib]System.Int32
			// !!! Zistuje ci 100 je INT32.
			isinst							[mscorlib]System.Int32
			// Na STACK sa ulozi konvertovany TYPE, alebo NULL, ak sa konverzia neda vykonat.
			stloc							ConversionResult

			ldstr							"100 is INT32 [{0}] !"
			ldloc							ConversionResult
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							100
			box								[mscorlib]System.Int32
			// !!! Zistuje ci 100 je FLOAT32.
			isinst							[mscorlib]System.Single
			// Na STACK sa ulozi konvertovany TYPE, alebo NULL, ak sa konverzia neda vykonat.
			stloc							ConversionResult

			ldstr							"100 is FLOAT32 [{0}] !"
			ldloc							ConversionResult
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test48() cil managed
		{
			.locals							init (int32 OriginalValue)
			.locals							init (object BoxedValue)
			.locals							init (int32& UnboxedValue)
			.locals							init (int32 UnboxedValue1)
			.locals							init (int32 UnboxedValue2)

			ldc.i4							100
			stloc							OriginalValue

			ldloc							OriginalValue
			box								[mscorlib]System.Int32
			stloc							BoxedValue

			ldstr							"OriginalValue [{0}] !"
			ldloc							OriginalValue
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"BoxedValue [{0}] !"
			ldloc							BoxedValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							BoxedValue
			unbox							[mscorlib]System.Int32
			// !!! UNBOX vracia MANAGED POINTER na UNBOXED VALUE TYPE.
			stloc							UnboxedValue

			ldloc							UnboxedValue
			ldobj							[mscorlib]System.Int32
			stloc							UnboxedValue1

			ldstr							"UnboxedValue1 [{0}] !"
			ldloc							UnboxedValue1
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							BoxedValue
			unbox.any						[mscorlib]System.Int32
			// !!! UNBOX.ANY vracia instanciu UNBOXED VALUE TYPE.
			stloc							UnboxedValue2

			ldstr							"UnboxedValue2 [{0}] !"
			ldloc							UnboxedValue2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test49() cil managed
		{
			.locals							init (string OriginalValue)
			.locals							init (string& PointerOriginalValue)
			.locals							init (typedref TypedReference)
			.locals							init (valuetype [mscorlib]System.RuntimeTypeHandle TypeHandle)
			.locals							init (native int NewValue)

			ldc.i4							100
			stloc							OriginalValue

			ldloca							OriginalValue
			stloc							PointerOriginalValue

			ldloc							PointerOriginalValue
			// !!! Vytvori TYPED REFERENCE.
			mkrefany						string
			stloc							TypedReference

			ldloc							TypedReference
			// Na STACK UKLADA TYPE HANDLE.
			refanytype
			stloc							TypeHandle

			ldstr							"TypedReference [{0}] !"
			ldloc							TypedReference
			box								valuetype [mscorlib]System.RuntimeTypeHandle
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							TypedReference
			refanyval						string
			stloc							NewValue

			ldstr							"NewValue [{0}] !"
			ldloc							NewValue
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test50() cil managed
		{
			.locals							init (valuetype [mscorlib]System.RuntimeTypeHandle TypeHandle)
			.locals							init (valuetype [mscorlib]System.RuntimeMethodHandle MethodHandle)
			.locals							init (valuetype [mscorlib]System.RuntimeFieldHandle FieldHandle)

			ldtoken							[mscorlib]System.String
			stloc							TypeHandle

			ldstr							"TypeHandle [{0}] !"
			ldloc							TypeHandle
			box								valuetype [mscorlib]System.RuntimeTypeHandle
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldtoken							method instance void ILInstructions.CBaseClass::NonVirtualMethod()
			stloc							MethodHandle

			ldstr							"MethodHandle [{0}] !"
			ldloc							MethodHandle
			box								valuetype [mscorlib]System.RuntimeMethodHandle
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldtoken							field string ILInstructions.CComplexValueType::MValue1
			stloc							FieldHandle

			ldstr							"FieldHandle [{0}] !"
			ldloc							FieldHandle
			box								valuetype [mscorlib]System.RuntimeFieldHandle
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test51() cil managed
		{
			.try
			{
				call						void ILInstructions.CILInstructions::RethrowException()

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test52() cil managed
		{
			.locals							init (int32 BoolSize)
			.locals							init (int32 ObjectSize)
			.locals							init (int32 StringSize)
			.locals							init (int32 Int32Size)
			.locals							init (int32 Float32Size)
			.locals							init (int32 Float64Size)
			.locals							init (int32 CComplexValueTypeSize)

			sizeof							[mscorlib]System.Boolean
			stloc							BoolSize

			sizeof							[mscorlib]System.Object
			stloc							ObjectSize

			sizeof							string
			stloc							StringSize

			sizeof							int32
			stloc							Int32Size

			sizeof							float32
			stloc							Float32Size

			sizeof							float64
			stloc							Float64Size
		
			sizeof							ILInstructions.CComplexValueType
			stloc							CComplexValueTypeSize

			ldstr							"BoolSize [{0}] !"
			ldloc							BoolSize
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ObjectSize [{0}] !"
			ldloc							ObjectSize
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"StringSize [{0}] !"
			ldloc							StringSize
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Int32Size [{0}] !"
			ldloc							Int32Size
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Float32Size [{0}] !"
			ldloc							Float32Size
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"Float64Size [{0}] !"
			ldloc							Float64Size
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CComplexValueTypeSize [{0}] !"
			ldloc							CComplexValueTypeSize
			box								valuetype [mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void ILInstructions.CILInstructions::Test1()
			//call							void ILInstructions.CILInstructions::Test2()
			//call							void ILInstructions.CILInstructions::Test3()
			//call							void ILInstructions.CILInstructions::Test4()
			//call							void ILInstructions.CILInstructions::Test5()
			//call							void ILInstructions.CILInstructions::Test6()
			//call							void ILInstructions.CILInstructions::Test7()
			//call							void ILInstructions.CILInstructions::Test8()
			//call							void ILInstructions.CILInstructions::Test9()
			//call							void ILInstructions.CILInstructions::Test10()
			//call							void ILInstructions.CILInstructions::Test11()
			call							void ILInstructions.CILInstructions::Test12()
			//call							void ILInstructions.CILInstructions::Test13()
			//call							void ILInstructions.CILInstructions::Test14()
			//call							void ILInstructions.CILInstructions::Test15()
			//call							void ILInstructions.CILInstructions::Test16()
			//call							void ILInstructions.CILInstructions::Test17()
			//call							void ILInstructions.CILInstructions::Test18()
			//call							void ILInstructions.CILInstructions::Test19()
			//call							void ILInstructions.CILInstructions::Test20()
			//call							void ILInstructions.CILInstructions::Test21()
			//call							void ILInstructions.CILInstructions::Test22()
			//call							void ILInstructions.CILInstructions::Test23()
			//call							void ILInstructions.CILInstructions::Test24()
			//call							void ILInstructions.CILInstructions::Test25()
			//call							void ILInstructions.CILInstructions::Test26()
			//call							void ILInstructions.CILInstructions::Test27()
			//call							void ILInstructions.CILInstructions::Test27()
			//call							void ILInstructions.CILInstructions::Test28()
			//call							void ILInstructions.CILInstructions::Test29()
			//call							void ILInstructions.CILInstructions::Test30()
			//call							void ILInstructions.CILInstructions::Test31()
			//call							void ILInstructions.CILInstructions::Test32()
			//call							void ILInstructions.CILInstructions::Test33()
			//call							void ILInstructions.CILInstructions::Test34()
			//call							void ILInstructions.CILInstructions::Test35()
			//call							void ILInstructions.CILInstructions::Test36()
			//call							void ILInstructions.CILInstructions::Test37()
			//call							void ILInstructions.CILInstructions::Test38()
			//call							void ILInstructions.CILInstructions::Test39()
			//call							void ILInstructions.CILInstructions::Test40()
			//call							void ILInstructions.CILInstructions::Test41()
			//call							void ILInstructions.CILInstructions::Test42()
			//call							void ILInstructions.CILInstructions::Test43()
			//call							void ILInstructions.CILInstructions::Test44()
			//call							void ILInstructions.CILInstructions::Test45()
			//call							void ILInstructions.CILInstructions::Test46()
			//call							void ILInstructions.CILInstructions::Test47()
			//call							void ILInstructions.CILInstructions::Test48()
			//call							void ILInstructions.CILInstructions::Test49()
			//call							void ILInstructions.CILInstructions::Test50()
			//call							void ILInstructions.CILInstructions::Test51()
			//call							void ILInstructions.CILInstructions::Test52()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------