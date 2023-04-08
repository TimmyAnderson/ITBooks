//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	var															String="Hello world !";
	// !!!!! REGULAR EXPRESSION v JavaScript na SYNTAX [/RegularExpression/Flags].
	var															Pattern=new RegExp(/Hello/g);
	var															Result=Pattern.exec(String);

    document.write("<p>Returned value: [" + Result + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	var															String="Hello world !";
	var															Pattern=new RegExp(/Hello/g);
	var															Result=Pattern.test(String);

    document.write("<p>Returned value: [" + Result + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	var															String="Hello world !";
	var															Pattern=new RegExp(/Hello/g);

	Pattern.compile(Pattern);

	var															Result=Pattern.exec(String);

    document.write("<p>Returned value: [" + Result + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	var															String="Hello world !";
	// !!! SPECIALNA SYNTAX (STRING zacinajuci znakom '/', ktora vytvara INSTANCIU RegExp zo STRING.
	var															Pattern=/Hello/g;
	var															Result=Pattern.exec(String);

    document.write("<p>Returned value: [" + Result + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	var															String="Hello world !";
	// Najde STRING cez REGULAR EXPRESSION.
	var															Result1=String.search(/ll*/);
	// !!! Nenajde STRING cez REGULAR EXPRESSION.
	var															Result2=String.search(/xx*/);

    document.write("<p>Returned value 1: [" + Result1 + "] !</p>");
    document.write("<p>Returned value 2: [" + Result2 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															String="Hello world !";
	// Najde STRING cez REGULAR EXPRESSION.
	var															Result1=String.replace(/ll/g,"XXXXX");
	// !!! Nenajde STRING cez REGULAR EXPRESSION.
	var															Result2=String.replace(/xx/g,"XXXXX");

    document.write("<p>Returned value 1: [" + Result1 + "] !</p>");
    document.write("<p>Returned value 2: [" + Result2 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	var															String="Number 3, Number 2, Number 1 !";
	var															Results=String.match(/[0-9]/g);

	for(PropertyName in Results)
	{
		document.write("<p>VALUE [" + PropertyName + "]: [" + Results[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	var															String="Three 3, Two 2, One 1 !";
	var															Results=String.split(/[0-9]/g);

	for(PropertyName in Results)
	{
		document.write("<p>VALUE [" + PropertyName + "]: [" + Results[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//TestFunction1();
//TestFunction2();
//TestFunction3();
//TestFunction4();
//TestFunction5();
//TestFunction6();
//TestFunction7();
TestFunction8();
//-------------------------------------------------------------------------------------------------------