//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	var															MyArray=[];

	// !!! Kedze ARRAYS su OBJECTS, tak pomocou OPERATOR[] je mozne pridavat aj PROPERTIES s INDEXMI, ktore su NON-INTEGER, ZAPORNE, alebo i STRINGS.
	MyArray[3]=111;
	MyArray[3.5]=222;
	MyArray[-4]=333;
	MyArray["Timmy"]=444;

	for(PropertyName in MyArray)
	{
		document.write("<p>INDEX: [" + PropertyName + "], VALUE: [" + MyArray[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	var															MyArray1=[1,2,3];

	document.write("<p>MyArray1: [" + MyArray1.length + "] !</p>");

	var															MyArray2=[];

	MyArray2[1]=111;
	MyArray2[50]=222;
	MyArray2[-50]=333;

	document.write("<p>MyArray2: [" + MyArray2.length + "] !</p>");

	var															MyArray3=new Array(35);

	document.write("<p>MyArray3: [" + MyArray3.length + "] !</p>");

	// !!! Array.length je WRITABLE PROPERTY a VSETKY ITEMS, ktore maju vyssi INDEX ako 'length' su ZMAZANE.
	MyArray3.length=20;

	document.write("<p>MyArray3: [" + MyArray3.length + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	var															MyArray=[1,2,3];

	for(PropertyName in MyArray)
	{
		document.write("<p>INDEX: [" + PropertyName + "], VALUE: [" + MyArray[PropertyName] + "] !</p>");
	}

	document.write("<p>MyArray: [" + MyArray.length + "] !</p>");

	delete(MyArray[1]);

	document.write("<hr/>");

	for(PropertyName in MyArray)
	{
		document.write("<p>INDEX: [" + PropertyName + "], VALUE: [" + MyArray[PropertyName] + "] !</p>");
	}

	document.write("<p>MyArray: [" + MyArray.length + "] !</p>");

	delete(MyArray[2]);

	document.write("<hr/>");

	for(PropertyName in MyArray)
	{
		document.write("<p>INDEX: [" + PropertyName + "], VALUE: [" + MyArray[PropertyName] + "] !</p>");
	}

	document.write("<p>MyArray: [" + MyArray.length + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	var															MyArray=[1,2,3];

	MyArray[5]=function()
	{
		document.write("XXXXXX");
	}

	for(PropertyName in MyArray)
	{
		document.write("<p>INDEX: [" + PropertyName + "], VALUE: [" + MyArray[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
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
function TestFunction6()
{
	var															MyArray=[1,2,3];
	var															Join1=MyArray.join();
	var															Join2=MyArray.join(" ");

	document.write("<p>Join1: [" + Join1 + "] !</p>");
	document.write("<p>Join2: [" + Join2 + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	var															MyArray=[1,2,3];

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	MyArray.reverse();

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	var															MyArray=[33,6,12];

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	// !!! Vykona ALPHANUMERIC SORT.
	MyArray.sort();

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															MyArray=[33,6,12];

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	var															NumericComparator=function(Param1,Param2)
	{
		if (Param1<Param2)
		{
			// Lubovolna ZAPORNA hodnota.
			return(-100);
		}
		else if (Param1>Param2)
		{
			// Lubovolna KLADNA hodnota.
			return(100);
		}
		else
		{
			return(0);
		}
	};

	// !!! Vykona SORT NUMBERIC VALUES.
	MyArray.sort(NumericComparator);

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															MyArray=[1,2,3];

	var															Concat1=MyArray.concat(4,5);

	for(var Index=0;Index<Concat1.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Concat1[Index] + "] !</p>");
	}

	// !!! ARRAY sa ROZLOZI a vysledkom bude 5 ITEMS.
	var															Concat2=MyArray.concat([4,5]);

	document.write("<hr/>");

	for(var Index=0;Index<Concat2.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Concat2[Index] + "] !</p>");
	}

	// !!! ROZLOZI sa iba 1. DIMENSION ARRAY budu ITEMS.
	var															Concat3=MyArray.concat([[4,5],[6,7]]);

	document.write("<hr/>");

	for(var Index=0;Index<Concat3.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Concat3[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															MyArray=[1,2,3,4,5];

	var															Slice1=MyArray.slice(1,4);

	for(var Index=0;Index<Slice1.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Slice1[Index] + "] !</p>");
	}

	// !!! Vrati ARRAY s INDEXAMI <LENGTH-3,5).
	var															Slice2=MyArray.slice(-3,5);

	document.write("<hr/>");

	for(var Index=0;Index<Slice2.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Slice2[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															MyArray=[1,2,3,4,5];

	// !!! Odstrani 1 ITEM na INDEXE 1 a vrati ARRAY s ODSTRANENYM ITEM.
	var															Splice1=MyArray.splice(1,1);

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	document.write("<hr/>");

	for(var Index=0;Index<Splice1.length;Index++)
	{
		document.write("<p>SPLICE1 - INDEX: [" + Index + "], VALUE: [" + Splice1[Index] + "] !</p>");
	}

	// !!! Prida ITEMS 11, 12 a 13 na INDEXE 2 a NEVYMAZE ZIADEN ITEM.
	var															Splice2=MyArray.splice(2,0,11,12,13);

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	document.write("<hr/>");

	// !!! ARRAY je PRAZDNE, pretoze sa ZIADEN ITEM NEODSTRANIL.
	for(var Index=0;Index<Splice2.length;Index++)
	{
		document.write("<p>SPLICE2 - INDEX: [" + Index + "], VALUE: [" + Splice2[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	var															MyArray=[1,2,3];

	MyArray.push(4,5);

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	document.write("<hr/>");

	document.write("<p>MyArray.pop(): [" + MyArray.pop() + "] !</p>");
	document.write("<p>MyArray.pop(): [" + MyArray.pop() + "] !</p>");

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	var															MyArray=[1,2,3];

	MyArray.unshift(4,5);

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}

	document.write("<hr/>");

	document.write("<p>MyArray.shift(): [" + MyArray.shift() + "] !</p>");
	document.write("<p>MyArray.shift(): [" + MyArray.shift() + "] !</p>");

	document.write("<hr/>");

	for(var Index=0;Index<MyArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MyArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction15()
{
	var															MyArray=[1,2,3];

	function Callback(Item, Index, Array)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + Item + "] !</p>");
	}

	MyArray.forEach(Callback);
}
//-------------------------------------------------------------------------------------------------------
function TestFunction16()
{
	var															MyArray=[1,2,3];

	function Callback(Item)
	{
		return(Item+100);
	}

	var															MapArray=MyArray.map(Callback);

	for(var Index=0;Index<MapArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + MapArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction17()
{
	var															MyArray=[1,2,3,,,4,5];

	function Predicate(Item)
	{
		if ((Item % 2)==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}

	var															FilterArray=MyArray.filter(Predicate);

	for(var Index=0;Index<FilterArray.length;Index++)
	{
		document.write("<p>INDEX: [" + Index + "], VALUE: [" + FilterArray[Index] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction18()
{
	var															MyArray=[1,2,3,4,5];

	function Predicate(Item)
	{
		if ((Item % 2)==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}

	document.write("<p>MyArray.some(Predicate): [" + MyArray.some(Predicate) + "] !</p>");
	document.write("<p>MyArray.every(Predicate): [" + MyArray.every(Predicate) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction19()
{
	var															MyArray=[1,2,3,4,5];

	function Aggregation(AggregatedValue,Item)
	{
		var														ReturnValue=(AggregatedValue+Item)/2;

		document.write("<p>ReturnValue: [" + ReturnValue + "] !</p>");

		return(ReturnValue);
	}

	document.write("<p>MyArray.reduce(Aggregation): [" + MyArray.reduce(Aggregation) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction20()
{
	var															MyArray=[1,2,3,4,5];

	function Aggregation(AggregatedValue,Item)
	{
		var														ReturnValue=(AggregatedValue+Item);

		document.write("<p>ReturnValue: [" + ReturnValue + "] !</p>");

		return(ReturnValue);
	}

	// Definoval som aj INITIAL VALUE.
	document.write("<p>MyArray.reduceRight(Aggregation,10): [" + MyArray.reduceRight(Aggregation,10) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction21()
{
	var															MyArray=[1,2,3,4,5];

	document.write("<p>MyArray.indexOf(4): [" + MyArray.indexOf(4) + "] !</p>");
	document.write("<p>MyArray.lastIndexOf(50): [" + MyArray.lastIndexOf(50) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction22()
{
	var															Object1=[1,2,3,4,5];
	var															Object2=3;
	var															Object3={X:1};

	document.write("<p>Array.isArray(Object1): [" + Array.isArray(Object1) + "] !</p>");
	document.write("<p>Array.isArray(Object2): [" + Array.isArray(Object2) + "] !</p>");
	document.write("<p>Array.isArray(Object3): [" + Array.isArray(Object3) + "] !</p>");
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
TestFunction22();
//-------------------------------------------------------------------------------------------------------