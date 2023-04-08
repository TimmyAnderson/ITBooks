//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cstdlib>
#include "MyDebug.h"
#include "NewDeleteGlobalOperators.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass1(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CGlobalNewDelete*											NewDelete=new CGlobalNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass2(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CGlobalNewDelete*											NewDelete=new CGlobalNewDelete();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CGlobalNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	operator delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass3(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDelete*										NewDelete=new (Param) CGlobalNewDelete();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE.
		// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
		delete(NewDelete);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass4(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDelete*										NewDelete=new (Param) CGlobalNewDelete();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDelete();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass5(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDelete*										NewDelete=new (Param) CGlobalNewDelete();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDelete();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE s 1 PARAMETER cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete,Param);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsSimpleClass6(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param1(L"XXX");
		wstring													Param2(L"YYY");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 2 PARAMETERS.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDelete*										NewDelete=new (Param1,Param2) CGlobalNewDelete();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDelete();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE s 2 PARAMETERS cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete,Param1,Param2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy1(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CGlobalNewDeleteDerived*									NewDelete=new CGlobalNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy2(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CGlobalNewDeleteDerived*									NewDelete=new CGlobalNewDeleteDerived();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CGlobalNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	operator delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy3(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDeleteDerived*								NewDelete=new (Param) CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE.
		// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
		delete(NewDelete);
}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy4(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDeleteDerived*								NewDelete=new (Param) CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy5(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param(L"XXX");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDeleteDerived*								NewDelete=new (Param) CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE s 1 PARAMETER cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete,Param);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGlobalNewDeleteOperatorsClassHierarchy6(void)
{
	PrintLineSeparator();

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param1(L"XXX");
		wstring													Param2(L"YYY");

		// !!! Vola sa PRETAZENY OPERATOR NEW s 2 PARAMETERS.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CGlobalNewDeleteDerived*								NewDelete=new (Param1,Param2) CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CGlobalNewDeleteDerived();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE s 2 PARAMETERS cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		operator delete(NewDelete,Param1,Param2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsSimpleClass1(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE].
	CGlobalNewDelete*											Array=new CGlobalNewDelete[ARRAY_SIZE];

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index].SetDummyA(10*(Index+1)+1);
		Array[Index].SetDummyB(10*(Index+1)+2);
		Array[Index].SetDummyC(10*(Index+1)+3);
		Array[Index].SetDummyD(10*(Index+1)+4);
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		std::wcout << L"INDEX [" << Index << L"] DUMMY A [" << Array[Index].GetDummyA() << L"] DUMMY B [" << Array[Index].GetDummyB() << L"] DUMMY C [" << Array[Index].GetDummyC() << L"] DUMMY D [" << Array[Index].GetDummyD() << L"] !" << std::endl;
	}

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! C++ AUTOMATICKY vola DESTRUCTORS pre jednotlive ITEMS.
	delete[](Array);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsSimpleClass2(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CGlobalNewDelete);

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE].
	CGlobalNewDelete*											Array=new CGlobalNewDelete[ARRAY_SIZE];

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index].SetDummyA(10*(Index+1)+1);
		Array[Index].SetDummyB(10*(Index+1)+2);
		Array[Index].SetDummyC(10*(Index+1)+3);
		Array[Index].SetDummyD(10*(Index+1)+4);
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		std::wcout << L"INDEX [" << Index << L"] DUMMY A [" << Array[Index].GetDummyA() << L"] DUMMY B [" << Array[Index].GetDummyB() << L"] DUMMY C [" << Array[Index].GetDummyC() << L"] DUMMY D [" << Array[Index].GetDummyD() << L"] !" << std::endl;
	}

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		// !!!!! Kedze OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre JEDNOTLIVE ITEMS, je ich nutne volat EXPLICITNE.
		Array[Index].~CGlobalNewDelete();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	operator delete[](PointerToBuffer,BUFFER_SIZE);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsSimpleClass3(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CGlobalNewDelete);

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param1(L"XXX");
		wstring													Param2(L"YYY");

		// !!! Vola sa PRETAZENY OPERATOR NEW[] s 2 PARAMETERS pomocou PLACEMENT SYNTAX.
		// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDelete)*ARRAY_SIZE].
		CGlobalNewDelete*										Array=new (BUFFER_SIZE,Param1,Param2) CGlobalNewDelete[ARRAY_SIZE];

		PrintLineSeparator();

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			Array[Index].SetDummyA(10*(Index+1)+1);
			Array[Index].SetDummyB(10*(Index+1)+2);
			Array[Index].SetDummyC(10*(Index+1)+3);
			Array[Index].SetDummyD(10*(Index+1)+4);
		}

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			std::wcout << L"INDEX [" << Index << L"] DUMMY A [" << Array[Index].GetDummyA() << L"] DUMMY B [" << Array[Index].GetDummyB() << L"] DUMMY C [" << Array[Index].GetDummyC() << L"] DUMMY D [" << Array[Index].GetDummyD() << L"] !" << std::endl;
		}

		PrintLineSeparator();

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			// !!!!! Kedze OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre JEDNOTLIVE ITEMS, je ich nutne volat EXPLICITNE.
			Array[Index].~CGlobalNewDelete();
		}

		PrintLineSeparator();

		size_t*													PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
		// !!! Vola sa PRETAZENY OPERATOR DELETE[] s 2 PARAMETERS.
		// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
		// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
		operator delete[](PointerToBuffer,BUFFER_SIZE,Param1,Param2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsClassHierarchy1(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE].
	CGlobalNewDeleteDerived*									Array=new CGlobalNewDeleteDerived[ARRAY_SIZE];

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index].SetDummyBase1A(10*(Index+1)+1);
		Array[Index].SetDummyBase1B(10*(Index+1)+2);
		Array[Index].SetDummyBase2A(10*(Index+1)+3);
		Array[Index].SetDummyBase2B(10*(Index+1)+4);
		Array[Index].SetDummyDerivedA(10*(Index+1)+5);
		Array[Index].SetDummyDerivedB(10*(Index+1)+6);
		Array[Index].SetDummyDerivedC(10*(Index+1)+7);
		Array[Index].SetDummyDerivedD(10*(Index+1)+8);
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		std::wcout << L"INDEX [" << Index << L"] DUMMY BASE 1A [" << Array[Index].GetDummyBase1A() << L"] DUMMY BASE 1B [" << Array[Index].GetDummyBase1B() << L"] DUMMY BASE 2A [" << Array[Index].GetDummyBase2A() << L"] DUMMY BASE 2B [" << Array[Index].GetDummyBase2B() << L"] DUMMY DERIVED A [" << Array[Index].GetDummyDerivedA() << L"] DUMMY DERIVED B [" << Array[Index].GetDummyDerivedB() << L"] DUMMY DERIVED C [" << Array[Index].GetDummyDerivedC() << L"] DUMMY DERIVED D [" << Array[Index].GetDummyDerivedD() << L"] CALLED !" << std::endl;
	}

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! C++ AUTOMATICKY vola DESTRUCTORS pre jednotlive ITEMS.
	delete[](Array);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsClassHierarchy2(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CGlobalNewDeleteDerived);

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE].
	CGlobalNewDeleteDerived*									Array=new CGlobalNewDeleteDerived[ARRAY_SIZE];

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index].SetDummyBase1A(10*(Index+1)+1);
		Array[Index].SetDummyBase1B(10*(Index+1)+2);
		Array[Index].SetDummyBase2A(10*(Index+1)+3);
		Array[Index].SetDummyBase2B(10*(Index+1)+4);
		Array[Index].SetDummyDerivedA(10*(Index+1)+5);
		Array[Index].SetDummyDerivedB(10*(Index+1)+6);
		Array[Index].SetDummyDerivedC(10*(Index+1)+7);
		Array[Index].SetDummyDerivedD(10*(Index+1)+8);
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		std::wcout << L"INDEX [" << Index << L"] DUMMY BASE 1A [" << Array[Index].GetDummyBase1A() << L"] DUMMY BASE 1B [" << Array[Index].GetDummyBase1B() << L"] DUMMY BASE 2A [" << Array[Index].GetDummyBase2A() << L"] DUMMY BASE 2B [" << Array[Index].GetDummyBase2B() << L"] DUMMY DERIVED A [" << Array[Index].GetDummyDerivedA() << L"] DUMMY DERIVED B [" << Array[Index].GetDummyDerivedB() << L"] DUMMY DERIVED C [" << Array[Index].GetDummyDerivedC() << L"] DUMMY DERIVED D [" << Array[Index].GetDummyDerivedD() << L"] CALLED !" << std::endl;
	}

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		// !!!!! Kedze OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre JEDNOTLIVE ITEMS, je ich nutne volat EXPLICITNE.
		Array[Index].~CGlobalNewDeleteDerived();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	operator delete[](PointerToBuffer,BUFFER_SIZE);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestGlobalNewDeleteArrayOperatorsClassHierarchy3(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CGlobalNewDeleteDerived);

	{
		// !!!!! Aj CLASS [wstring] vola CUSTOM OPERATOR NEW a CUSTOM OPERATOR DELETE.
		wstring													Param1(L"XXX");
		wstring													Param2(L"YYY");

		// !!! Vola sa PRETAZENY OPERATOR NEW[] s 2 PARAMETERS pomocou PLACEMENT SYNTAX.
		// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CGlobalNewDeleteDerived)*ARRAY_SIZE].
		CGlobalNewDeleteDerived*								Array=new (BUFFER_SIZE,Param1,Param2) CGlobalNewDeleteDerived[ARRAY_SIZE];

		PrintLineSeparator();

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			Array[Index].SetDummyBase1A(10*(Index+1)+1);
			Array[Index].SetDummyBase1B(10*(Index+1)+2);
			Array[Index].SetDummyBase2A(10*(Index+1)+3);
			Array[Index].SetDummyBase2B(10*(Index+1)+4);
			Array[Index].SetDummyDerivedA(10*(Index+1)+5);
			Array[Index].SetDummyDerivedB(10*(Index+1)+6);
			Array[Index].SetDummyDerivedC(10*(Index+1)+7);
			Array[Index].SetDummyDerivedD(10*(Index+1)+8);
		}

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			std::wcout << L"INDEX [" << Index << L"] DUMMY BASE 1A [" << Array[Index].GetDummyBase1A() << L"] DUMMY BASE 1B [" << Array[Index].GetDummyBase1B() << L"] DUMMY BASE 2A [" << Array[Index].GetDummyBase2A() << L"] DUMMY BASE 2B [" << Array[Index].GetDummyBase2B() << L"] DUMMY DERIVED A [" << Array[Index].GetDummyDerivedA() << L"] DUMMY DERIVED B [" << Array[Index].GetDummyDerivedB() << L"] DUMMY DERIVED C [" << Array[Index].GetDummyDerivedC() << L"] DUMMY DERIVED D [" << Array[Index].GetDummyDerivedD() << L"] CALLED !" << std::endl;
		}

		PrintLineSeparator();

		for(int Index=0;Index<ARRAY_SIZE;Index++)
		{
			// !!!!! Kedze OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre JEDNOTLIVE ITEMS, je ich nutne volat EXPLICITNE.
			Array[Index].~CGlobalNewDeleteDerived();
		}

		PrintLineSeparator();

		size_t*													PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
		// !!! Vola sa PRETAZENY OPERATOR DELETE[] s 2 PARAMETERS.
		// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
		// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
		operator delete[](PointerToBuffer,BUFFER_SIZE,Param1,Param2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestGlobalNewDeleteOperatorsSimpleClass1();
	//TestGlobalNewDeleteOperatorsSimpleClass2();
	//TestGlobalNewDeleteOperatorsSimpleClass3();
	//TestGlobalNewDeleteOperatorsSimpleClass4();
	//TestGlobalNewDeleteOperatorsSimpleClass5();
	//TestGlobalNewDeleteOperatorsSimpleClass6();
	//TestGlobalNewDeleteOperatorsClassHierarchy1();
	//TestGlobalNewDeleteOperatorsClassHierarchy2();
	//TestGlobalNewDeleteOperatorsClassHierarchy3();
	//TestGlobalNewDeleteOperatorsClassHierarchy4();
	//TestGlobalNewDeleteOperatorsClassHierarchy5();
	//TestGlobalNewDeleteOperatorsClassHierarchy6();
	//TestGlobalNewDeleteArrayOperatorsSimpleClass1();
	//TestGlobalNewDeleteArrayOperatorsSimpleClass2();
	//TestGlobalNewDeleteArrayOperatorsSimpleClass3();
	//TestGlobalNewDeleteArrayOperatorsClassHierarchy1();
	//TestGlobalNewDeleteArrayOperatorsClassHierarchy2();
	TestGlobalNewDeleteArrayOperatorsClassHierarchy3();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------