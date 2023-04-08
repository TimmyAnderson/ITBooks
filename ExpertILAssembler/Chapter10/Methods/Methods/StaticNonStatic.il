//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CStaticNonStatic extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .field private static string							MStaticField1
        .field private static string							MStaticField2
//-------------------------------------------------------------------------------------------------------
        .field private string									MNonStaticField1
        .field private string									MNonStaticField2
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void StaticMethod(string Param1, string Param2) cil managed
		{
			ldarg							Param1
			stsfld							string Methods.CStaticNonStatic::MStaticField1
			ldarg							Param2
			stsfld							string Methods.CStaticNonStatic::MStaticField2

			ldstr							"STATIC METHOD - PARAM1 [{0}], PARAM2 [{1}] !"
			ldsfld							string Methods.CStaticNonStatic::MStaticField1
			ldsfld							string Methods.CStaticNonStatic::MStaticField1
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! Ako 0. PARAMETER je THIS PARAMETER.
        .method public hidebysig instance void NonStaticMethod(string Param1, string Param2) cil managed
		{
			// !!!!! Nacita THIS PARAMETER, aby mohol pristupit k NON-STATIC FIELD.
			ldarg							0
			ldarg							Param1
			stfld							string Methods.CStaticNonStatic::MNonStaticField1
			// !!!!! Nacita THIS PARAMETER, aby mohol pristupit k NON-STATIC FIELD.
			ldarg							0
			ldarg							Param2
			stfld							string Methods.CStaticNonStatic::MNonStaticField2

			ldstr							"NON-STATIC METHOD - PARAM1 [{0}], PARAM2 [{1}] !"
			// !!!!! Nacita THIS PARAMETER, aby mohol pristupit k NON-STATIC FIELD.
			ldarg							0
			ldfld							string Methods.CStaticNonStatic::MNonStaticField1
			// !!!!! Nacita THIS PARAMETER, aby mohol pristupit k NON-STATIC FIELD.
			ldarg							0
			ldfld							string Methods.CStaticNonStatic::MNonStaticField2
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------