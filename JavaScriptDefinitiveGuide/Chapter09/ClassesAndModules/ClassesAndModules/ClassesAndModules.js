//-------------------------------------------------------------------------------------------------------
// Definujem BASE CLASS.
function CBaseClass(Name)
{
	this.Name=Name;
}
//-------------------------------------------------------------------------------------------------------
// Definujem PROTOTYPE OBJECT pre BASE CLASS.
CBaseClass.prototype=
{
	constructor: CBaseClass,

	Name: "NONE",

	NonVirtualMethodInBase: function()
	{
	    document.write("<p>BASE - NonVirtualMethodInBase() - Name: [" + this.Name + "] !</p>");
	},

	VirtualMethod: function()
	{
	    document.write("<p>BASE - VirtualMethod() - Name: [" + this.Name + "] !</p>");
	},

	VirtualMethodWithCallToBaseClassImplementation: function()
	{
	    document.write("<p>BASE - VirtualMethodWithCallToBaseClassImplementation() - Name: [" + this.Name + "] !</p>");
	},

	// !!! ABSTRACT METHOD sa simuluje tak, ze VZDY HODI EXCEPTION, takze ju volat nema zmysel.
	AbstractMethod: function()
	{
		throw("AbstractMethod from CBaseClass MUST NOT be CALLED !");
	}
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Definujem DERIVED CLASS.
function CDerivedClass(Name)
{
	// !!! Zavolam CONSTRUCTOR BASE CLASS.
	CBaseClass.apply(this,arguments);

	// !!! Toto je alternativne volanie. 2. PARAMETER MUSI BYT ARRAY, pretoze apply() VZDY ocakava ako 2. PARAMETER hodnotu ARRAY.
	//CBaseClass.apply(this,[Name]);
}
//-------------------------------------------------------------------------------------------------------
// Definujem PROTOTYPE OBJECT pre DERIVED CLASS.
// !!! PROTOTYPE OBJECT DERIVED CLASS MUSI DEDIT z PROTOTYPE OBJECT BASE CLASS.
CDerivedClass.prototype=Object.create(CBaseClass.prototype);
//-------------------------------------------------------------------------------------------------------
// !!! Je VELMI DOLEZITE, aby DERIVED CLASS nastavila PROPERTY constructor na CONSTRUCTOR DERIVED CLASS.
CDerivedClass.prototype.constructor=CDerivedClass;
//-------------------------------------------------------------------------------------------------------
// !!! Definujem METHOD v DERIVED CLASS.
CDerivedClass.prototype.NonVirtualMethodInDerived=function()
{
	document.write("<p>DERIVED - NonVirtualMethodInDerived() - Name: [" + this.Name + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
// !!!!! METHOD PRETAZUJE implementaciu VirtualMethod() definovanu v CBaseClass.
CDerivedClass.prototype.VirtualMethod=function()
{
	document.write("<p>DERIVED - VirtualMethod() - Name: [" + this.Name + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
// !!!!! METHOD PRETAZUJE implementaciu VirtualMethodWithCallToBaseClassImplementation() definovanu v CBaseClass a ZAROVEN vola jej BASE IMPLEMENTACIU v CBaseClass.
CDerivedClass.prototype.VirtualMethodWithCallToBaseClassImplementation=function()
{
	document.write("<p>DERIVED - VirtualMethodWithCallToBaseClassImplementation() - Name: [" + this.Name + "] !</p>");

	// !!!!! Zavolam BASE IMPLEMENTACIU v CBaseClass.
	// !!!!! FUNCTION apply() je NEVYHNUTNA, kedze inak by som nemal ako preniest 'this' PARAMETER.
	CBaseClass.prototype.VirtualMethodWithCallToBaseClassImplementation.apply(this,arguments);
}
//-------------------------------------------------------------------------------------------------------
// !!! Implementacia ABSTRACT METHOD.
CDerivedClass.prototype.AbstractMethod=function()
{
	document.write("<p>DERIVED - AbstractMethod() - Name: [" + this.Name + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FACTORY FUNCTION vytvara instanciu CName1 CLASS. Pozor TOTO NIE JE CONSTRUCTOR.
function CName1(FirstName,LastName,Age)
{
	// !!! ZDEDIM OBJECT z CName1Prototype.
	// !!!!! Kedze FUNCTION NIE JE CONSTRUCTOR, musim si NOVY OBJECT vytvori AUTOMATICKY.
	var															NewObject=Object.create(CName1Prototype);

	// !!! Inicializujem novy OBJECT.
	NewObject.FirstName=FirstName;
	NewObject.LastName=LastName;
	NewObject.Age=Age;

	return(NewObject);
}
//-------------------------------------------------------------------------------------------------------
// !!! Definujem PROTOTYPE pre CLASS CName1.
CName1Prototype=
{
	// !!! PROPERTIES CName1 CLASS.
	FirstName: "",
	LastName: "",
	Age: 0,

	// !!! METHOD CName1 CLASS.
	PrintName: function()
	{
	    document.write("<p>CLASS 1 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FACTORY FUNCTION vytvara instanciu CName2 CLASS. Pozor TOTO NIE JE CONSTRUCTOR.
function CName2(FirstName,LastName,Age)
{
	// !!! ZDEDIM OBJECT z CName2Prototype.
	// !!!!! Kedze FUNCTION NIE JE CONSTRUCTOR, musim si NOVY OBJECT vytvori AUTOMATICKY.
	var															NewObject=Object.create(CName2.CName2Prototype);

	// !!! Inicializujem novy OBJECT.
	NewObject.FirstName=FirstName;
	NewObject.LastName=LastName;
	NewObject.Age=Age;

	return(NewObject);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Definujem PROTOTYPE pre CLASS CName2 ako PROPERTY CONSTRUCTOR CName2. Toto je OBVYKLA PRAX ako definovat PROTOTYPE OBJECT.
CName2.CName2Prototype=
{
	// !!! PROPERTIES CName2 CLASS.
	FirstName: "",
	LastName: "",
	Age: 0,

	// !!! METHOD CName2 CLASS.
	PrintName: function()
	{
	    document.write("<p>CLASS 2 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR vytvara instanciu CName3 CLASS.
function CName3(FirstName,LastName,Age)
{
	// !!!!! NIE JE TREBA volat Object.create(), lebo CONSTRUCTOR vytvara NOVY OBJECT dediaci z CName3.prototype AUTOMATICKY.

	// !!! Inicializujem novy OBJECT.
	this.FirstName=FirstName;
	this.LastName=LastName;
	this.Age=Age;

	// !!!!! CONSTRUCTOR NEMUSI NIC VRACAT, lebo JavaScript AUTOMATICKY VRATI NOVY OBJECT, ktory vytvoril pred spustenim CONSTRUCTOR.
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Definujem PROTOTYPE pre CLASS CName3.
// !!!!! Meno PROPERTY 'prototype' je POVINNE, ak ho ma vediet najst CONSTRUCTOR.
CName3.prototype=
{
	// !!! PROPERTIES CName3 CLASS.
	FirstName: "",
	LastName: "",
	Age: 0,

	// !!! METHOD CName3 CLASS.
	PrintName: function()
	{
	    document.write("<p>CLASS 3 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR vytvara instanciu CName4 CLASS.
function CName4(FirstName,LastName,Age)
{
	// !!!!! NIE JE TREBA volat Object.create(), lebo CONSTRUCTOR vytvara NOVY OBJECT dediaci z CName4.prototype AUTOMATICKY.

	// !!! Inicializujem novy OBJECT.
	this.FirstName=FirstName;
	this.LastName=LastName;
	this.Age=Age;

	// !!!!! CONSTRUCTOR NEMUSI NIC VRACAT, lebo JavaScript AUTOMATICKY VRATI NOVY OBJECT, ktory vytvoril pred spustenim CONSTRUCTOR.
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Definujem PROTOTYPE pre CLASS CName4.
// !!!!! Meno PROPERTY 'prototype' je POVINNE, ak ho ma vediet najst CONSTRUCTOR.
CName4.prototype=
{
	// !!!!! STANDARDNY PROTOTYPE OBJECT by mal obsahovat PROPERTY 'constructor', ktora sa odkazuje na CONSTRUCTOR FUNCTION.
	constructor: CName4,

	// !!! PROPERTIES CName4 CLASS.
	FirstName: "",
	LastName: "",
	Age: 0,

	// !!! METHOD CName4 CLASS.
	PrintName: function()
	{
	    document.write("<p>CLASS 4 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR vytvara instanciu CName5 CLASS.
function CName5(FirstName,LastName,Age)
{
	// !!!!! NIE JE TREBA volat Object.create(), lebo CONSTRUCTOR vytvara NOVY OBJECT dediaci z CName5.prototype AUTOMATICKY.

	// !!! Inicializujem novy OBJECT.
	this.FirstName=FirstName;
	this.LastName=LastName;
	this.Age=Age;

	// !!!!! CONSTRUCTOR NEMUSI NIC VRACAT, lebo JavaScript AUTOMATICKY VRATI NOVY OBJECT, ktory vytvoril pred spustenim CONSTRUCTOR.
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Definujem PROTOTYPE pre CLASS CName5.
// !!!!! Meno PROPERTY 'prototype' je POVINNE, ak ho ma vediet najst CONSTRUCTOR.
CName5.prototype=
{
	// !!!!! STANDARDNY PROTOTYPE OBJECT by mal obsahovat PROPERTY 'constructor', ktora sa odkazuje na CONSTRUCTOR FUNCTION.
	constructor: CName5,

	// !!! PROPERTIES CName5 CLASS.
	FirstName: "",
	LastName: "",
	Age: 0,

	// !!! METHOD CName5 CLASS.
	PrintName: function()
	{
	    document.write("<p>CLASS 5 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "] !</p>");
	},

	// !!! Pretazim metodu toString().
	toString: function()
	{
		return("CLASS 5 - Name: [" + this.FirstName + " " + this.LastName + "], Age: [" + this.Age + "]");
	},

	// !!! Pretazim metodu valueOf().
	valueOf: function()
	{
	    document.write("<p>CLASS 5 valueOf() CALLED !</p>");

		return(this.Age);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function CNameWithPrivateFields(FirstName,LastName,Age)
{
	// !!! Pre kazdu READ-ONLY PROPERTY definuje CLOSURE. Ta bude sluzi ako v C# sluzi PROPERTY GETTER.
	// !!!!! Kedze KAZDA FUNCTION si DRZI SCOPE v ktorom bola volana, tak PARAMATRE 'FirstName', 'LastName' a 'Age' budu mat PLATNE HODNOTY aj po SKONCENI VOLANIA CONSTRUCTOR.
	// !!!!! PARAMATRE 'FirstName', 'LastName' a 'Age' DE-FACTO sluzia ako FIELDS.
	this.FirstName=function(){return(FirstName);}
	this.LastName=function(){return(LastName);}
	this.Age=function(){return(Age);}
}
//-------------------------------------------------------------------------------------------------------
CNameWithPrivateFields.prototype=
{
	constructor: CNameWithPrivateFields,

	// !!!!! Ak chcem z tychto PROPERTIES spravit PRIVATE FIELDS, tak ich musi z PROTOTYPE OBJECT VYHODIT.
	/*
	FirstName: "",
	LastName: "",
	Age: 0,
	*/

	PrintName: function()
	{
		// !!! Namiesto pristupu k PROPERTIES vola CLOSURE FUNCTIONS.
	    document.write("<p>CNameWithPrivateFields - Name: [" + this.FirstName() + " " + this.LastName() + "], Age: [" + this.Age() + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! CLASS simuluje KLASICKU C++ CLASS.
function CPPLikeClass(FirstName,LastName,Age)
{
	// Inicializuje 'MEMBER FIELDS'.
	this.MFirstName=FirstName;
	this.MLastName=LastName;
	this.MAge=Age;

	// !!! Inkrementujem 'STATIC FIELD'.
	CPPLikeClass.StaticInstanceCounter++;
}
//-------------------------------------------------------------------------------------------------------
CPPLikeClass.prototype=
{
	constructor: CPPLikeClass,

	// !!! Definujem MEMBER FIELDS.
	MFirstName: "",
	MLastName: "",
	MAge: 0,

	// !!! Definujem 'MEMBER METHODS'.
	MemberPrintName: function()
	{
	    document.write("<p>CPPLikeClass - Name: [" + this.MFirstName + " " + this.MLastName + "], Age: [" + this.MAge + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! Definujem 'STATIC FIELD'.
CPPLikeClass.StaticInstanceCounter=0;
//-------------------------------------------------------------------------------------------------------
// !!! Definujem 'STATIC METHOD'.
CPPLikeClass.StaticGetInstanceCounter=function()
{
	return(CPPLikeClass.StaticInstanceCounter);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
function TestFunction1()
{
	// !!! Vytvorim instancie CLASS CName1 volanim FACTORY FUNCTION CName1().
	var															Name1=CName1("Timmy","Anderson",12);
	var															Name2=CName1("Jenny","Thompson",13);

	Name1.PrintName();
	Name2.PrintName();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction2()
{
	// !!! Vytvorim instancie CLASS CName2 volanim FACTORY FUNCTION CName2().
	var															Name1=CName2("Timmy","Anderson",12);
	var															Name2=CName2("Jenny","Thompson",13);

	Name1.PrintName();
	Name2.PrintName();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction3()
{
	// !!! Vytvorim instancie CLASS CName3 pouzitim OPERATOR new.
	var															Name1=new CName3("Timmy","Anderson",12);
	var															Name2=new CName3("Jenny","Thompson",13);

	Name1.PrintName();
	Name2.PrintName();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction4()
{
	var															Name1=CName1("Timmy","Anderson",12);
	var															Name2=CName2("Timmy","Anderson",12);
	var															Name3=new CName3("Timmy","Anderson",12);

	// !!! Vrati FALSE, pretoze CName1 FUNCTION NEOBSAHUJE PROPERTY s nazvom 'prototype', ale PROTOTYPE OBJECT ma ulozeny v PROPERTY ako GLOBAL OBJECT CName1Prototype.
    document.write("<p>VALUE - (Name1 instanceof CName1): [" + (Name1 instanceof CName1) + "] !</p>");
	// !!! Vrati FALSE, pretoze CName2 FUNCTION NEOBSAHUJE PROPERTY s nazvom 'prototype', ale PROTOTYPE OBJECT ma ulozeny v PROPERTY ako PROPERTY CName2.CName2Prototype.
    document.write("<p>VALUE - (Name2 instanceof CName2): [" + (Name2 instanceof CName2) + "] !</p>");
	// !!! Vrati TRUE, pretoze CName3 CONSTRUCTOR OBSAHUJE PROPERTY s nazvom 'prototype'.
    document.write("<p>VALUE - (Name3 instanceof CName3): [" + (Name3 instanceof CName3) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction5()
{
	// !!! Vytvorim instancie CLASS CName4 pouzitim OPERATOR new.
	var															Name1=new CName4("Timmy","Anderson",12);
	var															Name2=new CName4("Jenny","Thompson",13);

	Name1.PrintName();
	Name2.PrintName();

    document.write("<p>VALUE - CName1.prototype: [" + CName1.prototype + "] !</p>");
    document.write("<p>VALUE - CName1.prototype.constructor: [" + CName1.prototype.constructor + "] !</p>");
    document.write("<p>VALUE - CName2.prototype: [" + CName2.prototype + "] !</p>");
    document.write("<p>VALUE - CName2.prototype.constructor: [" + CName2.prototype.constructor + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction6()
{
	var															DummyFunction=function()
	{
	};

    document.write("<p>VALUE - DummyFunction.prototype: [" + DummyFunction.prototype + "] !</p>");
    document.write("<p>VALUE - DummyFunction.prototype.constructor: [" + DummyFunction.prototype.constructor + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction7()
{
	// !!! Vypisem hodnotu 'STATIC FIELD' volanim 'STATIC METHOD'.
    document.write("<p>VALUE - CPPLikeClass.StaticGetInstanceCounter(): [" + CPPLikeClass.StaticGetInstanceCounter() + "] !</p>");
	
	// !!! Vytvorim INSTANCIE CLASS, ktora sa podoba na C++ CLASS.
	var															Name1=new CPPLikeClass("Timmy","Anderson",12);

    document.write("<p>VALUE - CPPLikeClass.StaticGetInstanceCounter(): [" + CPPLikeClass.StaticGetInstanceCounter() + "] !</p>");

	var															Name2=new CPPLikeClass("Jenny","Thompson",13);

    document.write("<p>VALUE - CPPLikeClass.StaticGetInstanceCounter(): [" + CPPLikeClass.StaticGetInstanceCounter() + "] !</p>");

	// !!! Zavolam 'MEMBER METHOD'.
	Name1.MemberPrintName();
	Name2.MemberPrintName();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction8()
{
	var															Name1=new CName4("Timmy","Anderson",12);
	var															Name2=new CName4("Jenny","Thompson",13);

	// !!! Do PROTOTYPE OBJECT PRIDAM NOVU PROPERTY.
	CName4.prototype.Gender="UNKNOWN";

	// !!! Novopridana PROPERTY je IHNED VIDITELNA v ZDEDENYCH OBJECTS.
    document.write("<p>VALUE - Name1.Gender: [" + Name1.Gender + "] !</p>");
    document.write("<p>VALUE - Name2.Gender: [" + Name2.Gender + "] !</p>");

	Name1.Gender="MALE";
	Name2.Gender="FEMALE";

    document.write("<p>VALUE - Name1.Gender: [" + Name1.Gender + "] !</p>");
    document.write("<p>VALUE - Name2.Gender: [" + Name2.Gender + "] !</p>");

    document.write("<hr/>");

	// !!!!! Ak pridam do PROTOTYPE OBJECT CLASS Object novu PROPERTY, tak je viditelna VSETKYMI OBJECT.
	Object.prototype.MyName="NONE";

    document.write("<p>VALUE - Name1.MyName: [" + Name1.MyName + "] !</p>");
    document.write("<p>VALUE - Name2.MyName: [" + Name2.MyName + "] !</p>");

	Name1.MyName="TIMMY";
	Name2.MyName="JENNY";

    document.write("<p>VALUE - Name1.MyName: [" + Name1.MyName + "] !</p>");
    document.write("<p>VALUE - Name2.MyName: [" + Name2.MyName + "] !</p>");

    document.write("<hr/>");

	var															MyInt=55;

    document.write("<p>VALUE - MyInt: [" + MyInt + "] !</p>");

	// !!! PROPERTY 'MyName' je viditelna aj v STANDARDNYCH OBJECTS.
    document.write("<p>VALUE - MyInt.MyName: [" + MyInt.MyName + "] !</p>");

	// !!!!! Avsak aspon v IE NIE JE pre PRIMITIVE TYPES EDITOVATELNA.
	MyInt.MyName="INT";

    document.write("<p>VALUE - MyInt.MyName: [" + MyInt.MyName + "] !</p>");

    document.write("<hr/>");

	var															MyDate=new Date;

	// !!! PROPERTY 'MyName' je viditelna aj v STANDARDNYCH OBJECTS.
    document.write("<p>VALUE - MyDate.MyName: [" + MyDate.MyName + "] !</p>");

	// !!!!! Avsak pre OBJECTS EDITOVATELNA JE.
	MyDate.MyName="DATE";

    document.write("<p>VALUE - MyDate.MyName: [" + MyDate.MyName + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction9()
{
	var															PrimitiveType="Timmy";
	var															ObjectType=new CName4("Timmy","Anderson",12);

	// !!! Kedze sa jedna o PRIMITIVNY TYPE STRING, tak je vrateny retazec 'string'.
    document.write("<p>VALUE - typeof(PrimitiveType): [" + typeof(PrimitiveType) + "] !</p>");
	// !!! Kedze sa jedna o OBJECT TYPE, vrati retazec 'object'.
    document.write("<p>VALUE - typeof(ObjectType): [" + typeof(ObjectType) + "] !</p>");

	// !!! Kedze sa jedna o OBJECT TYPE typu 'CName4', ktoreho CONSTRUCTOR MA DEFINOVANU PROPERTY 'prototype', vrati TRUE.
    document.write("<p>VALUE - (ObjectType instanceof CName4): [" + (ObjectType instanceof CName4) + "] !</p>");

	// !!! Kedze sa jedna o OBJECT TYPE typu 'CName4', vrati FALSE.
    document.write("<p>VALUE - (ObjectType instanceof CName3): [" + (ObjectType instanceof CName3) + "] !</p>");

	// !!!!! Kedze sa jedna o PRIMITIVNY TYPE STRING, vrati FALSE.
    document.write("<p>VALUE - (PrimitiveType instanceof String): [" + (PrimitiveType instanceof String) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction10()
{
	// Nema pretazenu metodu toString().
	var															Name1=new CName4("Timmy","Anderson",12);
	// Ma pretazenu metodu toString().
	var															Name2=new CName5("Jenny","Thompson",13);

    document.write("<p>VALUE - Name1: [" + Name1 + "] !</p>");
    document.write("<p>VALUE - Name2: [" + Name2 + "] !</p>");

    document.write("<hr/>");

	// !!! Vola sa METHOD valueOf().
    document.write("<p>VALUE - (10+Name2): [" + (10+Name2) + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction11()
{
	var															Name1=new CNameWithPrivateFields("Timmy","Anderson",12);
	var															Name2=new CNameWithPrivateFields("Jenny","Thompson",13);

	Name1.PrintName();
	Name2.PrintName();

    document.write("<hr/>");

	// !!! Namiesto k PROPERTIES vola METOHDS, ktore reprezentuju C# PROPERTY GETTERS.
	document.write("<p>Name1: [" + Name1.FirstName() + " " + Name1.LastName() + "], Age: [" + Name1.Age() + "] !</p>");
	document.write("<p>Name2: [" + Name2.FirstName() + " " + Name2.LastName() + "], Age: [" + Name2.Age() + "] !</p>");
}
//-------------------------------------------------------------------------------------------------------
function TestFunction12()
{
	var															Base=new CBaseClass("BASE");
	var															Derived=new CDerivedClass("DERIVED");

    document.write("<p>VALUE - Base.Name: [" + Base.Name + "] !</p>");
    document.write("<p>VALUE - Derived.Name: [" + Derived.Name + "] !</p>");

	Base.NonVirtualMethodInBase();
	
	// !!! METHOD NonVirtualMethodInBase() je ZDEDENA z CBaseClass.
	Derived.NonVirtualMethodInBase();

	Derived.NonVirtualMethodInDerived();

    document.write("<hr/>");

	Base.VirtualMethod();
	Derived.VirtualMethod();

    document.write("<hr/>");

	Base.VirtualMethodWithCallToBaseClassImplementation();
	Derived.VirtualMethodWithCallToBaseClassImplementation();

    document.write("<hr/>");

	try
	{
		// !!! Volanie ABSTRACT METHOD hodi EXCEPTION.
		Base.AbstractMethod();
	}
	catch(Error)
	{
		document.write("<p>EXCEPTION: [" + Error + "] !</p>");
	}

	Derived.AbstractMethod();
}
//-------------------------------------------------------------------------------------------------------
function TestFunction13()
{
	var															MyObject={X:100,Y:200};

	for(var PropertyName in MyObject)
	{
		document.write("<p>PROPERTY[" + PropertyName + "]: [" + MyObject[PropertyName] + "] !</p>");
	}

	// !!! PROPERTY 'X' PRESTANE byt ENUMERABLE.
	Object.defineProperty(MyObject,"X",{enumerable:false});

    document.write("<hr/>");

	for(var PropertyName in MyObject)
	{
		document.write("<p>PROPERTY[" + PropertyName + "]: [" + MyObject[PropertyName] + "] !</p>");
	}
}
//-------------------------------------------------------------------------------------------------------
function TestFunction14()
{
	// !!!!! Deklarujem FUNCTION a IHNED ju aj VYVOLAM, aby sa do 'PrivateNamespace' ulozila FUNCTION, ktoru ANONYMOUS FUNCTION VYTVARA.
	var															PrivateNamespace=function()
	{
		function PrivateFunction()
		{
			document.write("<p>PRIVATE FUNCTION CALLED !</p>");
		}

		return(PrivateFunction);
	}();

	PrivateNamespace();
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