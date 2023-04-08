//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
	// !!! Prvy PARAMETER musi implementovat ICloneable.
	// !!! Druhy PARAMETER musi implementovat IComparable'1<TParam2>.
	// !!!!! EXTREMNE DOLEZITY je fakt, ze zakladne GENERIC INTERFACES maju v nazve [XXX'ARITY]. Je to iba MENNA KONVENCIA, ktoru .NET zaviedol. CUSTOM CLASSES a INTERFACES ju nemusia dodrziavat.
    .class public auto ansi CContraints2<([mscorlib]System.ICloneable) TParam1,(class [mscorlib]System.IComparable`1<!TParam2>) TParam2> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field private !TParam1									MField1
		.field private !TParam2									MField2
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CContraints2<TParam1,TParam2> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void SetField1(!TParam1 Param) cil managed
		{
			ldarg							0
			ldarg							Param
			// !!! TYPE PARAMETER TYPE sa definuje cez ORDINAL NUMBER.
			stfld							!0 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField1

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void SetField2(!TParam2 Param) cil managed
		{
			ldarg							0
			ldarg							Param
			// !!! TYPE PARAMETER TYPE sa definuje cez ORDINAL NUMBER.
			stfld							!1 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField2

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void SetFields(!TParam1 Param1, !TParam2 Param2) cil managed
		{
			ldarg							0
			ldarg							Param1
			// !!! TYPE PARAMETER TYPE sa definuje cez TYPE PARAMTER NAME.
			stfld							!TParam1 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField1

			ldarg							0
			ldarg							Param2
			// !!! TYPE PARAMETER TYPE sa definuje cez TYPE PARAMTER NAME.
			stfld							!TParam2 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField2

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void PrintFields() cil managed
		{
			ldstr							"TEST - MField1 [{0}], MField2 [{1}] !"

			ldarg							0
			// !!! TYPE PARAMETER TYPE sa definuje cez TYPE PARAMTER NAME.
			ldfld							!TParam1 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField1
			box								!TParam1

			ldarg							0
			// !!! TYPE PARAMETER TYPE sa definuje cez TYPE PARAMTER NAME.
			ldfld							!TParam2 class GenericTypes.CContraints2<!TParam1,!TParam2>::MField2
			box								!TParam2

			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------