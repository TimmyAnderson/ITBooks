//-------------------------------------------------------------------------------------------------------
function ReturnFunction(Value)
{
	if (Value==1)
	{
		return(100);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	// Vnorene OBJECT INITIALIZES.
	var															SuperObject=
	{
		SubObject1:
		{
			SomeProperty:										"Timmy"
		},

		SubObject2:
		{
			SomeProperty:										"Jenny"
		}
	};

    document.write("<p>SuperObject.SubObject1.SomeProperty: [" + SuperObject.SubObject1.SomeProperty + "] !</p>");
    document.write("<p>SuperObject.SubObject2.SomeProperty: [" + SuperObject.SubObject2.SomeProperty + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	// !!! JavaScript umoznuje za PROPERTY NAME dat i STRING.
	var															SomeObject=
	{
		NormalProperty:											10,
		"NotNormalProperty":									20
	};

    document.write("<p>SomeObject.NormalProperty: [" + SomeObject.NormalProperty + "] !</p>");
    document.write("<p>SomeObject.NotNormalProperty: [" + SomeObject.NotNormalProperty + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	var															SomeVariable="Jenny Thompson";

	// !!! JavaScript umoznuje za PROPERTY VALUE dat i VARIABLE.
	var															SomeObject=
	{
		SomeProperty:											SomeVariable
	};

    document.write("<p>SomeObject.SomeProperty: [" + SomeObject.SomeProperty + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	// !!! JavaScript umoznuje definovat MATICU pomocou vnorenia ARRAY INITIALIZERS.
	var															MyMatrix=[[1,2],[3,4,5],[6,7,8,9]];
	
	for (var Index1=0;Index1<MyMatrix.length;Index1++)
	{
	    document.write("<p>MATRIX ROW " + Index1 + ": [");

		for (var Index2=0;Index2<MyMatrix[Index1].length;Index2++)
		{
			if (Index2!=0)
			{
				document.write(",");
			}

			document.write(MyMatrix[Index1][Index2]);
		}

		document.write("] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	var															HalfEmptyArray1=[1,2,,,,6,7];

    document.write("<p>HalfEmptyArray1: [");

	for (var Index=0;Index<HalfEmptyArray1.length;Index++)
	{
		if (Index!=0)
		{
			document.write(",");
		}

		document.write(HalfEmptyArray1[Index]);
	}
	
	document.write("] !</p>");

	// !!! Ak je na KONCI ARRAY INITIALIZER 1, alebo VIACERO znakov ',', tak PRVY (iba PRVY) z NICH sa IGNORUJE a ostatne INDEXES obsahuje hodnotu 'undefined'.
	var															HalfEmptyArray2=[1,2,,,];

    document.write("<p>HalfEmptyArray2: [");

	for (var Index=0;Index<HalfEmptyArray2.length;Index++)
	{
		if (Index!=0)
		{
			document.write(",");
		}

		document.write(HalfEmptyArray2[Index]);
	}

	document.write("] !</p>");

	// !!! Ak je na KONCI ARRAY INITIALIZER 1, alebo VIACERO znakov ',', tak PRVY (iba PRVY) z NICH sa IGNORUJE a ostatne INDEXES obsahuje hodnotu 'undefined'.
	var															HalfEmptyArray3=[1,2,];

    document.write("<p>HalfEmptyArray3: [");

	for (var Index=0;Index<HalfEmptyArray3.length;Index++)
	{
		if (Index!=0)
		{
			document.write(",");
		}

		document.write(HalfEmptyArray3[Index]);
	}

	document.write("] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															SomeObject=
	{
		SomeProperty:											"Timmy"
	};

    document.write("<p>SomeObject.SomeProperty: [" + SomeObject.SomeProperty + "] !</p>");

	try
	{
		// !!! Pouzita SYNTAX [OBJECT[PROPERTY]].
		// !!!!! Toto NIE JE VALIDNA JavaScript SYNTAX a preto je hodena EXCEPTION.
		document.write("<p>SomeObject[SomeProperty]: [" + SomeObject[SomeProperty] + "] !</p>");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
	}

	// !!! Pouzita SYNTAX [OBJECT["PROPERTY"]].
	document.write("<p>SomeObject[\"SomeProperty\"]: [" + SomeObject["SomeProperty"] + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	// Vracia RETURN VALUE 100.
	var															CallReturn1=ReturnFunction(1);

	// !!! Nevracia ZIADNU RETURN VALUE a teda bude obsahovat hodnotu 'undefined'.
	var															CallReturn2=ReturnFunction(2);

    document.write("<p>CallReturn1: [" + CallReturn1 + "] !</p>");
    document.write("<p>CallReturn2: [" + CallReturn2 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	// !!! Vysledok EXPRESSION je 'NaN'.
	var															Result1=4*NaN;

	// !!! Vysledok EXPRESSION je 'Infinity'.
	var															Result2=4/0;

	// !!! Vysledok EXPRESSION je '-Infinity'.
	var															Result3=-4/0;

	// !!! Vysledok EXPRESSION je 'NaN'.
	var															Result4=0/0;

	// Vrati 1.5.
	var															Result5=3.5%2;

	// Vrati -1.5.
	var															Result6=-3.5%2;

	// !!! Vrati 1.5 a NIE -1.5.
	var															Result7=3.5%(-2);

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
    document.write("<p>Result6: [" + Result6 + "] !</p>");
    document.write("<p>Result7: [" + Result7 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	// ADDITION.
	var															Result1=1+2;
	// CONCATENATION, lebo aspon 1 OPERAND je STRING.
	var															Result2="1"+"2";
	// CONCATENATION, lebo aspon 1 OPERAND je STRING.
	var															Result3="1"+2;
	// CONCATENATION, lebo aspon 1 OPERAND je STRING.
	var															Result4=1+"2";
	// MULTIPLICATION, pretoze OPERATROR* (rovnako ako OPERATOR- a OPERATOR/ NEROBIA NIKDY CONCATENATION).
	var															Result5="1"*"2";
	// MULTIPLICATION, pretoze OPERATROR* (rovnako ako OPERATOR- a OPERATOR/ NEROBIA NIKDY CONCATENATION).
	var															Result6="1"*2;
	// MULTIPLICATION, pretoze OPERATROR* (rovnako ako OPERATOR- a OPERATOR/ NEROBIA NIKDY CONCATENATION).
	var															Result7=1*"2";
	// ADDITION.
	var															Result8=true+true;
	// CONCATENATION, lebo aspon 2. OPERAND typu OBJECT je KONVERTOVATELNY na STRING.
	var															Result9=1+{};
	// CONCATENATION, lebo aspon 2. OPERAND typu ARRAY je KONVERTOVATELNY na STRING.
	var															Result10=1+[];
	// CONCATENATION, lebo aspon 2. OPERAND typu ARRAY je KONVERTOVATELNY na STRING.
	var															Result11=1+[123];
	// CONCATENATION s PRVYM ITEM ARRAY.
	var															Result12=1+[123,456];
	// ADDITION - vysledok 1.
	var															Result13=1+null;
	// ADDITION - vysledok NaN.
	var															Result14=1+undefined;

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
    document.write("<p>Result6: [" + Result6 + "] !</p>");
    document.write("<p>Result7: [" + Result7 + "] !</p>");
    document.write("<p>Result8: [" + Result8 + "] !</p>");
    document.write("<p>Result9: [" + Result9 + "] !</p>");
    document.write("<p>Result10: [" + Result10 + "] !</p>");
    document.write("<p>Result11: [" + Result11 + "] !</p>");
    document.write("<p>Result12: [" + Result12 + "] !</p>");
    document.write("<p>Result13: [" + Result13 + "] !</p>");
    document.write("<p>Result14: [" + Result14 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	// OPERANDY su konvertovane na 32 BIT INTERGER NUMBERS.
	var															Result1=15.123 & 7;
	var															Result2=15.123 | 7;

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	// !!! Kedze OPERATOR== vykonava KONVERZIE, tak vysledok bude TRUE.
	var															Result1=(1=="1");
	// !!! Kedze OPERATOR== vykonava KONVERZIE (konvertuje ARRAY na INT), tak vysledok bude TRUE.
	var															Result2=(10==[10]);
	// !!! Kedze OPERATOR!= vykonava KONVERZIE (konvertuje ARRAY na INT), tak vysledok bude TRUE.
	var															Result3=(10!=[11]);
	// !!! Kedze OPERATOR== vykonava KONVERZIE (konvertuje ARRAY na INT) a ARRAY s VACSIM poctom ITEMS ako 1 sa meni na hodnotu 'NaN', tak vysledok bude FALSE.
	var															Result4=(10==[10,11,12]);
	// !!! Kedze OPERATOR=== NEVYKONAVA KONVERZIE, tak vysledok bude FALSE.
	var															Result5=(1==="1");
	// !!! Kedze OPERATOR=== NEVYKONAVA KONVERZIE, tak vysledok bude FALSE.
	var															Result6=(10===[10]);
	// !!! Kedze OPERATOR!== NEVYKONAVA KONVERZIE, tak vysledok bude TRUE.
	var															Result7=(10!==[11]);
	// !!! Kedze OPERATOR=== NEVYKONAVA KONVERZIE, tak vysledok bude FALSE.
	var															Result8=(10===[10,11,12]);
	
	var															Object1={X:1};
	var															Object2={X:1};

	// !!! Kedze sa porovnavaju REFERENCES, tak aj napriek tomu, ze OBJECTS obsahuju rovnake PROPERTIES, vysledok je FALSE.
	var															Result9=(Object1==Object2);
	// !!! Kedze sa porovnavaju REFERENCES, tak aj napriek tomu, ze OBJECTS obsahuju rovnake PROPERTIES, vysledok je FALSE.
	var															Result10=(Object1===Object2);

	var															Object3=Object1;

	// !!! Kedze sa porovnavaju REFERENCES, tak sa vrati TRUE.
	var															Result11=(Object1==Object3);
	// !!! Kedze sa porovnavaju REFERENCES, tak sa vrati TRUE.
	var															Result12=(Object1===Object3);

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
    document.write("<p>Result6: [" + Result6 + "] !</p>");
    document.write("<p>Result7: [" + Result7 + "] !</p>");
    document.write("<p>Result8: [" + Result8 + "] !</p>");
    document.write("<p>Result9: [" + Result9 + "] !</p>");
    document.write("<p>Result10: [" + Result10 + "] !</p>");
    document.write("<p>Result11: [" + Result11 + "] !</p>");
    document.write("<p>Result12: [" + Result12 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															Result1=("Jenny"<"Timmy");
	// !!! Vrati FALSE, pretoze ALFANUMERICKY je znak 'j' VACSI ako znak 'T'.
	var															Result2=("jenny"<"Timmy");
	// Vykona ALFANUMERICKE POROVNANIE.
	var															Result3=("22"<"111");
	// !!! Vykona NUMERICKE POROVNANIE.
	var															Result4=("22"<111);

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	var															Result1="X" in {X:1};
	var															Result2="X" in {Y:1};
	// !!! Kedze ARRAYS maju ako PROPERTIES INDEXY ITEMS, tak sa je nutme dotazovat na PROPERTIES s menami INDEXOV ITEMS.
	// !!! Vykonava sa KONVERZIA hodnoty '2' z INT na STRING.
	var															Result3=2 in [100,200,300];
	// !!! Kedze ARRAYS maju ako PROPERTIES INDEXY ITEMS, tak sa je nutme dotazovat na PROPERTIES s menami INDEXOV ITEMS.
	var															Result4="2" in [100,200,300];
	var															Result5="55" in [100,200,300];
	var															Result6="0" in [100,200,300];
	// !!! Kedze INDEX 1 je UNDEFINED, tak vraci FALSE.
	var															Result7="1" in [100,,,,200,300];

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
    document.write("<p>Result6: [" + Result6 + "] !</p>");
    document.write("<p>Result7: [" + Result7 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	var															Object1=[1,2,3];

	// !!! Vrati TRUE, lebo ARRAY je typu Array.
	var															Result1=Object1 instanceof Array;
	// !!! Vrati TRUE, lebo KAZDY OBJECT dedi z CLASS Object.
	var															Result2=Object1 instanceof Object;
	var															Result3=Object1 instanceof Number;

	var															Object2={X:1};

	var															Result4=Object2 instanceof Array;
	// !!! Vrati TRUE, lebo KAZDY OBJECT dedi z CLASS Object.
	var															Result5=Object2 instanceof Object;
	var															Result6=Object2 instanceof Number;

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
    document.write("<p>Result6: [" + Result6 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction15()
{
	// !!! Vracia hodnotu '100' a NIE 'true'.
	var															Result1=(100 || false);
	// !!! Vracia hodnotu '50' a NIE 'true'.
	var															Result2=(100 && 50);
	// !!! Vracia hodnotu 'null' a NIE 'true'.
	var															Result3=(null && 100);
	// !!! Kedze OPERATOR! VYKONAVA KONVERZIU na 'true', alebo 'false', tak vysledkom bude 'true'.
	var															Result4=(!null);
	// !!! Kedze OPERATOR! VYKONAVA KONVERZIU na 'true', alebo 'false', tak vysledkom bude 'false'.
	var															Result5=(!100);

    document.write("<p>Result1: [" + Result1 + "] !</p>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");
    document.write("<p>Result3: [" + Result3 + "] !</p>");
    document.write("<p>Result4: [" + Result4 + "] !</p>");
    document.write("<p>Result5: [" + Result5 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction16()
{
	var															StringCommand="document.write(\"<p>Name: [Timmy] !</p>\")";

	eval(StringCommand);

	// !!! RETURN VALUE eval() je hodnota POSLEDNEJ EXPRESSION v eval().
	var															Result=eval("1+2");

    document.write("<p>Result: [" + Result + "] !</p>");

	try
	{
		// !!! EXCEPTION je PROPAGOVANA von z eval().
		eval("throw(\"EXCEPTION in EVAL !!!\");");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
	}

	var															OuterVariable1;

	eval("OuterVariable1=66;");

    document.write("<p>OuterVariable1: [" + OuterVariable1 + "] !</p>");

	var															OuterVariable2;

	eval("function Internal(){return(10);} OuterVariable2=Internal();");

    document.write("<p>OuterVariable2: [" + OuterVariable2 + "] !</p>");

	try
	{
		// !!! Tento KOD HODI EXCEPTION, lebo kod v STRINGU zaslanom do EVAL NIE JE SUCASTOU VOLAJUCEJ FUNKCIE (TestFunction16()).
		eval("return;");

		document.write("<p>OK !!!</p>");
	}
	catch(Error)
	{
		document.write("<p>Error: [" + Error + "] !</p>");
	}

	var															EvalAlias=eval;
	var															ResultEvalAlias=EvalAlias("1+2");

    document.write("<p>ResultEvalAlias: [" + ResultEvalAlias + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction17()
{
	var															Type1=typeof(10);
	var															Type2=typeof(TestFunction17);
	var															Type3=typeof(undefined);
	// Vracia 'object'.
	var															Type4=typeof(null);
	// Vracia 'number'.
	var															Type5=typeof(NaN);
	// Vracia 'object'.
	var															Type6=typeof({X:1});
	// Vracia 'object'.
	var															Type7=typeof([1,2,3]);
	// Vracia 'object'.
	var															Type8=typeof(new Date());

    document.write("<p>Type1: [" + Type1 + "] !</p>");
    document.write("<p>Type2: [" + Type2 + "] !</p>");
    document.write("<p>Type3: [" + Type3 + "] !</p>");
    document.write("<p>Type4: [" + Type4 + "] !</p>");
    document.write("<p>Type5: [" + Type5 + "] !</p>");
    document.write("<p>Type6: [" + Type6 + "] !</p>");
    document.write("<p>Type7: [" + Type7 + "] !</p>");
    document.write("<p>Type8: [" + Type8 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction18()
{
	var															Variable1={X:1};

    document.write("<p>OPERATION delete(Variable1.X): [" + delete(Variable1.X) + "] !</p>");
	// !!! Vrati hodnotu UNDEFINED.
    document.write("<p>Variable1.X: [" + Variable1.X + "] !</p>");

	// !!! Aj ked PROPERTY NEEXISTUJE, tak RETURN VALUE 'delete' je UPLNE NELOGICKY TRUE.
    document.write("<p>OPERATION delete(Variable1.Y): [" + delete(Variable1.Y) + "] !</p>");

	var															Variable2=[10,20,30];

    document.write("<p>Variable2[2]: [" + Variable2[2] + "] !</p>");
    document.write("<p>Variable2.length: [" + Variable2.length + "] !</p>");

    document.write("<p>OPERATION delete(Variable2[2]): [" + delete(Variable2[2]) + "] !</p>");

	// !!! Variable2[2] vrati podla ocakavanie 'undefined'.
    document.write("<p>Variable2[2]: [" + Variable2[2] + "] !</p>");
	// !!! Vrati 3, aj ked by mal vratit 2. Asi je to zasa nejaka specialita IE.
    document.write("<p>Variable2.length: [" + Variable2.length + "] !</p>");

	// !!! Uplne NELOGICKY vracia 'true', aj ked INDEX 200 NEEXISTUJE.
    document.write("<p>OPERATION delete(Variable2[200]): [" + delete(Variable2[200]) + "] !</p>");

	// !!! Vracia 'false', pretoze LOCAL VARIABLES NIE JE MOZNE ODSTRANIT.	
    document.write("<p>OPERATION delete(Variable1): [" + delete(Variable1) + "] !</p>");

	// !!! Vracia 'false', pretoze FUNCTIONS NIE JE MOZNE ODSTRANIT.	
    document.write("<p>OPERATION delete(TestFunction18): [" + delete(TestFunction18) + "] !</p>");

	// !!! Vracia 'true'.
    document.write("<p>OPERATION delete(this): [" + delete(this) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction19()
{
	var															SomeFunction=function()
	{
	    document.write("<p>HELLO WORLD !</p>");
		
		return(100);
	};

    document.write("<p>SomeFunction(): [" + SomeFunction() + "] !</p>");

	// !!! Kedze som pouzil 'void', tak RETURN VALUE bude 'undefined'.	
    document.write("<p>void(SomeFunction()): [" + void(SomeFunction()) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction20()
{
	var															Var1;
	var															Var2;
	var															Var3;

	// !!! EXPRESSION [(Var1=100,Var2=200,Var3=300)] vracia hodnotu POSLEDNEHO OPERANDU, teda 300.
    document.write("<p>(Var1=100,Var2=200,Var3=300): [" + (Var1=100,Var2=200,Var3=300) + "] !</p>");
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
TestFunction20();
//-------------------------------------------------------------------------------------------------------