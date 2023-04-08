.namespace UnmanagedCode
{
//-------------------------------------------------------------------------------------------------------
	// Implementacia COM CALLBACK INTERFACE.
	.class public auto ansi beforefieldinit CCOMCallback extends [mscorlib]System.Object implements [UnmanagedCOMServer]UnmanagedCOMServer.IUnmanagedCOMServerCallback
	{
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! CALLBACK METHOD.
		.method public hidebysig newslot virtual final instance void SendMessageToClient(string Message) cil managed
		{
			.locals							init (string Text)

			ldstr							"CLASS CCOMCallback - MESSAGE [{0}] !"
			ldarg							Message
			call							string [mscorlib]System.String::Format(string,object)
			stloc							Text

			ldloc							Text
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------