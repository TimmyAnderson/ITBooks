//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	// OBJECT vytvoreny ako LITERAL.
	var															ObjectLiteral=
	{
		FirstName: "Timmy",
		LastName: "Anderson"
	};

    document.write("<p>Name: [" + ObjectLiteral.FirstName + " " + ObjectLiteral.LastName + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	// OBJECT je vytvoreny volanim CONSTRUCTOR.
	var															DateObject=new Date();

    document.write("<p>Date: [" + DateObject.getDate() + "-" + (1+DateObject.getMonth()) + "-" + DateObject.getFullYear() + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
    document.write("<p>Date.prototype: [" + Date.prototype + "] !</p>");
    document.write("<p>Date.constructor.prototype: [" + Date.constructor.prototype + "] !</p>");

	var															ObjectLiteral=
	{
		FirstName: "Timmy",
		LastName: "Anderson"
	};

    document.write("<p>Object.getPrototypeOf(ObjectLiteral): [" + Object.getPrototypeOf(ObjectLiteral) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	// !!! Pomocou FUNCTION Object.create() je takisto mozne vytvorit novy OBJECT.
	var															MyObject=Object.create({X:100});

    document.write("<p>MyObject.X: [" + MyObject.X + "] !</p>");
    document.write("<p>Object.getPrototypeOf(MyObject): [" + Object.getPrototypeOf(MyObject) + "] !</p>");

	var															MyDerivedObject=Object.create(Object.prototype);
	
    document.write("<p>MyDerivedObject: [" + MyDerivedObject + "] !</p>");
    document.write("<p>Object.getPrototypeOf(MyDerivedObject): [" + Object.getPrototypeOf(MyDerivedObject) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	var															ObjectLiteral=
	{
		FirstName: "Timmy",
		LastName: "Anderson"
	};

	// !!! Prida NOVU PROPERTY do OBJECT.
	ObjectLiteral.Age=12;

	// !!! Prikaz ukazuje OBE SYNTAXE na pristup k PROPERTIES.
    document.write("<p>Name: [" + ObjectLiteral.FirstName + " " + ObjectLiteral["LastName"] + "], Age: [" + ObjectLiteral.Age + "] !</p>");

	document.write("<hr/>");

	var															PropertyNames=["FirstName","LastName","Age"];

	// !!! Vypis vsetkych PROPERTIES podla ich NAME.
	for(var Index=0;Index<PropertyNames.length;Index++)
	{
	    document.write("<p>PROPERTY: [" + PropertyNames[Index] + "], VALUE: [" + ObjectLiteral[PropertyNames[Index]] + "] !</p>");
	}

	document.write("<hr/>");

	// !!! Vypis PROPERTIES cez 'for-in' prikaz.
	for(var PropertyName in ObjectLiteral)
	{
	    document.write("<p>PROPERTY: [" + PropertyName + "], VALUE: [" + ObjectLiteral[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															BaseObject={X:1};
	// !!! Vykonam DEDENIE z OBJECT 'BaseObject'.
	var															DerivedObject=Object.create(BaseObject);

	// !!! Pridam novu PROPERTY do 'DerivedObject'.
	DerivedObject.Y=2;

    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	document.write("<hr/>");
    document.write("<p>BaseObject.Y: [" + BaseObject.Y + "] !</p>");
    document.write("<p>DerivedObject.Y: [" + DerivedObject.Y + "] !</p>");
	
	// !!!!! Zmeni sa IBA hodnota DerivedObject.X. Je to preto, lebo pridanim PROPERTY DerivedObject.X sa PROPERTY BaseObject.X stala HIDDEN. Teda de-facto budu existovat 2 PROPERTIES 'X', jedna v 'BaseObject' a jedna v 'DerivedObject'.
	DerivedObject.X+=100;

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	// !!! Zmeni sa IBA hodnota BaseObject.X.
	BaseObject.X+=100;

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	// !!! Zmeni sa IBA hodnota DerivedObject.X.
	DerivedObject.X+=100;

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	var															BaseObject={X:1};
	// !!! Vykonam DEDENIE z OBJECT 'BaseObject'.
	var															DerivedObject=Object.create(BaseObject);

	// !!! Pridam novu PROPERTY do 'DerivedObject'.
	DerivedObject.Y=2;

    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	document.write("<hr/>");
    document.write("<p>BaseObject.Y: [" + BaseObject.Y + "] !</p>");
    document.write("<p>DerivedObject.Y: [" + DerivedObject.Y + "] !</p>");

	// !!! Pridam novu PROPERTY do 'BaseObject'. PROPERTY sa vdaka INHERITANCE prida i do DERIVED OBJECT.
	BaseObject.Z=3;

	document.write("<hr/>");
    document.write("<p>BaseObject.Z: [" + BaseObject.Z + "] !</p>");
    document.write("<p>DerivedObject.Z: [" + DerivedObject.Z + "] !</p>");

	// Stav OBJECTS [BaseObject.X ma hodnotu 1], [DerivedObject.X NEEXISTUJE].
	// !!!!! Kedze DerivedObject.X NEEXISTUJE, zmeni sa hodnota BaseObject.X
	BaseObject.X+=100;
	// Stav OBJECTS [BaseObject.X ma hodnotu 101], [DerivedObject.X NEEXISTUJE].

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	// Stav OBJECTS [BaseObject.X ma hodnotu 101], [DerivedObject.X NEEXISTUJE].
	// !!!!! Kedze DerivedObject.X NEEXISTUJE, tak sa prida NOVA PROPERTY DerivedObject.X s hodnotou 201. Hodnota 201 je preto, lebo PRED ZAPISOM (a vytvorenim) DerivedObject.X OPERATOR+= NAJPRV CITAL HODNOTU DerivedObject.X a kedze ta este NEEXISTOVALA vratit hodnotu BaseObject.X, ktora mala hodnotu 101. Po INKREMENTACII o 100 sa hodnota DerivedObject.X nastavila na 201.
	DerivedObject.X+=100;
	// Stav OBJECTS [BaseObject.X ma hodnotu 101], [DerivedObject.X ma hodnotu 201].

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	// Stav OBJECTS [BaseObject.X ma hodnotu 101], [DerivedObject.X 201].
	// !!!!! Kedze hodnota BaseObject.X EXISTUJE, tak je INKREMENTOVANA o 100. Hodnota DerivedObject.X sa vsak NEMENI, kedze EXISTUJU 2 NEZAVISLE PROPERTIES BaseObject.X a DerivedObject.X.
	BaseObject.X+=100;
	// Stav OBJECTS [BaseObject.X ma hodnotu 201], [DerivedObject.X 201].

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");

	// Stav OBJECTS [BaseObject.X ma hodnotu 201], [DerivedObject.X 201].
	// !!!!! Kedze hodnota DerivedObject.X EXISTUJE, tak je INKREMENTOVANA o 100. Hodnota BaseObject.X sa NEMENI, kedze EXISTUJU 2 NEZAVISLE PROPERTIES BaseObject.X a DerivedObject.X.
	DerivedObject.X+=100;
	// Stav OBJECTS [BaseObject.X ma hodnotu 201], [DerivedObject.X 301].

	document.write("<hr/>");
    document.write("<p>BaseObject.X: [" + BaseObject.X + "] !</p>");
    document.write("<p>DerivedObject.X: [" + DerivedObject.X + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	// !!!!! JScript (implementacia JavaScript na IE) NEPODPORUJE GETTER a SETTER METHODS pri pristupe k OBJECT PROPERTIES.

	/*
	var															MyObject=
	{
		SomeProperty: 100,

		get MyProperty()
		{
			document.write("<p>GETTER CALLED !</p>");

			return(this.SomeProperty);
		},
		set MyProperty(Value)
		{
			document.write("<p>SETTER CALLED !</p>");

			this.SomeProperty=Value;
		}
	};

	// !!! Vola sa GETTER MyProperty().
    document.write("<p>MyObject.MyProperty: [" + MyObject.MyProperty + "] !</p>");

	// !!! Vola sa SETTER MyProperty(Value).
	MyObject.MyProperty=333;

	// !!! Vola sa GETTER MyProperty().
    document.write("<p>MyObject.MyProperty: [" + MyObject.MyProperty + "] !</p>");
	*/
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															MyObject={X:100,Y:200};

	for(PropertyName in MyObject)
	{
	    document.write("<p>MyObject[" + PropertyName + "]: [" + MyObject[PropertyName] + "] !</p>");
	}

	delete(MyObject.Y);

	document.write("<hr/>");

	for(PropertyName in MyObject)
	{
	    document.write("<p>MyObject[" + PropertyName + "]: [" + MyObject[PropertyName] + "] !</p>");
	}

	document.write("<hr/>");

	var															BaseObject={X:100};
	var															DerivedObject=Object.create(BaseObject);

	DerivedObject.Y=200;

	for(PropertyName in BaseObject)
	{
	    document.write("<p>BaseObject[" + PropertyName + "]: [" + BaseObject[PropertyName] + "] !</p>");
	}

	for(PropertyName in DerivedObject)
	{
	    document.write("<p>DerivedObject[" + PropertyName + "]: [" + DerivedObject[PropertyName] + "] !</p>");
	}

	// !!! Kedze DerivedObject.X je iba DERIVED, tak sa NEZMAZE.
	var															Result1=delete DerivedObject.X;

	document.write("<hr/>");
    document.write("<p>Result1: [" + Result1 + "] !</p>");

	for(PropertyName in BaseObject)
	{
	    document.write("<p>BaseObject[" + PropertyName + "]: [" + BaseObject[PropertyName] + "] !</p>");
	}

	for(PropertyName in DerivedObject)
	{
	    document.write("<p>DerivedObject[" + PropertyName + "]: [" + DerivedObject[PropertyName] + "] !</p>");
	}

	// !!! Kedze BaseObject.X EXISTUJE, tak sa ZMAZE.
	// !!!!! Vysledkom je, ze DerivedObject.X VRATI 'undefined', kedze v OBJECT DerivedObject PROPERTY 'X' NEBOLA NIKDY DEFINOVANA v z BaseObject bola PROPERTY 'X' ODSTRANENA.
	var															Result2=delete BaseObject.X;

	document.write("<hr/>");
    document.write("<p>Result2: [" + Result2 + "] !</p>");

	for(PropertyName in BaseObject)
	{
	    document.write("<p>BaseObject[" + PropertyName + "]: [" + BaseObject[PropertyName] + "] !</p>");
	}

	for(PropertyName in DerivedObject)
	{
	    document.write("<p>DerivedObject[" + PropertyName + "]: [" + DerivedObject[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															BaseObject={X:100};
	var															DerivedObject=Object.create(BaseObject);
	
	DerivedObject.Y=200;

    document.write("<p>X in BaseObject: [" + ("X" in BaseObject) + "] !</p>");
	// !!! Vrati TRUE, aj ked v skutocnosti je PROPERTY 'X' definovana v BASE OBJECT.
    document.write("<p>X in DerivedObject: [" + ("X" in DerivedObject) + "] !</p>");
    document.write("<p>Y in BaseObject: [" + ("Y" in BaseObject) + "] !</p>");
    document.write("<p>Y in DerivedObject: [" + ("Y" in DerivedObject) + "] !</p>");

	document.write("<hr/>");

    document.write("<p>BaseObject.hasOwnProperty(X): [" + (BaseObject.hasOwnProperty("X")) + "] !</p>");
	// !!! Vrati FALSE, lebo PROPERTY 'X' je definovana v BASE OBJECT.
    document.write("<p>DerivedObject.hasOwnProperty(X): [" + (DerivedObject.hasOwnProperty("X")) + "] !</p>");
    document.write("<p>BaseObject.hasOwnProperty(Y): [" + (BaseObject.hasOwnProperty("Y")) + "] !</p>");
    document.write("<p>DerivedObject.hasOwnProperty(Y): [" + (DerivedObject.hasOwnProperty("Y")) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	var															MyObject={X:1};
	var															PropertyDescriptorX=Object.getOwnPropertyDescriptor(MyObject,"X");
	
    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");
	
	PropertyDescriptorX.value=2;

    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");

	PropertyDescriptorX.writable=false;

    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");

	// !!! Prekvapujuco ZMENHI PROPERTY 'X', aj ked je PROPERTY 'X' READONLY. Vyzera vsak, ze pri pristupe cez PROPERTY DESCRIPTOR je mozne menit hodnotu PROPERTY aj ked ATTRIBUTE 'value' je READ-ONLY.
	PropertyDescriptorX.value=100;

    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");

	// !!! NEZMENI hodnotu 'X', lebo je READ-ONLY.
	MyObject.X=200;

    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															MyObject={X:1};
	var															PropertyDescriptorX=Object.getOwnPropertyDescriptor(MyObject,"X");

    document.write("<p>PropertyDescriptorX.value: [" + PropertyDescriptorX.value + "] !</p>");
    document.write("<p>PropertyDescriptorX.writable: [" + PropertyDescriptorX.writable + "] !</p>");
    document.write("<p>PropertyDescriptorX.enumerable: [" + PropertyDescriptorX.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorX.configurable: [" + PropertyDescriptorX.configurable + "] !</p>");

	// !!! Prida sa NOVA PROPERTY 'Y' s nastavenymi PROPERTY ATTRIBUTES.
	Object.defineProperty(MyObject,"Y",{value:33,writable:true});

	var															PropertyDescriptorY=Object.getOwnPropertyDescriptor(MyObject,"Y");

	document.write("<hr/>");
    document.write("<p>PropertyDescriptorY.value: [" + PropertyDescriptorY.value + "] !</p>");
    document.write("<p>PropertyDescriptorY.writable: [" + PropertyDescriptorY.writable + "] !</p>");
    document.write("<p>PropertyDescriptorY.enumerable: [" + PropertyDescriptorY.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorY.configurable: [" + PropertyDescriptorY.configurable + "] !</p>");

	// !!! Pomocou defineProperty() NIE JE MOZNE vykonat UPDATE ATTRIBUTES EXISTUJUCICH PROPERTIES, iba pridat NOVU PROPERTIES s ATTRIBUTES.
	Object.defineProperty(MyObject,"Y",{value:55,writable:false});

	document.write("<hr/>");
    document.write("<p>PropertyDescriptorY.value: [" + PropertyDescriptorY.value + "] !</p>");
    document.write("<p>PropertyDescriptorY.writable: [" + PropertyDescriptorY.writable + "] !</p>");
    document.write("<p>PropertyDescriptorY.enumerable: [" + PropertyDescriptorY.enumerable + "] !</p>");
    document.write("<p>PropertyDescriptorY.configurable: [" + PropertyDescriptorY.configurable + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															BaseObject={X:1};
	var															DerivedObject=Object.create(BaseObject);
	var															DerivedObjectProrotype=Object.getPrototypeOf(DerivedObject);
	var															BaseObjectProrotype=Object.getPrototypeOf(BaseObject);
	
    document.write("<p>DerivedObjectProrotype: [" + DerivedObjectProrotype + "] !</p>");
    document.write("<p>DerivedObjectProrotype.X: [" + DerivedObjectProrotype.X + "] !</p>");
    document.write("<p>BaseObjectProrotype: [" + BaseObjectProrotype + "] !</p>");
    document.write("<p>BaseObjectProrotype.X: [" + BaseObjectProrotype.X + "] !</p>");

	document.write("<hr/>");
    document.write("<p>BaseObject.isPrototypeOf(DerivedObject): [" + BaseObject.isPrototypeOf(DerivedObject) + "] !</p>");
    document.write("<p>BaseObject.isPrototypeOf(Object): [" + BaseObject.isPrototypeOf(Object) + "] !</p>");
    document.write("<p>DerivedObject.isPrototypeOf(BaseObject): [" + DerivedObject.isPrototypeOf(BaseObject) + "] !</p>");
    document.write("<p>Object.prototype.isPrototypeOf(BaseObject): [" + Object.prototype.isPrototypeOf(BaseObject) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	var															BaseObject={X:1};
	var															DerivedObject=Object.create(BaseObject);

    document.write("<p>Object.isExtensible(BaseObject): [" + Object.isExtensible(BaseObject) + "] !</p>");
    document.write("<p>Object.isExtensible(DerivedObject): [" + Object.isExtensible(DerivedObject) + "] !</p>");
    document.write("<p>Object.isSealed(DerivedObject): [" + Object.isSealed(DerivedObject) + "] !</p>");

	// !!! Zmeni OBJECT na NON-EXTENSIBLE.	
	Object.preventExtensions(DerivedObject);

    document.write("<p>Object.isExtensible(BaseObject): [" + Object.isExtensible(BaseObject) + "] !</p>");
    document.write("<p>Object.isExtensible(DerivedObject): [" + Object.isExtensible(DerivedObject) + "] !</p>");
    document.write("<p>Object.isSealed(DerivedObject): [" + Object.isSealed(DerivedObject) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	var															MyObject=
	{
		X:1,
		Y:2,
		InnerObject:
		{
			Z:3
		},
		Name: "Timmy"
	};

    document.write("<p>MyObject.X: [" + MyObject.X + "] !</p>");
    document.write("<p>MyObject.Y: [" + MyObject.Y + "] !</p>");
    document.write("<p>MyObject.InnerObject.Z: [" + MyObject.InnerObject.Z + "] !</p>");
    document.write("<p>MyObject.Name: [" + MyObject.Name + "] !</p>");

	// !!! Vykona SERIALIZACIU OBJECT do STRING.
	var															SerializedObject=JSON.stringify(MyObject);

	document.write("<hr/>");
    document.write("<p>SerializedObject: [" + SerializedObject + "] !</p>");

	// !!! Vykona DESERIALIZACIU zo STRING do OBJECT.
	var															MyDeserializedObject=JSON.parse(SerializedObject);

	document.write("<hr/>");
    document.write("<p>MyDeserializedObject.X: [" + MyDeserializedObject.X + "] !</p>");
    document.write("<p>MyDeserializedObject.Y: [" + MyDeserializedObject.Y + "] !</p>");
    document.write("<p>MyDeserializedObject.InnerObject.Z: [" + MyDeserializedObject.InnerObject.Z + "] !</p>");
    document.write("<p>MyDeserializedObject.Name: [" + MyDeserializedObject.Name + "] !</p>");
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
TestFunction14();
//-------------------------------------------------------------------------------------------------------