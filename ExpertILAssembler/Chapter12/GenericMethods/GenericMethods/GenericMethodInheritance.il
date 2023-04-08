//-------------------------------------------------------------------------------------------------------
.namespace GenericMethods
{
//-------------------------------------------------------------------------------------------------------
    .class interface public abstract auto ansi IInterface
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void Print1<TParam>(!!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void Print2<TParam>(!!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig abstract virtual instance void Print3<TParam>(!!TParam Param) cil managed
		{
		}		
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig abstract virtual instance void Print4<([mscorlib]System.ICloneable) TParam1,([mscorlib]System.IFormattable) TParam2>(!!TParam1 Param1, !!TParam2 Param2) cil managed
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	.class public auto ansi CDerivedClass extends [mscorlib]System.Object implements GenericMethods.IInterface
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CDerivedClass CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD IMPLICITNE pretazuje METHOD z INTERFACE IInterface.
        .method public hidebysig virtual instance void Print1<TParam>(!!TParam Param) cil managed
		{
			ldstr							"Print1(!!TParam Param) - [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD EXPLICITNE (SHORT EXPLICIT) pretazuje METHOD z INTERFACE IInterface.
        .method public hidebysig virtual instance void ExplicitlyOverriddenMethodShort<TParam>(!!TParam Param) cil managed
		{
			// !!!!! Hodnota <[1]> znamena, ze GENERIC METHOD ma 1 TYPE PARAMETER.
			.override						method instance void class GenericMethods.IInterface::Print2<[1]>(!!0)

			ldstr							"ExplicitlyOverriddenMethodShort(!!TParam Param) - [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD EXPLICITNE (LONG EXPLICIT) pretazuje METHOD z INTERFACE IInterface.
        .method public hidebysig virtual instance void ExplicitlyOverriddenMethodLong<TParam>(!!TParam Param) cil managed
		{
			ldstr							"ExplicitlyOverriddenMethodLong(!!TParam Param) - [{0}] !"
			ldarg							Param
			box								!!TParam
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig virtual instance void Print4OverridenExplicitly<([mscorlib]System.ICloneable) TParam1,([mscorlib]System.IFormattable) TParam2>(!!TParam1 Param1, !!TParam2 Param2) cil managed
		{
			// !!!!! Hodnota <[2]> znamena, ze GENERIC METHOD ma 2 TYPE PARAMETERS.
			.override						method instance void class GenericMethods.IInterface::Print4<[2]>(!!0,!!1)

            .locals							init (!!TParam1 Value1, !!TParam2 Value2)

			ldarg							Param1
			stloc							Value1

			ldarg							Param2
			stloc							Value2

			ldstr							"Print4OverridenExplicitly() - Value1 [{0}], Value2 [{1}] !"

			ldloc							Value1
			box								!!TParam1
			ldloc							Value2
			box								!!TParam2

			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! LONG EXPLICIT OVERRIDING.
		// !!!!! Hodnota <[1]> znamena, ze GENERIC METHOD ma 1 TYPE PARAMETER.
		.override							method instance void GenericMethods.IInterface::Print3<[1]>(!!0) with method instance void GenericMethods.CDerivedClass::ExplicitlyOverriddenMethodLong<[1]>(!!0)
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------