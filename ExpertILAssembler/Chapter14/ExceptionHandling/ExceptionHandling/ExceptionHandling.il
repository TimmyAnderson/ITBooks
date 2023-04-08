//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly ExceptionHandling
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! Ak program ma zachytavat INE EXCEPTIONS ako tie, ktore su zdedene z CLASS Exception, MUSI ma nastaveny ATTRIBUTE [RuntimeCompatibilityAttribute(WrapNonExceptionThrows=true)]. Ak ho nema nastaveny, je generovana UNHANDLED EXCEPTION.
	.custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78 63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
.module ExceptionHandling.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace ExceptionHandling
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CExceptionHandling extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void CatchBlocksTestLabelFormChangedOrder(int32 Value) cil managed
		{
			// !!!!! HANDLERS mozu byt definovat aj PRED TRY BLOCK.
			// !!! Preskocia sa HANDLERS a skoci sa na zaciatok TRY BLOCK.
			br								BEGIN_TRY

			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO FILTER BLOCKS.
		BEGIN_FILTER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							3
			beq								FILTER_SUCCEEDED_1

			ldstr							"FILTER 1 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_1

		FILTER_SUCCEEDED_1:
			ldstr							"FILTER 1 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_1:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"FILTER HANDLER BLOCK 1 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_1:
		BEGIN_FILTER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							4
			beq								FILTER_SUCCEEDED_2

			ldstr							"FILTER 2 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_2

		FILTER_SUCCEEDED_2:
			ldstr							"FILTER 2 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_2:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO CATCH BLOCKS.
			ldstr							"FILTER HANDLER BLOCK 2 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_2:
		BEGIN_CATCH_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"ARGUMENT EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_1:
		BEGIN_CATCH_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_2:


		BEGIN_TRY:
			// !!!!! Zaciatok TRY BLOCK.
			ldarg							Value
			ldc.i4							1
			bne.un							CASE_1

			ldstr							"Some ARGUMENT EXCEPTION !"
			newobj							instance void class [mscorlib]System.ArgumentException::.ctor(string)
			throw

		CASE_1:
			ldarg							Value
			ldc.i4							2
			bne.un							CASE_2
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_2:
			ldarg							Value
			ldc.i4							3
			bne.un							CASE_3
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_3:
			ldarg							Value
			ldc.i4							4
			bne.un							CASE_4
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_4:
			ldstr							"NO EXCEPTION is THROWN !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_TRY:

			// !!!!! LABEL FORM EXCEPTION CLAUSE.
			.try							BEGIN_TRY to END_TRY
			filter							BEGIN_FILTER_1
			handler							BEGIN_FILTER_HANDLER_1 to END_FILTER_HANDLER_1
			filter							BEGIN_FILTER_2
			handler							BEGIN_FILTER_HANDLER_2 to END_FILTER_HANDLER_2
			catch							[mscorlib]System.ArgumentException
			handler							BEGIN_CATCH_1 to END_CATCH_1
			catch							[mscorlib]System.Exception
			handler							BEGIN_CATCH_2 to END_CATCH_2

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void CatchBlocksTestMixedForm(int32 Value) cil managed
		{
			// !!! Preskocia sa HANDLERS a skoci sa na TRY BLOCK.
			br								BEGIN_TRY

			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO FILTER BLOCKS.
		BEGIN_FILTER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							3
			beq								FILTER_SUCCEEDED_1

			ldstr							"FILTER 1 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_1

		FILTER_SUCCEEDED_1:
			ldstr							"FILTER 1 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_1:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"FILTER HANDLER BLOCK 1 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_1:
		BEGIN_FILTER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							4
			beq								FILTER_SUCCEEDED_2

			ldstr							"FILTER 2 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_2

		FILTER_SUCCEEDED_2:
			ldstr							"FILTER 2 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_2:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_2:
			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO CATCH BLOCKS.
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"FILTER HANDLER BLOCK 2 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_2:
		BEGIN_CATCH_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"ARGUMENT EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_1:
		BEGIN_CATCH_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_2:

		BEGIN_TRY:
			// !!!!! Zacina TRY BLOCK.
			.try
			{
				ldarg						Value
				ldc.i4						1
				bne.un						CASE_1

				ldstr						"Some ARGUMENT EXCEPTION !"
				newobj						instance void class [mscorlib]System.ArgumentException::.ctor(string)
				throw

			CASE_1:
				ldarg						Value
				ldc.i4						2
				bne.un						CASE_2
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_2:
				ldarg						Value
				ldc.i4						3
				bne.un						CASE_3
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_3:
				ldarg						Value
				ldc.i4						4
				bne.un						CASE_4
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_4:
				ldstr						"NO EXCEPTION is THROWN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			// !!!!! MIXED FORM EXCEPTION CLAUSE.
			filter							BEGIN_FILTER_1
			handler							BEGIN_FILTER_HANDLER_1 to END_FILTER_HANDLER_1
			filter							BEGIN_FILTER_2
			handler							BEGIN_FILTER_HANDLER_2 to END_FILTER_HANDLER_2
			catch [mscorlib]System.ArgumentException
			handler							BEGIN_CATCH_1 to END_CATCH_1
			catch [mscorlib]System.Exception
			handler							BEGIN_CATCH_2 to END_CATCH_2

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void NestedException(int32 Value) cil managed
		{
			.try
			{
				.try
				{
					ldarg					Value
					ldc.i4					1
					bne.un					CASE_1

					ldstr					"Some ARGUMENT EXCEPTION !"
					newobj					instance void class [mscorlib]System.ArgumentException::.ctor(string)
					throw

				CASE_1:
					ldarg					Value
					ldc.i4					2
					bne.un					CASE_2
				
					ldstr					"Some EXCEPTION !"
					newobj					instance void class [mscorlib]System.Exception::.ctor(string)
					throw

				CASE_2:
					ldstr					"NO EXCEPTION is THROWN !"
					call					void [mscorlib]System.Console::WriteLine(string)

					leave					INNER_EXIT
				}
				catch [mscorlib]System.ArgumentException
				{
					ldstr					"INNER EXCEPTION was CAUGHT !"
					call					void [mscorlib]System.Console::WriteLine(string)

					leave					INNER_EXIT
				}

				INNER_EXIT:
					leave					OUTER_EXIT
			}
			catch [mscorlib]System.Exception
			{
				ldstr						"OUTER EXCEPTION was CAUGHT !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						OUTER_EXIT
			}

		OUTER_EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void CatchBlocksTestLabelForm(int32 Value) cil managed
		{
		BEGIN_TRY:
			ldarg							Value
			ldc.i4							1
			bne.un							CASE_1

			ldstr							"Some ARGUMENT EXCEPTION !"
			newobj							instance void class [mscorlib]System.ArgumentException::.ctor(string)
			throw

		CASE_1:
			ldarg							Value
			ldc.i4							2
			bne.un							CASE_2
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_2:
			ldarg							Value
			ldc.i4							3
			bne.un							CASE_3
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_3:
			ldarg							Value
			ldc.i4							4
			bne.un							CASE_4
				
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

		CASE_4:
			ldstr							"NO EXCEPTION is THROWN !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_TRY:
			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO FILTER BLOCKS.
		BEGIN_FILTER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							3
			beq								FILTER_SUCCEEDED_1

			ldstr							"FILTER 1 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_1

		FILTER_SUCCEEDED_1:
			ldstr							"FILTER 1 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_1:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"FILTER HANDLER BLOCK 1 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_1:
		BEGIN_FILTER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							4
			beq								FILTER_SUCCEEDED_2

			ldstr							"FILTER 2 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_2

		FILTER_SUCCEEDED_2:
			ldstr							"FILTER 2 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_2:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_2:
			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO CATCH BLOCKS.
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"FILTER HANDLER BLOCK 2 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_2:
		BEGIN_CATCH_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"ARGUMENT EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_1:
		BEGIN_CATCH_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

			ldstr							"EXCEPTION BLOCK caught EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_CATCH_2:

			// !!!!! LABEL FORM EXCEPTION CLAUSE.
			.try							BEGIN_TRY to END_TRY
			filter							BEGIN_FILTER_1
			handler							BEGIN_FILTER_HANDLER_1 to END_FILTER_HANDLER_1
			filter							BEGIN_FILTER_2
			handler							BEGIN_FILTER_HANDLER_2 to END_FILTER_HANDLER_2
			catch							[mscorlib]System.ArgumentException
			handler							BEGIN_CATCH_1 to END_CATCH_1
			catch							[mscorlib]System.Exception
			handler							BEGIN_CATCH_2 to END_CATCH_2

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FilterBlocksTestLabelForm(int32 Value) cil managed
		{
		BEGIN_TRY:
			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.Exception::.ctor(string)
			throw

			// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
			leave							EXIT
		END_TRY:
		BEGIN_FILTER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							1
			beq								FILTER_SUCCEEDED_1

			ldstr							"FILTER 1 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_1

		FILTER_SUCCEEDED_1:
			ldstr							"FILTER 1 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_1:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_1:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"CATCH BLOCK 1 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_1:
		BEGIN_FILTER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

			ldarg							Value
			ldc.i4							2
			beq								FILTER_SUCCEEDED_2

			ldstr							"FILTER 2 CALLED but FAILED to PROCESS EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER NEVYVOLA CATCH BLOCK a CLR ma pokracovat v hladani ineho vhodneho FILTER BLOCK.
			ldc.i4							0
			br								EXIT_FILTER_2

		FILTER_SUCCEEDED_2:
			ldstr							"FILTER 2 CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1

		EXIT_FILTER_2:
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_2:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"CATCH BLOCK 2 CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_2:
		BEGIN_FILTER_3:
			ldstr							"DEFAULT FILTER CALLED and PROCEEDED EXCEPTION !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
			ldc.i4							1
			// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
			endfilter
		BEGIN_FILTER_HANDLER_3:
			// !!! Na STACKU je ulozena hodnota EXCEPTION.
			call							void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

			ldstr							"DEFAULT CATCH BLOCK CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_FILTER_HANDLER_3:

			// !!!!! LABEL FORM EXCEPTION CLAUSE.
			.try							BEGIN_TRY to END_TRY
			filter							BEGIN_FILTER_1
			handler							BEGIN_FILTER_HANDLER_1 to END_FILTER_HANDLER_1
			filter							BEGIN_FILTER_2
			handler							BEGIN_FILTER_HANDLER_2 to END_FILTER_HANDLER_2
			filter							BEGIN_FILTER_3
			handler							BEGIN_FILTER_HANDLER_3 to END_FILTER_HANDLER_3

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FinallyBlockTestLabelForm(int32 Value) cil managed
		{
		BEGIN_TRY:
			ldarg							Value
			ldc.i4							1
			bne.un							CASE_NO_EXCEPTION

			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.ArgumentException::.ctor(string)
			throw

		CASE_NO_EXCEPTION:
			ldstr							"NO EXCEPTION is THROWN !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_TRY:
		BEGIN_FINALLY:
			ldstr							"FINALLY BLOCK was EXECUTED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! FINALLY BLOCK musi VZDY LEXIKALNE koncit INSTRUCTION [endfinally].
			endfinally
		END_FINALLY:
			// !!!!! LABEL FORM EXCEPTION CLAUSE.
			.try							BEGIN_TRY to END_TRY
			finally
			handler							BEGIN_FINALLY to END_FINALLY

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FaultBlockTestLabelForm(int32 Value) cil managed
		{
		BEGIN_TRY:
			ldarg							Value
			ldc.i4							1
			bne.un							CASE_NO_EXCEPTION

			ldstr							"Some EXCEPTION !"
			newobj							instance void class [mscorlib]System.ArgumentException::.ctor(string)
			throw

		CASE_NO_EXCEPTION:
			ldstr							"NO EXCEPTION is THROWN !"
			call							void [mscorlib]System.Console::WriteLine(string)

			leave							EXIT
		END_TRY:
		BEGIN_FAULT:
			ldstr							"FAULT BLOCK was EXECUTED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! FAULT BLOCK musi VZDY LEXIKALNE koncit INSTRUCTION [endfault], ktora je IDENTICKA s INSTRUCTION [endfinally].
			endfault
		END_FAULT:
			// !!!!! LABEL FORM EXCEPTION CLAUSE.
			.try							BEGIN_TRY to END_TRY
			fault
			handler							BEGIN_FAULT to END_FAULT

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void CatchBlocksTest(int32 Value) cil managed
		{
			.try
			{
				ldarg						Value
				ldc.i4						1
				bne.un						CASE_1

				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.ArgumentException::.ctor(string)
				throw

			CASE_1:
				ldarg						Value
				ldc.i4						2
				bne.un						CASE_2
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_2:
				ldarg						Value
				ldc.i4						3
				bne.un						CASE_3
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_3:
				ldarg						Value
				ldc.i4						4
				bne.un						CASE_4
				
				ldstr						"Some EXCEPTION !"
				newobj						instance void class [mscorlib]System.Exception::.ctor(string)
				throw

			CASE_4:
				ldstr						"NO EXCEPTION is THROWN !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO FILTER BLOCKS.
			filter
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

				ldarg						Value
				ldc.i4						3
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
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

				ldstr						"FILTER HANDLER BLOCK 1 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			filter
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

				ldarg						Value
				ldc.i4						4
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
			// !!!!! FILTER BLOCKS sa MOZU kombinovat s CATCH BLOCKS.
			// !!!!! Jedna EXCEPTION CLAUSE moze mat VIACERO CATCH BLOCKS.
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

				ldstr						"FILTER HANDLER BLOCK 2 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.ArgumentException
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				ldstr						"ARGUMENT EXCEPTION BLOCK caught EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			catch [mscorlib]System.Exception
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				ldstr						"EXCEPTION BLOCK caught EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			/*
			// !!!!! Ak je v EXCEPTION CLAUSE uz CATCH BLOCKS, tak NEMOZE mat ZAROVEN aj FINALLY ci FAULT BLOCKS.
			finally
			{
				ldstr						"FINALLY BLOCK was EXECUTED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! FINALLY BLOCKS musia byt VZDY LEXIKALNE ukoncene INSTRUCTION [endfinally].
				endfinally
			}
			*/
			/*
			// !!!!! Ak je v EXCEPTION CLAUSE uz CATCH BLOCKS, tak NEMOZE mat ZAROVEN aj FINALLY ci FAULT BLOCKS.
			fault
			{
				ldstr						"FAULT BLOCK was EXECUTED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! FAULT BLOCKS musia byt VZDY LEXIKALNE ukoncene INSTRUCTION [endfault].
				endfault
			}
			*/

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FilterBlocksTest(int32 Value) cil managed
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
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

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
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

				ldstr						"CATCH BLOCK 1 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			filter
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

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
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

				ldstr						"CATCH BLOCK 2 CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}
			filter
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterException(class [mscorlib]System.Exception Exception)

				ldstr						"DEFAULT FILTER CALLED and PROCEEDED EXCEPTION !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! Toto je PARAMETER pre INSTRUCTION [endfilter], ktory urcuje, ze FILTER VYVOLA CATCH BLOCK a CLR ZASTAVI prehladavanie dalsich FILTER BLOCKS.
				ldc.i4						1
				// !!!!! LEXICAL SCOPE FILTER BLOCK MUSI VZDY koncit INSTRUCTION [endfilter], ktora zo STACKU vybera hodnotu, ktora ak je 1, tak sa vyvola EXCEPTION BLOCK a UKONCI prehlavanie FILTER BLOCKS a ak je INA AKO 1, tak sa POKRACUJE v prehladavani FILTER BLOCKS.
				endfilter
			}
			{
				// !!! Na STACKU je ulozena hodnota EXCEPTION.
				call						void Helpers.CHelpers::PrintFilterHandlerException(class [mscorlib]System.Exception Exception)

				ldstr						"DEFAULT CATCH BLOCK CALLED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void FinallyBlockTest(int32 Value) cil managed
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
			finally
			{
				ldstr						"FINALLY BLOCK was EXECUTED !"
				call						void [mscorlib]System.Console::WriteLine(string)

				// !!!!! FINALLY BLOCK musi VZDY LEXIKALNE koncit INSTRUCTION [endfinally].
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
				call						void ExceptionHandling.CExceptionHandling::ThrowException()

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
        .method public hidebysig static void Test1() cil managed
		{
			.try
			{
				call						void ExceptionHandling.CExceptionHandling::RethrowException()

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
        .method public hidebysig static void Test2() cil managed
		{
			.try
			{
				// !!!!! Namiesto Object generuje EXCEPTION TYPU RuntimeWrappedException.
				newobj						instance void class [mscorlib]System.Object::.ctor()
				// !!! Hodi EXCEPTION.
				throw

				// !!!!! TRY BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}
			catch [mscorlib]System.Runtime.CompilerServices.RuntimeWrappedException
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)

				// !!!!! CATCH BLOCK MUSI VZDY koncit INSTRUCTION [leave], inak by doslo k CHYBE PROGRAMU.
				leave						EXIT
			}

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTest(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTest(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTest(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTest(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							5
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTest(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTest(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTest(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTest(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTest(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						0
				call						void ExceptionHandling.CExceptionHandling::FinallyBlockTest(int32)

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
				call						void ExceptionHandling.CExceptionHandling::FinallyBlockTest(int32)

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
        .method public hidebysig static void Test6() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						0
				call						void ExceptionHandling.CExceptionHandling::FaultBlockTest(int32)

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
				call						void ExceptionHandling.CExceptionHandling::FaultBlockTest(int32)

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
        .method public hidebysig static void Test7() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							5
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTestLabelForm(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTestLabelForm(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTestLabelForm(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::FilterBlocksTestLabelForm(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						0
				call						void ExceptionHandling.CExceptionHandling::FinallyBlockTestLabelForm(int32)

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
				call						void ExceptionHandling.CExceptionHandling::FinallyBlockTestLabelForm(int32)

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
        .method public hidebysig static void Test10() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			.try
			{
				ldc.i4						0
				call						void ExceptionHandling.CExceptionHandling::FaultBlockTestLabelForm(int32)

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
				call						void ExceptionHandling.CExceptionHandling::FaultBlockTestLabelForm(int32)

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
        .method public hidebysig static void Test11() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::NestedException(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::NestedException(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)
			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::NestedException(int32)
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test12() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestMixedForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestMixedForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestMixedForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestMixedForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test13() cil managed
		{
			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							1
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelFormChangedOrder(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							2
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelFormChangedOrder(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							3
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelFormChangedOrder(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							4
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							5
			call							void ExceptionHandling.CExceptionHandling::CatchBlocksTestLabelForm(int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void ExceptionHandling.CExceptionHandling::Test1()
			//call							void ExceptionHandling.CExceptionHandling::Test2()
			//call							void ExceptionHandling.CExceptionHandling::Test3()
			//call							void ExceptionHandling.CExceptionHandling::Test4()
			//call							void ExceptionHandling.CExceptionHandling::Test5()
			//call							void ExceptionHandling.CExceptionHandling::Test6()
			//call							void ExceptionHandling.CExceptionHandling::Test7()
			//call							void ExceptionHandling.CExceptionHandling::Test8()
			//call							void ExceptionHandling.CExceptionHandling::Test9()
			//call							void ExceptionHandling.CExceptionHandling::Test10()
			//call							void ExceptionHandling.CExceptionHandling::Test11()
			//call							void ExceptionHandling.CExceptionHandling::Test12()
			call							void ExceptionHandling.CExceptionHandling::Test13()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
