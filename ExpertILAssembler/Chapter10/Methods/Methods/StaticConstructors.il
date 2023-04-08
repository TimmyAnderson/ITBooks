//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! Kedze STATIC CONSTRUCTOR NIE JE DEKLAROVANY v TYPE, ale mimo, tak tento STATIC CONSTRUCTOR je MODULE STATIC CONSTRUCTOR, ktory sa vola PRED PRVYM pristupom k lubovolnemu ELEMENT CURRENT MODULE.
	.method public specialname rtspecialname static void .cctor() cil managed
	{
		ldstr								"MODULE STATIC CONSTRUCTOR CALLED !"
		call								void [mscorlib]System.Console::WriteLine(string)

		ret
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CStaticConstructors extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname static void .cctor() cil managed
		{
			ldstr							"CStaticConstructors STATIC CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CStaticConstructors CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void SomeMethod() cil managed
		{
			ldstr							"CStaticConstructors::SomeMethod() CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CStaticConstructorsNoBeforeFieldInit extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! Kedze CLASS sa v CODE NEPOUZIVA jej STATIC CONSTRUCTOR sa NEZAVOLA.
	    .method public specialname rtspecialname static void .cctor() cil managed
		{
			ldstr							"CStaticConstructorsNoBeforeFieldInit STATIC CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	// !!! CLASS ma aplikovany FLAG [beforefieldinit].
    .class public auto ansi beforefieldinit CStaticConstructorsWithBeforeFieldInit extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! Aj ked CODE CLASS NEPOUZIVA, kedze ma nastaveny FLAG [beforefieldinit] CLR moze STATIC CONSTRUCTOR zavolat aj bez toho, aby musel cakat na prvy pristup k tomuto TYPE.
		// !!! Pri testovani sa tento STATIC CONSTRUCTOR NEVOLAL.
	    .method public specialname rtspecialname static void .cctor() cil managed
		{
			ldstr							"CStaticConstructorsWithBeforeFieldInit STATIC CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------