//-------------------------------------------------------------------------------------------------------
.namespace EventsAndProperties
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
}
//-------------------------------------------------------------------------------------------------------