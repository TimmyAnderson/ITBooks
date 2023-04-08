//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include "SName.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
int					GlobalValue=999;
//-------------------------------------------------------------------------------------------------------
wstring ConvertToUpper(wstring Input)
{
	wstring			Ret;

	for(wstring::iterator i=Input.begin();i!=Input.end();i++)
	{
		wchar_t		Char=*i;

		if (Char>=L'a' && Char<=L'z')
		{
			wchar_t	NewChar=Char-(L'a'-L'A');

			Ret.push_back(NewChar);
		}
		else
		{
			Ret.push_back(Char);
		}
	}

	return(Ret);
}
//-------------------------------------------------------------------------------------------------------
void Increment(int &Value)
{
	Value++;
}
//-------------------------------------------------------------------------------------------------------
int& Add10(int &Value)
{
	Value+=10;

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
int& Add10OK(int Value)
{
	GlobalValue+=Value+10;

	// OK. Vraciam REFERENCIU na GLOBALNU PREMENNU, ktora ostane v PAMATI aj po SKONCENI VOLANIA FUNKCIE.
	return(GlobalValue);
}
//-------------------------------------------------------------------------------------------------------
// HODI WARNING, lebo sa pokusam vracat REFERENCE na TEMPORARY PREMENNU (PARAMETER), ktora po skonceni volania funkcie ZANIKNE, co by pri pristupe k takejto premennej viedlo k NARUSENIU PAMATE.
/*
int& Add10Error1(int Value)
{
	Value+=10;

	// !!!!! CHYBA. NESMIEM VRACAT REFERENCIU na PARAMETER.
	return(Value);
}
*/
//-------------------------------------------------------------------------------------------------------
// HODI WARNING, lebo sa pokusam vracat REFERENCE na LOKALNU PREMENNU, ktora po skonceni volania funkcie ZANIKNE, co by pri pristupe k takejto premennej viedlo k NARUSENIU PAMATE.
/*
int& Add10Error2(int& Value)
{
	int				Temp=Value+10;

	// !!!!! CHYBA. NESMIEM VRACAT REFERENCIU na LOKALNU PREMENNU.
	return(Temp);
}
*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestPointerToFunction(void)
{
	wstring				String=L"Timmy Anderson";

	// POINTER na FUNKCIU.
	wstring				(*PointerToFunction1)(wstring)=&ConvertToUpper;

	// POINTER na FUNKCIU - NEMUSIM pouzit operator &.
	wstring				(*PointerToFunction2)(wstring)=ConvertToUpper;

	// Zavolam FUNKCIU.
	wstring				Result1=PointerToFunction1(String);

	// Zavolam FUNKCIU.
	wstring				Result2=PointerToFunction2(String);

	wcout << L"Input string: [" << String << L"] !\n";
	wcout << L"Output string 1: [" << Result1 << L"] !\n";
	wcout << L"Output string 2: [" << Result2 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestArrayInitializers(void)
{
	// Posledne dve ITEMS maju hodnotu 0.
	int					Array1[5]={1,2,3};

	// Posledne dve ITEMS maju hodnotu 0.
	double				Array2[5]={1.1,2.2,3.3};

	// NEINICIALIZUJE posledne 2 ITEMS na 0.
	char				Array3[5]={'A','B','C'};

	// NEINICIALIZUJE posledne 2 ITEMS na 0.
	wchar_t				Array4[5]={L'A',L'B',L'C'};

	wcout << L"Array1: ";

	for(int i=0;i<_countof(Array1);i++)
	{
		if (i!=0)
		{
			wcout << L", ";
		}

		wcout << Array1[i];
	}

	wcout << L" !\n";

	wcout << L"Array2: ";

	for(int i=0;i<_countof(Array2);i++)
	{
		if (i!=0)
		{
			wcout << L", ";
		}

		wcout << Array2[i];
	}

	wcout << L" !\n";

	wcout << L"Array3: ";

	for(int i=0;i<_countof(Array3);i++)
	{
		if (i!=0)
		{
			wcout << L", ";
		}

		wcout << Array3[i];
	}

	wcout << L" !\n";

	wcout << L"Array4: ";

	for(int i=0;i<_countof(Array4);i++)
	{
		if (i!=0)
		{
			wcout << L", ";
		}

		wcout << Array4[i];
	}

	wcout << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestStringLiterals(void)
{
	wchar_t				MultiLineLiteral[]=	L"This is "
											L"Multiline literal";
										
	wcout << L"MultiLineLiteral: [" << MultiLineLiteral << L"] !\n";

	
	wchar_t				SimpleLiteral[]=L"Timmy Anderson";

	wcout << L"SimpleLiteral: [" << SimpleLiteral << L"] !\n";

	// POINTER na LITERAL.
	wchar_t*			PointerToSimpleLiteral=SimpleLiteral;

	// Pokus o zapis do LITERALU.
	// Vo VC++ ZAPISE BEZ PROBLEMOV PREBEHNE.
	PointerToSimpleLiteral[0]=L'X';

	wcout << L"PointerToSimpleLiteral: [" << PointerToSimpleLiteral << L"] !\n";
	wcout << L"SimpleLiteral: [" << SimpleLiteral << L"] !\n";

	wchar_t				SameLiteral1[]={L"Jenny Thompson"};
	wchar_t				SameLiteral2[]={L"Jenny Thompson"};

	wcout << L"SameLiteral1: [" << SameLiteral1 << L"] !\n";
	wcout << L"SameLiteral2: [" << SameLiteral2 << L"] !\n";

	void*				PointerToSameLiteral1=SameLiteral1;
	void*				PointerToSameLiteral2=SameLiteral2;

	wcout << L"PointerToSameLiteral1: [" << PointerToSameLiteral1 << L"] !\n";
	wcout << L"PointerToSameLiteral2: [" << PointerToSameLiteral2 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestArraysAndPointer(void)
{
	wchar_t				Array1[]=L"Timmy Anderson";
	wchar_t				Array2[]=L"Timmy Anderson";
	wchar_t*			Pointer1=Array1;
	wchar_t*			Pointer2=L"Jenny Thompson";

	wcout << L"Array1: [" << Array1 << L"] !\n";
	wcout << L"Array2: [" << Array2 << L"] !\n";

	wcout << L"Pointer1: [" << Pointer1 << L"] !\n";
	wcout << L"Pointer2: [" << Pointer2 << L"] !\n";

	// Toto priradenie hodi KOMPILACNU CHYBU.
	//Array1=Pointer2;

	// Aj toto priradenie hodi KOMPILACNU CHYBU, lebo Array2 NIE JE LVALUE.
	//Array1=Array2;

	int					IntArray[]={1,2,3};

	// !!! POINTER ukazujuci za POSLEDNY ITEM je VALIDNY POINTER z ktoreho vsak NEMOZNO CITAT ani do ZAPISOVAT.
	int*				PointerJustAfterArray=&IntArray[3];

	// CHYBNY POINTER - ukazuje az 2 ITEMS za koncom ARRAY.
	int*				InvalidPointer=&IntArray[4];

	wcout << L"Array: ";

	// POINTER UKAZUJUCI HNED za POSLEDNY ITEM ARRAY je mozne pouzit v ALGORITMOCH.
	for(int* Pointer=IntArray;Pointer!=PointerJustAfterArray;Pointer++)
	{
		wcout << *Pointer;
		wcout << " ";
	}

	wcout << L"!\n";
}
//-------------------------------------------------------------------------------------------------------
void TestConstants(void)
{
	// Pole KONSTANT.
	const int			ConstArray[]={1,2,3};

	wcout << L"ConstArray: ";

	for(int i=0;i<_countof(ConstArray);i++)
	{
		if (i!=0)
		{
			wcout << L", ";
		}

		wcout << ConstArray[i];
	}

	wcout << L" !\n";

	// Pokus o ZAPIS do ARRAY ITEM ZLYHA, kedze sa jedna o KONSTATNY ARRAY.
	//ConstArray[0]=10;

	int						Value1=100;
	int						Value2=200;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";

	const int*				PointerToConstInt=&Value1;

	wcout << L"PointerToConstInt: [" << *PointerToConstInt << L"] !\n";

	// Povolena operacia.
	PointerToConstInt=&Value2;

	wcout << L"PointerToConstInt: [" << *PointerToConstInt << L"] !\n";

	// !!! NEPOVOLENA OPERACIA.
	//(*PointerToConstInt)++;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";

	int *const				ConstPointerToInt=&Value1;

	wcout << L"PointerToConstInt: [" << *PointerToConstInt << L"] !\n";

	// Povolena operacia.
	(*ConstPointerToInt)++;

	// !!! NEPOVOLENA OPERACIA.
	//ConstPointerToInt=&Value2;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";

	const int *const		ConstPointerToConstInt=&Value1;

	wcout << L"ConstPointerToConstInt: [" << *ConstPointerToConstInt << L"] !\n";

	// !!! NEPOVOLENA OPERACIA.
	//(*ConstPointerToConstInt)++;

	// !!! NEPOVOLENA OPERACIA.
	//ConstPointerToConstInt=&Value2;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestReference1(void)
{
	int				Value=100;

	// Vytvorim ALIAS na 'Value'.
	int&			ReferenceToValue=Value;

	wcout << L"Value: [" << Value << L"] !\n";
	wcout << L"ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	// Zmenim hodnotu 'Value' - zmeni sa aj hodnota 'ReferenceToValue'.
	Value=50;

	wcout << L"Value: [" << Value << L"] !\n";
	wcout << L"ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	// Zmenim hodnotu 'ReferenceToValue' - zmeni sa aj hodnota 'Value'.
	ReferenceToValue=300;

	wcout << L"Value: [" << Value << L"] !\n";
	wcout << L"ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	void*			PointerToValue=&Value;
	void*			PointerToReferenceToValue=&ReferenceToValue;

	// 'PointerToValue' a 'PointerToReferenceToValue' odkazuju na TO ISTE MIESTO v PAMATI.
	wcout << L"PointerToValue: [" << PointerToValue << L"] !\n";
	wcout << L"PointerToReferenceToValue: [" << PointerToReferenceToValue << L"] !\n";

	if (PointerToReferenceToValue==PointerToReferenceToValue)
	{
		wcout << L"PointerToValue and PointerToReferenceToValue ARE SAME !\n";
	}
	else
	{
		wcout << L"PointerToValue and PointerToReferenceToValue ARE DIFFERENT !\n";
	}

	int				OtherValue=200;

	// !!! Toto nie je INICIALIZACIA REFERENCE, ale iba PRIRADENIE HODNOTY premennej 'OtherValue' do 'ReferenceToValue'. Tym, ze 'ReferenceToValue' REFERUJE na 'Value' DOJDE aj k ZMENE 'Value'.
	ReferenceToValue=OtherValue;

	// !!! 'Value' a 'ReferenceToValue' ukazuju na TU ISTU HODNOTU a teda MAJU TU ISTU HODNOTU.
	wcout << L"Value: [" << Value << L"] !\n";
	wcout << L"ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	// 'PointerToValue' a 'PointerToReferenceToValue' odkazuju na TO ISTE MIESTO v PAMATI.
	wcout << L"PointerToValue: [" << PointerToValue << L"] !\n";
	wcout << L"PointerToReferenceToValue: [" << PointerToReferenceToValue << L"] !\n";

	if (PointerToReferenceToValue==PointerToReferenceToValue)
	{
		wcout << L"PointerToValue and PointerToReferenceToValue ARE SAME !\n";
	}
	else
	{
		wcout << L"PointerToValue and PointerToReferenceToValue ARE DIFFERENT !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void TestReference2(void)
{
	// Hodi KOMPILACNU CHYBU - NON-CONST REFERENCE na NON-LVALUE NIE JE MOZNE VYTVORIT.
	//int&			ReferenceToValue=100;

	// Hodi KOMPILACNU CHYBU - NIE JE MOZNE vytvorit pole REFERENCES.
	//int&			ArrayOfReferences[100];

	
	int				SomeValue=100;
	int*			PointerToSomeValue=&SomeValue;

	// Hodi KOMPILACNU CHYBU - NIE JE MOZNE POINTER na REFERENCE.
	//int&*			ReferencePointer=&SomeValue;

	// !!! Toto vsak prekompiluje, pretoze REFERENCE na POINTER je MOZNE VYTVORIT.
	int*&			PointerReference=PointerToSomeValue;

	wcout << L"SomeValue: [" << SomeValue << L"] !\n";
	wcout << L"PointerToSomeValue - VALUE: [" << *PointerToSomeValue << L"] !\n";
	wcout << L"PointerReference - VALUE: [" << *PointerReference << L"] !\n";
	wcout << L"PointerToSomeValue - ADDRESS: [" << PointerToSomeValue << L"] !\n";
	wcout << L"PointerReference - ADDRESS: [" << PointerReference << L"] !\n";
	

	// Toto je OK, lebo sa jedna o KONSTANTNU REFERENCIU. C++ si vytvori TEMPORARY PREMENNU na ktoru sa bude REFEROVAT.
	const int&		ReferenceToConstant1=100;

	wcout << L"ReferenceToConstant1: [" << ReferenceToConstant1 << L"] !\n";

	const int		SOME_CONST=200;

	// !!! Teraz sa vsak TEMPORARY PREMENNA NEVYTVARA, kedze 'SOME_CONST' je LVALUE.
	const int&		ReferenceToConstant2=SOME_CONST;

	wcout << L"ReferenceToConstant2: [" << ReferenceToConstant2 << L"] !\n";

	const int*		PointerToSOME_CONST=&SOME_CONST;
	const int*		PointerToReferenceToConstant2=&ReferenceToConstant2;

	wcout << L"PointerToSOME_CONST: [" << PointerToSOME_CONST << L"] !\n";
	wcout << L"PointerToReferenceToConstant2: [" << PointerToReferenceToConstant2 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestReference3(void)
{
	int				Value=100;
	int&			ReferenceToValue=Value;

	wcout << L"Value: [" << Value << L"] !\n";
	wcout << L"ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	Increment(Value);

	wcout << L"After INCREMENT Value - Value: [" << Value << L"] !\n";
	wcout << L"After INCREMENT Value - ReferenceToValue: [" << ReferenceToValue << L"] !\n";

	Increment(ReferenceToValue);

	wcout << L"After INCREMENT ReferenceToValue - Value: [" << Value << L"] !\n";
	wcout << L"After INCREMENT ReferenceToValue - ReferenceToValue: [" << ReferenceToValue << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestReference4(void)
{
	int				ValueIn=100;

	wcout << L"ValueIn: [" << ValueIn << L"] !\n";

	// !!!!! Kedze 'ValueIn' je prenasana ako REFERENCE a ZAROVEN je i VRACANA z funkcie Add10() ako REFERENCE, REFERENCES 'ValueIn' a 'ValueOut' budu REFEROVAT na TU ISTU PREMENNU.
	int&			ValueOut=Add10(ValueIn);

	wcout << L"AFTER CALL - ValueIn: [" << ValueIn << L"] !\n";
	wcout << L"AFTER CALL - ValueOut: [" << ValueOut << L"] !\n";

	ValueOut++;

	wcout << L"AFTER CHANGE - ValueIn: [" << ValueIn << L"] !\n";
	wcout << L"AFTER CHANGE - ValueOut: [" << ValueOut << L"] !\n";

	int*			PointerToValueIn=&ValueIn;
	int*			PointerToValueOut=&ValueOut;

	// 'PointerToValueIn' a 'PointerToValueOut' odkazuju na TO ISTE MIESTO v PAMATI.
	wcout << L"PointerToValueIn: [" << PointerToValueIn << L"] !\n";
	wcout << L"PointerToValueOut: [" << PointerToValueOut << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void TestStruct(void)
{
	// Inicializacia STRUCTURE.
	SName			Name={L"Timmy",L"Anderson",12};

	wcout << L"Name.MFirstName: [" << Name.MFirstName << L"] !\n";
	wcout << L"Name.MLastName: [" << Name.MLastName << L"] !\n";
	wcout << L"Name.MAge: [" << Name.MAge << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//TestPointerToFunction();
	//TestArrayInitializers();
	//TestStringLiterals();
	//TestArraysAndPointer();
	//TestConstants();
	//TestReference1();
	//TestReference2();
	//TestReference3();
	//TestReference4();
	TestStruct();
	
	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------