//-------------------------------------------------------------------------------------------------------
function Exception1()
{
	try
	{
	    document.write("<p>Exception1 TRY !</p>");

		throw("SUPER ERROR !");
	}
	finally
	{
	    document.write("<p>Exception1 FINALLY !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function Exception2()
{
	try
	{
	    document.write("<p>Exception2 TRY !</p>");

		throw("SUPER ERROR !");
	}
	catch(Exception)
	{
	    document.write("<p>Exception2 CATCH - Exception: [" + Exception + "] !</p>");
	}
	finally
	{
	    document.write("<p>Exception2 FINALLY !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function Exception3()
{
	try
	{
	    document.write("<p>Exception3 TRY !</p>");

		throw("SUPER ERROR !");
	}
	catch(Exception)
	{
	    document.write("<p>Exception3 CATCH - Exception: [" + Exception + "] !</p>");
		throw(Exception);
	}
	finally
	{
	    document.write("<p>Exception3 FINALLY !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function Exception4()
{
	try
	{
	    document.write("<p>Exception4 TRY !</p>");

		throw("SUPER ERROR !");
	}
	finally
	{
	    document.write("<p>Exception4 FINALLY !</p>");

		// !!!!! Prikaz RETURN vo FINALLY VZDY POHLTI EXCEPTION a tato NIE JE DALEJ PROPAGOVANA.
		return;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	var															Variable=5;

	// !!! EXPRESSION, kedze ma SIDE EFFECT (meni hodnotu 'Variable') je povazovana tiez za STATEMENT.
	Variable=3*(Variable*=2);

    document.write("<p>Variable: [" + Variable + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	// !!! K 'Variable' mozem pristuput dokonca i PRED JEJ DEKLARACIOU, kedze COMPOUND STATEMENT NEDEKLARUJE VLASTNY SCOPE.
    document.write("<p>Variable: [" + Variable + "] !</p>");

	if (1==1)
	{
		var															Variable="INSIDE";
	}

	// !!! Kedze COMPOUND STATEMENT NEDEKLARUJE VLASTNY SCOPE, tak k 'Variable' deklarovanej v COMPOUND STATEMENT MOZEM pristupi i MIMO COMPOUND STATEMENT.
    document.write("<p>Variable: [" + Variable + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	// !!! Lokalna FUNCTION priradena do VARIABLE NEMA MENO.
	var															LocalFunction=function()
	{
	    document.write("<p>Text from LOCAL FUNCTION !</p>");
	}

	LocalFunction();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	// !!! Lokalna FUNCTION priradena do VARIABLE NEMA MENO.
	var															LocalFunction1=function()
	{
		// !!! NESTED FUNCTION musi byt deklarovana VZDY v TOP SCOPE FUNCTION v ktorej je NESTED.
		var														LocalFunction2=function()
		{
		    document.write("<p>Text from LOCAL FUNCTION 2 !</p>");
		}

	    document.write("<p>Text from LOCAL FUNCTION 1 !</p>");

		LocalFunction2();
	}

	LocalFunction1();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	// !!! Lokalna FUNCTION priradena do VARIABLE NEMA MENO.
	var															LocalFunction1=function()
	{
		if (1==1)
		{
			// !!! NESTED FUNCTION musi byt deklarovana VZDY v TOP SCOPE FUNCTION v ktorej je NESTED.
			// !!!!! JScript toto PODPORUJE, ale jedna sa o NON-PORTABLE FEATURE.
			var													LocalFunction2=function()
			{
				document.write("<p>Text from LOCAL FUNCTION 2 !</p>");
			}
		}

	    document.write("<p>Text from LOCAL FUNCTION 1 !</p>");

		LocalFunction2();
	}

	LocalFunction1();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	function LocalFunction1()
	{
		if (1==1)
		{
			// !!! NESTED FUNCTION musi byt deklarovana VZDY v TOP SCOPE FUNCTION v ktorej je NESTED.
			// !!!!! JScript toto PODPORUJE, ale jedna sa o NON-PORTABLE FEATURE.
			function LocalFunction2()
			{
				document.write("<p>Text from LOCAL FUNCTION 2 !</p>");
			}
		}

	    document.write("<p>Text from LOCAL FUNCTION 1 !</p>");

		LocalFunction2();
	}

	LocalFunction1();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	try
	{
		// !!!!! FUNCTION deklarovanu ako VARIABLE NIE JE mozne pouzit PRED DEKLARACIOU. Prikaz hodi EXCEPTION !
		LocalFunction1();

		// !!! Lokalna FUNCTION priradena do VARIABLE NEMA MENO.
		var															LocalFunction1=function()
		{
			// !!! FUNCTION je mozne pouzit i PRED DEKLARACIOU.
			document.write("<p>Text from LOCAL FUNCTION 1 !</p>");

			// !!!!! FUNCTION deklarovanu ako VARIABLE NIE JE mozne pouzit PRED DEKLARACIOU. Prikaz hodi EXCEPTION !
			LocalFunction2();

			if (1==1)
			{
				// !!! NESTED FUNCTION musi byt deklarovana VZDY v TOP SCOPE FUNCTION v ktorej je NESTED.
				// !!!!! JScript toto PODPORUJE, ale jedna sa o NON-PORTABLE FEATURE.
				var													LocalFunction2=function()
				{
					document.write("<p>Text from LOCAL FUNCTION 2 !</p>");
				}
			}
		}
	}
	catch(Error)
	{
	    document.write("<p>Error: [" + Error + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	// !!! FUNCTION deklarovanu ako NESTED FUNCTION je mozne pouzit i PRED DEKLARACIOU.
	LocalFunction1();

	function LocalFunction1()
	{
	    document.write("<p>Text from LOCAL FUNCTION 1 !</p>");

		// !!! FUNCTION deklarovanu ako NESTED FUNCTION je mozne pouzit i PRED DEKLARACIOU.
		LocalFunction2();

		if (1==1)
		{
			// !!! NESTED FUNCTION musi byt deklarovana VZDY v TOP SCOPE FUNCTION v ktorej je NESTED.
			// !!!!! JScript toto PODPORUJE, ale jedna sa o NON-PORTABLE FEATURE.
			function LocalFunction2()
			{
				document.write("<p>Text from LOCAL FUNCTION 2 !</p>");
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															Variable1=1;

	switch(Variable1)
	{
		case 1:
		{
			document.write("<p>CASE 1 !</p>");
		}
		break;

		default:
		{
			document.write("<p>DEFAULT !</p>");
		}
		break;
	}

	var															Variable2=1;

	// !!! Kedze sa pouziva OPERATOR===, tak nasledujuci SWITCH skoci na DEFAULT a NIE na [case "1"].
	switch(Variable2)
	{
		case "1":
		{
			document.write("<p>CASE 1 !</p>");
		}
		break;

		default:
		{
			document.write("<p>DEFAULT !</p>");
		}
		break;
	}

	function CaseTest(Value)
	{
	    document.write("<p>CaseTest() with VALUE [" + Value + "] CALLED !</p>");

		return(Value);
	}

	var															Variable3=2;

	switch(Variable3)
	{
		// !!! V 'case' BLOCKS mozu byt LUBOVOLNE EXPRESSIONS a teda aj VOLANIA FUNCTIONS.
		case CaseTest(1):
		{
			document.write("<p>CASE 1 !</p>");
		}
		break;

		case CaseTest(2):
		{
			document.write("<p>CASE 2 !</p>");
		}
		break;

		default:
		{
			document.write("<p>DEFAULT !</p>");
		}
		break;
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															CustomObject=
	{
		X: 100,
		Y: 200,

		// !!! V CUSTOM OBJECTS sa ENUMERUJU AJ METHODS.
		MyFunction: function()
		{
			document.write("<p>MyFunction() CALLED !</p>");
		}
	};

	for(var PropertyName in CustomObject)
	{
	    document.write("<p>PropertyName: [" + PropertyName + "] !</p>");
	    document.write("<p>CustomObject[Property]: [" + CustomObject[PropertyName] + "] !</p>");

		// !!! Hodi UNDEFINED.
	    document.write("<p>CustomObject.PropertyName: [" + CustomObject.PropertyName + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															CustomObject="Timmy";

	// !!!!! V BUILT-IN OBJECTS sa METHODS NEENUMERUJU, pretoze su NON-ENUMERABLE.
	// !!! OBJECT String ma napriklad METHOD indexOf(), ale kedze ta je BUILT-IN METHOD, sa sa NEENUMERUJE.
	for(var PropertyName in CustomObject)
	{
	    document.write("<p>PropertyName: [" + PropertyName + "] !</p>");
	    document.write("<p>CustomObject[Property]: [" + CustomObject[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															CustomObject=[1,2,3];

	for(var PropertyName in CustomObject)
	{
	    document.write("<p>PropertyName: [" + PropertyName + "] !</p>");
	    document.write("<p>CustomObject[Property]: [" + CustomObject[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	var															CustomObject=[];

	CustomObject[50]=1;
	CustomObject[100]=2;

	for(var PropertyName in CustomObject)
	{
	    document.write("<p>PropertyName: [" + PropertyName + "] !</p>");
	    document.write("<p>CustomObject[Property]: [" + CustomObject[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	var															CustomObject=[];

	CustomObject[50]=1;
	CustomObject[100]=2;

	var															Index=0;
	var															MyArray=[];

	// !!!!! Za 'VARIABLE' vo 'for-in' mozem dosadit i lubovolny EXPRESSION, ktory sa evaluuje na LVALUE.
	for(MyArray[Index++] in CustomObject)
	{
	    document.write("<p>MyArray[Index-1]: [" + MyArray[Index-1] + "] !</p>");
	    document.write("<p>CustomObject[MyArray[Index-1]]: [" + CustomObject[MyArray[Index-1]] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction15()
{
	// !!! LABEL musi byt definovany SKOR ako sa pouzije v prikaze 'break'.
	EndLabel:
	for (var Index1=0;Index1<5;Index1++)
	{
		for (var Index2=0;Index2<5;Index2++)
		{
		    document.write("<p>Index1: [" + Index1 + "], Index2: [" + Index2 + "] !</p>");

			if (Index1==2 && Index2==1)
			{
				// !!!!! Kedze SKOK na 'EndLabel' cez 'break' znamena skocenie na KONIEC STATEMENT, ktory je oznaceny tymto LABEL, tak prakticky to znamena, ze nasledujuci 'break' sposobi ukoncenie OBOCH CYKLOV.
				break EndLabel;
			}
		}
	}

	document.write("<p>END of LOOP !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction16()
{
	for (var Index1=0;Index1<5;Index1++)
	{
		// !!! LABEL musi byt definovany SKOR ako sa pouzije v prikaze 'break'.
		EndLabel:
		for (var Index2=0;Index2<5;Index2++)
		{
			for (var Index3=0;Index3<5;Index3++)
			{
				document.write("<p>Index1: [" + Index1 + "], Index2: [" + Index2 + "], Index3: [" + Index3 + "] !</p>");

				if (Index2==1)
				{
					document.write("<p>BREAK !!!</p>");
					// !!!!! Kedze SKOK na 'EndLabel' cez 'break' znamena skocenie na KONIEC STATEMENT, ktory je oznaceny tymto LABEL, tak prakticky to znamena, ze nasledujuci 'break' sposobi ukoncenie 2 CYKLOV a vrati sa do NAJVYSSIEHO.
					break EndLabel;
				}
			}
		}
	}

	document.write("<p>END of LOOP !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction17()
{
	IfLabel:
	if (1==1)
	{
		document.write("<p>STEP 1 !</p>");

		// !!! Vyskoci sa na KONIEC STATEMENT oznaceneho danym LABEL. V tomto pripade to znaci ze skok sa vykona na KONIEC prikazu 'if'.
		break IfLabel;

		document.write("<p>STEP 2 !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction18()
{
	// !!! LABEL musi byt definovany SKOR ako sa pouzije v prikaze 'break'.
	EndLabel:
	for (var Index1=0;Index1<3;Index1++)
	{
		for (var Index2=0;Index2<3;Index2++)
		{
			if (Index1==1 && Index2==1)
			{
				document.write("<p>CONTINUE !!!</p>");

				// !!!!! Kedze SKOK na 'EndLabel' cez 'continue' znamena skocenie na ZACIATOK STATEMENT, ktory je oznaceny tymto LABEL, tak prakticky to znamena, ze nasledujuci 'continue' VYSKOCI z INNER LOOP a skoci na DALSIU ITERACIU OUTER LOOP.
				continue EndLabel;
			}

		    document.write("<p>Index1: [" + Index1 + "], Index2: [" + Index2 + "] !</p>");
		}
	}

	document.write("<p>END of LOOP !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction19()
{
	try
	{
		document.write("<p>BEFORE method CALL !</p>");

		Exception1();

		document.write("<p>AFTER method CALL !</p>");
	}
	catch(Exception)
	{
	    document.write("<p>TEST CATCH - Exception: [" + Exception + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction20()
{
	try
	{
		document.write("<p>BEFORE method CALL !</p>");

		Exception2();

		document.write("<p>AFTER method CALL !</p>");
	}
	catch(Exception)
	{
	    document.write("<p>TEST CATCH - Exception: [" + Exception + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction21()
{
	try
	{
		document.write("<p>BEFORE method CALL !</p>");

		Exception3();

		document.write("<p>AFTER method CALL !</p>");
	}
	catch(Exception)
	{
	    document.write("<p>TEST CATCH - Exception: [" + Exception + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction22()
{
	try
	{
		document.write("<p>BEFORE method CALL !</p>");

		Exception4();

		document.write("<p>AFTER method CALL !</p>");
	}
	catch(Exception)
	{
	    document.write("<p>TEST CATCH - Exception: [" + Exception + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction23()
{
	var															MyObject=
	{
		X: 100,
		Y: 200
	};

	var															Z=300;

	with(MyObject)
	{
		// !!! Inkrementuje MyObject.X.
		X++;
		// !!! Inkrementuje MyObject.Y.
		Y++;
		// !!! Inkrementuje Z, pretoze 'MyObject' NEOBSAHUJE PROPERY 'Z'.
		Z++;
	}

	with(MyObject)
	{
	    document.write("<p>MyObject.X: [" + MyObject.X + "] !</p>");
	    document.write("<p>MyObject.Y: [" + MyObject.Y + "] !</p>");
	    document.write("<p>Z: [" + Z + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction24()
{
	document.write("<p>STEP 1 !</p>");
	
	debugger;

	document.write("<p>STEP 2 !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction25()
{
	var															HasStrictMode=function()
	{
		"use strict";

		return(this==undefined);
	};

	// !!!!! Vracia FALSE, pretoze STRICT MODE je podporovany AZ od verzie IE 10.0.. Tato informacia je PRIAMO s MSDN.
    document.write("<p>HasStrictMode(): [" + HasStrictMode() + "] !</p>");
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
//TestFunction8();
//TestFunction9();
//TestFunction10();
//TestFunction11();
//TestFunction12();
//TestFunction13();
//TestFunction14();
//TestFunction15();
//TestFunction16();
//TestFunction17();
//TestFunction18();
//TestFunction19();
//TestFunction20();
//TestFunction21();
//TestFunction22();
//TestFunction23();
//TestFunction24();
TestFunction25();
//-------------------------------------------------------------------------------------------------------