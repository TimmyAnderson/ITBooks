//-------------------------------------------------------------------------------------------------------
// !!! Dohodil som to kvoli DEBILNYCH WARNINGS, ktore pri pouziti copy() papulovalo.
#define _SCL_SECURE_NO_WARNINGS
//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <crtdbg.h>
#include <new>
#include "CustomIntputIterator.h"
#include "CustomIntputIterator.cpp"
#include "PrimitiveCustomAllocator.h"
#include "PrimitiveCustomAllocator.cpp"
#include "MyCustomAllocator.h"
#include "MyCustomAllocator.cpp"
#include "Text.h"
#include "MyText.h"
#include "NewDelete.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf_s(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf_s(L"Expression: %s !\n\n\n", Expression);
}
//-------------------------------------------------------------------------------------------------------
void PrintInt(int Value)
{
	wprintf_s(L"ITEM: [%d] !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	// !!! Ako ITERATOR moze sluzit CLASS definovana v STL.
	for_each(Vector.begin(),Vector.end(),PrintInt);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	int															Array[]={1,2,3};

	// !!! Ako ITERATOR moze sluzit aj POINTER.
	for_each(&Array[0],&Array[_countof(Array)],PrintInt);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	int															Array[]={1,2,3};

	// !!! Ako ITERATOR moze sluzit aj CUSTOM CLASS.
	CCustomIntputIterator<int>									IteratorBegin(&Array[0]);
	CCustomIntputIterator<int>									IteratorEnd(&Array[_countof(Array)]);

	for_each(IteratorBegin,IteratorEnd,PrintInt);
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// !!! Na demonstraciu INSERTER ITERATORS pouzijem LIST, lebo ten ma VSETKY METODY push_back(), push_front() i insert().
	list<int>													List;

	List.push_back(1);
	List.push_back(2);
	List.push_back(3);

	fill_n(front_inserter(List),1,4);

	fill_n(back_inserter(List),1,5);

	list<int>::iterator											InsertPosition=List.begin();

	InsertPosition++;
	InsertPosition++;
	InsertPosition++;

	fill_n(insert_iterator<list<int>>(List,InsertPosition),1,6);

	for_each(List.begin(),List.end(),PrintInt);
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	// !!!!! Aj ked sa jedna o REVERSE ITERATOR, tak begin() a end() pouzivam ROVNAKO ako pri BEZNYCH ITERATORS.
	for_each(Vector.rbegin(),Vector.rend(),PrintInt);
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	// Budem zapisovat INT hodnoty.
	ostream_iterator<wstring,wchar_t>							Iterator1(wcout);
	ostream_iterator<int,wchar_t>								Iterator2(wcout);

	// Vypise na konzolu text.
	*Iterator1=L"Name: [Timmy";
	// !!! Po kazdom zapise by som MAL posunut ITERATOR. Hoci ak to nespravim NIC sa NESTANE.
	Iterator1++;

	*Iterator1=L" ";
	Iterator1++;

	*Iterator1=L"Anderson";
	Iterator1++;

	*Iterator1=L" ";
	Iterator1++;

	// Zapisem INT hodnotu.
	*Iterator2=12;
	Iterator2++;

	*Iterator1=L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	const int													SIZE=10;
	allocator<int>												Allocator;

	// Alokujem pamat pre ITEMS.
	allocator<int>::pointer										Memory=Allocator.allocate(SIZE,NULL);

	for (int i=0;i<SIZE;i++)
	{
		// Vytvorim ITEM v uz alokovanej pamati.
		Allocator.construct(&Memory[i],i);
	}

	for (int i=0;i<SIZE;i++)
	{
		wprintf_s(L"ITEM[%d]: [%d] !\n",i,Memory[i]);
	}

	for (int i=0;i<SIZE;i++)
	{
		// Odstranim ITEM v alokovanej pamati.
		Allocator.destroy(&Memory[i]);
	}

	// Dealokujem pamat alokovanu pre ITEMS.
	Allocator.deallocate(Memory,SIZE);
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	const int													SIZE=10;
	allocator<wstring>											Allocator;

	// Alokujem pamat pre ITEMS.
	allocator<wstring>::pointer									Memory=Allocator.allocate(SIZE,NULL);

	for (int i=0;i<SIZE;i++)
	{
		wstringstream											StringStream;

		StringStream << "Text " << i;

		wstring													String=StringStream.str();

		// Vytvorim ITEM v uz alokovanej pamati.
		Allocator.construct(&Memory[i],String);
	}

	for (int i=0;i<SIZE;i++)
	{
		wprintf_s(L"ITEM[%d]: [%s] !\n",i,Memory[i].c_str());
	}

	for (int i=0;i<SIZE;i++)
	{
		// Odstranim ITEM v alokovanej pamati.
		Allocator.destroy(&Memory[i]);
	}

	// Dealokujem pamat alokovanu pre ITEMS.
	Allocator.deallocate(Memory,SIZE);
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	const int													SIZE=10;

	// !!! Pouzijem CUSTOM ALLOCATOR. Je to iba pseudo ALLOCATOR, kedze v nom nemam ziadnu realnu implementaciu.
	CPrimitiveCustomAllocator<wstring>							Allocator;

	// Alokujem pamat pre ITEMS.
	allocator<wstring>::pointer									Memory=Allocator.allocate(SIZE,NULL);

	for (int i=0;i<SIZE;i++)
	{
		wstringstream											StringStream;

		StringStream << "Text " << i;

		wstring													String=StringStream.str();

		// Vytvorim ITEM v uz alokovanej pamati.
		Allocator.construct(&Memory[i],String);
	}

	for (int i=0;i<SIZE;i++)
	{
		wprintf_s(L"ITEM[%d]: [%s] !\n",i,Memory[i].c_str());
	}

	for (int i=0;i<SIZE;i++)
	{
		// Odstranim ITEM v alokovanej pamati.
		Allocator.destroy(&Memory[i]);
	}

	// Dealokujem pamat alokovanu pre ITEMS.
	Allocator.deallocate(Memory,SIZE);
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	// !!! Pouzijem CUSTOM ALLOCATOR.
	vector<int,CPrimitiveCustomAllocator<int>>					Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	for(vector<int,CPrimitiveCustomAllocator<int>>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	// !!! Pouzijem CUSTOM ALLOCATOR.
	vector<int,CMyCustomAllocator<int>>							Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	for(vector<int,CMyCustomAllocator<int>>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	// Alokujem RAW PAMAT. Aj ked ALOKUJEM pamat pre CText, tak kedze sa jedna o RAW PAMAT, ta sa NEVOLAJU CONSTRUCTORS.
	pair<CText*,ptrdiff_t>										Pair=get_temporary_buffer<CText>(3);

	if (Pair.second>0)
	{
		CText													Texts[]={CText(L"Text 1"),CText(L"Text 2"),CText(L"Text 3")};

		CText*													RawMemory=Pair.first;

		// !!! Pouzijem 'raw_storage_iterator' na inicializaciu OBJEKTOV. Ak by som ho NEPOUZIL dojde k CHYBE, pretoze ALGORITMS predpokladaju, ze PAMAT je INICIALIZOVANA a pouzivaju OPERATOR=.
		copy(&Texts[0],&Texts[_countof(Texts)],raw_storage_iterator<CText*,CText>(RawMemory));

		// !!!!! Toto volanie sposobi CHYBU pristupu k PAMATI.
		//copy(&Texts[0],&Texts[_countof(Texts)],RawMemory);

		for (int i=0;i<_countof(Texts);i++)
		{
			wprintf_s(L"!!!!! ITEM[%d]: [%s] !\n",i,RawMemory[i].GetText().c_str());
		}

		// !!! Kedze teraz som v 'RawMemory' spravil KOPIE objektov, pre ktore NIZSIE volana funkcia return_temporary_buffer() NEVOLA DESTRUCTORS, tak ich musim EXPLICITE UVOLNIT volanim DESTRUCTOR.
		for (int i=0;i<_countof(Texts);i++)
		{
			RawMemory[i].~CText();
		}

		// Uvolnim alokovanu RAW PAMAT.
		return_temporary_buffer(Pair.first);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	// Alokujem RAW PAMAT. Aj ked ALOKUJEM pamat pre CText, tak kedze sa jedna o RAW PAMAT, ta sa NEVOLAJU CONSTRUCTORS.
	pair<CText*,ptrdiff_t>										Pair=get_temporary_buffer<CText>(3);

	if (Pair.second>0)
	{
		CText													Texts[]={CText(L"Text 1"),CText(L"Text 2"),CText(L"Text 3")};

		CText*													RawMemory=Pair.first;

		// !!! OBJEKTY sa INICIALIZUJU cez uninitialized_copy(). Je to vlastne ALTERNATIVA voci 'raw_storage_iterator'.
		uninitialized_copy(&Texts[0],&Texts[_countof(Texts)],RawMemory);

		for (int i=0;i<_countof(Texts);i++)
		{
			wprintf_s(L"!!!!! ITEM[%d]: [%s] !\n",i,RawMemory[i].GetText().c_str());
		}

		// !!! Kedze teraz som v 'RawMemory' spravil KOPIE objektov, pre ktore NIZSIE volana funkcia return_temporary_buffer() NEVOLA DESTRUCTORS, tak ich musim EXPLICITE UVOLNIT volanim DESTRUCTOR.
		for (int i=0;i<_countof(Texts);i++)
		{
			RawMemory[i].~CText();
		}

		// Uvolnim alokovanu RAW PAMAT.
		return_temporary_buffer(Pair.first);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	// !!! Tento BUFFER sa pouzije na 'alokovanie' (presnejsie priradzovanie) pamate OPERATOROM PLACEMENT NEW.
	char*														Buffer=new char[10000];

	memset(Buffer,0,sizeof(Buffer));

	// Pouzitie standardneho NEW.
	CMyText*													Text1=new CMyText(L"STANDARD OPERATOR NEW");

	// !!! Urcim si poziciu, kde NAMAPUJEM cez PLACEMENT NEW novy OBJEKT.
	char*														Pointer=Buffer;

	// !!!!! Pouzitie PLACEMENT NEW. V tomto pripade sa pre OBJEKT 'Text2' NEALOKUJE PAMAT na HEAP, iba sa objekt 'NAMAPUJE' do pozicie POINTERA 'Pointer' (zaciatok BUFFER).
	// !!!!! PLACEMENT NEW aj ked NEALOKUJE ZIADNU PAMAT, tak VOLA CONSTRUCTOR.
	CMyText*													Text2=new (Pointer) CMyText(L"PLACEMENT SYNTAX 1 for OPERATOR NEW");

	// !!!!! Posuniem MAPOVANIE na DALSIU VOLNU POZICIU v BUFFERI.
	Pointer+=sizeof(CMyText);

	CMyText*													Text3=new (Pointer) CMyText(L"PLACEMENT SYNTAX 2 for OPERATOR NEW");

	wprintf_s(L"!!! Text1 [%s] !\n",Text1->GetText().c_str());
	wprintf_s(L"!!! Text2 [%s] !\n",Text2->GetText().c_str());
	wprintf_s(L"!!! Text3 [%s] !\n",Text3->GetText().c_str());

	delete(Text1);

	// !!!!! OPERATOR DELETE NEMA PLACEMENT EXPRESSION.
	// !!!!! Objekt 'alokovany' cez PLACEMENT NEW (kedze v skutocnosti PLACEMENT ZIADNU PAMAT NEALOKUJE, iba MAPUJE EXISATUJUCU PAMAT), ak by nan bol zavolany DELETE, skoncilo by to NARUSENIM PAMATE, kedze PLACEMENT NEW ZIADNU PAMAT na HEAP NEALOKUJE iba MAPUJE PAMAT z BUFFERA zaslaneho ako PARAMETER PLACEMENT NEW.
	//delete(Text2);
	//delete(Text3);

	// !!!!! Pozor toto NEFUNGUJE. C++ ho NEINTEPRETUJE ako DELETE s PLACEMENT EXPRESSION (ktory NEPODPORUJE), ale ako 2 EXPRESSIONS oddelene CIARKOU.
	//delete(Text2,Buffer);

	// !!!!! Dokonca i toto C++ akceptuje, aj ked je to logicky NEZMYSEL.
	//delete(Text2,Buffer,Buffer,Buffer,Buffer,Buffer);

	// !!!!! Kedze [delete(Text2)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text2->~CMyText();

	// !!!!! Kedze [delete(Text3)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text3->~CMyText();

	// Dealokujem BUFFER.
	delete[](Buffer);
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	// !!! Tento BUFFER sa pouzije na 'alokovanie' (presnejsie priradzovanie) pamate OPERATOROM PLACEMENT NEW.
	char														Buffer[10000];

	memset(Buffer,0,sizeof(Buffer));

	// Pouzitie standardneho NEW.
	CMyText*													Text1=new CMyText(L"STANDARD OPERATOR NEW");

	// !!! Urcim si poziciu, kde NAMAPUJEM cez PLACEMENT NEW novy OBJEKT.
	char*														Pointer=Buffer;

	// !!!!! Pouzitie PLACEMENT NEW. V tomto pripade sa pre OBJEKT 'Text2' NEALOKUJE PAMAT na HEAP, iba sa objekt 'NAMAPUJE' do pozicie POINTERA 'Pointer' (zaciatok BUFFER).
	// !!!!! PLACEMENT NEW aj ked NEALOKUJE ZIADNU PAMAT, tak VOLA CONSTRUCTOR.
	CMyText*													Text2=new (Pointer) CMyText(L"PLACEMENT SYNTAX 1 for OPERATOR NEW");

	// !!!!! Posuniem MAPOVANIE na DALSIU VOLNU POZICIU v BUFFERI.
	Pointer+=sizeof(CMyText);

	CMyText*													Text3=new (Pointer) CMyText(L"PLACEMENT SYNTAX 2 for OPERATOR NEW");

	wprintf_s(L"!!! Text1 [%s] !\n",Text1->GetText().c_str());
	wprintf_s(L"!!! Text2 [%s] !\n",Text2->GetText().c_str());
	wprintf_s(L"!!! Text3 [%s] !\n",Text3->GetText().c_str());

	delete(Text1);

	// !!!!! OPERATOR DELETE NEMA PLACEMENT EXPRESSION.
	// !!!!! Objekt 'alokovany' cez PLACEMENT NEW (kedze v skutocnosti PLACEMENT ZIADNU PAMAT NEALOKUJE, iba MAPUJE EXISATUJUCU PAMAT), ak by nan bol zavolany DELETE, skoncilo by to NARUSENIM PAMATE, kedze PLACEMENT NEW ZIADNU PAMAT na HEAP NEALOKUJE iba MAPUJE PAMAT z BUFFERA zaslaneho ako PARAMETER PLACEMENT NEW.
	//delete(Text2);
	//delete(Text3);

	// !!!!! Pozor toto NEFUNGUJE. C++ ho NEINTEPRETUJE ako DELETE s PLACEMENT EXPRESSION (ktory NEPODPORUJE), ale ako 2 EXPRESSIONS oddelene CIARKOU.
	//delete(Text2,Buffer);

	// !!!!! Dokonca i toto C++ akceptuje, aj ked je to logicky NEZMYSEL.
	//delete(Text2,Buffer,Buffer,Buffer,Buffer,Buffer);

	// !!!!! Kedze [delete(Text2)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text2->~CMyText();

	// !!!!! Kedze [delete(Text3)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text3->~CMyText();

	// !!! Kedze BUFFER je v STACK, tak sa uvolni na KONCI FUNKCIE.
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	CNewDelete*													NewDelete1=new CNewDelete();
	CNewDelete*													NewDelete2=new (Param1) CNewDelete();
	CNewDelete*													NewDelete3=new (Param1,Param2) CNewDelete();

	delete(NewDelete1);
	NewDelete2->operator delete(NewDelete2,Param1);
	NewDelete3->operator delete(NewDelete3,Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	while(true)
	{
		// !!! NEHODI EXCEPTION, ale vracia NULL.
		void*													Temp=new (nothrow) char[100000000];

		if (Temp!=NULL)
		{
			wprintf_s(L"Memory ALLOCATED !\n");
		}
		else
		{
			wprintf_s(L"OUT OF MEMORY !\n");
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT,0);

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
	Test17();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------