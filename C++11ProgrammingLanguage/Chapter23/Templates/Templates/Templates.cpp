//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include "MyDebug.h"
#include "CClassTemplate1.h"
#include "CClassTemplate2.h"
#include "CClassOverloading.h"
#include "CSimpleTemplate.h"
#include "CBase.h"
#include "CDerived.h"
#include "CComplexTemplate.h"
#include "CFriendlyTemplate.h"
#include "CComplexTemplateComparer.h"
#include "CClassWithOverloadedMethods.h"
#include "CTypeWithMethodXXX.h"
#include "SFINAEExpressions1.h"
#include "SFINAEExpressions2.h"
#include "SFINAEExpressions3.h"
#include "SFINAEExpressions4.h"
#include "CBaseTemplate.h"
#include "CDerivedTemplate.h"
#include "CBiggerTypeTypeFunction.h"
#include "HasMethodXXX.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType1,typename TType2>
using IsBigger=typename CBiggerTypeTypeFunction<int,int>::BiggerType;
//-----------------------------------------------------------------------------
// TYPE ALIAS.
template<typename TType>
using IsBiggerAsInt=typename CBiggerTypeTypeFunction<int,TType>::BiggerType;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
TType TemplateFunction(TType Value)
{
	TType														NewValue=++Value;

	return(NewValue);
}
//-----------------------------------------------------------------------------
void TestTemplateClassTemplateMethodAndTemplateFunction(void)
{
	PrintLineSeparator();

	CClassTemplate1<int>										Object(100);

	wprintf_s(L"VALUE [%d] !\n",Object.GetValue());
	wprintf_s(L"CONVERTED VALUE [%f] !\n",Object.Convert<double>());
	wprintf_s(L"RETURNED VALUE [%f] !\n",TemplateFunction(3.4));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateClassWithExternalTemplateMethods(void)
{
	PrintLineSeparator();

	CClassTemplate2<int>										Object(100);

	wprintf_s(L"VALUE [%d] !\n",Object.GetValue());
	wprintf_s(L"CONVERTED VALUE [%f] !\n",Object.Convert<double>());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void FunctionOverloading1(void)
{
	wprintf_s(L"FUNCTION [void FunctionOverloading(void)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! Pri FUNCTION TEMPLATE OVERLOADING je MOZNE definovat FUNCTIONS s ROVNAKYM PROTOTYPE, ktory sa lisi IBA v pocte TYPE PARAMETERS.
template<typename TType>
void FunctionOverloading1(void)
{
	wprintf_s(L"FUNCTION [template<typename TType> void FunctionOverloading(void)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! Pri FUNCTION TEMPLATE OVERLOADING je MOZNE definovat FUNCTIONS s ROVNAKYM PROTOTYPE, ktory sa lisi IBA v pocte TYPE PARAMETERS.
template<typename TType1,typename TType2>
void FunctionOverloading1(void)
{
	wprintf_s(L"FUNCTION [template<typename TType1,typename TType2> void FunctionOverloading(void)] CALLED !\n");
}
//-----------------------------------------------------------------------------
void FunctionOverloading2(int)
{
	wprintf_s(L"FUNCTION [void FunctionOverloading(int)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! Pri FUNCTION TEMPLATE OVERLOADING je MOZNE definovat FUNCTIONS s ROVNAKYM PROTOTYPE, ktory sa lisi IBA v pocte TYPE PARAMETERS.
template<typename TType>
void FunctionOverloading2(TType)
{
	wprintf_s(L"FUNCTION [template<typename TType> void FunctionOverloading(TType)] CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestTemplateFunctionOverloading(void)
{
	PrintLineSeparator();

	FunctionOverloading1();
	FunctionOverloading1<int>();
	FunctionOverloading1<int,double>();

	PrintLineSeparator();

	// !!! Kedze PARAMETER NON-TEMPLATE FUNCTION FunctionOverloading2() je INT, COMPILER PREFERUJE tuto FUNCTION pre FUNCTION TEMPLATE, ktora by tiez mohla byt volana, pretoze pocet a TYPES vsetkych PARAMETERS sedia.
	FunctionOverloading2(100);
	FunctionOverloading2<int>(100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
void TestTemplateClassOverloading(void)
{
	PrintLineSeparator();

	CClassOverloading<int>										Object(100);

	wprintf_s(L"VALUE [%d] !\n",Object.GetValue());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemplateEquivalence(void)
{
	PrintLineSeparator();

	using MyInt=int;

	wprintf_s(L"CSimpleTemplate<int>==CSimpleTemplate<int> [%ls] !\n",(typeid(CSimpleTemplate<int>)==typeid(CSimpleTemplate<int>)) ? L"TRUE" : L"FALSE");
	wprintf_s(L"CSimpleTemplate<int>==CSimpleTemplate<unsigned int> [%ls] !\n",(typeid(CSimpleTemplate<int>)==typeid(CSimpleTemplate<unsigned int>)) ? L"TRUE" : L"FALSE");
	// !!! TYPES su EKVIVALENTNE.
	wprintf_s(L"CSimpleTemplate<int>==CSimpleTemplate<MyInt> [%ls] !\n",(typeid(CSimpleTemplate<int>)==typeid(CSimpleTemplate<MyInt>)) ? L"TRUE" : L"FALSE");
	wprintf_s(L"CSimpleTemplate<CDerived*>==CSimpleTemplate<CBase*> [%ls] !\n",(typeid(CSimpleTemplate<CDerived*>)==typeid(CSimpleTemplate<CBase*>)) ? L"TRUE" : L"FALSE");

	/*
	// !!! Hodi ERROR pretoze TYPES CSimpleTemplate<CBase*> a CSimpleTemplate<CDerived*> NIE SU EKVIVALENTNE.
	CSimpleTemplate<CBase*>*									Value1=new CSimpleTemplate<CDerived*>();
	// !!! Hodi ERROR pretoze TYPES CSimpleTemplate<CBase*> a CSimpleTemplate<CDerived*> NIE SU EKVIVALENTNE.
	CSimpleTemplate<CBase*>&									Value2=CSimpleTemplate<CDerived*>();
	// !!! Hodi ERROR pretoze TYPES CSimpleTemplate<CBase*> a CSimpleTemplate<CDerived*> NIE SU EKVIVALENTNE.
	CSimpleTemplate<CBase*>										Value3=CSimpleTemplate<CBase*>();

	delete(Value1);
	Value1=nullptr;
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassTemplate(void)
{
	PrintLineSeparator();

	CComplexTemplate<wstring>									Value;

	Value.MVariable2=L"Timmy";
	CComplexTemplate<wstring>::MStaticVariable2=L"Atreyu";

	wprintf_s(L"Value.MVariable1 [%d] !\n",Value.MVariable1);
	wprintf_s(L"Value.MVariable2 [%ls] !\n",Value.MVariable2.c_str());
	wprintf_s(L"CComplexTemplate<wstring>::MStaticVariable1 [%d] !\n",CComplexTemplate<wstring>::MStaticVariable1);
	wprintf_s(L"CComplexTemplate<wstring>::MStaticVariable2 [%ls] !\n",CComplexTemplate<wstring>::MStaticVariable2.c_str());
	wprintf_s(L"CComplexTemplate<wstring>::MStaticConstVariable1 [%d] !\n",CComplexTemplate<wstring>::MStaticConstVariable1);
	wprintf_s(L"CComplexTemplate<wstring>::MStaticConstVariable2 [%ls] !\n",CComplexTemplate<wstring>::MStaticConstVariable2.c_str());

	PrintLineSeparator();

	wprintf_s(L"Value.GetVariable2() [%ls] !\n",Value.GetVariable2().c_str());
	wprintf_s(L"Value.GetStaticVariable2() [%ls] !\n",Value.GetStaticVariable2().c_str());

	PrintLineSeparator();

	CComplexTemplate<wstring>::CUnderlyingTypePointer			Pointer=&Value.MVariable2;
	CComplexTemplate<wstring>::CUnderlyingType					ValueFromPointer=*Pointer;

	wprintf_s(L"*Pointer [%ls] !\n",Pointer->c_str());
	wprintf_s(L"ValueFromPointer [%ls] !\n",ValueFromPointer.c_str());

	PrintLineSeparator();

	CComplexTemplate<wstring>::SInnerStruct1					Struct1;

	Struct1.MValue=L"Anderson";

	wprintf_s(L"Struct1.MValue [%ls] !\n",Struct1.MValue.c_str());

	CComplexTemplate<wstring>::SInnerStruct2					Struct2;

	Struct2.MValueOutside=L"Thompson";

	wprintf_s(L"Struct2.MValueOutside [%ls] !\n",Struct2.MValueOutside.c_str());

	CComplexTemplate<wstring>::EInnerEnum1						Enum1=CComplexTemplate<wstring>::E_YES;

	wprintf_s(L"Enum1 [%d] !\n",Enum1);

#ifndef _MSC_VER
/*
	// !!!!! COMPILER NEUMOZNIL pristup k E_Y, hoci TYPE EInnerEnum2 poznal.
	CComplexTemplate<wstring>::EInnerEnum2					Enum2=CComplexTemplate<wstring>::E_Y;

	wprintf_s(L"Enum2 [%d] !\n",Enum2);
*/
#endif

	PrintLineSeparator();

	CComplexTemplate<double>									DoubleValue;

	DoubleValue.MVariable2=12.2;

	int															IntValue1=DoubleValue.Convert<int>();
	// Pouzije sa KONVERZNY OPERATOR.
	int															IntValue2=DoubleValue;

	wprintf_s(L"DoubleValue [%f] !\n",DoubleValue.MVariable2);
	wprintf_s(L"IntValue1 [%d] !\n",IntValue1);
	wprintf_s(L"IntValue2 [%d] !\n",IntValue2);

	PrintLineSeparator();

	CComplexTemplate<wstring>::CNestedTemplate<int>				NestedType;

	NestedType.MNestedValue=44;

	wprintf_s(L"NestedType [%d] !\n",NestedType.MNestedValue);

	PrintLineSeparator();

	Value.SetPrivateMember(L"Timmy Anderson");

	CFriendlyTemplate<wstring>									FriendlyTemplate;
	wstring														PrivateMember=FriendlyTemplate.GetPrivateMember(Value);

	wprintf_s(L"PrivateMember [%ls] !\n",PrivateMember.c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
bool AreEqual(TType Value1, TType Value2)
{
	if (Value1==Value2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
template<typename TType, typename TComparer>
bool AreEqual(TType Value1, TType Value2)
{
	TComparer													Comparer;

	if (Comparer(Value1,Value2)==true)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 operator*(TType1 Value1, TType1 Value2)
{
	wprintf_s(L"CONVERSION OPERATOR CALLED !\n");

	TType2														ConvertedValue=Value1.size()*Value2.size();

	return(ConvertedValue);
}
//-----------------------------------------------------------------------------
void TestFunctionTemplate(void)
{
	PrintLineSeparator();

	wprintf_s(L"AreEqual<int>(8,8) [%ls] !\n",(AreEqual<int>(8,8)==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AreEqual<int>(8,2) [%ls] !\n",(AreEqual<int>(8,2)==true) ? L"TRUE" : L"FALSE");

	// Dedukcia TYPE PARAMETERS.
	wprintf_s(L"AreEqual(8,8) [%ls] !\n",(AreEqual(8,8)==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AreEqual(8,2) [%ls] !\n",(AreEqual(8,2)==true) ? L"TRUE" : L"FALSE");

	CComplexTemplate<int>										CT1;
	CComplexTemplate<int>										CT2;

	CT1.MVariable2=8;
	CT2.MVariable2=2;

	wprintf_s(L"AreEqual<int,CComplexTemplateComparer>(CT1,CT1) [%ls] !\n",(AreEqual<CComplexTemplate<int>,CComplexTemplateComparer>(CT1,CT1)==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AreEqual<int,CComplexTemplateComparer>(CT1,CT2) [%ls] !\n",(AreEqual<CComplexTemplate<int>,CComplexTemplateComparer>(CT1,CT2)==true) ? L"TRUE" : L"FALSE");

	wstring														Value1=L"Timmy Anderson";
	wstring														Value2=L"Atreyu";
	size_t														ConvertedValue=operator*<wstring,size_t>(Value1,Value2);

	wprintf_s(L"Value1.size() [%zd] !\n",Value1.size());
	wprintf_s(L"Value2.size() [%zd] !\n",Value2.size());
	wprintf_s(L"ConvertedValue [%zd] !\n",ConvertedValue);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void CopyMoveSemanticsTemplate(TType&)
{
	wprintf_s(L"COPY VERSION of CopyMoveSemanticsTemplate() CALLED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
void CopyMoveSemanticsTemplate(TType&&)
{
	wprintf_s(L"MOVE VERSION of CopyMoveSemanticsTemplate() CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestCopyMoveSemanticsTemplate(void)
{
	PrintLineSeparator();

	int															Value1=100;

	// Vola sa TEMPLATE s COPY SEMANTICS, pretoze [Value1] je LVALUE.
	CopyMoveSemanticsTemplate(Value1);

	// Vola sa TEMPLATE s MOVE SEMANTICS, pretoze [100] je RVALUE.
	CopyMoveSemanticsTemplate(100);

	PrintLineSeparator();

	wstring														Value2=L"ABC";

	// Vola sa TEMPLATE s COPY SEMANTICS, pretoze [Value2] je LVALUE.
	CopyMoveSemanticsTemplate(Value2);

	// Vola sa TEMPLATE s MOVE SEMANTICS, pretoze [L"ABC"] je RVALUE.
	CopyMoveSemanticsTemplate<wstring>(L"ABC");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// TEMPLATE.
template<typename TType>
void TemplateOverloading(TType)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverloading(TType)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// TEMPLATE s PARAMETER vector<TType>.
template<typename TType>
void TemplateOverloading(vector<TType>)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverloading(vector<TType>)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION k TEMPLATE [void TemplateOverloading(TType)].
template<>
void TemplateOverloading(double)
{
	wprintf_s(L"TEMPLATE SPECIALIZATION FUNCTION [void TemplateOverloading(double)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! NON-TEMPLATE FUNCTION.
void TemplateOverloading(double)
{
	wprintf_s(L"NON-TEMPLATE FUNCTION [void TemplateOverloading(double)] CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestTemplateOverloading(void)
{
	PrintLineSeparator();

	// Vola sa [void TemplateOverloading(TType)].
	TemplateOverloading(100);
	// Vola sa [void TemplateOverloading(vector<TType>)].
	TemplateOverloading(vector<int>());
	// !!! Vola sa [void TemplateOverloading(TType)] a NIE [void TemplateOverloading(vector<TType>)], pretoze sa pouzila EXPLICIT QUALIFICATION.
	TemplateOverloading<vector<int>>(vector<int>());
	// Vola sa [void TemplateOverloading(TType)].
	TemplateOverloading(list<int>());

	PrintLineSeparator();

	// !!! Vola sa TEMPLATE SPECIALIZATION [void TemplateOverloading(double)].
	TemplateOverloading<>(3.2);
	// !!! Vola sa NON-TEMPLATE FUNCTION [void TemplateOverloading(double)].
	TemplateOverloading(3.2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TemplateOverride1(TType, typename TType::value_type)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverride1(TType, TType::value_type)] CALLED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
void TemplateOverride1(TType, TType)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverride1(TType, TType)] CALLED !\n");
}
//-----------------------------------------------------------------------------
// !!! SFINAE sa aplikuje aj na RETURN VALUE.
template<typename TType>
typename TType::value_type TemplateOverride2(TType)
{
	wprintf_s(L"TEMPLATE FUNCTION [typename TType::value_type TemplateOverride2(TType)] CALLED !\n");

	typename TType::value_type									Value;

	memset(&Value,0,sizeof(typename TType::value_type));

	return(Value);
}
//-----------------------------------------------------------------------------
// !!! SFINAE sa aplikuje aj na RETURN VALUE.
template<typename TType>
TType TemplateOverride2(TType* Value)
{
	wprintf_s(L"TEMPLATE FUNCTION [TType TemplateOverride2(TType)] CALLED !\n");

	return(*Value);
}
//-----------------------------------------------------------------------------
template<typename TType>
void TemplateOverride3(TType Value, typename TType::value_type)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverride3(TType Value, typename TType::value_type)] CALLED !\n");

	// !!! SFINAE sa NEAPLIKUJE na BODY TEMPLATE FUNCTIONS a TEMPLATE METHODS. Iba na ich DEKLARACIU.
	// !!!!! Preto ked C++ vyberie tuto FUNCTION (pri pouziti SFINAE), tak jej nasledna kompilacia vyhodi COMPILER ERROR, pre TYPE ARGUMENTS, ktore NEMAJU OPERATOR++.
	Value++;
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateOverride3(TType1 Value, TType2)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateOverride3(TType1 Value, TType2)] CALLED !\n");

	Value++;
}
//-----------------------------------------------------------------------------
void TestTemplateFunctionSFINAE(void)
{
	PrintLineSeparator();

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [void TemplateOverride1(TType, typename TType::value_type)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [void TemplateOverride1(TType, TType)].
	TemplateOverride1(100,100);

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [void TemplateOverride1(TType, typename TType)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [void TemplateOverride1(TType, TType::value_type)].
	TemplateOverride1(vector<int>(),100);

	PrintLineSeparator();

	int															Value=100;

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [typename TType::value_type TemplateOverride2(TType)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [TType TemplateOverride2(TType* Value)].
	TemplateOverride2(&Value);

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [TType TemplateOverride2(TType* Value)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [typename TType::value_type TemplateOverride2(TType)].
	TemplateOverride2(vector<int>());

	PrintLineSeparator();

	// !!! Aplikuje sa SFINAE a preto sa vola TEMPLATE FUNCTION [void TemplateOverride3(TType1 Value, TType2)].
	TemplateOverride3(100,100);

	// !!!!! Aj tu sa SFINAE aplikuje a preto sa vyberie TEMPLATE FUNCTION [void TemplateOverride3(TType Value, typename TType::value_type)].
	// !!!!! Kedze vsak v BODY TEMPLATE FUNCTION sa nachadza CODE, ktory chce INKREMENTOVAT [vector<int>], pricom [vector<int>] NEMA OPERATOR++, tak COMPILER hodi ERROR.
	//TemplateOverride3(vector<int>(),100);

	PrintLineSeparator();

	CClassWithOverloadedMethods									ClassWithOverloadedMethods;

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, typename TType::value_type)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, TType)].
	ClassWithOverloadedMethods.TemplateOverride(100,100);

	// !!! Aj napriek tomu, ze pokus o substituciu pre TEMPLATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, typename TType)] hodi COMPILATION ERROR, mechanizmus SFINAE zabezpeci, ze sa ERROR IGNORUJE a vyberie sa TEMPATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, TType::value_type)].
	ClassWithOverloadedMethods.TemplateOverride(vector<int>(),100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! POZOR. SYNTAX [-> RETURN TYPE] neoznacuje FUNCTION ako LAMBDA FUNCTION. Ta ma inu SYNTAX. Je to iba novy sposob v C++ ako oznacit RETURN TYPE lubovolnej FUNCTION.
// !!!!! SYNTAX [-> RETURN TYPE] je NEVYHNUTNE POUZIT. Pri pokuse zmenit ju na klasicku RETURN VALUE (tj. pred nazvom FUNCTION) VC++ COMPILER vykona NESPRAVNU TEMPLATE DEDUCTION a nevrati spravnu informaciu ci TYPE ma, alebo nema OPERATOR+.
// !!!!! V G++ pri pokuse nahradit [auto] za [decltype(Value1+Value2,true)] COMPILER hodi ERROR, v ktorom sa pise, ze PARAMETERS [Value1] a [Value2] su OUT OF SCOPE. Je to preto, lebo su deklarovane ako klasicke PARAMETERS FYZICKY AZ za [decltype(Value1+Value2,true)] a tym padom ich COMPILER NEPOZNA.
// !!!!! POZOR. Na to, aby mechanizmus fungoval MUSI tato verzia obsahovat iba 1 TYPE PARAMETERS a vracia TEMPLATE FUNCTION vracajuca FALSE MUSI mat 2 TYPE PARAMETERS. Tym COMPILER, aj ked OBE TEMPLATE FUNCTIONS je mozne subsituovat vyberie 1. VERZIU, ktora ma iba 1 TYPE PARAMETER.
template <typename TType>
auto TypeHasOperatorPlus(TType Value1, TType Value2) -> decltype(Value1+Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	wprintf_s(L"TYPE HAS OPERATOR+ !\n");

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool TypeHasOperatorPlus(TType1, TType2)
{
	wprintf_s(L"!!! TYPE does NOT have OPERATOR+ !\n");

	return(false);
}
//-----------------------------------------------------------------------------
// !!!!! POZOR. SYNTAX [-> RETURN TYPE] neoznacuje FUNCTION ako LAMBDA FUNCTION. Ta ma inu SYNTAX. Je to iba novy sposob v C++ ako oznacit RETURN TYPE lubovolnej FUNCTION.
// !!!!! SYNTAX [-> RETURN TYPE] je NEVYHNUTNE POUZIT. Pri pokuse zmenit ju na klasicku RETURN VALUE (tj. pred nazvom FUNCTION) VC++ COMPILER vykona NESPRAVNU TEMPLATE DEDUCTION a nevrati spravnu informaciu ci TYPE ma, alebo nema OPERATOR-.
// !!!!! V G++ pri pokuse nahradit [auto] za [decltype(Value1-Value2,true)] COMPILER hodi ERROR v ktorom sa pise, ze PARAMETERS [Value1] a [Value2] su OUT OF SCOPE. Je to preto, lebo su deklarovane ako klasicke PARAMETERS FYZICKY AZ za [decltype(Value1-Value2,true)] a tym padom ich COMPILER NEPOZNA.
// !!!!! POZOR. Na to, aby mechanizmus fungoval MUSI tato verzia obsahovat iba 1 TYPE PARAMETERS a vracia TEMPLATE FUNCTION vracajuca FALSE MUSI mat 2 TYPE PARAMETERS. Tym COMPILER, aj ked OBE TEMPLATE FUNCTIONS je mozne subsituovat vyberie 1. VERZIU, ktora ma iba 1 TYPE PARAMETER.
template <typename TType>
auto TypeHasOperatorMinus(TType Value1, TType Value2) -> decltype(Value1-Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	wprintf_s(L"TYPE HAS OPERATOR- !\n");

	return(true);
}
//-----------------------------------------------------------------------------
template <typename TType1, typename TType2>
bool TypeHasOperatorMinus(TType1, TType2)
{
	wprintf_s(L"!!! TYPE does NOT have OPERATOR- !\n");

	return(false);
}
//-----------------------------------------------------------------------------
// !!!!! Tato dvojica OVERLOADED TEMPLATE FUNCTIONS NonFunctionalTypeHasOperatorMinus() NESPRAVNE DETEKUJE pritomnost OPERATOR- v TYPE, pretoze verzia NonFunctionalTypeHasOperatorMinus() vracajuca TRUE ma VIAC TYPE PARAMETERS ako verzia vracajuca FALSE a kedze pre ARGUMENTS (100,100) OBE TEMPLATE FUNCTION VYHOVOUJU substitucii, COMPILER da prednost TEMPLATE FUNCTION s MENSIM POCTOM TYPE PARAMETERS.
template <typename TType1, typename TType2>
auto NonFunctionalTypeHasOperatorMinus(TType1 Value1, TType2 Value2) -> decltype(Value1-Value2,true)
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value1;
	(void)Value2;

	wprintf_s(L"TYPE HAS OPERATOR- !\n");

	return(true);
}
//-----------------------------------------------------------------------------
// !!!!! Tato dvojica OVERLOADED TEMPLATE FUNCTIONS NonFunctionalTypeHasOperatorMinus() NESPRAVNE DETEKUJE pritomnost OPERATOR- v TYPE, pretoze verzia NonFunctionalTypeHasOperatorMinus() vracajuca TRUE ma VIAC TYPE PARAMETERS ako verzia vracajuca FALSE a kedze pre ARGUMENTS (100,100) OBE TEMPLATE FUNCTION VYHOVOUJU substitucii, COMPILER da prednost TEMPLATE FUNCTION s MENSIM POCTOM TYPE PARAMETERS.
template <typename TType>
bool NonFunctionalTypeHasOperatorMinus(TType, TType)
{
	wprintf_s(L"????? TYPE does NOT have OPERATOR- !\n");

	return(false);
}
//-----------------------------------------------------------------------------
void TestHasOperatorsSFINAE(void)
{
	PrintLineSeparator();

	if (TypeHasOperatorPlus(100,200)==true)
	{
		wprintf_s(L"\tTypeHasOperatorPlus(100,200)==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorPlus(100,200)==FALSE !\n");
	}

	PrintLineSeparator();

	if (TypeHasOperatorPlus(wstring(L"100"),wstring(L"200"))==true)
	{
		wprintf_s(L"\tTypeHasOperatorPlus(wstring(L\"100\"),wstring(L\"200\"))==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorPlus(wstring(L\"100\"),wstring(L\"200\"))==FALSE !\n");
	}

	PrintLineSeparator();

	if (TypeHasOperatorMinus(100,200)==true)
	{
		wprintf_s(L"\tTypeHasOperatorMinus(100,200)==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorMinus(100,200)==FALSE !\n");
	}

	PrintLineSeparator();

	if (TypeHasOperatorMinus(wstring(L"100"),wstring(L"200"))==true)
	{
		wprintf_s(L"\tTypeHasOperatorMinus(wstring(L\"100\"),wstring(L\"200\"))==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorMinus(wstring(L\"100\"),wstring(L\"200\"))==FALSE !\n");
	}

	PrintLineSeparator();

	// !!! FUNCTION VRATI NEKORETNE FALSE, pretoze NonFunctionalTypeHasOperatorMinus(), ktora vracia TRUE ma VIAC TYPE PARAMETERS ako verzia, ktora vracia TRUE a tak ju COMPILER ako OBE OVERLOADED VERZIE VYHOVUJU ARGUMENTS (100,200) PREFERUJE.
	if (NonFunctionalTypeHasOperatorMinus(100,200)==true)
	{
		wprintf_s(L"\tNonFunctionalTypeHasOperatorMinus(100,200)==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorMinus(100,200)==FALSE !\n");
	}

	PrintLineSeparator();

	// !!! FUNCTION VRATI NEKORETNE FALSE, pretoze NonFunctionalTypeHasOperatorMinus(), ktora vracia TRUE ma VIAC TYPE PARAMETERS ako verzia, ktora vracia TRUE a tak ju COMPILER ako OBE OVERLOADED VERZIE VYHOVUJU ARGUMENTS ("100","200") PREFERUJE.
	if (NonFunctionalTypeHasOperatorMinus(wstring(L"100"),wstring(L"200"))==true)
	{
		wprintf_s(L"\tNonFunctionalTypeHasOperatorMinus(wstring(L\"100\"),wstring(L\"200\"))==TRUE !\n");
	}
	else
	{
		wprintf_s(L"\tTypeHasOperatorMinus(wstring(L\"100\"),wstring(L\"200\"))==FALSE !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Klasicka SYNTAX pre RETURN VALUE.
int ReturnValue1(int Value)
{
	return(Value);
}
//-----------------------------------------------------------------------------
// Nova SYNTAX pre RETURN VALUE.
auto ReturnValue2(int Value) -> int
{
	return(Value);
}
//-----------------------------------------------------------------------------
// !!! Nova SYNTAX pre RETURN VALUE umoznujuca definovat EXPRESSIONS, ktore sa vykonaju v COMPILE TIME.
// !!!!! V OPERATOR decltype() moze byt EXPRESSION, ktory C++ vypocita v COMPILE TIME a zisti jeho TYPE, ktory je potom povazovany za RETURN TYPE danej FUNCTION.
// !!!!! POZOR. Vysledok EXPRESSION v OPERATOR decltype() NIE JE RETURN VALUE. Je to iba COMPILE TIME CONSTANT, ktoru C++ pouziva na detekciu RETURN TYPE danej FUNCTION.
auto ReturnValue3(int Value) -> decltype(Value*6+45)
{
	return(Value);
}
//-----------------------------------------------------------------------------
// !!! Priklad EXPRESSION v OPERATOR decltype(), ktora vracia DOUBLE.
auto ReturnValue4(int Value) -> decltype(Value*6+45.0)
{
	return(Value);
}
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
// !!! Priklad EXPRESSION s pouzitim [OPERATOR,]. FUNCTION vracia ako RETURN VALUE TYPE [long], pretoze [OPERATOR,] vracia ako RETURN VALUE EXPRESSION SUBEXPRESSION za ciarkou.
auto ReturnValue5(int Value) -> decltype(Value*6+45.0,100L)
{
	return(Value);
}
#endif
//-----------------------------------------------------------------------------
void TestReturnValue(void)
{
	PrintLineSeparator();

	printf_s("RETURN VALUE ReturnValue1(100) [%s] !\n",typeid(ReturnValue1(100)).name());
	printf_s("RETURN VALUE ReturnValue2(100) [%s] !\n",typeid(ReturnValue2(100)).name());
	printf_s("RETURN VALUE ReturnValue3(100) [%s] !\n",typeid(ReturnValue3(100)).name());
	printf_s("RETURN VALUE ReturnValue4(100) [%s] !\n",typeid(ReturnValue4(100)).name());

#ifdef _MSC_VER
	printf_s("RETURN VALUE ReturnValue5(100) [%s] !\n",typeid(ReturnValue5(100)).name());
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSFINAEExpressions1(void)
{
	PrintLineSeparator();

	int															IntValue1=111;
	int															IntValue2=222;
	double														DoubleValue1=111.11;
	double														DoubleValue2=222.22;
	string														StringValue1="A";
	string														StringValue2="B";

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(IntValue1,IntValue2) [%ls] !\n",(HasOperatorPlus(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia FALSE.
	// !!! C++ pri TEMPLATE INSTANCING NEROBI IMPLICITNE KONVERZIE, a preto FUNCTION vrati FALSE.
	wprintf_s(L"HasOperatorPlus(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorPlus(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorPlus(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorPlus(StringValue1,IntValue1) [%ls] !\n",(HasOperatorPlus(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlus(StringValue1,StringValue2) [%ls] !\n",(HasOperatorPlus(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(IntValue1,IntValue2) [%ls] !\n",(HasOperatorDivide(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia FALSE.
	// !!! C++ pri TEMPLATE INSTANCING NEROBI IMPLICITNE KONVERZIE, a preto FUNCTION vrati FALSE.
	wprintf_s(L"HasOperatorDivide(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorDivide(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivide(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorDivide(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(StringValue1,IntValue1) [%ls] !\n",(HasOperatorDivide(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivide(StringValue1,StringValue2) [%ls] !\n",(HasOperatorDivide(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSFINAEExpressions2(void)
{
	PrintLineSeparator();

	int															IntValue1=111;
	int															IntValue2=222;
	double														DoubleValue1=111.11;
	double														DoubleValue2=222.22;
	string														StringValue1="A";
	string														StringValue2="B";

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusVCPP(IntValue1,IntValue2) [%ls] !\n",(HasOperatorPlusVCPP(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia TRUE.
	// !!! VISUAL C++ KOREKTNE vrati TRUE. Tento CODE vsak funguje IBA vo VISUAL C++. G++ vrati COMPILER ERROR, pretoze TYPE [string] ako NON-COPYABLE NEMOZE byt preneseny ako ARGUMENT do FUNCTION s VARIABILNYM POCTOM PARAMETERS (...).
	wprintf_s(L"HasOperatorPlusVCPP(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorPlusVCPP(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusVCPP(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorPlusVCPP(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorPlusVCPP(StringValue1,IntValue1) [%ls] !\n",(HasOperatorPlusVCPP(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusVCPP(StringValue1,StringValue2) [%ls] !\n",(HasOperatorPlusVCPP(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivideVCPP(IntValue1,IntValue2) [%ls] !\n",(HasOperatorDivideVCPP(IntValue1,IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia TRUE.
	// !!! VISUAL C++ KOREKTNE vrati TRUE. Tento CODE vsak funguje IBA vo VISUAL C++. G++ vrati COMPILER ERROR, pretoze TYPE [string] ako NON-COPYABLE NEMOZE byt preneseny ako ARGUMENT do FUNCTION s VARIABILNYM POCTOM PARAMETERS (...).
	wprintf_s(L"HasOperatorDivideVCPP(IntValue1,DoubleValue1) [%ls] !\n",(HasOperatorDivideVCPP(IntValue1,DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivideVCPP(DoubleValue1,DoubleValue2) [%ls] !\n",(HasOperatorDivideVCPP(DoubleValue1,DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivideVCPP(StringValue1,IntValue1) [%ls] !\n",(HasOperatorDivideVCPP(StringValue1,IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivideVCPP(StringValue1,StringValue2) [%ls] !\n",(HasOperatorDivideVCPP(StringValue1,StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSFINAEExpressions3(void)
{
	PrintLineSeparator();

	int															IntValue1=111;
	int															IntValue2=222;
	double														DoubleValue1=111.11;
	double														DoubleValue2=222.22;
	string														StringValue1="A";
	string														StringValue2="B";

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusByPointer(&IntValue1,&IntValue2) [%ls] !\n",(HasOperatorPlusByPointer(&IntValue1,&IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia TRUE.
	wprintf_s(L"HasOperatorPlusByPointer(&IntValue1,&DoubleValue1) [%ls] !\n",(HasOperatorPlusByPointer(&IntValue1,&DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusByPointer(&DoubleValue1,&DoubleValue2) [%ls] !\n",(HasOperatorPlusByPointer(&DoubleValue1,&DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorPlusByPointer(&StringValue1,&IntValue1) [%ls] !\n",(HasOperatorPlusByPointer(&StringValue1,&IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorPlusByPointer(&StringValue1,&StringValue2) [%ls] !\n",(HasOperatorPlusByPointer(&StringValue1,&StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivideByPointer(&IntValue1,&IntValue2) [%ls] !\n",(HasOperatorDivideByPointer(&IntValue1,&IntValue2)==true) ? L"TRUE" : L"FALSE");

	// !!! Vracia TRUE.
	wprintf_s(L"HasOperatorDivideByPointer(&IntValue1,&DoubleValue1) [%ls] !\n",(HasOperatorDivideByPointer(&IntValue1,&DoubleValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia TRUE.
	wprintf_s(L"HasOperatorDivideByPointer(&DoubleValue1,&DoubleValue2) [%ls] !\n",(HasOperatorDivideByPointer(&DoubleValue1,&DoubleValue2)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivideByPointer(&StringValue1,&IntValue1) [%ls] !\n",(HasOperatorDivideByPointer(&StringValue1,&IntValue1)==true) ? L"TRUE" : L"FALSE");

	// Vracia FALSE.
	wprintf_s(L"HasOperatorDivideByPointer(&StringValue1,&StringValue2) [%ls] !\n",(HasOperatorDivideByPointer(&StringValue1,&StringValue2)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSFINAEExpressions4(void)
{
	PrintLineSeparator();

	int															IntValue=100;
	string														StringValue="AAA";
	CTypeWithMethodXXX											TypeWithMethodXXXValue;

	wprintf_s(L"HasMethodXXX(IntValue) [%ls] !\n",(HasMethodXXX(IntValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXX(StringValue) [%ls] !\n",(HasMethodXXX(StringValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXXByPointer(&StringValue) [%ls] !\n",(HasMethodXXXByPointer(&StringValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXX(TypeWithMethodXXXValue) [%ls] !\n",(HasMethodXXX(TypeWithMethodXXXValue)==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"HasMethodXXXByPointer(&TypeWithMethodXXXValue) [%ls] !\n",(HasMethodXXXByPointer(&TypeWithMethodXXXValue)==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void Derivation1(CBaseTemplate<TType>* Value)
{
	wprintf_s(L"FUNCTION [void Derivation1(CBaseTemplate<TType>*)] CALLED !\n");

	Value->TestFunction();
}
//-----------------------------------------------------------------------------
template<typename TType>
void Derivation2(CBaseTemplate<TType>* Value)
{
	wprintf_s(L"FUNCTION [void Derivation2(CBaseTemplate<TType>*)] CALLED !\n");

	Value->TestFunction();
}
//-----------------------------------------------------------------------------
template<typename TType>
void Derivation2(CDerivedTemplate<TType>* Value)
{
	wprintf_s(L"FUNCTION [void Derivation2(CDerivedTemplate<TType>*)] CALLED !\n");

	Value->TestFunction();
}
//-----------------------------------------------------------------------------
void TestTemplateDerivations(void)
{
	PrintLineSeparator();

	CDerivedTemplate<int>										Derived;
	CBaseTemplate<int>*											PointerToBase=&Derived;
	CDerivedTemplate<int>*										PointerToDerived=&Derived;

	Derivation1(PointerToBase);

	PrintLineSeparator();

	// COMPILER vykonava standardne konverzie z POINTER/REFERENCE na DERIVED CLASS na POINTER/REFERENCE na BASE CLASS.
	Derivation1(PointerToDerived);

	PrintLineSeparator();

	Derivation2(PointerToBase);

	PrintLineSeparator();

	Derivation2(PointerToDerived);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TemplateConversions1(TType, TType)
{
	wprintf_s(L"TEMPLATE FUNCTION with 1 TYPE PARAMETER CALLED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateConversions1(TType1, TType2)
{
	wprintf_s(L"TEMPLATE FUNCTION with 2 TYPE PARAMETERS CALLED !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
void TemplateConversions2(TType, double)
{
	wprintf_s(L"TEMPLATE FUNCTION [void TemplateConversions2(TType Value1, double Value2)] CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestTemplateConversions(void)
{
	PrintLineSeparator();

	TemplateConversions1(10,20);

	// !!! Kedze COMPILER pri substitucii TYPE PARAMETERS NEVYKONAVA ani ZAKLADNE KONVERZIE, tak sa vola verzia FUNCTION s 2 TYPE PARAMETERS.
	TemplateConversions1(10,20.25);

	// !!! Kedze COMPILER pri substitucii TYPE PARAMETERS NEVYKONAVA ani ZAKLADNE KONVERZIE, tak sa vola verzia FUNCTION s 2 TYPE PARAMETERS.
	TemplateConversions1(10,20L);

	TemplateConversions1(10,(int) 20L);

	// !!! Pre NON-TEMPLATE PARAMETERS COMPILER vykonava STANDARDNE CONVERSIONS.
	TemplateConversions2("AAA",100);

	// !!! Pre NON-TEMPLATE PARAMETERS COMPILER vykonava STANDARDNE CONVERSIONS.
	TemplateConversions2("AAA",100L);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAliases(void)
{
	PrintLineSeparator();

	printf_s("IsBigger<int,double>::Type [%s] !\n",typeid(IsBigger<int,double>).name());
	printf_s("IsBiggerAsInt<double>::Type [%s] !\n",typeid(IsBiggerAsInt<double>).name());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasFunctionXXX(void)
{
	PrintLineSeparator();

	wprintf_s(L"SFunctionXXXCheck<int>::RESULT [%ls] !\n",(SFunctionXXXCheck<int>::RESULT==true) ? L"TRUE" : L"FALSE");

	// !!! Toto uz FUNGUJE aj v G++.
	wprintf_s(L"SFunctionXXXCheck<wstring>::RESULT [%ls] !\n",(SFunctionXXXCheck<wstring>::RESULT==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT [%ls] !\n",(SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateClassTemplateMethodAndTemplateFunction();
	//TestTemplateClassWithExternalTemplateMethods();
	//TestTemplateFunctionOverloading();
	//TestTemplateClassOverloading();
	//TestTemplateEquivalence();
	//TestClassTemplate();
	//TestFunctionTemplate();
	//TestCopyMoveSemanticsTemplate();
	//TestTemplateOverloading();
	//TestTemplateFunctionSFINAE();
	//TestHasOperatorsSFINAE();
	//TestReturnValue();
	//TestSFINAEExpressions1();
	//TestSFINAEExpressions2();
	//TestSFINAEExpressions3();
	//TestSFINAEExpressions4();
	//TestTemplateDerivations();
	//TestTemplateConversions();
	//TestAliases();
	TestHasFunctionXXX();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------