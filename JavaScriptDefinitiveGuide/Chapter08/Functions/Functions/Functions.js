//-------------------------------------------------------------------------------------------------------
function GlobalFunction(ClosureFunction)
{
	// !!!!! Aj ked ClosureFunction() pristupuje k 'OutsideVariable', vdaka LEXICAL SCOPING je pristupna TA VARIABLE 'OutsideVariable', ktora bola definovana v SCOPE v ktorom bola ClosureFunction() DEFINOVANA.
	var															OutsideVariable="Jenny Thompson";

	// !!!!! FUNCTION vola CLOSURE a ta zobrazi LOCAL VARIABLE definovanu v INEJ FUNCTION.
	// !!!!! Toto volanie vypise text 'Timmy Anderson'.
	ClosureFunction();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	var															InnerFunction=function()
	{
		document.write("<p>InnerFunction.MyFunctionProperty: [" + InnerFunction.MyFunctionProperty + "] !</p>");
	};

	// !!! Do FUNCTION OBJECT pridam PROPERTY. Je to mozne preto, lebo FUNCTION je v JavaScript KLASICKYM OBJECT, ktory moze mat PROPERTIES i METHODS.
	InnerFunction.MyFunctionProperty="Timmy Anderson";

	InnerFunction();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	var															DoRecursion=true;

	var															InnerFunction1=function()
	{
		document.write("<p>Hello Function1 !</p>");
	};

	// !!! FUNCTION, ktora je priradena do VARIABLE je mozne priradit NAME.
	// !!!!! Takto pomenovanu FUNCTION cez svoje MENO (NamedFunction1()) NIE JE MOZNE VOLAT INDE ako REKURZIVNE vo VLASTOM TELE.
	var															InnerFunction2=function NamedFunction1()
	{
		document.write("<p>Hello Function2 !</p>");

		if (DoRecursion==true)
		{
			DoRecursion=false;

			// !!! Na REKURZIVNE VOLANIE je mozne pouzit NAME NamedFunction1().
			NamedFunction1();
		}
	};

	function NamedFunction2()
	{
		document.write("<p>Hello Function3 !</p>");
	};

	// !!! FUNCTION je mozne priradit do VARIABLE.
	var															InnerFunction3=NamedFunction2;

	InnerFunction1();
	InnerFunction2();
	InnerFunction3();

	// !!!!! HODI ECEPTION. FUNCTION, ktora ma NAME a ZAROVEN bola priradena do VARIABLE nie je cez jej NAME mozne volat INDE ako REKURZIVNE v ramci svojho tela.
	//NamedFunction1();

	NamedFunction2();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	function Function1(Param1,Param2)
	{
		function Function2()
		{
			// !!! NESTED FUNCTIONS mozu pristupovat k VARIABLES z OUTSIDE SCOPE.
			return(Param1+Param2);
		}

		return(Function2());
	}

	document.write("<p>Function1(10,2): [" + Function1(10,2) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	if (1==1)
	{
		// !!! JScript UMOZNUJE definovat FUNCTIONS i v LOOPS ci IF prikazoch.
		function Function1(Param1,Param2)
		{
			while(true)
			{
				function Function2()
				{
					// !!! NESTED FUNCTIONS mozu pristupovat k VARIABLES z OUTSIDE SCOPE.
					return(Param1+Param2);
				}

				break;
			}

			return(Function2());
		}

		document.write("<p>Function1(10,2): [" + Function1(10,2) + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	if (1==1)
	{
		// !!! FUNCTIONS definovane ako EXPRESSIONS je mozne definovat AJ v LOOPS ci IF prikazoch, kedze je to sucastou standardu ECMAScript.
		var														Function1=function(Param1,Param2)
		{
			while(true)
			{
				var												Function2=function()
				{
					// !!! NESTED FUNCTIONS mozu pristupovat k VARIABLES z OUTSIDE SCOPE.
					return(Param1+Param2);
				}

				break;
			}

			return(Function2());
		}

		document.write("<p>Function1(10,2): [" + Function1(10,2) + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															Variable="Timmy Anderson";

	// !!! FUNCTION je volana ako METHOD.
	document.write("<p>Variable.toUpperCase(): [" + Variable.toUpperCase() + "] !</p>");

	document.write("<hr/>");

	var															MyObject=
	{
		X: 100,

		MyMethod: function()
		{
			document.write("<p>VALUE - this.X: [" + this.X + "] !</p>");
		}
	};

	MyObject.MyMethod();

	// !!! METHOD je mozne volat AJ pomocou OPERATOR[].
	MyObject["MyMethod"]();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	var															MyFunction=function(Param1,Param2)
	{
		document.write("<p>Param1: [" + Param1 + "] !</p>");
		document.write("<p>Param2: [" + Param2 + "] !</p>");
	};

	MyFunction(10);

	document.write("<hr/>");

	MyFunction();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	var															MyFunction=function(Param1,Param2)
	{
		for(var Argument in arguments)
		{
			document.write("<p>ARGUMENT: [" + Argument + "], VALUE: [" + Argument + "] !</p>");
		}
	};

	MyFunction(10);

	document.write("<hr/>");

	MyFunction(10,20);

	document.write("<hr/>");

	MyFunction(10,20,30);

	document.write("<hr/>");

	MyFunction(10,20,30,40);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															MyFunction=function()
	{
		document.write("<p>VALUE - arguments.callee: [" + arguments.callee + "] !</p>");
		document.write("<hr/>");
		document.write("<p>VALUE - arguments.caller: [" + arguments.caller + "] !</p>");
	};

	MyFunction();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															MyCallbackFunction=function()
	{
		document.write("<p>MyCallbackFunction() CALLED !</p>");
	};

	var															MyFunction=function(CallbackFunction)
	{
		// !!! CALLBACK FUNCTION je preneseny do FUNCTION ako PARAMETER.
		CallbackFunction();
	};

	MyFunction(MyCallbackFunction);

	var															CallbackAlias=MyCallbackFunction;

	MyFunction(CallbackAlias);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															MyFunction=function()
	{
		document.write("<p>FUNCTION PROPERTY: [" + MyFunction.MyProperty + "] !</p>");

		MyFunction.MethodFunction();
	};

	// !!! FUNCTION sluzi ako METHOD FUNCTION OBJECT 'MyFunction()'.
	MyFunction.MethodFunction=function()
	{
		document.write("<p>MyFunction.MethodFunction() CALLED !</p>");
	}

	// !!! PROPERTY 'MyProperty' sluzi ako PROPERTY FUNCTION OBJECT 'MyFunction()'.
	MyFunction.MyProperty="Timmy Anderson";

	MyFunction.MethodFunction();

	MyFunction();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															OutsideVariable="Timmy Anderson";

	// !!! CLOSURE FUNCTION.
	var															ClosureFunction=function()
	{
		document.write("<p>OutsideVariable: [" + OutsideVariable + "] !</p>");
	};

	ClosureFunction();

	// !!!!! VARIABLE 'OutsideVariable' je PRISTUPNA i v GlobalFunction().
	GlobalFunction(ClosureFunction);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	function CreateClosure1(Param)
	{
		var														Closures=[];

		for(var Index=0;Index<3;Index++)
		{
			// !!!!! Vsetky CLOSURES ZDIELAJU hodnotu 'Param' a jej zmena sa premietne do VSETKYCH CLOSURES.
			Param++;

			var													Closure=function()
			{
				return(Param);
			}

			Closures[Index]=Closure;
		}

		return(Closures);
	}

	var															ClosuresArray1=CreateClosure1(10);

	for(var Index=0;Index<3;Index++)
	{
		// !!!!! Kedze 'Param' je ZDIELANA VARIABLE, tak VSETKY 3 volania ClosuresArray1[Index]() vrati hodnotu 13.
		document.write("<p>ClosuresArray1[" + Index + "](): [" + ClosuresArray1[Index]() + "] !</p>");
	}

	document.write("<hr/>");
	document.write("<hr/>");
	document.write("<hr/>");

	// !!!!! Kazda vytvorena CLOSURE ma VLASTNU HODNOTU Param.
	function CreateClosure2(Param)
	{
		var														Closure=function()
		{
			return(Param);
		}

		return(Closure);
	}

	var															ClosuresArray2=[];

	for(var Index=0;Index<3;Index++)
	{
		ClosuresArray2[Index]=CreateClosure2(10+Index);
	}

	for(var Index=0;Index<3;Index++)
	{
		// !!!!! Kedze 'Param' je NEZDIELANA VARIABLE, tak KAZDE VOLANIE ClosuresArray2[Index]() vrati INU HODNOTU.
		document.write("<p>ClosuresArray2[" + Index + "](): [" + ClosuresArray2[Index]() + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	var															InnerFunction=function(Param1,Param2,Param3)
	{
		// PROPERTY 'length' vracia pocet OCAKAVANYCH PARAMETROV.
		document.write("<p>VALUE InnerFunction.length: [" + InnerFunction.length + "] !</p>");
		document.write("<p>VALUE InnerFunction.prototype: [" + InnerFunction.prototype + "] !</p>");
	};

	InnerFunction(1,2,3,4,5);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction15()
{
	var															SomeContext={X:100};

	var															MyFunction=function(Param1,Param2)
	{
		document.write("<p>VALUE - Param1: [" + Param1 + "] !</p>");
		document.write("<p>VALUE - Param2: [" + Param2 + "] !</p>");
		document.write("<p>VALUE - this.X: [" + this.X + "] !</p>");
	};

	// !!! VARIABLE 'SomeContext' sa stane 'this' hodnotou v MyFunction().
	MyFunction.call(SomeContext,"XXX","YYY");

	document.write("<hr/>");

	// !!! PARAMETRE do MyFunction() sa prenasaju ako ARRAY.
	MyFunction.apply(SomeContext,["XXX","YYY"]);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction16()
{
	var															SomeContext={X:100};

	var															MyFunction=function(Param1,Param2)
	{
		document.write("<p>VALUE - Param1: [" + Param1 + "] !</p>");
		document.write("<p>VALUE - Param2: [" + Param2 + "] !</p>");
		document.write("<p>VALUE - this.X: [" + this.X + "] !</p>");
	};

	// !!! Z 2 PARAMETRICKEJ FUNCTION spravim 1 PARAMETRICKU.
	var															NewFunction=MyFunction.bind(SomeContext,200);

	NewFunction(300);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction17()
{
	// !!! Definujem FUNCTION cez CONSTRUCTOR.
	var															MyFunction=new Function("Param1","Param2","return(Param1+Param2);");

	document.write("<p>VALUE - MyFunction(100,200): [" + MyFunction(100,200) + "] !</p>");
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
TestFunction17();
//-------------------------------------------------------------------------------------------------------