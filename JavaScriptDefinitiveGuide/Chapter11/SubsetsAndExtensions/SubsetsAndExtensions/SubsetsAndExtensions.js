//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	var															StringCommand="document.write(\"<p>Name: [Timmy] !</p>\")";

	// !!!!! FUNCTION eval() je VELMI CASTO NEPRISTUPNA zo SUBSETS, kedze ju SUBSET ANALYZATORY nedokazu ANALYZOVAT a okrem toho umoznuje spustit LUBOVOLNY, teda i potencialne UNSECURE KOD.
	eval(StringCommand);

	var															Result=eval("1+2");

    document.write("<p>Result: [" + Result + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	// !!! Aj ked 'const' je casto ako v EXTENSTIONS ako KEYWORD, JScript ho NEPODPORUJE.

	/*
	const PI=3.14;

    document.write("<p>PI: [" + PI + "] !</p>");
	*/
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
TestFunction1();
//TestFunction2();
//-------------------------------------------------------------------------------------------------------