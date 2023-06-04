//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include <iomanip>
#include <climits>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26800 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxExplicitParameters(TType A, TType B)
{
	// !!! TEMPLATE vyzaduje, aby TYPE 'TType' mal definovany OPERATOR<.
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestExplicitTemplateParameters(void)
{
	PrintLineSeparator();

	// !!! TEMPLATE PARAMETERS su definovane EXPLICITNE.
	int															IntMax=MaxExplicitParameters<int>(20,10);
	double														DoubleMax=MaxExplicitParameters<double>(10.1,20.2);
	wstring														WStringMax=MaxExplicitParameters<wstring>(L"Timmy",L"Tim");

	wcout << L"INT MAX [" << IntMax << L"] !" << endl;
	wcout << L"DOUBLE MAX [" << DoubleMax << L"] !" << endl;
	wcout << L"WSTRING MAX [" << WStringMax << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxImplicitParameters(TType A, TType B)
{
	// !!! TEMPLATE vyzaduje, aby TYPE 'TType' mal definovany OPERATOR<.
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestImplicitTemplateParameters(void)
{
	PrintLineSeparator();

	// !!! TEMPLATE PARAMETERS su odvodene pomocou COMPILER.
	int															IntMax=MaxImplicitParameters(20,10);
	double														DoubleMax=MaxImplicitParameters(10.1,20.2);
	wstring														WStringMax=MaxImplicitParameters(wstring(L"Timmy"),wstring(L"Tim"));

	wcout << L"INT MAX [" << IntMax << L"] !" << endl;
	wcout << L"DOUBLE MAX [" << DoubleMax << L"] !" << endl;
	wcout << L"WSTRING MAX [" << WStringMax << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void NullCheck(TType* Pointer)
{
	if (Pointer==nullptr)
	{
		wcout << L"POINTER is NULL !" << endl;
	}
	else
	{
		wcout << L"POINTER is NOT NULL !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestVoidTemplateParameter(void)
{
	PrintLineSeparator();

	wstring														Value=L"Timmy";
	void*														Pointer=&Value;

	NullCheck<void>(Pointer);
	NullCheck<void>(nullptr);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// TENTO CODE NIE JE urceny na spustenie, pretoze UMYSELNE generuje COMPILE ERROR.
template<typename TType>
void GenerateCompilerErrors(TType Parameter)
{
	// !!!!! TENTO CODE generuje ERROR v 1. PHASE TWO-PHASE TRANSLATION, pretoze volanie METHOD NEPOUZIVA TEMPLATE PARAMETERS a COMIPLER moze uz v 1. PHASE skontrolovat, ze takato METHOD sa v CODE NENACHADZA.
	MyUndeclaredMethod();

	// !!!!! TENTO CODE generuje ERROR az v 2. PHASE TWO-PHASE TRANSLATION, pretoze volanie METHOD POUZIVA TEMPLATE PARAMETERS, a tym padom COMPILER moze vykonat kontrolu az po definovani TEMPLATE PARAMETERS.
	MyUndeclaredMethod(Parameter);

	// !!!!! TENTO CODE generuje ERROR v 1. PHASE TWO-PHASE TRANSLATION, pretoze volanie STATIC ASSERT NEPOUZIVA TEMPLATE PARAMETERS a COMIPLER moze uz v 1. PHASE skontrolovat, ze STATIC ASSERT sposobi COMPILE ERROR.
	static_assert(sizeof(int)>10,"TYPE 'INT' is too small !");

	// !!!!! TENTO CODE generuje ERROR az v 2. PHASE TWO-PHASE TRANSLATION, pretoze volanie STATIC ASSERT POUZIVA TEMPLATE PARAMETERS, a tym padom COMPILER moze vykonat kontrolu az po definovani TEMPLATE PARAMETERS.
	static_assert(sizeof(TType)>10,"TYPE 'TType' is too small !");
}
//----------------------------------------------------------------------------------------------------------------------
// TENTO CODE NIE JE urceny na spustenie, pretoze UMYSELNE generuje COMPILE ERROR.
void TestUsingGenerateCompilerErrors(void)
{
	PrintLineSeparator();

	GenerateCompilerErrors<double>(10.5);

	PrintLineSeparator();
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTypeDeduction(const TType& A, const TType& B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeDeduction(void)
{
	PrintLineSeparator();

	// !!! Vykona spravnu DEDUCTION, aj ked TYPE [TType] je iba PARTIAL TYPE celkoveho TYPE [const TType&].
	int															IntMax=MaxTypeDeduction(10,20);

	wcout << L"INT MAX [" << IntMax << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTypeDeductionConversions(TType A, TType B)
{
	// !!! TEMPLATE vyzaduje, aby TYPE 'TType' mal definovany OPERATOR<.
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeDeductionConversions(void)
{
	PrintLineSeparator();

	const int													CONSTANT=20;

	{
		// !!! TYPE 'TType' je DEDUCED ako TYPE [int].
		int														Result=MaxTypeDeductionConversions(10,CONSTANT);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	{
		// !!! TYPE 'TType' je DEDUCED ako TYPE [int].
		int														Result=MaxTypeDeductionConversions(CONSTANT,CONSTANT);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	{
		int														IntValue1=10;
		int														IntValue2=20;
		int&													IntValue2Reference=IntValue2;

		// !!! TYPE 'TType' je DEDUCED ako TYPE [int].
		int														Result=MaxTypeDeductionConversions(IntValue1,IntValue2Reference);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	{
		int														IntArray1[4]={1,2,3,4};
		int														IntArray2[4]={5,6,7,8};
		int*													PointerToIntArray2=IntArray2;

		// !!! TYPE 'TType' je DEDUCED ako TYPE [int*].
		int*													Result=MaxTypeDeductionConversions(IntArray1,PointerToIntArray2);

		wcout << L"RESULT [" << Result << L"] PARAMETER 1 [" << IntArray1 << L"] PARAMETER 2 [" << PointerToIntArray2 << L"] !" << endl;
	}

	/*
	{
		// !!!!! COMPILER hodi ERROR.
		double													Result=MaxTypeDeductionConversions(10,20.2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	/*
	{
		wstring													Parameter1=L"Timmy";
		wchar_t													Parameter2[]=L"Anderson";

		// !!!!! COMPILER hodi ERROR.
		double													Result=MaxTypeDeductionConversions(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TypeDeductionDefault1(TType Parameter=L"EMPTY")
{
	wcout << L"TypeDeductionDefault1 - PARAMETER [" << Parameter << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Definuje sa DEFAULT TEMPLATE TYPE PARAMETER.
template<typename TType=wstring>
void TypeDeductionDefault2(TType Parameter=wstring(L"EMPTY"))
{
	wcout << L"TypeDeductionDefault2 - PARAMETER [" << Parameter << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypeDeductionDefault(void)
{
	PrintLineSeparator();

	/*
	{
		// !!!!! COMPILER hodi ERROR.
		TypeDeductionDefault1();
	}
	*/

#ifndef _MSC_VER
	{
		// !!!!! G++ funguje spravne, kym VC++ hodi COMPILER ERROR. Je to ERROR vo VC++.
		TypeDeductionDefault2();
	}
#endif

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 MaxMultipleTemplateParameters(TType1 A, TType2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleTemplateParameters(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=20;
		double													Parameter2=10.2;

		// !!! RETURN TYPE je TYPE [int].
		int														Result=MaxMultipleTemplateParameters(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	{
		double													Parameter1=20.2;
		int														Parameter2=10;

		// !!! RETURN TYPE je TYPE [double].
		double													Result=MaxMultipleTemplateParameters(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TParameter1, typename TParameter2, typename TReturnValue>
TReturnValue MaxExplicitParametersAndReturnValueType1(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename TParameter1, typename TParameter2>
TReturnValue MaxExplicitParametersAndReturnValueType2(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestExplicitParametersAndReturnValueType(void)
{
	PrintLineSeparator();

	/*
	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!!!! COMPILER hodi ERROR, pretoze pre RETURN TYPE sa NEVYKONAVA TYPE DEDUCTION.
		double													Result=MaxExplicitParametersAndReturnValueType1(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}
	*/

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN TYPE je TYPE [double].
		// !!!!! FUNCTION MUSI mat definovane VSETKY TEMPLATE PARAMETERS, pretoze posledny TEMPLATE PARAMETER, ktory NEMOZE byt DEDUCED je zaroven POSLEDNY TEMPLATE PARAMETER. Takze je treba zadat vsetky 3 TEMPLATE PARAMETERS.
		double													Result=MaxExplicitParametersAndReturnValueType1<int,double,double>(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN TYPE je TYPE [double].
		// !!!!! FUNCTION MUSI mat definovany IBA 1. TEMPLATE PARAMETERS, pretoze iba 1. TEMPLATE PARAMETER NEMOZE byt DEDUCED.
		double													Result=MaxExplicitParametersAndReturnValueType2<double>(Parameter1,Parameter2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TParameter1, typename TParameter2>
auto MaxDeducedReturnValueTypeCPP11(TParameter1 A, TParameter2 B) -> decltype(true ? A : B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Spravi sa TYPE DECAY, aby bolo mozne pouzit ako PARAMETERS aj REFERENCES.
template<typename TParameter1, typename TParameter2>
auto MaxDeducedReturnValueTypeCPP11Decay(TParameter1 A, TParameter2 B) -> typename decay<decltype(true? A : B)>::type
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER NEHODI ERROR, lebo v CODE sa vyskutuje iba 1 vyskyt SYNTAX [return(EXPRESSION)].
template<typename TParameter1, typename TParameter2>
auto MaxDeducedReturnValueTypeCPP14OK(TParameter1 A, TParameter2 B)
{
	return((A<B) ? B : A);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze CODE TEMPLATE FUNCTION obsahuje 2 vyskyty SYNTAX [return(EXPRESSION)], kde kazda EXPRESSION 'EXPRESSION' vracia INY TYPE.
template<typename TParameter1, typename TParameter2>
auto MaxDeducedReturnValueTypeCPP14Error(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestDeducedReturnValueType(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		const type_info&										ReturnValueType=typeid(MaxDeducedReturnValueTypeCPP11(Parameter1,Parameter2));
		double													Result=MaxDeducedReturnValueTypeCPP11(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	/*
	{
		int														Parameter1=10;
		int														Parameter2=20;
		const int&												ReferenceToParameter2=Parameter2;

		const type_info&										ReturnValueType=typeid(MaxDeducedReturnValueTypeCPP11(Parameter1,ReferenceToParameter2));

		// !!!!! COMPILER HODI WARNING, lebo sa nespravil TYPE DECAY. Ked sa nespravi TYPE DECAY, tak pri pouziti PARAMETER [int] a PARAMETER [const int&] C++ COMPILER urci pomocou DEDUCTION RETURN VALUE TYPE ako TYPE [const int&]. No a to znamena, ze FUNCTION vracia REFERENCE na LOCAL VARIABLE co je samozrejme ERROR.
		double													Result=MaxDeducedReturnValueTypeCPP11(Parameter1,ReferenceToParameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}
	*/

	{
		int														Parameter1=10;
		int														Parameter2=20;
		const int&												ReferenceToParameter2=Parameter2;

		const type_info&										ReturnValueType=typeid(MaxDeducedReturnValueTypeCPP11Decay(Parameter1,ReferenceToParameter2));

		// !!! RETURN VALUE TYPE je [int].
		int														Result=MaxDeducedReturnValueTypeCPP11Decay(Parameter1,ReferenceToParameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxDeducedReturnValueTypeCPP14OK(Parameter1,Parameter2));
		double													Result=MaxDeducedReturnValueTypeCPP14OK(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	/*
	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION obsahuje 2 vyskyty SYNTAX [return(EXPRESSION)], kde kazda EXPRESSION 'EXPRESSION' vracia INY TYPE.
		const type_info&										ReturnValueType=typeid(MaxDeducedReturnValueTypeCPP14Error(Parameter1,Parameter2));
		double													Result=MaxDeducedReturnValueTypeCPP14Error(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TParameter1, typename TParameter2>
common_type<TParameter1,TParameter2>::type MaxCommonReturnValueTypeCPP11(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TParameter1, typename TParameter2>
common_type_t<TParameter1,TParameter2> MaxCommonReturnValueTypeCPP14(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCommonReturnValueType(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxCommonReturnValueTypeCPP11(Parameter1,Parameter2));
		double													Result=MaxCommonReturnValueTypeCPP11(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxCommonReturnValueTypeCPP14(Parameter1,Parameter2));
		double													Result=MaxCommonReturnValueTypeCPP14(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFAULT TEMPLATE PARAMETER sa moze referovat na TEMPLATE PARAMETERS definovane skor nez TEMPLATE PARAMETER na ktory je aplikovana DEFAULT VALUE. To znamena, ze TEMPLATE PARAMETER 'TReturnValue' sa pri definicii DEFAULT TEMPLATE VALUE moze referovat na TEMPLATE PARAMETER 'TParameter1' a TEMPLATE PARAMETER 'TParameter2'.
// !!!!! Kedze DEFAULT TEMPLATE PARAMETER sa DEFINUJE este pred definiciu TEMPLATE FUNCTION PROTOTYPE, NIE JE mozne pouzit FUNCTION PARAMETER 'A' a FUNCTION PARAMETER 'B' pri definicii DEFAULT TEMPLATE PARAMETER.
// !!!!! TEMPLATE FUNCTION vyzaduje, aby TYPE 'TParameter1' a TYPE 'TParameter2' mali DEFAULT CONSTRUCTOR.
template<typename TParameter1, typename TParameter2, typename TReturnValue=decay_t<decltype(true ? TParameter1() : TParameter2())>>
TReturnValue MaxDefaultTemplateValue1(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFAULT TEMPLATE PARAMETER sa moze referovat na TEMPLATE PARAMETERS definovane skor nez TEMPLATE PARAMETER na ktory je aplikovana DEFAULT VALUE. To znamena, ze TEMPLATE PARAMETER 'TReturnValue' sa pri definicii DEFAULT TEMPLATE VALUE moze referovat na TEMPLATE PARAMETER 'TParameter1' a TEMPLATE PARAMETER 'TParameter2'.
// !!!!! Kedze DEFAULT TEMPLATE PARAMETER sa DEFINUJE este pred definiciu TEMPLATE FUNCTION PROTOTYPE, NIE JE mozne pouzit FUNCTION PARAMETER 'A' a FUNCTION PARAMETER 'B' pri definicii DEFAULT TEMPLATE PARAMETER.
template<typename TParameter1, typename TParameter2, typename TReturnValue=common_type_t<TParameter1,TParameter2>>
TReturnValue MaxDefaultTemplateValue2(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFAULT TEMPLATE PARAMETER sa moze referovat na TEMPLATE PARAMETERS definovane skor nez TEMPLATE PARAMETER na ktory je aplikovana DEFAULT VALUE. To znamena, ze TEMPLATE PARAMETER 'TReturnValue' sa pri definicii DEFAULT TEMPLATE VALUE moze referovat na TEMPLATE PARAMETER 'TParameter1' a TEMPLATE PARAMETER 'TParameter2'.
template<typename TReturnValue=int, typename TParameter1, typename TParameter2>
TReturnValue MaxDefaultTemplateValue3(TParameter1 A, TParameter2 B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestDefaultTemplateParameters(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue1(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue1(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [int].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue1<int,double,int>(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue1<int,double,int>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue2(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue2(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!! RETURN VALUE TYPE je [int].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue2<int,double,int>(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue2<int,double,int>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!!!! TYPE DEDUCTION vykona DEDUCTION TEMPLATE PARAMETER 'TParameter1' a TEMPLATE PARAMETER 'TParameter2' a pre TEMPLATE PARAMETER 'TReturnValue' pouzije DEFAULT VALUE.
		// !!! RETURN VALUE TYPE je [int].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue3(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue3(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		// !!!!! TYPE DEDUCTION vykona DEDUCTION TEMPLATE PARAMETER 'TParameter1' a TEMPLATE PARAMETER 'TParameter2' a pre TEMPLATE PARAMETER 'TReturnValue' sa pouzije explicitne definovany TYPE.
		// !!! RETURN VALUE TYPE je [double].
		const type_info&										ReturnValueType=typeid(MaxDefaultTemplateValue3<double>(Parameter1,Parameter2));
		double													Result=MaxDefaultTemplateValue3<double>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int MaxTemplateFunctionsOverloading1(int A, int B)
{
	wcout << L"NON-TEMPLATE FUNCTION CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTemplateFunctionsOverloading1(TType A, TType B)
{
	wcout << L"TEMPLATE FUNCTION CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsOverloading1(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		int														Parameter2=20;

		// !!!!! Zavola sa NON-TEMPLATE FUNCTION.
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1(Parameter1,Parameter2));
		int														Result=MaxTemplateFunctionsOverloading1(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		double													Parameter1=10.1;
		double													Parameter2=20.2;

		// !!!!! Zavola sa TEMPLATE FUNCTION.
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1(Parameter1,Parameter2));
		double													Result=MaxTemplateFunctionsOverloading1(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		char													Parameter1='A';
		char													Parameter2='B';

		// !!!!! Zavola sa TEMPLATE FUNCTION.
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1(Parameter1,Parameter2));
		char													Result=MaxTemplateFunctionsOverloading1(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << ConvertCharToWideChar(Result) << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Parameter1=10;
		int														Parameter2=20;

		// !!!!! Zavola sa TEMPLATE FUNCTION, lebo sa EXPLICITNE pouzila SYNTAX [<>].
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1<>(Parameter1,Parameter2));
		int														Result=MaxTemplateFunctionsOverloading1<>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		double													Parameter1=10.1;
		double													Parameter2=20.2;

		// !!!!! Zavola sa NON-TEMPLATE FUNCTION
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1<double>(Parameter1,Parameter2));
		double													Result=MaxTemplateFunctionsOverloading1<double>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		char													Parameter1='A';
		double													Parameter2=20.2;

		// !!!!! Zavola sa NON-TEMPLATE FUNCTION, pretoze PARAMETERS su ROZDIELNE, a tak NIE JE MOZNE pouzit TEMPLATE FUNCTION, ktora predpoklada ROVNAKE TEMPLATE PARAMETER TYPES. No kedze pri NON-TEMPLATE OVERLOADING sa vykonavaju AUTOMATIC TYPE CONVERSIONS, tak sa pouzije NON-TEMPLATE FUNCTION.
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading1(Parameter1,Parameter2));
		int														Result=MaxTemplateFunctionsOverloading1(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TParameter1, typename TParameter2>
auto MaxTemplateFunctionsOverloading2(TParameter1 A, TParameter2 B)
{
	wcout << L"TEMPLATE FUNCTION CALLED with 2 TEMPLATE PARAMETERS !" << endl;

	// !!!!! Musi mat IBA 1 KEYWORD [return].
	return((A<B) ? B : A);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnType, typename TParameter1, typename TParameter2>
TReturnType MaxTemplateFunctionsOverloading2(TParameter1 A, TParameter2 B)
{
	wcout << L"TEMPLATE FUNCTION CALLED with 3 TEMPLATE PARAMETERS !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsOverloading2(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading2(Parameter1,Parameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION s 2 TEMPLATE PARAMETERS.
		// !!! RETURN VALUE TYPE je [double].
		double													Result=MaxTemplateFunctionsOverloading2(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading2<long double>(Parameter1,Parameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION s 3 TEMPLATE PARAMETERS.
		// !!! RETURN VALUE TYPE je [long double].
		long double												Result=MaxTemplateFunctionsOverloading2<long double>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading2<long double,int,double>(Parameter1,Parameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION s 3 TEMPLATE PARAMETERS.
		// !!! RETURN VALUE TYPE je [long double].
		long double												Result=MaxTemplateFunctionsOverloading2<long double,int,double>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	{
		int														Parameter1=10;
		double													Parameter2=20.2;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading2<int>(Parameter1,Parameter2));

		// !!!!! COMPILER HODI ERROR, pretoze TYPE PARAMETERS [int,int,double] vyhovuje TEMPLATE s 2 i 3 PARAMETERS. Je to preto, lebo 1. a 2. PARAMETER maju rovnaky TYPE. Ak by NEBOLI ROVNAKE, tak by sa musela pouzit verzia TEMPLATE FUNCTION s 3 TEMPLATE PARAMETERS.
		int														Result=MaxTemplateFunctionsOverloading2<int>(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTemplateFunctionsOverloading3(TType A, TType B)
{
	wcout << L"TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading3(TType A, TType B)] CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType* MaxTemplateFunctionsOverloading3(TType* A, TType* B)
{
	wcout << L"TEMPLATE FUNCTION [TType* MaxTemplateFunctionsOverloading3(TType* A, TType* B)] CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
const wchar_t* MaxTemplateFunctionsOverloading3(const wchar_t* A, const wchar_t* B)
{
	wcout << L"NON-TEMPLATE FUNCTION [const wchar_t* MaxTemplateFunctionsOverloading3(const wchar_t* A, const wchar_t* B)] CALLED !" << endl;

	if (wcscmp(A,B)<0)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsOverloading3(void)
{
	PrintLineSeparator();

	{
		int														Parameter1=10;
		int														Parameter2=20;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading3(Parameter1,Parameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading3(TType A, TType B)].
		// !!! RETURN VALUE TYPE je [int].
		int														Result=MaxTemplateFunctionsOverloading3(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wstring													Parameter1=L"Timmy";
		wstring													Parameter2=L"Anderson";

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading3(Parameter1,Parameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading3(TType A, TType B)].
		// !!! RETURN VALUE TYPE je [wstring].
		wstring													Result=MaxTemplateFunctionsOverloading3(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Parameter1=10;
		int														Parameter2=20;
		int*													PointerToParameter1=&Parameter1;
		int*													PointerToParameter2=&Parameter2;

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading3(PointerToParameter1,PointerToParameter2));

		// !!!!! Zavola sa TEMPLATE FUNCTION [TType* MaxTemplateFunctionsOverloading3(TType* A, TType* B)].
		// !!! RETURN VALUE TYPE je [int*].
		int*													Result=MaxTemplateFunctionsOverloading3(PointerToParameter1,PointerToParameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] PARAMETER 1 [" << PointerToParameter1 << L"] PARAMETER 2 [" << PointerToParameter2 << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		const wchar_t*											Parameter1=L"Timmy";
		const wchar_t*											Parameter2=L"Anderson";

		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading3(Parameter1,Parameter2));

		// !!!!! Zavola sa NON-TEMPLATE FUNCTION [const wchar_t* MaxTemplateFunctionsOverloading3(const wchar_t* A, const wchar_t* B)].
		// !!! RETURN VALUE TYPE je [const wchar_t*].
		const wchar_t*											Result=MaxTemplateFunctionsOverloading3(Parameter1,Parameter2);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B)
{
	wcout << L"TEMPLATE FUNCTION [const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B)] CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
const wchar_t* MaxTemplateFunctionsOverloading4(const wchar_t* A, const wchar_t* B)
{
	wcout << L"NON-TEMPLATE FUNCTION [const wchar_t* MaxTemplateFunctionsOverloading4(const wchar_t* A, const wchar_t* B)] CALLED !" << endl;

	if (wcscmp(A,B)<0)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B, const TType& C)
{
	wcout << L"TEMPLATE FUNCTION [const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B, const TType& C)] CALLED !" << endl;

	return(MaxTemplateFunctionsOverloading4(MaxTemplateFunctionsOverloading4(A,B),C));
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsOverloading4(void)
{
	PrintLineSeparator();

	{
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading4(100,200,300));

		// !!!!! Zavola sa TEMPLATE FUNCTION [const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B, const TType& C)].
		// !!! RETURN VALUE TYPE je [int].
		int														Result=MaxTemplateFunctionsOverloading4(100,200,300);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	// !!!!! CODE hodi RUNTIME ERROR.
	{
		const wchar_t*											Parameter1=L"Timmy";
		const wchar_t*											Parameter2=L"Atreyu";
		const wchar_t*											Parameter3=L"Jenny";
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading4(Parameter1,Parameter2,Parameter3));

		// !!!!! Zavola sa TEMPLATE FUNCTION [const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B, const TType& C)].
		// !!!!! CODE hodi RUNTIME ERROR.
		// !!!!! K RUNTIME ERROR dochadza preto, lebo sa vo FUNCTION [const TType& MaxTemplateFunctionsOverloading4(const TType& A, const TType& B, const TType& C)] vytvori TEMPORARY VARIABLE a FUNCTION vrati REFERENCE na tuto TEMPORARY VARIABLE, ktora po skonceni volania FUNCTION skonci svoju platnost.
		// !!!!! PARAMETERS sa prenasaju ako TYPE [const wchar_t * const &].
		// !!! RETURN VALUE TYPE je [const wchar_t*].
		const wchar_t*											Result=MaxTemplateFunctionsOverloading4(Parameter1,Parameter2,Parameter3);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTemplateFunctionsOverloading5(TType A, TType B)
{
	wcout << L"TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading5(TType A, TType B)] CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType MaxTemplateFunctionsOverloading5(TType A, TType B, TType C)
{
	wcout << L"TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading5(TType A, TType B, TType C)] CALLED !" << endl;

	// !!!!! Pre TYPE 'int' sa nepouzije NON-TEMPLATE VERSION, pretoze je definovana AZ PO DEFINICII tejto TEMPLATE.
	return(MaxTemplateFunctionsOverloading5(MaxTemplateFunctionsOverloading5(A,B),C));
}
//----------------------------------------------------------------------------------------------------------------------
int MaxTemplateFunctionsOverloading5(int A, int B)
{
	wcout << L"NON-TEMPLATE FUNCTION [int MaxTemplateFunctionsOverloading5(int A, int B)] CALLED !" << endl;

	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsOverloading5(void)
{
	PrintLineSeparator();

	{
		const type_info&										ReturnValueType=typeid(MaxTemplateFunctionsOverloading5(100,200,300));

		// !!!!! Zavola sa TEMPLATE FUNCTION [TType MaxTemplateFunctionsOverloading5(TType A, TType B, TType C)].
		// !!! RETURN VALUE TYPE je [int].
		int														Result=MaxTemplateFunctionsOverloading5(100,200,300);

		wcout << L"TYPE [" << GetTypeInfoName(ReturnValueType) << L"] RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION je oznacena pomocou KEYWORD [constexpr].
template<typename TType>
constexpr TType MaxTemplateFunctionsConstxpr(TType A, TType B)
{
	if (A<B)
	{
		return(B);
	}
	else
	{
		return(A);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionsConstxpr(void)
{
	PrintLineSeparator();

	// !!!!! Kedze TEMPLATE FUNCTION je oznacena KEYWORD [constexpr], je ju mozne pouzit napriklad pri definicii velkosti ARRAYS.
	int															Array[MaxTemplateFunctionsConstxpr(10,20)];

	wcout << L"NUMBER of ARRAY ITEMS [" << (sizeof(Array)/sizeof(Array[0])) << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestExplicitTemplateParameters();
	//TestImplicitTemplateParameters();
	//TestVoidTemplateParameter();
	//TestTypeDeduction();
	//TestTypeDeductionConversions();
	//TestTypeDeductionDefault();
	//TestMultipleTemplateParameters();
	//TestExplicitParametersAndReturnValueType();
	//TestDeducedReturnValueType();
	//TestCommonReturnValueType();
	//TestDefaultTemplateParameters();
	//TestTemplateFunctionsOverloading1();
	//TestTemplateFunctionsOverloading2();
	//TestTemplateFunctionsOverloading3();
	//TestTemplateFunctionsOverloading4();
	//TestTemplateFunctionsOverloading5();
	TestTemplateFunctionsConstxpr();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------