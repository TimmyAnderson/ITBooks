//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
    .class interface public abstract auto ansi IGenericInterface1<TParam>
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void PrintField1(!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class interface public abstract auto ansi IGenericInterface2<TParam>
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void PrintField2(!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class interface public abstract auto ansi IGenericInterface3<TParam>
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void PrintField3(!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class interface public abstract auto ansi IGenericInterface4<TParam>
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void PrintField4(!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGenericBaseClass<TParam> extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		.field family !TParam									MField
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CGenericBaseClass<TParam> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! DERIVED CLASSES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
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
			stfld							!0 class GenericTypes.CGenericBaseClass<!TParam>::MField

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	// !!! Je NUTNE pouzit znak '!', aby sa TYPE namieril za TYPE INSTANCE.
    .class public auto ansi CGenericDerivedClass<TParam> extends class GenericTypes.CGenericBaseClass<!TParam> implements class GenericTypes.IGenericInterface1<!TParam>, class GenericTypes.IGenericInterface2<!TParam>, class GenericTypes.IGenericInterface3<!TParam>, class GenericTypes.IGenericInterface4<!TParam>
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CGenericDerivedClass<TParam> CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void class GenericTypes.CGenericBaseClass<!TParam>::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig instance void PrintField() cil managed
		{
			ldstr							"TEST - MField [{0}] !"

			ldarg							0
			ldfld							!0 class GenericTypes.CGenericBaseClass<!TParam>::MField
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD z INTERFACE IGenericInterface1<TParam>.
        .method public hidebysig virtual instance void PrintField1(!TParam Param) cil managed
		{
			ldstr							"PrintField1(!TParam Param) - [{0}] !"
			ldarg							Param
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD z INTERFACE IGenericInterface2<TParam>.
        .method public hidebysig virtual instance void PrintField2(!TParam Param) cil managed
		{
			ldstr							"PrintField2(!TParam Param) - [{0}] !"
			ldarg							Param
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD EXPLICITNE (SHORT EXPLICIT) pretazuje METHOD z INTERFACE IGenericInterface3<TParam>.
        .method public hidebysig virtual instance void ExplicitlyOverriddenMethodShort(!TParam Param) cil managed
		{
			.override						method instance void class GenericTypes.IGenericInterface3<!TParam>::PrintField3(!0)

			ldstr							"ExplicitlyOverriddenMethodShort(!TParam Param) - [{0}] !"
			ldarg							Param
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD EXPLICITNE (LONG EXPLICIT) pretazuje METHOD z INTERFACE IGenericInterface4<TParam>.
        .method public hidebysig virtual instance void ExplicitlyOverriddenMethodLong(!TParam Param) cil managed
		{
			ldstr							"ExplicitlyOverriddenMethodLong(!TParam Param) - [{0}] !"
			ldarg							Param
			box								!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! LONG EXPLICIT OVERRIDING.
		.override							method instance void class GenericTypes.IGenericInterface4<!TParam>::PrintField4(!0) with method instance void class GenericTypes.CGenericDerivedClass::ExplicitlyOverriddenMethodLong(!0)
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------