//-------------------------------------------------------------------------------------------------------
function TestFunction()
{
	// JavaScript je CASE SENSITIVE a je pisany VZDY v UNICODE.
	var															name="Atreyu";
	var															Name="Jenny";
	var															Ňame="Timmy";
	var															UnicodeChar="\u0041";
	// Toto je TIEZ STRING.
	var															StringLiteral='Timmy';

    document.write("<p>VARIABLE - name: [" + name + "] !</p>");
    document.write("<p>VARIABLE - Name: [" + Name + "] !</p>");
    document.write("<p>VARIABLE - Ňame: [" + Ňame + "] !</p>");
    document.write("<p>VARIABLE - UnicodeChar: [" + UnicodeChar + "] !</p>");
    document.write("<p>VARIABLE - StringLiteral: [" + StringLiteral + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
TestFunction();
//-------------------------------------------------------------------------------------------------------