.assembly extern mscorlib { }
.module Module1.mod
//-------------------------------------------------------------------------------------------------------
.class public CModule1
{
//-------------------------------------------------------------------------------------------------------
	.method static public void SimpleTest()
	{
		ldstr								"Hello from MODULE 1 !"
		call								void [mscorlib]System.Console::WriteLine(string)
		ret
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------