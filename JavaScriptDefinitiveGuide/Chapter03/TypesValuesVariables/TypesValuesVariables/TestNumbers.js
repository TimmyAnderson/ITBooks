//-------------------------------------------------------------------------------------------------------
var																GlobalVariableDeclaredByVar="GLOBAL by VAR";
// !!! Umyselne sa NEPOUZIJE 'var'.
																GlobalVariableDeclaredByDefinition="GLOBAL by DEFINITION";
// !!! Umyselne sa NEPOUZIJE 'var'.
																this.GlobalVariableDeclaredByThisDefinition="GLOBAL by THIS DEFINITION";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	// JavaScript NEROZLISUJE medzi INT a DOUBLE a VSETKY cisla povazuje za DOUBLE.
	var															Int=10;
	var															Double=10.123;
	var															Hex=0x10;
	// !!! Ci bude cislo reprezentovane ako OCTAL, alebo ako DECIMAL zavisi od KONKRETNEJ IMPLEMENTACIE JavaScript.
	// !!!!! JScript PODPORUJE OCTAL NUMBERS.
	var															OctalOrDecimal=0777;

    document.write("<p>VARIABLE - Int: [" + Int + "] !</p>");
    document.write("<p>VARIABLE - Double: [" + Double + "] !</p>");
    document.write("<p>VARIABLE - Hex: [" + Hex + "] !</p>");
    document.write("<p>VARIABLE - OctalOrDecimal: [" + OctalOrDecimal + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	var															MyArray=[];

	MyArray[0]="Timmy";
	MyArray[1000]="Atreyu";
	MyArray[-1000]="Jenny";
	MyArray[1000.55]="XXX";

    document.write("<p>MyArray.length: [" + MyArray.length + "] !</p>");

    document.write("<p>MyArray[0]: [" + MyArray[0] + "] !</p>");
    document.write("<p>MyArray[1000]: [" + MyArray[1000] + "] !</p>");
    document.write("<p>MyArray[-1000]: [" + MyArray[-1000] + "] !</p>");
    document.write("<p>MyArray[1000.55]: [" + MyArray[1000.55] + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
    document.write("<p>Math.cos(0): [" + Math.cos(0) + "] !</p>");
    document.write("<p>Math.random(): [" + Math.random() + "] !</p>");
    document.write("<p>Math.ceil(3.45): [" + Math.ceil(3.45) + "] !</p>");
    document.write("<p>Math.floor(3.45): [" + Math.floor(3.45) + "] !</p>");

    document.write("<p>1/0: [" + 1/0 + "] !</p>");
    document.write("<p>-1/0: [" + -1/0 + "] !</p>");
    document.write("<p>1/-0: [" + 1/-0 + "] !</p>");
    document.write("<p>-1/-0: [" + -1/-0 + "] !</p>");
    document.write("<p>0/0: [" + 0/0 + "] !</p>");
    document.write("<p>Math.sqrt(-4): [" + Math.sqrt(-4) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
    document.write("<p>Number.MAX_VALUE: [" + Number.MAX_VALUE + "] !</p>");
    document.write("<p>Number.MIN_VALUE: [" + Number.MIN_VALUE + "] !</p>");
    document.write("<p>Number.POSITIVE_INFINITY: [" + Number.POSITIVE_INFINITY + "] !</p>");
    document.write("<p>Number.NEGATIVE_INFINITY: [" + Number.NEGATIVE_INFINITY + "] !</p>");
    document.write("<p>Number.NaN: [" + Number.NaN + "] !</p>");

	// !!! Pouziva sa VARIABLE NaN.
    document.write("<p>NaN: [" + NaN + "] !</p>");
    document.write("<p>Infinity: [" + Infinity + "] !</p>");

	// !!! Nastastie sa hodnota Infinity NEZMENI, aj ked EXCEPTION NIE JE HODENA.
	Infinity=100;

    document.write("<p>Infinity: [" + Infinity + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	var															Value1=100/0;

	if (Value1==Number.POSITIVE_INFINITY)
	{
		document.write("<p>Value is INFINITY !</p>");
	}
	else
	{
		document.write("<p>Value is NOT INFINITY !</p>");
	}

	var															Value2=0/0;

	// !!! Toto porovnanie NEFUNGUJE.
	if (Value2==Number.NaN)
	{
		document.write("<p>Value is NaN !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NaN !</p>");
	}

	// !!! Toto porovnanie vsak UZ FUNGUJE.
	if (Value2!=Value2)
	{
		document.write("<p>Value is NaN !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NaN !</p>");
	}

	if (0==-0)
	{
		document.write("<p>0==-0 !</p>");
	}
	else
	{
		document.write("<p>0!=-0 !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															Date1=new Date(2012,0,1,15,0,0);
	var															Date2=new Date(2012,0,1,16,0,0);
	var															DateDiff=Date2-Date1;

    document.write("<p>Date1: [" + Date1 + "] !</p>");
    document.write("<p>Date2: [" + Date2 + "] !</p>");
    document.write("<p>DateDiff: [" + DateDiff + "] !</p>");
    document.write("<p>Date1.getUTCMonth(): [" + Date1.getUTCMonth() + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	var															MyString="Timmy";

    document.write("<p>MyString: [" + MyString + "] !</p>");
    document.write("<p>MyString.length: [" + MyString.length + "] !</p>");

	// !!! PROPERTY NIE JE WRITABLE.
	MyString.length=10;

    document.write("<p>MyString: [" + MyString + "] !</p>");
    document.write("<p>MyString.length: [" + MyString.length + "] !</p>");

    for (var Index=0;Index<MyString.length;Index++)
	{
	    document.write("<p>MyString[" + Index + "]: [" + MyString[Index] + "] !</p>");
	}

	// !!! Znak [\n] reprezentuje NEW LINE.
    document.write('<p>Timmy\nAnderson</p>');

	// !!! Medzi [''] je mozne vlozit ["].
    document.write('<p>DoubleQuote: ["XXX"] !</p>');
	// !!! Medzi [""] je mozne vlozit ['] aj cez ESCAPE SEQUENCE.
    document.write('<p>DoubleQuote be ESCAPE SEQUENCE: [\"XXX\"] !</p>');
	// !!! Medzi [""] je mozne vlozit ['].
    document.write("<p>Quote: ['XXX'] !</p>");
	// !!! Medzi [""] je mozne vlozit ['] aj cez ESCAPE SEQUENCE.
    document.write("<p>Quote be ESCAPE SEQUENCE: [\'XXX\'] !</p>");

    document.write("<p>MyString.toLowerCase(): [" + MyString.toLowerCase() + "] !</p>");
    document.write("<p>MyString.toUpperCase(): [" + MyString.toUpperCase() + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	var															Value;

    document.write("<p>Value: [" + Value + "] !</p>");

	if (Value==undefined)
	{
		document.write("<p>Value is UNDEFINED !</p>");
	}
	else
	{
		document.write("<p>Value is NOT UNDEFINED !</p>");
	}

	if (Value==null)
	{
		document.write("<p>Value is NULL !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NULL !</p>");
	}

	Value=100;

    document.write("<p>Value: [" + Value + "] !</p>");

	if (Value==undefined)
	{
		document.write("<p>Value is UNDEFINED !</p>");
	}
	else
	{
		document.write("<p>Value is NOT UNDEFINED !</p>");
	}

	if (Value==null)
	{
		document.write("<p>Value is NULL !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NULL !</p>");
	}

	Value=null;

    document.write("<p>Value: [" + Value + "] !</p>");

	if (Value==undefined)
	{
		document.write("<p>Value is UNDEFINED !</p>");
	}
	else
	{
		document.write("<p>Value is NOT UNDEFINED !</p>");
	}

	if (Value==null)
	{
		document.write("<p>Value is NULL !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NULL !</p>");
	}

	Value=undefined;

    document.write("<p>Value: [" + Value + "] !</p>");

	if (Value==undefined)
	{
		document.write("<p>Value is UNDEFINED !</p>");
	}
	else
	{
		document.write("<p>Value is NOT UNDEFINED !</p>");
	}

	if (Value==null)
	{
		document.write("<p>Value is NULL !</p>");
	}
	else
	{
		document.write("<p>Value is NOT NULL !</p>");
	}

	// Hodnoty 'null' a 'undefined' su v OPERATOR== IDENTICKE.
	if (null==undefined)
	{
		document.write("<p>NULL is EQUAL to UNDEFINED !</p>");
	}
	else
	{
		document.write("<p>NULL is NOT EQUAL to UNDEFINED !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															Value=100;

	// !!! METHOD isFinite() je definovana v GLOBAL objekte.
	if (isFinite(Value)==true)
	{
		document.write("<p>Value is FINITE !</p>");
	}
	else
	{
		document.write("<p>Value is NOT FINITE !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															Value=100;

	// !!! JavaScript vykona OBALENIE DATA TYPE NUMBER objektom Number.
	var															ValueAsString=Value.toString();

    document.write("<p>ValueAsString: [" + ValueAsString + "] !</p>");

	// !!! Dynamicky PRIDAM PROPERTY do DATA TYPE NUMBER. V skutocnosti sa PROPERTY 'XXX' prida IBA do TEMPORARY VARIABLE, ktora IHNED ZANIKNE.
	Value.XXX=333;

	// !!!!! Pri pokuse o vycitanie DYNAMICKY PRIRADENEJ PROPERTY 'XXX' sa vrati hodnota 'undefined', pretoze okolo NUMBER sa vytvorila NOVA INSTANCIA objektu Number, ktora NEMA PROPERTY 'XXX'.
    document.write("<p>Value.XXX: [" + Value.XXX + "] !</p>");

	// !!! Vyskusam pridanie DYNAMICKEJ PROPERTY do CUSTOM CLASS.
	var															MyClass=
	{
		SomeProperty: 100
	};

	var															MyClassAsString=MyClass.SomeProperty;

    document.write("<p>MyClassAsString: [" + MyClassAsString + "] !</p>");

	// !!! Teraz DYNAMICKY PRIDAM NOVU PROPERTY.
	MyClass.XXX=333;

	// !!!!! Kedze sa PROPERTY 'XXX' pridala do SKUTOCNEHO a NIE TEMPORARY objektu, tak jej hodnota je EXISTUJE.
    document.write("<p>MyClass.XXX: [" + MyClass.XXX + "] !</p>");

	// !!! EXPLICITNE sa vytvori objekt typu Number.
	var															ValueNumber=new Number(100);

	// !!! JavaScript tentoraz NEROBI OBALENIE.
	var															ValueNumberAsString=ValueNumber.toString();

    document.write("<p>ValueNumber: [" + ValueNumber + "] !</p>");

	// !!! Dynamicky PRIDAM PROPERTY do DATA TYPE NUMBER. Kedze sa jedna o SKUTOCNY a NIE WRAPPED objekt, tak sa PROPERTY pridava do REALNEHO a NIE TEMPORARY objekty.
	ValueNumber.XXX=333;

	// !!!!! PROPERTY 'XXX' je PLATNA, lebo ValueNumber je REALNY OBJEKT a NIE TEMPORARY WRAPPER.
    document.write("<p>ValueNumber.XXX: [" + ValueNumber.XXX + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															CustomClass1=
	{
		SomeProperty: "Timmy"
	}

	var															CustomClass2=
	{
		SomeProperty: "Timmy"
	}

	// !!! CUSTOM CLASSES sa porovnavaju BY REFERENCE.
	if (CustomClass1==CustomClass2)
	{
		document.write("<p>CustomClass1==CustomClass2 !</p>");
	}
	else
	{
		document.write("<p>CustomClass1!=CustomClass2 !</p>");
	}

	var															Array1=[];
	var															Array2=[];

	// !!! ARRAYS sa porovnavaju BY REFERENCE.
	if (Array1==Array2)
	{
		document.write("<p>Array1==Array2 !</p>");
	}
	else
	{
		document.write("<p>Array1!=Array2 !</p>");
	}

	var															String1="Timmy";
	var															String2="Timmy";

	// !!!!! Kedze STRINGS su PRIMITIVE TYPES porovnavaju sa BY VALUE.
	if (String1==String2)
	{
		document.write("<p>String1==String2 !</p>");
	}
	else
	{
		document.write("<p>String1!=String2 !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	// !!! Vracia TYP STRING, lebo OPERATOR+ je pre STRINGS PRETAZENY.
	var															Value1="7"+3;
	// !!! Vracia TYP STRING, lebo OPERATOR+ je pre STRINGS PRETAZENY.
	var															Value2=7+"3";
	// !!! Vracia TYP INT.
	var															Value3="7"*3;
	// !!! Vracia TYP INT.
	var															Value4=7*"3";
	// !!! Vracia NaN, lebo hodnota ["aaa"] NEPREDSTAVUJE STRING.
	var															Value5=7*"aaa";

    document.write("<p>Value1: [" + Value1 + "], Type: [" + typeof(Value1) + "] !</p>");
    document.write("<p>Value2: [" + Value2 + "], Type: [" + typeof(Value2) + "] !</p>");
    document.write("<p>Value3: [" + Value3 + "], Type: [" + typeof(Value3) + "] !</p>");
    document.write("<p>Value4: [" + Value4 + "], Type: [" + typeof(Value4) + "] !</p>");
    document.write("<p>Value5: [" + Value5 + "], Type: [" + typeof(Value5) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	// !!! JavaScript vykona IMPLICITNU KOVERZIU a vysledok je TRUE.
	if ("100"==100)
	{
		document.write("<p>EXPRESSION [\"100\"==100] is TRUE !</p>");
	}
	else
	{
		document.write("<p>EXPRESSION [\"100\"==100] is FALSE !</p>");
	}

	// !!! JavaScript vykona IMPLICITNU KOVERZIU a vysledok je TRUE.
	if (undefined==false)
	{
		document.write("<p>EXPRESSION [undefined==false] is TRUE !</p>");
	}
	else
	{
		document.write("<p>EXPRESSION [undefined==false] is FALSE !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	// !!! Vykonava sa KONVERZIA zo STRING na INT.
    document.write("<p>Number(\"100\"): [" + Number("100") + "] !</p>");

	var															Value=123.45;

    document.write("<p>Value.toFixed(5): [" + Value.toFixed(5) + "] !</p>");
    document.write("<p>Value.toExponential(5): [" + Value.toExponential(5) + "] !</p>");
    document.write("<p>Value.toPrecision(7): [" + Value.toPrecision(7) + "] !</p>");

	var															IntValue=100;

	// !!! Vypise cislo v HEXA tvare.
    document.write("<p>IntValue.toString(16): [" + IntValue.toString(16) + "] !</p>");

    document.write("<p>parseInt(Value): [" + parseInt(Value) + "] !</p>");
    document.write("<p>parseFloat(Value): [" + parseFloat(Value) + "] !</p>");

	// !!! Vrati NaN.
    document.write("<p>parseFloat(\"XXX\"): [" + parseFloat("XXX") + "] !</p>");

	// !!! Robi sa PARSING z HEXA hodnoty.
    document.write("<p>parseInt(\"0x41\",16): [" + parseInt("0x41",16) + "] !</p>");
    document.write("<p>parseInt(\"0xAA\",16): [" + parseInt("0xAA",16) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction15()
{
    document.write("<p>[1,2,3].toString(): [" + [1,2,3].toString() + "] !</p>");

	function MyFunction()
	{
	    document.write("<p>MyFunction() CALLED !</p>");
	}

	var															SomeFunction=MyFunction;

	// !!! Konverzia FUNCTION na STRING.
    document.write("<p>SomeFunction.toString(): [" + SomeFunction.toString() + "] !</p>");

	// Pouzitie valueOf().
    document.write("<p>SomeFunction.valueOf(): [" + SomeFunction.valueOf() + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction16()
{
	var															MyClass=
	{
		SomeProperty: "Timmy"
	};

    document.write("<p>MyClass: [" + MyClass + "] !</p>");

	var															MyClassWithToString=
	{
		SomeProperty: "Timmy"
	};

	function SomeToString()
	{
	    document.write("<p>SomeToString() CALLED - this.SomeProperty: [" + this.SomeProperty + "] !</p>");

		// !!! Vratim STRING, aj ked to nie je nevyhnutne nutne, ale najvhodnejsie.
		return(this.SomeProperty);
	}

	MyClassWithToString.toString=SomeToString;

	// !!! Zavola sa metoda MyClassWithToString.toString().
    document.write("<p>MyClassWithToString: [" + MyClassWithToString + "] !</p>");

	var															MyClassWithValueOf=
	{
		SomeProperty: "Timmy"
	};

	function SomeValueOf()
	{
	    document.write("<p>SomeValueOf() CALLED - this.SomeProperty: [" + this.SomeProperty + "] !</p>");

		// !!! Vratim PRIMITIVE VALUE, aj ked to nie je nevyhnutne nutne, ale najvhodnejsie.
		return(this.SomeProperty);
	}

	MyClassWithValueOf.valueOf=SomeValueOf;

	// !!! Zavola sa metoda MyClassWithValueOf.valueOf().
    document.write("<p>MyClassWithValueOf: [" + MyClassWithValueOf + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction17()
{
	var															MyClass=
	{
		SomeProperty: "Timmy"
	};

	var															MyClassToNumber=10*MyClass;

	// !!! Kedze NIE JE IMPLEMENTOVANY ani valueOf() ani toString(), tak sa hodi hodnota NaN.
    document.write("<p>MyClassToNumber: [" + MyClassToNumber + "] !</p>");

	var															MyClassWithToString=
	{
		SomeProperty: "Timmy"
	};

	function SomeToString()
	{
	    document.write("<p>SomeToString() CALLED - this.SomeProperty: [" + this.SomeProperty + "] !</p>");

		// !!! Vratim PRIMITIVE VALUE, ktora je konvertibilna na INT.
		return(20);
	}

	MyClassWithToString.toString=SomeToString;

	var															MyClassWithToStringToNumber=10*MyClassWithToString;

	// !!! Kedze je implementovany toString(), tak zavola tato metoda.
    document.write("<p>MyClassWithToStringToNumber: [" + MyClassWithToStringToNumber + "] !</p>");

	var															MyClassWithValueOf=
	{
		SomeProperty: "Timmy"
	};

	function SomeValueOf()
	{
	    document.write("<p>SomeValueOf() CALLED - this.SomeProperty: [" + this.SomeProperty + "] !</p>");

		// !!! Vratim PRIMITIVE VALUE, ktora je konvertibilna na INT.
		return(30);
	}

	MyClassWithValueOf.valueOf=SomeValueOf;

	var															MyClassWithValueOfToNumber=10*MyClassWithValueOf;

	// !!! Kedze je implementovany valueOf(), tak zavola tato metoda.
    document.write("<p>MyClassWithValueOfToNumber: [" + MyClassWithValueOfToNumber + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction18()
{
	var															Array1=[5];
	var															Array2=[5,6,7];
	var															Array3=[];

	// !!! Konvertuje ARRAY o velkost 1 na NUMBER.
	var															Value1=10*Array1;
	// !!! ARRAY o velkosti vacsej ako 1 JavaScript NEVIE KONVEROVAT na NUMBER a hodi hodnotu NaN.
	var															Value2=10*Array2;
	var															Value3=10*Array3;

    document.write("<p>Value1: [" + Value1 + "] !</p>");
    document.write("<p>Value2: [" + Value2 + "] !</p>");
    document.write("<p>Value3: [" + Value3 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction19()
{
	var															MyClassWithValueOf=
	{
		SomeProperty: "Timmy"
	};

	function SomeValueOf()
	{
	    document.write("<p>SomeValueOf() CALLED - this.SomeProperty: [" + this.SomeProperty + "] !</p>");

		// !!! Vratim PRIMITIVE VALUE, ktora je konvertibilna na INT.
		return(30);
	}

	MyClassWithValueOf.valueOf=SomeValueOf;

	// !!! Kedze je implementovany valueOf(), tak zavola tato metoda.
	var															MyClassWithValueOfToNumber=10*MyClassWithValueOf;

    document.write("<p>MyClassWithValueOfToNumber: [" + MyClassWithValueOfToNumber + "] !</p>");

    document.write("<p>-------------------------------------------------------------------------------------------------------</p>");

	// !!! Pre OPERATOR!= sa vola KONVERZNA METODA valueOf().
	if (MyClassWithValueOf!=100)
	{
	    document.write("<p>MyClassWithValueOf!=100 returns TRUE !</p>");
	}
	else
	{
	    document.write("<p>MyClassWithValueOf!=100 returns FALSE !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction20()
{
	var															Now=new Date();

	// !!! Konvertuje (Now+1) na STRING.
    document.write("<p>VALUE typeof(Now+1): [" + typeof(Now+1) + "] !</p>");
	// !!! Konvertuje (Now-1) na NUMBER.
    document.write("<p>VALUE typeof(Now+1): [" + typeof(Now-1) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction21()
{
	var															Variable1;

	// !!! Variable1 ma hodnotu 'undefined'.
    document.write("<p>Variable1: [" + Variable1 + "] !</p>");

	Variable1=111;

    document.write("<p>Variable1: [" + Variable1 + "] !</p>");

	// !!! JavaScript NEPREKAZA, ani ked deklaruje ROVNAKO POMENOVANU VARIABLE VIAC KRAT.
	var															Variable2=111;

    document.write("<p>Variable2: [" + Variable2 + "] !</p>");

	// !!! JavaScript povazuje tento kod za obycajne PRIRADENIE.
	var															Variable2=222;

    document.write("<p>Variable2: [" + Variable2 + "] !</p>");

	// !!!!! JavaScript umoznuje v NON-STRICT mode pouzit i VARIABLES, ktore su NEDEKLAROVANE. Z takychto VARIABLES JavaScript na pozadi vytvori PROPERTIES GLOBAL OBJECT.
	Variable3=333;

    document.write("<p>Variable3: [" + Variable3 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction22()
{
	var															Variable="GLOBAL";

    document.write("<p>Variable: [" + Variable + "] !</p>");

	function Internal()
	{
		var														Variable="LOCAL";

	    document.write("<p>Internal(): Variable: [" + Variable + "] !</p>");
	}

	Internal();

    document.write("<p>Variable: [" + Variable + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction23()
{
	var															Variable="Timmy";

	function Internal()
	{
		// !!! FUNCTION funguje ako CLOSURE a teda VARIABLES z OUTSIDE SCOPE su VIDITELNE.
	    document.write("<p>Internal(): Variable: [" + Variable + "] !</p>");
	}

	Internal();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction24()
{
	var															OuterVariable="OUTER";

	function Internal()
	{
		var														InnerVariable="INNER";

		// !!! FUNCTION funguje ako CLOSURE a teda VARIABLES z OUTSIDE SCOPE su VIDITELNE.
	    document.write("<p>Internal(): OuterVariable: [" + OuterVariable + "] !</p>");

	    document.write("<p>Internal(): InnerVariable: [" + InnerVariable + "] !</p>");
	}

	Internal();

	try
	{
		// !!! VARIABLE 'InnerVariable' je definovane v INNER FUNCTION, ktora ma VLASTNY SCOPE a teda v OUTER SCOPE je NEVIDITELNA.
		// !!!!! Kod hodi EXCEPTION.
		document.write("<p>InnerVariable: [" + InnerVariable + "] !</p>");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction25()
{
	// !!! VARIABLES Scope1, Scope2 a Scope3 su viditelne v CELEJ FUNCTION, aj ked Scope2 a Scope3 su deklarovane v INNER SCOPES a to dokonca i PRED DELAROVANIM.

	document.write("<p>Scope1: [" + Scope1 + "] !</p>");
	document.write("<p>Scope2: [" + Scope2 + "] !</p>");
	document.write("<p>Scope3: [" + Scope3 + "] !</p>");

	var															Scope1="SCOPE 1";

	if (1==1)
	{
		var														Scope2="SCOPE 2";
	
		if (1==1)
		{
			var													Scope3="SCOPE 3";
		}
	}	

	document.write("<p>Scope1: [" + Scope1 + "] !</p>");
	document.write("<p>Scope2: [" + Scope2 + "] !</p>");
	document.write("<p>Scope3: [" + Scope3 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction26()
{
	// !!! GlobalVariableDeclaredByVar, GlobalVariableDeclaredByDefinition a GlobalVariableDeclaredByThisDefinition su deklarovane na ZACIATKU SUBORU.
	document.write("<p>GlobalVariableDeclaredByVar: [" + GlobalVariableDeclaredByVar + "] !</p>");
	document.write("<p>GlobalVariableDeclaredByDefinition: [" + GlobalVariableDeclaredByDefinition + "] !</p>");
	document.write("<p>GlobalVariableDeclaredByThisDefinition: [" + this.GlobalVariableDeclaredByThisDefinition + "] !</p>");
	
	// !!! Operacia NEODSTRANI VARIABLE z PROPERTY LIST GLOBAL OBJECT.
	delete GlobalVariableDeclaredByVar;

	// !!! Operacia ODSTRANI VARIABLE z PROPERTY LIST GLOBAL OBJECT, lebo VARIABLE bola deklarovana BEZ KEYWORD 'var'.
	delete GlobalVariableDeclaredByDefinition;

	// !!! Operacia ODSTRANI VARIABLE z PROPERTY LIST GLOBAL OBJECT, lebo VARIABLE bola deklarovana BEZ KEYWORD 'var'.
	delete this.GlobalVariableDeclaredByThisDefinition;

	document.write("<p>GlobalVariableDeclaredByVar: [" + GlobalVariableDeclaredByVar + "] !</p>");

	try
	{
		document.write("<p>GlobalVariableDeclaredByDefinition: [" + GlobalVariableDeclaredByDefinition + "] !</p>");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
	}

	try
	{
		document.write("<p>this.GlobalVariableDeclaredByThisDefinition: [" + this.GlobalVariableDeclaredByThisDefinition + "] !</p>");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
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
//TestFunction25();
TestFunction26();
//-------------------------------------------------------------------------------------------------------