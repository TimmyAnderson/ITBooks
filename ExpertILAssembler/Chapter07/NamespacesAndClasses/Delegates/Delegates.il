//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Delegates {}
.module Delegates.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Delegates
{
//-------------------------------------------------------------------------------------------------------
	// !!! DELEGATES NESMU mat BODIES svojich METHODS.
	.class public sealed DMyDelegate extends [mscorlib]System.MulticastDelegate
	{
//-------------------------------------------------------------------------------------------------------
		// !!! DELEGATES NESMU mat BODIES svojich METHODS.
		.method public hidebysig specialname rtspecialname instance void .ctor(object MethodsClass, native int MethodPtr) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
		// !!! DELEGATES NESMU mat BODIES svojich METHODS.
		// !!!!! SIGNATURE METHOD Invoke() MUSI byt IDENTICKA so SIGNATURE METHOD, ktora ma byt volana.
		.method public hidebysig newslot virtual instance void Invoke(string Name, int32 Age) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
		// !!! DELEGATES NESMU mat BODIES svojich METHODS.
		// !!!!! SIGNATURE METHOD BeginInvoke() MUSI zacinat TYMI ISTYMI PARAMETERS ako METHOD, ktora ma byt volana. Okrem nich MUSI mat este 2 EXTRA PARAMETERS.
		.method public hidebysig newslot virtual instance class [mscorlib]System.IAsyncResult BeginInvoke(string Name, int32 Age, class [mscorlib]System.AsyncCallback Callback, object State) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
		// !!! DELEGATES NESMU mat BODIES svojich METHODS.
		.method public hidebysig newslot virtual instance void EndInvoke(class [mscorlib]System.IAsyncResult Result) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CDelegates extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void DelegateMethod(string Name, int32 Age) cil managed
		{
			ldstr							"DELEGATE - Name: [{0}], Age [{1}] !"

			ldarg.0
			ldarg.1
			box								[mscorlib]System.Int32

			call							string [mscorlib]System.String::Format(string,object,object)

	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
			.locals init					(class Delegates.DMyDelegate MyDelegate)

			// Priame volanie METHOD.
			//ldstr							"My name is Timmy Anderson !"
			//ldc.i4						12
			//call							void Delegates.CDelegates::DelegateMethod(string,int32)

			ldnull
			// Ziska MANAGED REFERENCE na CALLBACK METHOD.
			ldftn							void Delegates.CDelegates::DelegateMethod(string,int32)
			// Vytvori instanciu DELEGATE OBJECT.
			newobj							instance void Delegates.DMyDelegate::.ctor(object,native int)
			stloc.0

			ldloc.0
			ldstr							"My name is Timmy Anderson !"
			ldc.i4							12
			// !!! Vyvola sa DELEGATE. Kedze Invoke() je VIRTUAL METHOD, tak sa MUSI volat pomocou INSTRUCTION [callvirt].
			callvirt						instance void Delegates.DMyDelegate::Invoke(string,int32)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------