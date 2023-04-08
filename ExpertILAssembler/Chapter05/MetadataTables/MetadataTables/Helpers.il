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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------