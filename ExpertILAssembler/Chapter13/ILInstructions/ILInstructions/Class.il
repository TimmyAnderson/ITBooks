//-------------------------------------------------------------------------------------------------------
.namespace ILInstructions
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field private string									MField
//-------------------------------------------------------------------------------------------------------
		.field private static string							MStaticField
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
		.method public void TestMethod1(string Param1, string Param2)
		{
			// !!! Nacita THIS PARAMETER, ktory je v NON-STATIC METHODS VZDY 0. ARGUMENT.
			ldarg							0
			ldstr							"Timmy Anderson"
			// !!! Kedze sa pristupuje k NON-STATIC FIELD je NUTNE nacitat THIS PARAMETER pred zapisom do NON-STATIC FIELD.
			stfld							string ILInstructions.CClass::MField

			ldstr							"PARAM 1 [{0}], PARAM 2 [{1}], FIELD [{2}] !"
			// !!! Pristup k ARGUMENT cez ARGUMENT NAME.
			ldarg							Param1
			// !!! Pristup k ARGUMENT cez ARGUMENT INDEX.
			// !!! Aj ked INDEX zacina od 0, tak pre NON-STATIC METHODS je 0. ARGUMENT THIS PARAMETER.
			ldarg							2
			// !!! Nacita THIS PARAMETER, ktory je v NON-STATIC METHODS VZDY 0. ARGUMENT.
			ldarg							0
			// !!! Kedze sa pristupuje k NON-STATIC FIELD je NUTNE nacitat THIS PARAMETER pred citanim z NON-STATIC FIELD.
			ldfld							string ILInstructions.CClass::MField
			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public void TestMethod2(string Param)
		{
            .locals							init (string& PointerToParam)

			ldstr							"PARAM BEFORE CHANGE [{0}] !"
			ldarg							Param
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska POINTER na ARGUMENT.
			ldarga							Param
			stloc							PointerToParam

			ldloc							PointerToParam
			ldstr							"Jenny Thompson"
			// !!! Ulozi hodnotu do ARGUMENT.
			stind.i4

			ldstr							"PARAM AFTER CHANGE [{0}] !"
			ldarg							Param
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public void TestMethod3()
		{
            .locals							init (string& PointerToNonStaticField, string& PointerToStaticField)

			// !!! Pre pristup k NON-STATIC FIELDS je nutne na STACK ulozit THIS PARAMETER.
			ldarg							0
			ldstr							"Timmy Anderson"
			// !!! INSTRUCTION na pristup k NON-STATIC FIELD.
			stfld							string ILInstructions.CClass::MField

			ldstr							"Jenny Thompson"
			// !!! INSTRUCTION na pristup k STATIC FIELD.
			stsfld							string ILInstructions.CClass::MStaticField

			ldstr							"BEFORE CHANGE - NON-STATIC FIELD [{0}], STATIC FIELD [{1}] !"
			ldarg							0
			ldfld							string ILInstructions.CClass::MField
			ldsfld							string ILInstructions.CClass::MStaticField
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska POINTER na NON-STATIC FIELD.
			ldarg							0
			ldflda							string ILInstructions.CClass::MField
			stloc							PointerToNonStaticField

			// !!! Ziska POINTER na STATIC FIELD.
			ldsflda							string ILInstructions.CClass::MStaticField
			stloc							PointerToStaticField

			ldloc							PointerToNonStaticField
			ldstr							"XXX"
			// !!! Ulozi hodnotu do NON-STATIC FIELD.
			stind.i4

			ldloc							PointerToStaticField
			ldstr							"YYY"
			// !!! Ulozi hodnotu do STATIC FIELD.
			stind.i4

			ldstr							"AFTER CHANGE - NON-STATIC FIELD [{0}], STATIC FIELD [{1}] !"
			ldarg							0
			ldfld							string ILInstructions.CClass::MField
			ldsfld							string ILInstructions.CClass::MStaticField
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------