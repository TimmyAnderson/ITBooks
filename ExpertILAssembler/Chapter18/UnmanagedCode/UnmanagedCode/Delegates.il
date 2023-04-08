//-------------------------------------------------------------------------------------------------------
.namespace UnmanagedCode
{
//-------------------------------------------------------------------------------------------------------
	// !!! DELEGATE reprezentuje CALLBACK DELEGATE, ktory sa pouziva pri zasielani CALLBACK FUNCTION do UNMANAGED FUNCTION volanej cez PINVOKE.
	.class public sealed DMyDelegate extends [mscorlib]System.MulticastDelegate
	{
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname rtspecialname instance void .ctor(object MethodsClass, native int MethodPtr) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! MUSI byt nastaveny FLAG [modopt([mscorlib]System.Runtime.CompilerServices.CallConvCdecl)].
		// !!! Aby sa preniesol cely STRING, tak sa nastavi FLAG [marshal(lpwstr)].
		.method public hidebysig newslot virtual instance void modopt([mscorlib]System.Runtime.CompilerServices.CallConvCdecl) Invoke(string marshal(lpwstr) Message, int32 Length) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig newslot virtual instance class [mscorlib]System.IAsyncResult BeginInvoke(string marshal(lpwstr) Message, int32 Length, class [mscorlib]System.AsyncCallback Callback, object State) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig newslot virtual instance void EndInvoke(class [mscorlib]System.IAsyncResult Result) runtime managed
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------