//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGenericClassMembers<TParam1,TParam2,TParam3> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field private !TParam1									MField1
		.field private !TParam2									MField2
		.field private !TParam3									MField3
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor(!TParam3 Param3) cil managed
		{
			ldstr							"CGenericClassMembers<TParam1,TParam2,TParam3> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ldarg							0
			ldarg							Param3
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			stfld							!TParam3 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField3

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance !TParam3 SetFieldsAndPrint(!TParam1 Param1, !TParam2 Param2) cil managed
		{
			ldarg							0
			ldarg							Param1
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			stfld							!TParam1 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField1

			ldarg							0
			ldarg							Param2
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			stfld							!TParam2 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField2

			ldstr							"METHOD - MField1 [{0}], MField2 [{1}], MField3 [{2}] !"

			ldarg							0
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			ldfld							!TParam1 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField1
			box								!TParam1

			ldarg							0
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			ldfld							!TParam2 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField2
			box								!TParam2

			ldarg							0
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			ldfld							!TParam3 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField3
			box								!TParam3

			call							string [mscorlib]System.String::Format(string,object,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			// !!! Pri referovani na MEMBERS v ramci CLASS je NUTNE vykonat GENERIC TYPE INSTANTION. Za TYPE PARAMETERS sa pouzivaju ich NAMES (mozu byt aj ORDINAL NUMBERS) s prefixom '!'.
			ldfld							!TParam3 class GenericTypes.CGenericClassMembers<!TParam1,!TParam2,!TParam3>::MField3

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------