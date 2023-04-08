//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi COverloading extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR aj MSIL UMOZNUJU FIELD OVERLOADING ak sa FIELDS lisia vo FIELD TYPE.
        .field public static string								MOverloadedField
        .field public static int32								MOverloadedField
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR aj MSIL NEUMOZNUJU FIELD OVERLOADING iba na zaklade nastavenia STATIC/NON-STATIC FLAG a nasledujuci CODE by hodil COMPILATION ERROR, pretoze FIELDS s NAME MOverloadedField pre STRING a INT32 uz EXISTUJU ako STATIC FIELDS.
        //.field public string									MOverloadedField
        //.field public int32									MOverloadedField
//-------------------------------------------------------------------------------------------------------
		// !!!!! CLR aj MSIL UMOZNUJU FIELD OVERLOADING ak sa FIELDS lisia vo FIELD TYPE.
        .field public string									MNonStaticOverloadedField
        .field public int32										MNonStaticOverloadedField
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
        .method public hidebysig static void OverloadedMethod() cil managed
		{
			ldstr							"METHOD [static void OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static vararg void OverloadedMethod() cil managed
		{
			ldstr							"METHOD [vararg static void OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static int32 OverloadedMethod() cil managed
		{
			ldstr							"METHOD [static int32 OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							999

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void OverloadedMethod() cil managed
		{
			ldstr							"METHOD [void OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig vararg void OverloadedMethod() cil managed
		{
			ldstr							"METHOD [vararg void OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig int32 OverloadedMethod() cil managed
		{
			ldstr							"METHOD [int32 OverloadedMethod()] CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldc.i4							999

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------