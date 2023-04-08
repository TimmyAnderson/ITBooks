//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CSubscriptOperators.h"
#include "CFunctionCallOperators.h"
#include "CDereferencingOperatorsPointerToClass.h"
#include "CDereferencingOperatorsClass.h"
#include "CDereferencingOperatorsPointerToPrimitiveType.h"
#include "CDereferencingOperatorsPrimitiveType.h"
#include "CIncrementDecrementOperators.h"
#include "CNewDelete.h"
#include "CNewDeleteBase1.h"
#include "CNewDeleteBase2.h"
#include "CNewDeleteDerived.h"
#include "CNewDeleteNonVirtualDerived.h"
#include "CNewDeleteVirtualDerived.h"
#include "UserDefinedLiterals.h"
#include "CFriendMembers.h"
#include "CFriendMembersClass1.h"
#include "CFriendMembersClass2.h"
#include "CFriendVisibility.h"
#include "CFriendVisibilityTest.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSubscriptOperators(void)
{
	PrintLineSeparator();

	const size_t												SIZE=4;

	CSubscriptOperators											Value(SIZE);

	Value[1]=L"Timmy Anderson";
	Value[3]=L"Jenny Thompson";

	PrintLineSeparator();

	for(size_t Index=0;Index<SIZE;Index++)
	{
		wcout << L"VALUE[" << Index << L"] [" << Value[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	const CSubscriptOperators&									ConstValue=Value;

	for(size_t Index=0;Index<SIZE;Index++)
	{
		wcout << L"VALUE[" << Index << L"] [" << ConstValue[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunctionCallOperators(void)
{
	PrintLineSeparator();

	CFunctionCallOperators										Value(10);

	wcout << L"VALUE [" << Value(20,30) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDereferencingOperators1(void)
{
	PrintLineSeparator();

	CDereferencingOperatorsPointerToClass						Value(L"Timmy Anderson");

	// !!! Vola sa CUSTOM OPERATOR->.
	wcout << L"VALUE [" << Value->c_str() << L"] !" << endl;

	PrintLineSeparator();
	
	// !!! Vola sa CUSTOM OPERATOR->.
	wcout << L"VALUE.SIZE [" << Value->size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDereferencingOperators2(void)
{
	PrintLineSeparator();

	CDereferencingOperatorsClass								Value(CDereferencingOperatorsPointerToClass(L"Timmy Anderson"));

	// !!! Vola sa CUSTOM CDereferencingOperatorsClass::OPERATOR->, ktory vola CUSTOM OPERATOR CDereferencingOperatorsPointerToClass::OPERATOR->.
	wcout << L"VALUE [" << Value->c_str() << L"] !" << endl;

	PrintLineSeparator();
	
	// !!! Vola sa CUSTOM CDereferencingOperatorsClass::OPERATOR->, ktory vola CUSTOM OPERATOR CDereferencingOperatorsPointerToClass::OPERATOR->.
	wcout << L"VALUE.SIZE [" << Value->size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDereferencingOperators3(void)
{
	PrintLineSeparator();

	CDereferencingOperatorsPointerToPrimitiveType				Value(100);

	// !!!!! Kedze OPERATOR-> TYPE [CDereferencingOperatorsPointerToPrimitiveType] vracia POINTER na PRIMITIVE TYPE, ktory NEMA MEMBERS, je mozne volat OPERATOR-> iba cez FUNCTION CALL SYNTAX.
	wcout << L"VALUE [" << *(Value.operator->()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDereferencingOperators4(void)
{
	PrintLineSeparator();

	CDereferencingOperatorsPrimitiveType						Value(100);

	// !!!!! Kedze OPERATOR-> TYPE [CDereferencingOperatorsPointerToPrimitiveType] vracia POINTER na PRIMITIVE TYPE, ktory NEMA MEMBERS, je mozne volat OPERATOR-> iba cez FUNCTION CALL SYNTAX.
	wcout << L"VALUE [" << Value.operator->() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIncrementDecrementOperators(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (++CIncrementDecrementOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CIncrementDecrementOperators(20)++).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (--CIncrementDecrementOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CIncrementDecrementOperators(20)--).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass1(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CNewDelete*													NewDelete=new CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass2(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CNewDelete*													NewDelete=new CNewDelete();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDelete));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass3(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDelete*													NewDelete=new (Param) CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass4(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDelete*													NewDelete=new (Param) CNewDelete();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDelete));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass5(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDelete*													NewDelete=new (Param) CNewDelete();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE s 1 PARAMETER cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDelete),Param);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsSimpleClass6(void)
{
	PrintLineSeparator();

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 2 PARAMETERS.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDelete*													NewDelete=new (Param1,Param2) CNewDelete();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDelete();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE s 2 PARAMETERS cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDelete),Param1,Param2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy1(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CNewDeleteDerived*											NewDelete=new CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy2(void)
{
	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR NEW.
	CNewDeleteDerived*											NewDelete=new CNewDeleteDerived();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDeleteDerived));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy3(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDeleteDerived*											NewDelete=new (Param) CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE.
	// !!!!! OPERATOR DELETE IMPLICITNE VOLA DESTRUCTOR bez toho, aby to CODE CUSTOM OPERATOR DELETE musel robit.
	delete(NewDelete);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy4(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDeleteDerived*											NewDelete=new (Param) CNewDeleteDerived();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDeleteDerived));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy5(void)
{
	PrintLineSeparator();

	wstring														Param(L"XXX");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 1 PARAMETER.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDeleteDerived*											NewDelete=new (Param) CNewDeleteDerived();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE s 1 PARAMETER cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDeleteDerived),Param);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsClassHierarchy6(void)
{
	PrintLineSeparator();

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR NEW s 2 PARAMETERS.
	// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
	CNewDeleteDerived*											NewDelete=new (Param1,Param2) CNewDeleteDerived();

	PrintLineSeparator();

	// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
	NewDelete->~CNewDeleteDerived();

	PrintLineSeparator();

	// !!! Vola sa PRETAZENY OPERATOR DELETE s 2 PARAMETERS cez FUNCTION CALL SYNTAX.
	// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
	NewDelete->operator delete(NewDelete,sizeof(CNewDeleteDerived),Param1,Param2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsSimpleClass1(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE].
	CNewDelete*													Array=new CNewDelete[ARRAY_SIZE];

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
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsSimpleClass2(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CNewDelete);

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE].
	CNewDelete*													Array=new CNewDelete[ARRAY_SIZE];

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
		Array[Index].~CNewDelete();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	Array->operator delete[](PointerToBuffer,BUFFER_SIZE);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsSimpleClass3(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CNewDelete);

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR NEW[] s 2 PARAMETERS pomocou PLACEMENT SYNTAX.
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDelete)*ARRAY_SIZE].
	CNewDelete*													Array=new (BUFFER_SIZE,Param1,Param2) CNewDelete[ARRAY_SIZE];

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
		Array[Index].~CNewDelete();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[] s 2 PARAMETERS.
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	Array->operator delete[](PointerToBuffer,BUFFER_SIZE,Param1,Param2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsClassHierarchy1(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE].
	CNewDeleteDerived*											Array=new CNewDeleteDerived[ARRAY_SIZE];

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
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsClassHierarchy2(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CNewDeleteDerived);

	// !!! Vola sa PRETAZENY OPERATOR NEW[].
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE].
	CNewDeleteDerived*											Array=new CNewDeleteDerived[ARRAY_SIZE];

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
		Array[Index].~CNewDeleteDerived();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[].
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	Array->operator delete[](PointerToBuffer,BUFFER_SIZE);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Tento CODE NIE JE PLATFORM INDEPENDENT, pretoze C++ NEDEFINUJE, ze do OPERATOR NEW[] sa MUSI ako SIZE zaslat VALUE [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE]. VALUE [SIZEOF(size_t)] sluziaca na ulozene poctu ITEMS je IMPLEMENTATION DEPENDENT.
void TestNewDeleteArrayOperatorsClassHierarchy3(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=6;
	const int													BUFFER_SIZE=sizeof(size_t)+ARRAY_SIZE*sizeof(CNewDeleteDerived);

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	// !!! Vola sa PRETAZENY OPERATOR NEW[] s 2 PARAMETERS pomocou PLACEMENT SYNTAX.
	// !!!!! Ako SIZE sa do CUSTOM OPERATOR NEW[] zasiela [SIZEOF(size_t)+SIZEOF(CNewDeleteDerived)*ARRAY_SIZE].
	CNewDeleteDerived*											Array=new (BUFFER_SIZE,Param1,Param2) CNewDeleteDerived[ARRAY_SIZE];

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
		Array[Index].~CNewDeleteDerived();
	}

	PrintLineSeparator();

	size_t*														PointerToBuffer=(size_t*) (((int8_t*)Array)-sizeof(size_t));
	
	// !!! Vola sa PRETAZENY OPERATOR DELETE[] s 2 PARAMETERS.
	// !!!!! OPERATOR DELETE[] volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTORS pre jednotlive ITEMS.
	// !!!!! Ako 1. PARAMETER musi byt POINTER na ALOKOVANY BUFFER a NIE POINTER na 1. ITEM. Ak COMPILER pouziva OVERHEAD o dlzke SIZEOF(size_t) BYTES na zaciatku alokovaneho BUFFER, potom je nutne od POINTER na 1. ITEM odcitat dlzku SIZEOF(size_t), aby sa ziskal POINTER na alokovany BUFFER.
	Array->operator delete[](PointerToBuffer,BUFFER_SIZE,Param1,Param2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteArrayOperatorsClassHierarchyPlacementSyntaxException(void)
{
	PrintLineSeparator();

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	try
	{
		// !!!!! Ked CONSTRUCTOR sa vola cez PLACEMENT SYNTAX a hodi EXCEPTION, tak C++ zavola OPERATOR DELETE[] s ROVNAKYMI PARAMETERS ako OPERATOR NEW.

		// !!! Vola sa PRETAZENY OPERATOR NEW s 2 PARAMETERS.
		// !!! Na volanie sa pouziva PLACEMENT SYNTAX.
		CNewDeleteDerived*										NewDelete=new (Param1,Param2) CNewDeleteDerived(true);

		PrintLineSeparator();

		// !!!!! Kedze OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR je ho nutne volat EXPLICITNE.
		NewDelete->~CNewDeleteDerived();

		PrintLineSeparator();

		// !!! Vola sa PRETAZENY OPERATOR DELETE s 2 PARAMETERS cez FUNCTION CALL SYNTAX.
		// !!!!! OPERATOR DELETE volany cez FUNCTION CALL SYNTAX NEVOLA IMPLICITNE DESTRUCTOR.
		NewDelete->operator delete(NewDelete,sizeof(CNewDeleteDerived),Param1,Param2);
	}
	catch(const wstring& E)
	{
		wcout << "EXCEPTION [" << E << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsNonVirtual1(void)
{
	PrintLineSeparator();

	CNewDeleteNonVirtualDerived*								Derived=new CNewDeleteNonVirtualDerived();

	PrintLineSeparator();

	delete(Derived);

	PrintLineSeparator();

	CNewDeleteNonVirtualBase*									Base=new CNewDeleteNonVirtualDerived();

	PrintLineSeparator();

	// !!!!! Kedze DESTRUCTOR CLASS 'CNewDeleteNonVirtualBase' NIE JE VIRTUAL, C++ zavola OPERATOR DELETE CLASS 'CNewDeleteNonVirtualBase' a NIE CLASS 'CNewDeleteNonVirtualDerived'.
	// !!!!! Zaroven COMPILER do OPERATOR DELETE CLASS 'CNewDeleteNonVirtualBase' zasle NESPRAVNU DLZKU ALOKOVANEHO BUFFER, pretoze NESPRAVNE PREDOKLADA, ze VARIABLE 'Base' odkazuje na CLASS 'CNewDeleteNonVirtualBase' a NIE na CLASS 'CNewDeleteNonVirtualDerived'.
	delete(Base);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsVirtual1(void)
{
	PrintLineSeparator();

	CNewDeleteVirtualDerived*									Derived=new CNewDeleteVirtualDerived();

	PrintLineSeparator();

	delete(Derived);

	PrintLineSeparator();

	CNewDeleteVirtualBase*										Base=new CNewDeleteVirtualDerived();

	PrintLineSeparator();

	delete(Base);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsNonVirtual2(void)
{
	PrintLineSeparator();

	CNewDeleteNonVirtualDerived*								Derived=new CNewDeleteNonVirtualDerived[3];

	PrintLineSeparator();

	delete[](Derived);

	PrintLineSeparator();

	CNewDeleteNonVirtualBase*									Base=new CNewDeleteNonVirtualDerived[3];

	PrintLineSeparator();

	// !!!!! Kedze DESTRUCTOR CLASS 'CNewDeleteNonVirtualBase' NIE JE VIRTUAL, C++ zavola OPERATOR DELETE[] CLASS 'CNewDeleteNonVirtualBase' a NIE CLASS 'CNewDeleteNonVirtualDerived'.
	// !!!!! Zaroven COMPILER do OPERATOR DELETE[] CLASS 'CNewDeleteNonVirtualBase' zasle NESPRAVNU DLZKU ALOKOVANEHO BUFFER, pretoze NESPRAVNE PREDOKLADA, ze VARIABLE 'Base' odkazuje na ARRAY CLASS 'CNewDeleteNonVirtualBase' a NIE na ARRAY CLASS 'CNewDeleteNonVirtualDerived'.
	delete[](Base);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNewDeleteOperatorsVirtual2(void)
{
	PrintLineSeparator();

	CNewDeleteVirtualDerived*									Derived=new CNewDeleteVirtualDerived[3];

	PrintLineSeparator();

	delete[](Derived);

	PrintLineSeparator();

	CNewDeleteVirtualBase*										Base=new CNewDeleteVirtualDerived[3];

	PrintLineSeparator();

	delete[](Base);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUserDefinedLiteralOperators(void)
{
	PrintLineSeparator();

	std::wcout << "VALUE [" << 100_I1 << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << 100_I2 << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << 4567_I3 << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << 4567_i4 << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << 123.45_F << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << L'Z'_C << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << L"Timmy Anderson"_S.size() << L"] !" << std::endl;

	PrintLineSeparator();

	std::wcout << "VALUE [" << 100_i << L"] !" << std::endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void FriendFunction(CFriendMembers& Object)
{
	// !!! Kedze FUNCTION bola oznacena ako FRIEND, moze pristupovat k PRIVATE MEMBERS.
	Object.PrivateMethod();
}
//-----------------------------------------------------------------------------
void TestFriends(void)
{
	PrintLineSeparator();

	CFriendMembersClass1										Members1;

	Members1.Test();

	PrintLineSeparator();

	CFriendMembersClass2										Members2;

	Members2.Test1();

	PrintLineSeparator();

	Members2.Test2();

	PrintLineSeparator();

	Members1.TestTemplateClass1();

	PrintLineSeparator();

	Members1.TestTemplateClass2();

	PrintLineSeparator();

	Members2.TestTemplateClass1();

	PrintLineSeparator();

	Members2.TestTemplateClass2();

	PrintLineSeparator();

	CFriendMembers												Object;

	FriendFunction(Object);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ParameterVisibility(CFriendMembers& Object)
{
	FriendFunction(Object);
}
//-----------------------------------------------------------------------------
void TestFriendsVisibility(void)
{
	PrintLineSeparator();

	FRIENDS::CFriendVisibilityTest								Object1;

	Object1.Test();

	PrintLineSeparator();

	FriendVisibilityFunction();

	PrintLineSeparator();

	CFriendMembers												Object2;

	ParameterVisibility(Object2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSubscriptOperators();
	//TestFunctionCallOperators();
	//TestDereferencingOperators1();
	//TestDereferencingOperators2();
	//TestDereferencingOperators3();
	//TestDereferencingOperators4();
	//TestIncrementDecrementOperators();
	//TestNewDeleteOperatorsSimpleClass1();
	//TestNewDeleteOperatorsSimpleClass2();
	//TestNewDeleteOperatorsSimpleClass3();
	//TestNewDeleteOperatorsSimpleClass4();
	//TestNewDeleteOperatorsSimpleClass5();
	//TestNewDeleteOperatorsSimpleClass6();
	//TestNewDeleteOperatorsClassHierarchy1();
	//TestNewDeleteOperatorsClassHierarchy2();
	//TestNewDeleteOperatorsClassHierarchy3();
	//TestNewDeleteOperatorsClassHierarchy4();
	//TestNewDeleteOperatorsClassHierarchy5();
	//TestNewDeleteOperatorsClassHierarchy6();
	//TestNewDeleteArrayOperatorsSimpleClass1();
	//TestNewDeleteArrayOperatorsSimpleClass2();
	//TestNewDeleteArrayOperatorsSimpleClass3();
	//TestNewDeleteArrayOperatorsClassHierarchy1();
	//TestNewDeleteArrayOperatorsClassHierarchy2();
	//TestNewDeleteArrayOperatorsClassHierarchy3();
	//TestNewDeleteArrayOperatorsClassHierarchyPlacementSyntaxException();
	//TestNewDeleteOperatorsNonVirtual1();
	//TestNewDeleteOperatorsVirtual1();
	//TestNewDeleteOperatorsNonVirtual2();
	//TestNewDeleteOperatorsVirtual2();
	//TestUserDefinedLiteralOperators();
	//TestFriends();
	TestFriendsVisibility();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------