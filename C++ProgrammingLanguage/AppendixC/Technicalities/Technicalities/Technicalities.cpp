//-------------------------------------------------------------------------------------------------------
#pragma warning(disable : 4244)
//-------------------------------------------------------------------------------------------------------
#include "ISO646.H"
#include "stdafx.h"
#include <conio.h>
#include <string>
// !!!!! Pri TEMPLATES je treba spravit INCLUDE .H i .CPP FILES.
#include "Template.h"
#include "Template.cpp"
#include "TemplateWithTemplateAsParameter.h"
// !!!!! Pri TEMPLATES je treba spravit INCLUDE .H i .CPP FILES.
#include "TemplateWithTemplateAsParameter.cpp"
#include "TypenameTemplate.h"
// !!!!! Pri TEMPLATES je treba spravit INCLUDE .H i .CPP FILES.
#include "TypenameTemplate.cpp"
#include "TemplateAsQualifier.h"
#include "TemplateForInstance.h"
#include "Name.h"
#include "AccessControlBase.h"
#include "AccessControlDerivedPrivate.h"
#include "AccessControlDerivedProtected.h"
#include "AccessControlMostDerivedPrivate.h"
#include "AccessControlMostDerivedProtected.h"
#include "AccessControlDerivedUsingTest.h"
#include "OuterClass.h"
#include "Friend.h"
#include "FriendBase.h"
#include "FriendDerived.h"
#include "SBitFields.h"
#include "SUnion.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!! MULTIDIMENSIONAL ARRAY sa prenasa ako JEDNODUCHY POINTER.
void PrintMultidimensionalArray(int* Array, int Dim1, int Dim2, int Dim3)
{
	for(int i=0;i<Dim1;i++)
	{
		for(int j=0;j<Dim2;j++)
		{
			for(int k=0;k<Dim3;k++)
			{
				int												Index=(i*Dim2*Dim3)+(j*Dim3)+(k);

				wprintf_s(L"Array[%d][%d][%d]: [%d] !\n",i,j,k,Array[Index]);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------
namespace Test
{
//-------------------------------------------------------------------------------------------------------
	void SomeFunction(void)
	{
		wprintf_s(L"Test::SomeFunction() !\n");
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
namespace NTest1
{
//-------------------------------------------------------------------------------------------------------
	void Function1(void)
	{
		wprintf_s(L"Test1::Function1() !\n");
	}
//-------------------------------------------------------------------------------------------------------
	namespace NTest2
	{
//-------------------------------------------------------------------------------------------------------
		void Function2(void)
		{
			wprintf_s(L"Test1::Test2::Function2() !\n");

			// !!! Umoznuje volanie z OUTER NAMESPACE.
			Function1();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	void Function2(void)
	{
		wprintf_s(L"Test1::Function2() !\n");

		// !!! Neumoznuje volanie v INNER NAMESPACE.
		//Function();

		// !!! Musim specifikovat INNER NAMESPACE.
		NTest2::Function2();
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
void SomeFunction(void)
{
	wprintf_s(L"GLOBAL::SomeFunction() !\n");
}
//-------------------------------------------------------------------------------------------------------
// !!! Explicitna SPECIALIZATION pre STATIC METHOD.
void CTemplate<int>::SetStaticField(const int& Value)
{
	wprintf_s(L"SPECIALIZED version of SetStaticField() CALLED !\n");

	MStaticField=Value;
}

//-------------------------------------------------------------------------------------------------------
// !!! Funkcia je FRIEND danej TEMPLATE.
wstring FriendGetValue(CTemplate<wstring> Template)
{
	// !!! Kedze metoda je FRIEND, moze pristupovat k PRIVATE FIELDS.
	return(Template.MField);
}
//-------------------------------------------------------------------------------------------------------
template <typename TReturnType, typename TParam>
TReturnType SomeTemplateFunctions(TParam Value1, TParam Value2)
{
	TParam														Value=Value1+Value2;
	TReturnType													ReturnValue=(TReturnType) Value;

	return(ReturnValue);
}
//-------------------------------------------------------------------------------------------------------
template<typename TFunctionType>
void TypenameTestTemplateFunction(TFunctionType Param)
{
	// !!! TEMPLATE PARAMETER musi byt typu CTypenameTemplate<TType>.

	// !!!!! Podla knihy by pri tychto deklaraciach mal byt POVINNY KEYWORD 'typename', no Visual C++ to skompiluje aj bez neho.
	typename TFunctionType::CValueType							Value1=Param.GetValue();
	typename TFunctionType::CPointerType						Pointer=&Value1;

	// !!! Aj toto Visual C++ bez problemov skompiluje.
	TFunctionType::CValueType									Value2;

	Value2=44;

	wprintf_s(L"Value1: [%d] !\n",Value1);
	wprintf_s(L"Value2: [%d] !\n",Value2);
	wprintf_s(L"Pointer: [%d] !\n",*Pointer);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateAsQualifierTest(TType Value)
{
	// !!! Predpoklada sa, ze TType je INT.

	wprintf_s(L"Value: [%d] !\n",Value);

	CTemplateAsQualifier										Object;

	// !!!!! SPECIALNE pouzitie KEYWORD 'template'. 
	int*														Memory1=Object.template Allocate<int>();

	Object.Delocate(Memory1);

	// !!! Ako je vidiet, Visaul C++ to dokaze skompilovat aj bez 'template'.
	int*														Memory2=Object.Allocate<int>();

	Object.Delocate(Memory2);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType* CTemplateAsQualifier::Allocate(void)
{
	return(new TType);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
void CTemplateAsQualifier::Delocate(TType* Object)
{
	delete(Object);
}
//------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateScopeTest(TType Value)
{
	GlobalFunction(Value);

	// !!!!! Podla knihy by toto COMPILER NEMAL AKCEPTOVAT a hodi CHYBU, kedze volanie FUNKCIE NEZALEZI na TEMPLATE PARAMETER, malo by byt enumerovane OKAMZTIE (este pred INSTANTIATION TEMPLATE) a malo by zistit, ze GLOBALNA FUNKCIE NIE JE DEKLAROVANA, kedze sa nachadza az ZA TemplateScopeTest(). Visual C++ vsak toto IGNORUJE a kod SKOMPILUJE.
	GlobalFunction(4);
}
//------------------------------------------------------------------------------------------------------
// !!! Funkcia je DEFINOVANA a DEKLAROVANA AZ po TemplateScopeTest(), ktora ju vola.
void GlobalFunction(int Param)
{
	wprintf_s(L"GlobalFunction(): [%d] !\n",Param);
}
//------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	// !!! Premenne typu TEMPLATE deklarujem iba, aby C++ generoval pre ich typy CLASSES z TEMPLATE.
	CTemplate<int>												IntVariable;
	CTemplate<wstring>											StringVariable;

	printf_s("Type: [%s] !\n",typeid(IntVariable).name());
	printf_s("Type: [%s] !\n",typeid(StringVariable).name());

	int															DefaultIntValue=CTemplate<int>::GetStaticField();
	wstring														DefaultStringValue=CTemplate<wstring>::GetStaticField();

	wprintf_s(L"DefaultIntValue: [%d] !\n",DefaultIntValue);
	wprintf_s(L"DefaultStringValue: [%s] !\n",DefaultStringValue.c_str());

	CTemplate<int>::SetStaticField(66);
	CTemplate<wstring>::SetStaticField(L"Jenny Thompson");

	int															IntValue=CTemplate<int>::GetStaticField();
	wstring														StringValue=CTemplate<wstring>::GetStaticField();

	wprintf_s(L"IntValue: [%d] !\n",DefaultIntValue);
	wprintf_s(L"StringValue: [%s] !\n",DefaultStringValue.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CTemplate<wstring>											StringVariable(L"Timmy Anderson");
	const wstring												Value=FriendGetValue(StringVariable);

	wprintf_s(L"Value: [%s] !\n",Value.c_str());
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	// !!! TEMPLATE ma ako PARAMTER INU TEMPLATE.
	CTemplateWithTemplateAsParameter<int,CTemplate>				Template;

	CTemplate<int>												ValueTemplate;
	CTemplate<int*>												PointerTemplate;

	Template.SetTemplateValues(ValueTemplate);
	Template.SetTemplatePointers(PointerTemplate);

	Template.GetTemplateValues();
	Template.GetTemplatePointers();
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// !!! Klasicke volanie TEMPLATE FUNCTION s definovanim parametrov.
	double														Result1=SomeTemplateFunctions<double,int>(3.5,4.2);

	wprintf_s(L"Result1: [%f] !\n",Result1);

	// !!! Jeden parameter je EXPLICITNE ZADANY a druhy sa DEDUKUJE.
	double														Result2=SomeTemplateFunctions<int>(3,4);

	wprintf_s(L"Result2: [%f] !\n",Result2);

	/*
	// !!! COMPILER NEDOKAZE VYKONAT DEDUKCIU RETURN VALUE.
	double														Result3=SomeTemplateFunctions(3,4);

	wprintf_s(L"Result3: [%f] !\n",Result3);
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	CTypenameTemplate<int>										Template(33);

	TypenameTestTemplateFunction(Template);
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	TemplateAsQualifierTest(100);
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	TemplateScopeTest(100);
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	struct														SLocalStruct
	{
		int														Value;
	};

	SLocalStruct												Param;

	Param.Value=66;

	// !!! Podla knihy, toto by C++ NEMAL SKOMPILOVAT (kedze ako TEMPLATE PARAMETER sa pouziva lokalne definovany TYPE) a hodit CHYBU. Ale Visual Studio s tym problem nema a bezproblemov tento kod skompiluje.
	CTemplate<SLocalStruct>										Object(Param);

	SLocalStruct												StructValue=Object.GetField();

	wprintf_s(L"Value: [%d] !\n",StructValue.Value);
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	CTemplateForInstance<int>									Object(10);

	// !!! Instancia pre INT je vytvorena EXPLICITNE v TemplateForInstance.cpp.
	wprintf_s(L"Object: [%d] !\n",Object.GetValue());
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	// POINTER na FIELD.
	wstring														CName::*PointerToField;
	// POINTER na METHOD.
	void														(CName::*PointerToMethod)(void);

	// Priradim POINTERS na MEMBERS do prislusnych MEMBERS.
	PointerToField=&CName::MFirstName;
	PointerToMethod=&CName::PrintFullName;

	CName														Name(L"Timmy",L"Anderson",12);

	// Volam MEMBERS cez POINTER na MEMBERS.
	wprintf_s(L"First name: [%s] !\n",(Name.*PointerToField).c_str());
	(Name.*PointerToMethod)();
}

//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CAccessControlDerivedPrivate								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED metoda.
	//Object.BaseProtected();

	// !!! Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	/*
	CAccessControlDerivedPrivate								TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PRIVATE INHERITANCE.
	//Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlDerivedPrivate ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	CAccessControlDerivedProtected								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// !!! Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	/*
	CAccessControlDerivedProtected								TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PROTECTED INHERITANCE.
	//Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlDerivedProtected ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	CAccessControlMostDerivedPrivate							Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// Pouziva sa PRIVATE INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedPrivate();

	wprintf_s(L"\n");

	Object.TestMostDerivedPrivate();

	/*
	CAccessControlMostDerivedPrivate							TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PRIVATE INHERITANCE.
	Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	CAccessControlMostDerivedProtected							Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// Je to PROTECTED METODA.
	//Object.BaseProtected();

	// Pouziva sa PROTECTED INHERITANCE a preto ju NIE JE MOZNE VOLAT.
	//Object.BasePublic();

	Object.TestDerivedProtected();

	wprintf_s(L"\n");

	Object.TestMostDerivedProtected();

	/*
	CAccessControlMostDerivedProtected							TempObject;
	CAccessControlBase*											Pointer;

	// !!! Zlyha, lebo je pouzita PROTECTED INHERITANCE.
	Pointer=&TempObject;

	Pointer->ExternalConversionSucceeded(L"CAccessControlMostDerivedProtected ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	CAccessControlDerivedUsingTest								Object;

	// Je to PRIVATE metoda.
	//Object.BasePrivate();

	// !!! Je to PROTECTED METODA, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BaseProtected();

	// !!! Je to PUBLIC METODA, ktora NEPOUZIVA na zviditelnenie USING DECLARAION a kedze sa pouziva PRIVATE INHERITANCE, tak je NEPRISTUPNA.
	//Object.BasePublic();

	// !!! Je to PRIVATE metoda a ta je nepristupna i pre CAccessControlDerivedUsingTest a preto ju ta ANI cez USING DECLARAION NEMOZE SPRISTUPNIT.
	//Object.DummyPrivate();

	// !!! Je to PROTECTED METODA, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyProtected();

	// !!! Je to PUBLIC METODA, ktora POUZIVA na zviditelnenie USING DECLARAION. Pouzitie USING DECLARAION je NUTNE, lebo sa pouziva PRIVATE INHERITANCE.
	Object.DummyPublic();
	
	wprintf_s(L"\n");

	Object.Test();
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	COuterClass													OC;
	// !!! Je pristupny LEBO je definovany ako PUBLIC. Ak by bol PRIVATE, tak by NEBOL PRISTUPNY.
	COuterClass::CInnerClass									IC;

	OC.OuterPublic();

	IC.InnerPublic();
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	CFriend														Friend;
	CFriendBase													FriendBase;
	CFriendDerived												FriendDerived;

	Friend.PrintPublic();
	FriendBase.PrintPublic();
	FriendDerived.PrintPublic();
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	// Vola sa GLOBALNA VERZIA FUNCTION.
	SomeFunction();

	using Test::SomeFunction;

	// !!! Vola sa verzia FUNCTION z 'Test'.
	SomeFunction();

	// Vola sa GLOBALNA VERZIA FUNCTION.	
	::SomeFunction();
}	
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	SBitFields													BitFields;
	SBitFields*													Pointer=&BitFields;

	// !!! Kedze dlzka je len 5 BITS a 'A' ma hodnotu 0x41, zoberie iba 0x01.
	BitFields.MChar=L'A';
	BitFields.MHigh=7;
	// !!! Kedze dlzka je 4 BITS a pouziva sa INT a NIE UNSIGNED INT, tak 10 sa do FIELD NEZMESTI.
	BitFields.MLow=10;

	wprintf_s(L"MChar: [%d] !\n",Pointer->MChar);
	wprintf_s(L"MHigh: [%d] !\n",Pointer->MHigh);
	wprintf_s(L"MLow: [%d] !\n",Pointer->MLow);

	// !!! Kedze dlzka je len 5 BITS a 'D' ma hodnotu 0x44, zoberie iba 0x04.
	BitFields.MChar=L'D';

	wprintf_s(L"MChar: [%d] !\n",Pointer->MChar);
	wprintf_s(L"MHigh: [%d] !\n",Pointer->MHigh);
	wprintf_s(L"MLow: [%d] !\n",Pointer->MLow);

	/*
	// !!! Pointer na BIT FIELD NIE JE MOZNE ZISKAT.
	int*														PointerToBitField=&BitFields.MHigh;

	wprintf_s(L"*PointerToBitField: [%d] !\n",*PointerToBitField);
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	SUnion														Union;

	wprintf_s(L"SIZEOF(Union): [%d] !\n",sizeof(Union));

	Union.CharValue=L'A';
	
	wprintf_s(L"CharValue: [%c] !\n",Union.CharValue);

	CName*														Name=new CName(L"Timmy",L"Anderson",12);

	Union.Name=Name;

	wprintf_s(L"CharValue: [%c] !\n",Union.CharValue);

	Union.Name->PrintFullName();

	Union.Name=NULL;

	delete(Name);
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	int															Array[2][3][4];

	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<4;k++)
			{
				int												Value=i*100+j*10+k;

				Array[i][j][k]=Value;
			}
		}
	}

	PrintMultidimensionalArray(&Array[0][0][0],2,3,4);
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	int															Value=7;

	// !!! Na to aby to fungovalo je treba spravit INCLUDE 'ISO646.h'.

	// !!! Pouzitie KEYWORD.
	if (Value>0 and Value not_eq 7)
	{
		wprintf_s(L"Value is NOT 7 !\n");
	}
	else
	{
		wprintf_s(L"Value is 7 !\n");
	}

	int															Array[3];

	Array[0]=1;
	Array[1]=2;
	Array[2]=3;

	/*
	// !!! Pouzitie DIGRAPHS.
	// !!!!! Visual C++ toto vyzera, ze NEPODPORUJE.
	for (int i=0;i<3;i++)
	{
		wprintf_s(L"Value: [%d] !\n",Array<:i:>);
	}
	*/

	/*
	// !!! Pouzitie TRIGRAPHS.
	// !!!!! Visual C++ toto vyzera, ze NEPODPORUJE.
	for (int i=0;i<3;i++)
	{
		wprintf_s(L"Value: [%d] !\n",Array??(i??));
	}
	*/

	// !!!!! Visual C++ toto vyzera, ze NEPODPORUJE.
	wprintf_s(L"TRIGRAPH: [??!] !\n");
	// !!!!! Visual C++ toto vyzera, ze NEPODPORUJE.
	printf_s("TRIGRAPH: [??!] !\n");
	// !!!!! Visual C++ toto vyzera, ze NEPODPORUJE.
	printf("TRIGRAPH: [??!] !\n");

	wprintf_s(L"HEXA 7A: [%d] !\n",L'\x7A');
	// !!! Je to OCTAL cislo, ktore NESMIE pouzivat hodnoty '8' a '9'.
	wprintf_s(L"OCTAL 60: [%d] !\n",L'\60');

	wprintf_s(L"UNICODE: [%c] !\n",L'\u1e2b');
	wprintf_s(L"UNICODE: [%c] !\n",L'\U00001e2b');

	char														C=255;
	int															I=C;

	wprintf_s(L"255: [%d] !\n",I);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	//Test21();
	Test22();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------