//-------------------------------------------------------------------------------------------------------
.namespace Helpers
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CHelpers extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void PrintException(class [mscorlib]System.Exception Exception) cil managed
		{
			ldstr							"EXCEPTION [{0}] !"
			ldarg.0
			callvirt						instance string [mscorlib]System.Object::ToString()
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static string ConvertToHex(int32 Value) cil managed
		{
			ldarga							Value
			ldstr							"X"
			call							instance string [mscorlib]System.Int32::ToString(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void ThrowBreakpoint() cil managed
		{
			call							void [mscorlib]System.Diagnostics.Debugger::Break()

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------