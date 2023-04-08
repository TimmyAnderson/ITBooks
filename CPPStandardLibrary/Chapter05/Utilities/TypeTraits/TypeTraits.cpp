//-----------------------------------------------------------------------------
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <string>
#include <iostream>
#include <functional>
#include <list>
#include <locale>
#include <codecvt> 
#include "MyDebug.h"
#include "CClassWithCustomOperators.h"
#include "CHasOperators.h"
#include "CType1.h"
#include "CType2.h"
#include "CBase.h"
#include "CDerivedPublic.h"
#include "CDerivedProtected.h"
#include "CDerivedPrivate.h"
#include "ESimpleEnum1.h"
#include "ESimpleEnum2.h"
#include "EClassEnum1.h"
#include "EClassEnum2.h"
#include "SFields.h"
#include "CBaseClass.h"
#include "CDerivedClass1.h"
#include "CDerivedClass2.h"
#include "CTypeWithCopyConstructor.h"
#include "CFunctor.h"
#include "CName.h"
#include "CTypeWithOperatorsAndMethods.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintValueOrPointer() ma ako 2. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je NON-POINTER VALUE.
template<typename TType>
void InternalPrintValueOrPointer(TType ValueOrPointer, false_type)
{
	wcout << L"VALUE from VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintValueOrPointer() ma ako 2. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je POINTER VALUE.
template<typename TType>
void InternalPrintValueOrPointer(TType ValueOrPointer, true_type)
{
	wcout << L"VALUE from POINTER [" << *ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValueOrPointer(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je POINTER sa pouziva TYPE TRAIT is_pointer<T>().
	InternalPrintValueOrPointer(ValueOrPointer,is_pointer<TType>());
}
//-----------------------------------------------------------------------------
void TestIsPointerTrait(void)
{
	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=100;
	wstring*													PointerToName=&Name;
	int*														PointerToAge=&Age;

	PrintValueOrPointer(Name);
	PrintValueOrPointer(Age);

	PrintLineSeparator();

	PrintValueOrPointer(PointerToName);
	PrintValueOrPointer(PointerToAge);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)
{
	wcout << L"INTEGER VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)
{
	wcout << L"FLOAT VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 2. PARAMETER TYPE [false_type], TYPE je NON-ARITHMETIC TYPE.
// Pre PARAMETER [int] sa C++ chova nasledovne.
// !!!!! A. CODE [InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<int>(),is_integral<int>())] volany vo FUNCTION PrintIntegerOrFloat1() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty FALSE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat1(int,true,true)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!! F. Kedze z 3 kandidatov vyhovuje IBA FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)], C++ vyberie prave tuto FUNCTION.
// Pre PARAMETER [wstring] sa C++ chova nasledovne.
// !!!!! A. CODE [InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<wstring>(),is_integral<wstring>())] volany vo FUNCTION PrintIntegerOrFloat1() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty FALSE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA VALUE [false] na TYPE [true_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [false] na TYPE [true_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [false] na TYPE [false_type] co C++ PODPORUJE. Pre 3. PARAMETER NIE JE NUTNA ZIADNA KONVERZIA, kedze sa jedna o GENERIC PARAMETER. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!! F. Kedze z 3 kandidatov vyhovuje IBA FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)], C++ vyberie prave tuto FUNCTION.
template<typename TType, typename... TTypes>
void InternalPrintIntegerOrFloat1(TType, false_type, TTypes...)
{
	wcout << L"TYPE is NOT an ARITHMETIC TYPE !" << endl;
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintIntegerOrFloat1(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<TType>(),is_integral<TType>());
}
//-----------------------------------------------------------------------------
void TestIsIntegerTrait1(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	PrintIntegerOrFloat1(Value1);
	PrintIntegerOrFloat1(Value2);
	PrintIntegerOrFloat1(Value3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat2() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, true_type)
{
	wcout << L"INTEGER VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat2() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, false_type)
{
	wcout << L"FLOAT VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak TYPE NIE JE ARITHMETIC TYPE, zavola sa tato verzia OVERLOADED FUNCTION.
template<typename... TTypes>
void InternalPrintIntegerOrFloat2(TTypes...)
{
	wcout << L"TYPE is NOT an ARITHMETIC TYPE !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!!!! Vdaka OVERLOADING RULES tento CODE aj pre INTEGER a FLOAT TYPES ZAVOLA VARIADIC FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)], co je ERROR. Dovod je nasledujuci.
// !!!!! A. CODE [InternalPrintIntegerOrFloat2(int,is_arithmetic<int>(),is_integral<int>())] volany vo FUNCTION PrintIntegerOrFloat2() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat2(int,true,true). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty TRUE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!!!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat2(int,true,true)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER zisti, ze je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE CONVERSIONS, pretoze FUNCTION je VARIADIC FUNCTION, ktora moze mat LUBOVLNY POCET TYPE PARAMETERS. C++ zaradi FUNCTION ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze NIE SU NUTNE ZIADNE USER DEFINED CONVERSIONS.
// !!!!! F. Nasledne C++ porovna vsetky VYHOVUJUCU 1. a 3. FUNCTIONS. Kedze 3. FUNCTION NEVYZADUJE ZIADNE USER DEFINED CONVERSIONS, zatial do 1. FUNCTION VYZADUJE 2 USER DEFINED CONVERSIONS, vyberie 3. FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)].
// !!!!! G. Vysledkom je NESPRAVNA DETEKCIA, kde aj INTEGER a FLOAT TYPES su oznacene ako TYPES, ktore NIE SU ARITHMETIC TYPES. Cely PROBLEM spociva v tom, ze OPERATOR() pre TYPE [is_arithmetic<T>] a TYPE [is_integral<T>] vracia TYPE [bool], ktory je NUTNE KONVERTOVAT na OCAKAVANE TYPES [true_type] a [false_type].
template<typename TType>
void PrintIntegerOrFloat2(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	// !!!!! Vola sa OPERATOR() a NIE FIELD [type].
	InternalPrintIntegerOrFloat2(ValueOrPointer,is_arithmetic<TType>(),is_integral<TType>());
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
void TestIsIntegerTrait2(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	// !!!!! CODE CHYBNE vypise, ze ZIADEN z TYPES NIE JE ARITHMETIC TYPE co je NEZMYSEL.
	PrintIntegerOrFloat2(Value1);
	PrintIntegerOrFloat2(Value2);
	PrintIntegerOrFloat2(Value3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat3() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)
{
	wcout << L"INTEGER VALUE [" << ValueOrPointer << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat3() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, false_type)
{
	wcout << L"FLOAT VALUE [" << ValueOrPointer << "] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak TYPE NIE JE ARITHMETIC TYPE, zavola sa tato verzia OVERLOADED FUNCTION.
template<typename... TTypes>
void InternalPrintIntegerOrFloat3(TTypes...)
{
	wcout << L"TYPE is NOT an ARITHMETIC TYPE !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION PrintIntegerOrFloat3().
// !!!!! A. CODE [InternalPrintIntegerOrFloat3(int,is_arithmetic<int>::type(),is_integral<int>::type())] volany vo FUNCTION PrintIntegerOrFloat3() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type).
// !!!!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!! C. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! D. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE KONVERZIE a preto tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze ZIADNE CONVERSIONS NIE SU NUTNE.
// !!!!! E. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 3. PARAMETER je NUTNA KONVERZIA z TYPE [true_type] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! F. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TTypes...)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE CONVERSIONS, pretoze FUNCTION je VARIADIC FUNCTION, ktora moze mat LUBOVLNY POCET TYPE PARAMETERS. C++ zaradi FUNCTION ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze NIE SU NUTNE ZIADNE USER DEFINED CONVERSIONS.
// !!!!! G. Nasledne C++ porovna 1. a 3. FUNCTIONS, ktore ako JEDINE VYHOVUJU. Kedze ANI JEDNA FUNCTIONS NEVYZADUJE USER DEFINED CONVERSIONS, su v tomto kriteriu ROVNOCENNE. C++ v takom pripade PREFERUJE NON-VARIADIC FUNCTION PRED VARIADIC FUNCTION a preto vyberie 1. FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)].
// !!!!! H. Vysledkom je SPRAVNA DETEKCIA TYPE.
template<typename TType>
void PrintIntegerOrFloat3(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	// !!!!! ZASADNYM ROZDIELOM oproti FUNCTION PrintIntegerOrFloat3() je vytvorenie INSTANCII TYPE [is_arithmetic<TType>::type] a [is_integral<TType>::type] NAMIESTO POUZITIA OPERATOR(). DOVODOM PRECO tento variant FUNGUJE je v tom, ze [is_arithmetic<TType>::type] a [is_integral<TType>::type] su vo vysledku bud [true_type], alebo [false_type] co umoznuje EXACT TYPE MATCH voci TYPES pozadovanym InternalPrintIntegerOrFloat3(). OPERATOR() naopak vracia TYPE [bool], kde su na TYPES [true_type] a [false_type] co ZNEVYHODNUJE NON-VARIADIC FUNCTIONS oproti VARIADIC-FUNCTION.
	InternalPrintIntegerOrFloat3(ValueOrPointer,typename is_arithmetic<TType>::type(),typename is_integral<TType>::type());
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION TestIsIntegerTrait2().
void TestIsIntegerTrait3(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	// !!!!! CODE FNGUJE KOREKTNE.
	PrintIntegerOrFloat3(Value1);
	PrintIntegerOrFloat3(Value2);
	PrintIntegerOrFloat3(Value3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHasOperators(void)
{
	PrintLineSeparator();

	string														StringValue1="A";
	string														StringValue2="B";
	CClassWithCustomOperators									ClassWithCustomOperators1(100);
	CClassWithCustomOperators									ClassWithCustomOperators2(200);

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(int,int) [" << ((CHasOperators<int,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(int,double) [" << ((CHasOperators<int,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(double,double) [" << ((CHasOperators<double,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorPlus(string,int) [" << ((CHasOperators<string,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(string,string) [" << ((CHasOperators<string,string>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,CClassWithCustomOperators) [" << ((CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,int) [" << ((CHasOperators<CClassWithCustomOperators,int>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!! Vracia FALSE, pretoze je pretazeny iba OPERATOR (CClassWithCustomOperators+INT) a NIE (INT+CClassWithCustomOperators).
	wcout << L"HasOperatorPlus(int,CClassWithCustomOperators) [" << ((CHasOperators<int,CClassWithCustomOperators>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!!!! Vracia TRUE, pretoze C++ AUTOMATICKY KONVERTUJE DOUBLE na INT, aj ked pri pouziti hodi COMPILER WARNING.
	wcout << L"HasOperatorPlus(CClassWithCustomOperators,double) [" << ((CHasOperators<CClassWithCustomOperators,double>::IsOperatorPlusDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(int,int) [" << ((CHasOperators<int,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(int,double) [" << ((CHasOperators<int,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia TRUE.
	wcout << L"HasOperatorDivide(double,double) [" << ((CHasOperators<double,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(string,int) [" << ((CHasOperators<string,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(string,string) [" << ((CHasOperators<string,string>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,CClassWithCustomOperators) [" << ((CHasOperators<CClassWithCustomOperators,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,int) [" << ((CHasOperators<CClassWithCustomOperators,int>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(int,CClassWithCustomOperators) [" << ((CHasOperators<int,CClassWithCustomOperators>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Vracia FALSE.
	wcout << L"HasOperatorDivide(CClassWithCustomOperators,double) [" << ((CHasOperators<CClassWithCustomOperators,double>::IsOperatorDivideDefined==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits1(void)
{
	PrintLineSeparator();

	wcout << L"IS_CLASS<int> [" << is_class<int>::value << L"] !" << endl;
	wcout << L"IS_CLASS<wstring> [" << is_class<wstring>::value << L"] !" << endl;
	wcout << L"IS_CLASS<CType1> [" << is_class<CType1>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<int> [" << is_abstract<int>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<wstring> [" << is_abstract<wstring>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<CType1> [" << is_abstract<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DESTRUCTIBLE<CType1> [" << is_trivially_destructible<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DESTRUCTIBLE<CType2> [" << is_trivially_destructible<CType2>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType1> [" << is_trivially_default_constructible<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType2> [" << is_trivially_default_constructible<CType2>::value << L"] !" << endl;
	wcout << L"IS_FUNCTION<CType2> [" << is_function<CType2>::value << L"] !" << endl;
	wcout << L"IS_FUNCTION<decltype(TypeTraits1)> [" << is_function<decltype(TestTypeTraits1)>::value << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits2(void)
{
	PrintLineSeparator();

	using														XXX=int;
	typedef int													YYY;

	wcout << L"IS_SAME<int,int> [" << is_same<int,int>::value << L"] !" << endl;
	// Vrati FALSE.
	wcout << L"IS_SAME<int,const int> [" << is_same<int,const int>::value << L"] !" << endl;
	wcout << L"IS_SAME<int,double> [" << is_same<int,double>::value << L"] !" << endl;
	wcout << L"IS_SAME<int,XXX> [" << is_same<int,XXX>::value << L"] !" << endl;
	wcout << L"IS_SAME<int,YYY> [" << is_same<int,YYY>::value << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"IS_BASE_OF<CBase,CDerivedPublic> [" << is_base_of<CBase,CDerivedPublic>::value << L"] !" << endl;
	// !!! Vrati TRUE.
	wcout << L"IS_BASE_OF<CBase,CDerivedProtected> [" << is_base_of<CBase,CDerivedProtected>::value << L"] !" << endl;
	// !!! Vrati TRUE.
	wcout << L"IS_BASE_OF<CBase,CDerivedPrivate> [" << is_base_of<CBase,CDerivedPrivate>::value << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"IS_CONVERTIBLE<CDerivedPublic,CBase> [" << is_convertible<CDerivedPublic,CBase>::value << L"] !" << endl;
	// !!! Vrati TRUE.
	wcout << L"IS_CONVERTIBLE<CDerivedProtected,CBase> [" << is_convertible<CDerivedProtected,CBase>::value << L"] !" << endl;
	// !!! Vrati TRUE.
	wcout << L"IS_CONVERTIBLE<CDerivedPrivate,CBase> [" << is_convertible<CDerivedPrivate,CBase>::value << L"] !" << endl;
	// Vrati TRUE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int].
	wcout << L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,int> [" << is_constructible<CClassWithCustomOperators,int>::value << L"] !" << endl;
	// Vrati TRUE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int] a TYPE [double] je na TYPE KONVERTOVATELNY.
	wcout << L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,double> [" << is_constructible<CClassWithCustomOperators,double>::value << L"] !" << endl;
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA CONSTRUCTOR s PARAMETER TYPU [wstring] a ani NEEXISTUJE CONVERSION s TYPE [wstring] na TYPE [int].
	wcout << L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,wstring> [" << is_constructible<CClassWithCustomOperators,wstring>::value << L"] !" << endl;
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA DEFAULT CONSTRUCTOR.
	wcout << L"IS_CONSTRUCTIBLE<CClassWithCustomOperators> [" << is_constructible<CClassWithCustomOperators>::value << L"] !" << endl;
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA CONSTRUCTOR s 2 PARAMETERS.
	wcout << L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,int,int> [" << is_constructible<CClassWithCustomOperators,int,int>::value << L"] !" << endl;
	// !!! Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int] a TYPE [double] je na TYPE KONVERTOVATELNY, tak konverzia NIE JE POVAZOVANA za TRIVIALNU OPERACIU.
	wcout << L"IS_TRIVIALLY_CONSTRUCTIBLE<CClassWithCustomOperators,double> [" << is_trivially_constructible<CClassWithCustomOperators,double>::value << L"] !" << endl;
	// !!! Vrati TRUE, lebo aj ked CLASS 'CClassWithCustomOperators' NEMA OPERATOR=(int), tak ma NON-EXPLICIT CONSTRUCTOR s 1 PARAMETROM TYPU [int] a ten je na priradenie mozne vyuzit. Ak by vsak CONSTRUCTOR oznaceny ako EXPLICIT, vysledkom by bola VALUE FALSE.
	wcout << L"IS_ASSIGNABLE<CClassWithCustomOperators,int> [" << is_assignable<CClassWithCustomOperators,int>::value << L"] !" << endl;
	// !!! Vrati TRUE, lebo aj ked CLASS 'CClassWithCustomOperators' NEMA OPERATOR=(double), tak ma NON-EXPLICIT CONSTRUCTOR s 1 PARAMETROM TYPU [int] a ten je po konverzii z TYPE [double] na priradenie mozne vyuzit. Ak by vsak CONSTRUCTOR oznaceny ako EXPLICIT, vysledkom by bola VALUE FALSE.
	wcout << L"IS_ASSIGNABLE<CClassWithCustomOperators,double> [" << is_assignable<CClassWithCustomOperators,double>::value << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits3(void)
{
	PrintLineSeparator();

	wcout << L"REMOVE_CONST<int> [" << ConvertStringToWideString(typeid(remove_const<int>::type).name()) << L"] !" << endl;
	wcout << L"REMOVE_CONST<const int> [" << ConvertStringToWideString(typeid(remove_const<const int>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE 'CONST' MODIFIERS.
	wcout << L"ADD_CONST<int> [" << ConvertStringToWideString(typeid(add_const<int>::type).name()) << L"] !" << endl;
	wcout << L"MAKE_SIGNED<int> [" << ConvertStringToWideString(typeid(make_signed<int>::type).name()) << L"] !" << endl;
	wcout << L"MAKE_UNSIGNED<int> [" << ConvertStringToWideString(typeid(make_unsigned<int>::type).name()) << L"] !" << endl;
	wcout << L"MAKE_SIGNED<unsigned int> [" << ConvertStringToWideString(typeid(make_signed<unsigned int>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int&> [" << ConvertStringToWideString(typeid(remove_reference<int&>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int&&> [" << ConvertStringToWideString(typeid(remove_reference<int&&>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int> [" << ConvertStringToWideString(typeid(remove_reference<int>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"ADD_LVALUE_REFERENCE<int> [" << ConvertStringToWideString(typeid(add_lvalue_reference<int>::type).name()) << L"] !" << endl;
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"ADD_RVALUE_REFERENCE<int> [" << ConvertStringToWideString(typeid(add_rvalue_reference<int>::type).name()) << L"] !" << endl;
	wcout << L"ADD_POINTER<int> [" << ConvertStringToWideString(typeid(add_pointer<int>::type).name()) << L"] !" << endl;
	wcout << L"ADD_POINTER<int*> [" << ConvertStringToWideString(typeid(add_pointer<int*>::type).name()) << L"] !" << endl;
	wcout << L"REMOVE_POINTER<int*> [" << ConvertStringToWideString(typeid(remove_pointer<int*>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits4(void)
{
	PrintLineSeparator();

	wcout << L"RANK<int> [" << rank<int>::value << L"] !" << endl;
	wcout << L"RANK<int[]> [" << rank<int[]>::value << L"] !" << endl;
	wcout << L"RANK<int[5][5][5]> [" << rank<int[5][5][5]>::value << L"] !" << endl;
	wcout << L"RANK<int[2][3][5][2]> [" << rank<int[2][3][5][2]>::value << L"] !" << endl;
	wcout << L"EXTENT<int> [" << extent<int>::value << L"] !" << endl;
	wcout << L"EXTENT<int[]> [" << extent<int[]>::value << L"] !" << endl;
	wcout << L"EXTENT<int[5][4][3][2]> [" << extent<int[5][4][3][2]>::value << L"] !" << endl;
	wcout << L"EXTENT<int[15][14][13][12],2> [" << extent<int[15][14][13][12],2>::value << L"] !" << endl;
	wcout << L"EXTENT<int[15][14][13][12],7> [" << extent<int[15][14][13][12],7>::value << L"] !" << endl;
	wcout << L"REMOVE_EXTENT<int> [" << ConvertStringToWideString(typeid(remove_extent<int>::type).name()) << L"] !" << endl;
	wcout << L"REMOVE_EXTENT<int[10][20]> [" << ConvertStringToWideString(typeid(remove_extent<int[10][20]>::type).name()) << L"] !" << endl;
	wcout << L"REMOVE_ALL_EXTENTS<int> [" << ConvertStringToWideString(typeid(remove_all_extents<int>::type).name()) << L"] !" << endl;
	wcout << L"REMOVE_ALL_EXTENTS<int[10][20]> [" << ConvertStringToWideString(typeid(remove_all_extents<int[10][20]>::type).name()) << L"] !" << endl;
	wcout << L"UNDERLYING_TYPE<ESimpleEnum1> [" << ConvertStringToWideString(typeid(underlying_type<ESimpleEnum1>::type).name()) << L"] !" << endl;
	wcout << L"UNDERLYING_TYPE<ESimpleEnum2> [" << ConvertStringToWideString(typeid(underlying_type<ESimpleEnum2>::type).name()) << L"] !" << endl;
	wcout << L"UNDERLYING_TYPE<EClassEnum1> [" << ConvertStringToWideString(typeid(underlying_type<EClassEnum1>::type).name()) << L"] !" << endl;
	wcout << L"UNDERLYING_TYPE<EClassEnum2> [" << ConvertStringToWideString(typeid(underlying_type<EClassEnum2>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void MyFunction(void)
{
}
//-------------------------------------------------------------------------------------------------------
int MyFunction(int)
{
	return(0);
}
//-------------------------------------------------------------------------------------------------------
float MyFunction(double,int)
{
	return(float());
}
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits5(void)
{
	PrintLineSeparator();

	wcout << L"DECAY<int> [" << ConvertStringToWideString(typeid(decay<int>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int&> [" << ConvertStringToWideString(typeid(decay<int&>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int&&> [" << ConvertStringToWideString(typeid(decay<int&&>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int*> [" << ConvertStringToWideString(typeid(decay<int*>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int**> [" << ConvertStringToWideString(typeid(decay<int**>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int[10]> [" << ConvertStringToWideString(typeid(decay<int[10]>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int[10][20]> [" << ConvertStringToWideString(typeid(decay<int[10][20]>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<int (*)(int,double)> [" << ConvertStringToWideString(typeid(decay<int (*)(int,double)>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<const volatile int> [" << ConvertStringToWideString(typeid(decay<const volatile int>::type).name()) << L"] !" << endl;
	wcout << L"DECAY<const volatile unsigned int> [" << ConvertStringToWideString(typeid(decay<const volatile unsigned int>::type).name()) << L"] !" << endl;
	wcout << L"ENABLE_IF<true,int> [" << ConvertStringToWideString(typeid(enable_if<true,int>::type).name()) << L"] !" << endl;
	// !!! Ak je PODMIENKA FALSE, potom ALIAS 'type' NIE JE DEFINOVANY a COMPILER hodi ERROR.
	//wcout << L"ENABLE_IF<false,int> [" << ConvertStringToWideString(typeid(enable_if<false,int>::type).name()) << L"] !" << endl;
	wcout << L"CONDITIONAL<true,int,double> [" << ConvertStringToWideString(typeid(conditional<true,int,double>::type).name()) << L"] !" << endl;
	wcout << L"CONDITIONAL<false,int,double> [" << ConvertStringToWideString(typeid(conditional<false,int,double>::type).name()) << L"] !" << endl;
	wcout << L"COMMON_TYPE<int,double,bool> [" << ConvertStringToWideString(typeid(common_type<int,double,bool>::type).name()) << L"] !" << endl;
	// !!! Vracia COMPILATION ERROR, pretoze medzi TYPES NEEXISTUJE TYPE, na ktory by vsetky ostatne TYPES bolo mozne konvertovat.
	//wcout << L"COMMON_TYPE<int,double,bool,CType1> [" << ConvertStringToWideString(typeid(common_type<int,double,bool,CType1>::type).name()) << L"] !" << endl;
	// !!! Vracia COMPILATION ERROR, pretoze medzi TYPES NEEXISTUJE TYPE, na ktory by vsetky ostatne TYPES bolo mozne konvertovat.
	//wcout << L"COMMON_TYPE<ESimpleEnum1,ESimpleEnum2,EClassEnum1,EClassEnum2> [" << ConvertStringToWideString(typeid(common_type<ESimpleEnum1,ESimpleEnum2,EClassEnum1,EClassEnum2>::type).name()) << L"] !" << endl;
	wcout << L"COMMON_TYPE<ESimpleEnum1,ESimpleEnum2> [" << ConvertStringToWideString(typeid(common_type<ESimpleEnum1,ESimpleEnum2>::type).name()) << L"] !" << endl;

	PrintLineSeparator();

	using														Refrence1=void(&)(void);
	using														Pointer1=void(*)(void);
	using														Refrence2=int(&)(int);
	using														Pointer2=int(*)(int);
	using														Refrence3=float(&)(double,int);
	using														Pointer3=float(*)(double,int);
	using														Pointer4=int(CTypeWithOperatorsAndMethods::*)(int,float);

	wcout << L"RESULT_OF<Refrence1()> [" << ConvertStringToWideString(typeid(result_of<Refrence1()>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Pointer1()> [" << ConvertStringToWideString(typeid(result_of<Pointer1()>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Refrence2(int)> [" << ConvertStringToWideString(typeid(result_of<Refrence2(int)>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Pointer2(int)> [" << ConvertStringToWideString(typeid(result_of<Pointer2(int)>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Refrence3(double,int)> [" << ConvertStringToWideString(typeid(result_of<Refrence3(double,int)>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Pointer3(double,int)> [" << ConvertStringToWideString(typeid(result_of<Pointer3(double,int)>::type).name()) << L"] !" << endl;
	wcout << L"RESULT_OF<Pointer4(double,int)> [" << ConvertStringToWideString(typeid(result_of<Pointer4(CTypeWithOperatorsAndMethods*,int,float)>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeTraits6(void)
{
	PrintLineSeparator();

	// Pouzitie C++ OPERATOR.
	wcout << L"ALIGNOF<SFields> [" << alignof(SFields) << L"] !" << endl;
	wcout << L"ALIGNMENT_OF<SFields> [" << alignment_of<SFields>::value << L"] !" << endl;
	wcout << L"ALIGNMENT_OF<char> [" << alignment_of<char>::value << L"] !" << endl;
	wcout << L"ALIGNMENT_OF<short> [" << alignment_of<short>::value << L"] !" << endl;
	wcout << L"ALIGNMENT_OF<long double> [" << alignment_of<long double>::value << L"] !" << endl;
	wcout << L"ALIGNMENT_OF<CType1*> [" << alignment_of<CType1*>::value << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<1> [" << ConvertStringToWideString(typeid(aligned_storage<1>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<4> [" << ConvertStringToWideString(typeid(aligned_storage<4>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<8> [" << ConvertStringToWideString(typeid(aligned_storage<8>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<32> [" << ConvertStringToWideString(typeid(aligned_storage<32>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<100> [" << ConvertStringToWideString(typeid(aligned_storage<100>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<4,2> [" << ConvertStringToWideString(typeid(aligned_storage<4,2>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<8,2> [" << ConvertStringToWideString(typeid(aligned_storage<8,2>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_STORAGE<32,4> [" << ConvertStringToWideString(typeid(aligned_storage<32,4>::type).name()) << L"] !" << endl;
	wcout << L"ALIGNED_UNION<5,int,int,double> [" << ConvertStringToWideString(typeid(aligned_union<5,int,int,double>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void SomeFunction1(TType /*Value*/)
{
	wcout << L"FUNCTION 1 CALLED !" << endl;

	// !!!!! Hodi ERROR, pretoze CLASS [reference_wrapper<CTypeWithCopyConstructor>] NEMA METHOD CallMethod().
	//Value.CallMethod();
}
//-----------------------------------------------------------------------------
template<typename TType>
void SomeFunction2(TType Value)
{
	wcout << L"FUNCTION 2 CALLED !" << endl;

	((typename TType::type&) Value).CallMethod();
}
//-----------------------------------------------------------------------------
void TestReferenceWrapper1(void)
{
	PrintLineSeparator();

	CTypeWithCopyConstructor									Value;

	PrintLineSeparator();

	// VARIABLE 'Value' sa prenasa BY-VALUE a preto sa VOLA COPY-CONSTRUCTOR.
	SomeFunction1(Value);

	PrintLineSeparator();

	// !!! VARIABLE 'Value' sa prenasa BY-REFERENCE a preto sa NEVOLA COPY-CONSTRUCTOR.
	SomeFunction1(reference_wrapper<CTypeWithCopyConstructor>(Value));

	PrintLineSeparator();

	// !!!!! FUNCTION ref() vracia INSTANCIU CLASS [reference_wrapper<CTypeWithCopyConstructor>].
	SomeFunction1(ref(Value));

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze TYPE [CTypeWithCopyConstructor] NEMA ALIAS 'type'.
	SomeFunction2(Value);
	*/

	PrintLineSeparator();

	// !!! VARIABLE 'Value' sa prenasa BY-REFERENCE a preto sa NEVOLA COPY-CONSTRUCTOR.
	SomeFunction2(reference_wrapper<CTypeWithCopyConstructor>(Value));

	PrintLineSeparator();

	// !!!!! FUNCTION ref() vracia INSTANCIU CLASS [reference_wrapper<CTypeWithCopyConstructor>].
	SomeFunction2(ref(Value));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReferenceWrapper2(void)
{
	PrintLineSeparator();

	CDerivedClass1												Derived11;
	CDerivedClass1												Derived12;
	CDerivedClass2												Derived21;
	CDerivedClass2												Derived22;

	PrintLineSeparator();

	list<reference_wrapper<CBaseClass>>							List;

	// !!! Ukladaju sa REFERENCES, a preto sa NEVOLA COPY CONSTRUCTOR.
	List.push_back(Derived11);
	List.push_back(Derived12);
	List.push_back(Derived21);
	List.push_back(Derived22);

	for(CBaseClass& Object : List)
	{
		// Zavola sa METHOD DERIVED CLASS a NIE BASE CLASS.
		Object.VirtualMethod();
	}

	PrintLineSeparator();

	// !!! Kedze su ulozene REFERENCES, NEVOLA sa COPY CONSTRUCTOR.
	List.reverse();

	for(CBaseClass& Object : List)
	{
		// Zavola sa METHOD DERIVED CLASS a NIE BASE CLASS.
		Object.VirtualMethod();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int Add(int X, int Y)
{
	return(X+Y);
}
//-----------------------------------------------------------------------------
int Subtract(int X, int Y)
{
	return(X-Y);
}
//-----------------------------------------------------------------------------
int Multiple(int X, int Y)
{
	return(X*Y);
}
//-----------------------------------------------------------------------------
int Divide(int X, int Y)
{
	return(X/Y);
}
//-----------------------------------------------------------------------------
void TestFunctionWrapper(void)
{
	PrintLineSeparator();

	// FUNCTIONS je mozne vdaka CLASS [function<R(TArgs...)>] ukladat do COLLECTIONS.
	list<function<int(int,int)>>								Functions;

	Functions.push_back(Add);
	Functions.push_back(Subtract);
	Functions.push_back(Multiple);
	Functions.push_back(Divide);
	// CLASS [function<R(TArgs...)>] reprezentuje aj LAMBDA FUNCTIONS.
	Functions.push_back([](int X, int Y){return(Y-X);});
	// CLASS [function<R(TArgs...)>] reprezentuje FUNCTOR.
	Functions.push_back(CFunctor());

	for(function<int(int,int)>& Function : Functions)
	{
		wcout << L"FUNCTION(10,2) [" << Function(10,2) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMethodWrapper(void)
{
	PrintLineSeparator();

	CName														Name(L"Timmy",L"Anderson",12);

	// !!! CLASS [function<R(TArgs...)>] moze reprezentovat aj METHODS.
	// !!! 1. PARAMETER je skryty THIS POINTER reprezentujuci CLASS, v ktorej je METHOD definovana.
	function<void(CName&,wstring,wstring)>						Method=&CName::PrintName;

	Method(Name,L"This is",L"!\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestIsPointerTrait();
	//TestIsIntegerTrait1();
	//TestIsIntegerTrait2();
	//TestIsIntegerTrait3();
	//TestHasOperators();
	//TestTypeTraits1();
	//TestTypeTraits2();
	//TestTypeTraits3();
	//TestTypeTraits4();
	TestTypeTraits5();
	//TestTypeTraits6();
	//TestReferenceWrapper1();
	//TestReferenceWrapper2();
	//TestFunctionWrapper();
	//TestMethodWrapper();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------