//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include "MyDebug.h"
#include "CCustomOperatorUsage.h"
#include "CArithmeticOperators.h"
#include "CComparisonOperators.h"
#include "CLogicalOperators.h"
#include "CDeletedOperators.h"
#include "CBitwiseOperators.h"
#include "CAssignmentOperators.h"
#include "CPointerOperators.h"
#include "CCommaOperators.h"
#include "CUserDefinedLiteralsOperators.h"
#include "CPointerParameterOperators.h"
#include "EEnumOperators.h"
#include "CBaseClassOperators.h"
#include "CDerivedClassOperators.h"
#include "CClassInNamespaceX.h"
#include "CClassInNamespaceY.h"
#include "CClassInNamespaceYOperators.h"
#include "COperatorHiding1.h"
#include "COperatorHiding2.h"
#include "CPointerToMemberOperators.h"
#include "CConversionOperators.h"
#include "CAmbiguities1X.h"
#include "CAmbiguities1Y.h"
#include "CAmbiguities1Z.h"
#include "CAmbiguities2.h"
#include "CAmbiguities3.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomOperatorUsage(void)
{
	PrintLineSeparator();

	CCustomOperatorUsage										Value(10);

	// !!! Pouzitie OPERATOR SYNTAX.
	wcout << L"VALUE [" << (Value+20) << L"] !" << endl;

	// !!! Pouzitie FUNCTION CALL SYNTAX.
	wcout << L"VALUE [" << (Value.operator+(20)) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArithmeticOperators1(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)+10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)-10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)*10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)/10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)%10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20+CArithmeticOperators(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20-CArithmeticOperators(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20*CArithmeticOperators(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20/CArithmeticOperators(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20%CArithmeticOperators(10)).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArithmeticOperators2(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (+CArithmeticOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (-CArithmeticOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (++CArithmeticOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)++).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (--CArithmeticOperators(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CArithmeticOperators(20)--).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComparisonOperators(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)==CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)!=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)<CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)>CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)<=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((CComparisonOperators(10)>=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10==CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10!=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10<CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10>CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10<=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << ((10>=CComparisonOperators(20)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLogicalOperators(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << ((!CLogicalOperators(true)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// !!! Na rozdiel od STANDARD OPERATOR && su LEFT OPERAND aj RIGHT OPERAND CUSTOM OPERATORS VZDY EVALUATED.
	wcout << L"VALUE [" << ((CLogicalOperators(true) && CLogicalOperators(false)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// !!! Na rozdiel od STANDARD OPERATOR || su LEFT OPERAND aj RIGHT OPERAND CUSTOM OPERATORS VZDY EVALUATED.
	wcout << L"VALUE [" << ((CLogicalOperators(true) || CLogicalOperators(false)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// !!! Na rozdiel od STANDARD OPERATOR && su LEFT OPERAND aj RIGHT OPERAND CUSTOM OPERATORS VZDY EVALUATED.
	wcout << L"VALUE [" << ((true && CLogicalOperators(false)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// !!! Na rozdiel od STANDARD OPERATOR || su LEFT OPERAND aj RIGHT OPERAND CUSTOM OPERATORS VZDY EVALUATED.
	wcout << L"VALUE [" << ((false || CLogicalOperators(false)) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDeletedOperators(void)
{
	PrintLineSeparator();

	CCustomOperatorUsage										NonDeletedObject(10);
	CCustomOperatorUsage*										PointerNonDeletedObject=&NonDeletedObject;

	wcout << L"NON-DELETED OBJECT [" << NonDeletedObject.GetValue() << L"] !" << endl;
	wcout << L"NON-DELETED OBJECT [" << PointerNonDeletedObject->GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CDeletedOperators											DeletedObject(10);

	// !!! Z CLASS 'CDeletedOperators' sa NEDA ziskat POINTER, lebo CLASS 'CDeletedOperators' ma OPERATOR& oznaceny ako DELETED.
	//CDeletedOperators*											PointerDeletedObject=&DeletedObject;

	wcout << L"DELETED OBJECT [" << DeletedObject.GetValue() << L"] !" << endl;
	//wcout << L"DELETED OBJECT [" << PointerDeletedObject->GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBitwiseOperators(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (~CBitwiseOperators(0xA3)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) & CBitwiseOperators(0x6F)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) | CBitwiseOperators(0x6F)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) ^ CBitwiseOperators(0x6F)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) << CBitwiseOperators(3)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) >> CBitwiseOperators(3)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	const CBitwiseOperators										Value(0xA3);

	wcout << L"VALUE [" << (~Value).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) & 0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) | 0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) ^ 0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) << 3).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (CBitwiseOperators(0xA3) >> 3).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssignmentOperators1(void)
{
	PrintLineSeparator();

	CAssignmentOperators										Value1(20);
	CAssignmentOperators										Value2(5);

	wcout << L"VALUE [" << (Value1+=Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1-=Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1*=Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1/=Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1%=Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CAssignmentOperators										Value3(0xA3);
	CAssignmentOperators										Value4(0x6F);

	wcout << L"VALUE [" << (Value3&=Value4).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value3|=Value4).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value3^=Value4).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value3<<=Value4).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value3>>=Value4).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssignmentOperators2(void)
{
	PrintLineSeparator();

	CAssignmentOperators										Value1(20);

	wcout << L"VALUE [" << (Value1+=5).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1-=5).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1*=5).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1/=5).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value1%=5).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CAssignmentOperators										Value2(20);

	wcout << L"VALUE [" << (Value2&=0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value2|=0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value2^=0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value2<<=0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (Value2>>=0x6F).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerOperators(void)
{
	PrintLineSeparator();

	int															RawValue=100;
	CPointerOperators											Value(&RawValue);

	*Value=200;

	PrintLineSeparator();

	wcout << L"VALUE [" << (*Value) << L"] !" << endl;
	wcout << L"RAW VALUE [" << (RawValue) << L"] !" << endl;

	PrintLineSeparator();

	int*														PointerValue=&Value;

	*PointerValue=300;

	PrintLineSeparator();

	wcout << L"VALUE [" << (*Value) << L"] !" << endl;
	wcout << L"RAW VALUE [" << (RawValue) << L"] !" << endl;

	PrintLineSeparator();

	const CPointerOperators										ConstValue(&RawValue);

	wcout << L"VALUE [" << (*(&(ConstValue))) << L"] !" << endl;
	wcout << L"VALUE [" << (*ConstValue) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCommaOperators(void)
{
	PrintLineSeparator();

	CCommaOperators												Value1(10);
	CCommaOperators												Value2(20);

	// Vola sa OPERATOR COMMA.
	wcout << L"VALUE [" << (Value1,Value2) << L"] !" << endl;

	PrintLineSeparator();

	// Vola sa OPERATOR COMMA.
	wcout << L"VALUE [" << (10,Value2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUserDefinedLiteralsOperators(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << 123_THOUSANDS << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << 123.45_DOUBLE_THOUSANDS << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerParameterOperators(void)
{
	PrintLineSeparator();

	CPointerParameterOperators									Value1(10);
	CPointerParameterOperators									Value2(20);
	CPointerParameterOperators*									PointerToValue2=&Value2;

	wcout << L"VALUE [" << (Value1+PointerToValue2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (PointerToValue2+Value1).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEnumOperators(void)
{
	PrintLineSeparator();

	EEnumOperators												Value1=E_10;
	EEnumOperators												Value2=E_20;

	wcout << L"VALUE [" << (Value1+Value2) << L"] !" << endl;

	PrintLineSeparator();

	EEnumClassOperators											ClassValue1=EEnumClassOperators::E_10;
	EEnumClassOperators											ClassValue2=EEnumClassOperators::E_20;

	wcout << L"VALUE [" << int(ClassValue1+ClassValue2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDerivedOperators(void)
{
	PrintLineSeparator();

	CBaseClassOperators											Base1(10);
	CBaseClassOperators											Base2(20);

	// Vola OPERATOR z CLASS [CBaseClassOperators].
	wcout << L"VALUE [" << (Base1+Base2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// Vola OPERATOR z CLASS [CBaseClassOperators].
	wcout << L"VALUE [" << (Base1-Base2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CDerivedClassOperators										Derived1(10);
	CDerivedClassOperators										Derived2(20);

	// Vola OPERATOR z CLASS [CBaseClassOperators], ktory bol DERIVED do CLASS [CDerivedClassOperators].
	wcout << L"VALUE [" << (Derived1+Derived2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// Vola OPERATOR z CLASS [CDerivedClassOperators], pretoze OPERATOR- bol OVERRIDEN v CLASS [CDerivedClassOperators].
	wcout << L"VALUE [" << (Derived1-Derived2).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorsInNamespaces(void)
{
	PrintLineSeparator();

	// Pre NAMESPACE 'X' a NAMESPACE 'Y' sa NEPOUZIL USING NAMESPACE.

	X::CClassInNamespaceX										Value1(10);
	Y::CClassInNamespaceY										Value2(20);

	// !!! Pouzije sa MEMBER OPERATOR.
	wcout << L"VALUE [" << (Value1+Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzije sa NON-MEMBER OPERATOR- a to aj NAPRIEK TOMU, ze je definovany v NAMESPACE 'X' pre ktory NEBOL POUZITY USING NAMESPACE. C++ vsak aj napriek tomu dokaze OPERATOR- NAJST.
	wcout << L"VALUE [" << (Value1-Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzije sa NON-MEMBER OPERATOR* a to aj NAPRIEK TOMU, ze je definovany v NAMESPACE 'Y' pre ktory NEBOL POUZITY USING NAMESPACE. C++ vsak aj napriek tomu dokaze OPERATOR* NAJST.
	wcout << L"VALUE [" << (Value1*Value2).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorsHiding(void)
{
	PrintLineSeparator();

	COperatorHiding1											Value1(10);
	COperatorHiding2											Value2(20);

	wcout << L"VALUE [" << (Value2+Value1).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerToMemberOperators(void)
{
	PrintLineSeparator();

	CPointerToMemberOperators									Value1(L"Timmy",L"Anderson",12,22);
	CPointerToMemberOperators									Value2(L"Jenny",L"Thompson",13,23);
	CPointerToMemberOperators*									PointerToValue1=&Value1;
	CPointerToMemberOperators*									PointerToValue2=&Value2;

	// MEMBER REFERENCE VARIABLE odkazuje na FIELD TYPE 'wstring' v CLASS 'CPointerToMemberOperators'.
	wstring														CPointerToMemberOperators::*PointerToString;

	// MEMBER REFERENCE VARIABLE odkazuje na FIELD TYPE 'int' v CLASS 'CPointerToMemberOperators'.
	int															CPointerToMemberOperators::*PointerToInt;

	// !!! VARIABLE 'PointerToString' bude odkazovat na FIELD 'MStringValue1'.
	PointerToString=&CPointerToMemberOperators::MStringValue1;

	// !!! VARIABLE 'PointerToInt' bude odkazovat na FIELD 'MIntValue1'.
	PointerToInt=&CPointerToMemberOperators::MIntValue1;

	// !!!!! Pouzitie OPERATOR.* na rozlicne OBJECTS.
	wcout << L"Value1.*PointerToString [" << (Value1.*PointerToString) << L"] !" << endl;
	wcout << L"Value1.*PointerToInt [" << (Value1.*PointerToInt) << L"] !" << endl;
	wcout << L"Value2.*PointerToString [" << (Value2.*PointerToString) << L"] !" << endl;
	wcout << L"Value2.*PointerToInt [" << (Value2.*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzitie OPERATOR->* na rozlicne OBJECTS.
	wcout << L"PointerToValue1->*PointerToString [" << (PointerToValue1->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue1->*PointerToInt [" << (PointerToValue1->*PointerToInt) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToString [" << (PointerToValue2->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToInt [" << (PointerToValue2->*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	// !!! VARIABLE 'PointerToString' bude odkazovat na FIELD 'MStringValue2'.
	PointerToString=&CPointerToMemberOperators::MStringValue2;

	// !!! VARIABLE 'PointerToInt' bude odkazovat na FIELD 'MIntValue2'.
	PointerToInt=&CPointerToMemberOperators::MIntValue2;

	// !!!!! Pouzitie OPERATOR.* na rozlicne OBJECTS.
	wcout << L"Value1.*PointerToString [" << (Value1.*PointerToString) << L"] !" << endl;
	wcout << L"Value1.*PointerToInt [" << (Value1.*PointerToInt) << L"] !" << endl;
	wcout << L"Value2.*PointerToString [" << (Value2.*PointerToString) << L"] !" << endl;
	wcout << L"Value2.*PointerToInt [" << (Value2.*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzitie OPERATOR->* na rozlicne OBJECTS.
	wcout << L"PointerToValue1->*PointerToString [" << (PointerToValue1->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue1->*PointerToInt [" << (PointerToValue1->*PointerToInt) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToString [" << (PointerToValue2->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToInt [" << (PointerToValue2->*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	// MEMBER REFERENCE VARIABLE odkazuje na METHOD v CLASS 'CPointerToMemberOperators', ktora NEMA ZIADNE PARAMETERS a vracia TYPE 'const wstring&'.
	const wstring&												(CPointerToMemberOperators::*MethodGettingString)() const;

	// MEMBER REFERENCE VARIABLE odkazuje na METHOD v CLASS 'CPointerToMemberOperators', ktora NEMA ZIADNE PARAMETERS a vracia TYPE 'int'.
	int															(CPointerToMemberOperators::*MethodGettingInt)() const;

	// !!! VARIABLE 'PointerToString' bude odkazovat na METHOD GetStringValue1().
	MethodGettingString=&CPointerToMemberOperators::GetStringValue1;

	// !!! VARIABLE 'PointerToInt' bude odkazovat na METHOD GetIntValue1().
	MethodGettingInt=&CPointerToMemberOperators::GetIntValue1;

	// !!!!! Pouzitie OPERATOR.* na rozlicne OBJECTS pre volanie METHODS.
	wcout << L"Value1.*MethodGettingString() [" << ((Value1.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value1.*MethodGettingInt() [" << ((Value1.*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingString() [" << ((Value2.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingInt() [" << ((Value2.*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzitie OPERATOR->* na rozlicne OBJECTS pre volanie METHODS.
	wcout << L"PointerToValue1->*MethodGettingString() [" << ((PointerToValue1->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue1->*MethodGettingInt() [" << ((PointerToValue1->*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingString() [" << ((PointerToValue2->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingInt() [" << ((PointerToValue2->*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! VARIABLE 'PointerToString' bude odkazovat na METHOD GetStringValue2().
	MethodGettingString=&CPointerToMemberOperators::GetStringValue2;

	// !!! VARIABLE 'PointerToInt' bude odkazovat na METHOD GetIntValue2().
	MethodGettingInt=&CPointerToMemberOperators::GetIntValue2;

	// !!!!! Pouzitie OPERATOR.* na rozlicne OBJECTS pre volanie METHODS.
	wcout << L"Value1.*MethodGettingString() [" << ((Value1.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value1.*MethodGettingInt() [" << ((Value1.*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingString() [" << ((Value2.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingInt() [" << ((Value2.*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Pouzitie OPERATOR->* na rozlicne OBJECTS pre volanie METHODS.
	wcout << L"PointerToValue1->*MethodGettingString() [" << ((PointerToValue1->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue1->*MethodGettingInt() [" << ((PointerToValue1->*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingString() [" << ((PointerToValue2->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingInt() [" << ((PointerToValue2->*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Vola sa CUSTOM OPERATOR->* ako MEMBER METHOD.
	// !!!!! CUSTOM OPERATOR->* NEVYKONAVA pristup k MEMBER FIELDS a MEMBER METHODS ako STANDARD OPERATOR->*.
	wcout << L"CUSTOM OPERATOR->* [" << (Value1->*123.45) << L"] !" << endl;
	wcout << L"CUSTOM OPERATOR->* [" << (Value2->*123.45) << L"] !" << endl;

	PrintLineSeparator();
	
	// !!!!! Vola sa CUSTOM OPERATOR->* ako NON-MEMBER FUNCTION.
	// !!!!! CUSTOM OPERATOR->* NEVYKONAVA pristup k MEMBER FIELDS a MEMBER METHODS ako STANDARD OPERATOR->*.
	wcout << L"CUSTOM OPERATOR->* [" << (123.45->*Value1) << L"] !" << endl;
	wcout << L"CUSTOM OPERATOR->* [" << (123.45->*Value2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConversionOperators(void)
{
	PrintLineSeparator();

	CConversionOperators										Value1(100);

	wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	short														ShortValue=200;

	CConversionOperators										Value2;

	// !!! Vola sa IMPLICIT CONVERSION CONSTRUCTOR.
	Value2=ShortValue;

	wcout << L"VALUE 2 [" << Value2.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	double														DoubleValue=333.333;

	CConversionOperators										Value3;

	// COMPILER HODI ERROR.
	//Value3=DoubleValue;

	// !!! Vola sa EXPLICIT CONVERSION CONSTRUCTOR.
	Value3=CConversionOperators(DoubleValue);

	wcout << L"VALUE 3 [" << Value3.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	double														Value4;

	// !!! Vola sa IMPLICIT CONVERSION OPERATOR.
	Value4=Value3;

	wcout << L"VALUE 4 [" << Value4 << L"] !" << endl;

	PrintLineSeparator();

	short														Value5;

	// COMPILER zavola IMPLICIT CONVERSION OPERATOR.
	//Value5=Value3;

	// !!! Vola sa EXPLICIT CONVERSION OPERATOR.
	Value5=short(Value3);

	wcout << L"VALUE 5 [" << Value5 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAmbiguities1X Ambiguities1(CAmbiguities1X Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
CAmbiguities1Y Ambiguities1(CAmbiguities1Y Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
CAmbiguities1Z Ambiguities2(CAmbiguities1Z Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
void TestConversionOperatorsAmbiguities1(void)
{
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze sa nevie rozhodnut ci ma pouzit CONVERSION CAmbiguities1X(10), alebo CONVERSION CAmbiguities1Y(10).
	//wcout << L"AMBIGUITIES [" << Ambiguities1(10).GetValue1() << L"] !" << endl;

	// Volanie prebehne v poriadku.
	wcout << L"AMBIGUITIES [" << Ambiguities1(CAmbiguities1X(10)).GetValue1() << L"] !" << endl;

	// Volanie prebehne v poriadku.
	wcout << L"AMBIGUITIES [" << Ambiguities1(CAmbiguities1Y(10)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze CODE vyzaduje 2 USER DEFINED CONVERSIONS [Ambiguities2(CAmbiguities1Z(CAmbiguities1X(L"Timmy Anderson")))] a C++ umoznuje IMPLICITNE VOLAT iba 1 USER DEFINED CONVERSION.
	//wcout << L"AMBIGUITIES [" << Ambiguities2(L"Timmy Anderson").GetValue() << L"] !" << endl;
	
	// Volanie prebehne v poriadku, lebo vyzaduje volanie iba 1 USER DEFINED CONVERSION.
	wcout << L"AMBIGUITIES [" << Ambiguities2(CAmbiguities1X(L"Timmy Anderson")).GetValue().GetValue2() << L"] !" << endl;

	// Volanie prebehne v poriadku, lebo vyzaduje volanie iba 1 USER DEFINED CONVERSION.
	wcout << L"AMBIGUITIES [" << Ambiguities2(CAmbiguities1Z(L"Timmy Anderson")).GetValue().GetValue2() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
double Ambiguities3(double Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
CAmbiguities2 Ambiguities3(CAmbiguities2 Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
void TestConversionOperatorsAmbiguities2(void)
{
	PrintLineSeparator();

	// !!! COMPILER ma na vyber 2 mozne CONVERSIONS. CONVERSION [Ambiguities3(double(10))], alebo CONVERSION [Ambiguities3(CAmbiguities2(10))].
	// !!!!! C++ zvoli 1. CONVERSION, pretoze ta NEVYZADUJE volanie USER DEFINED CONVERSION CONSTRUCTOR a taketo CONVERSIONS maju VZDY PREDNOST pred CONVERSIONS vyzadujucimi volanie USER DEFINED CONVERSIONS.
	wcout << L"AMBIGUITIES [" << Ambiguities3(10) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConversionOperatorsAmbiguities3(void)
{
	PrintLineSeparator();

	// !!! NEVOLA sa CAmbiguities3::OPERATOR+, pretoze C++ uprednostni volanie OPERATOR+(double,double), kedze pri hladani CONVERSIONS sa RETURN VALUE NEBERIE do UVAHY.
	CAmbiguities3												Value1=10.5+8.2;

	wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! VOLA sa CAmbiguities3::OPERATOR+, pretoze 1. PARAMETER je TYPE 'CAmbiguities3'.
	CAmbiguities3												Value2=CAmbiguities3(10.5)+8.2;

	wcout << L"VALUE 2 [" << Value2.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestCustomOperatorUsage();
	//TestArithmeticOperators1();
	//TestArithmeticOperators2();
	//TestComparisonOperators();
	//TestLogicalOperators();
	//TestDeletedOperators();
	//TestBitwiseOperators();
	//TestAssignmentOperators1();
	//TestAssignmentOperators2();
	//TestPointerOperators();
	//TestCommaOperators();
	//TestUserDefinedLiteralsOperators();
	//TestPointerParameterOperators();
	//TestEnumOperators();
	//TestDerivedOperators();
	//TestOperatorsInNamespaces();
	//TestOperatorsHiding();
	//TestPointerToMemberOperators();
	//TestConversionOperators();
	//TestConversionOperatorsAmbiguities1();
	//TestConversionOperatorsAmbiguities2();
	TestConversionOperatorsAmbiguities3();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------