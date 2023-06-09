//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <vector>
#include "MyDebug.h"
#include "CTypenameKeyword.h"
#include "CTypenameKeywordValue.h"
#include "CZeroInitialization.h"
#include "CThisKeywordInTemplateClassBase.h"
#include "CThisKeywordInTemplateClassDerived.h"
#include "CCArrayTemplateClass.h"
#include "CTemplateMethods.h"
#include "CTemplateMethodsFriends1.h"
#include "CTemplateMethodsFriends2.h"
#include "CTemplateMethodsSpecializations.h"
#include "CTemplateDefaultMethods.h"
#include "CTemplateDisambiguator.h"
#include "CTemplateTemplateParameterInnerClass1.h"
#include "CTemplateTemplateParameterInnerClass2.h"
#include "CTemplateTemplateParameterOuterClass1.h"
#include "CTemplateTemplateParameterOuterClass2.h"
#include "CTemplateVariablesDefinition.h"
#include "CTemplateVariablesCompilationUnit1.h"
#include "CTemplateVariablesCompilationUnit2.h"
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
void TemplateTypenameKeyword(const TType& Collection)
{
	// !!! Kedze IDENTIFIER 'TType::const_iterator' pouziva TEMPLATE PARAMETER 'TType' a zaroven definuje TYPE, je NUTNE pouzit KEYWORD [typename].
	typename TType::const_iterator								BeginIterator=Collection.cbegin();
	typename TType::const_iterator								EndIterator=Collection.cend();
	typename TType::const_iterator								CurrentIterator=BeginIterator;

	wstringstream												Stream;

	Stream << L"VALUES [";

	while(CurrentIterator!=EndIterator)
	{
		if (CurrentIterator!=BeginIterator)
		{
			Stream << L',';
		}

		Stream << (*CurrentIterator);

		++CurrentIterator;
	}

	Stream << L"] !";

	wcout << Stream.str() << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTypenameKeyword(void)
{
	PrintLineSeparator();

	{
		vector<wstring>											Values;

		Values.push_back(L"Timmy");
		Values.push_back(L"Jenny");
		Values.push_back(L"Josh");
		
		TemplateTypenameKeyword(Values);
	}

	PrintLineSeparator();

	{
		CTypenameKeywordValue									InternalValue(123);
		CTypenameKeyword<CTypenameKeywordValue>					Value(InternalValue);

		wcout << L"VALUE [" << Value.GetValue().GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void TemplateZeroInitialization(void)
{
	// !!! Rozlicne sposoby vykonania ZERO INITIALIZATION.
	TType														Value1=TType();
	TType														Value2{};

	wcout << L"VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Rozlicne sposoby vykonania ZERO INITIALIZATION.
template<typename TType>
void TemplateZeroInitializationDefaultParameters(TType Value1=TType(), TType Value2=TType{})
{
	wcout << L"VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestZeroInitialization(void)
{
	PrintLineSeparator();

	{
		TemplateZeroInitialization<int>();
	}

	PrintLineSeparator();

	{
		CZeroInitialization<int>								Object;

		wcout << L"OBJECT - VALUE 1 [" << Object.GetValue1() << L"] VALUE 2 [" << Object.GetValue2() << L"] VALUE 3 [" << Object.GetValue3() << L"] VALUE 4 [" << Object.GetValue4() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		TemplateZeroInitializationDefaultParameters<int>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestThisKeywordInTemplateClass(void)
{
	PrintLineSeparator();

	CThisKeywordInTemplateClassDerived<int>						Object;

	// !!!!! Volanie MEMBER z BASE CLASS v METHOD v DERIVED CLASS, ak BASE CLASS je TEMPLATE CLASS zavisla na TEMPLATE PARAMETER BASE CLASS, C++ NEPOUZIJE AUTOMATICKY pri volani takeho MEMBER SEMANTIKU [this->MEMBER] a hodi ERROR.
	Object.TestMethod();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION demonstruje ako zasielat C-ARRAYS pomocou REFERENCES. Zasielaju sa ARRAYS o znamej LENGTH.
template<typename TType, size_t SIZE>
void TemplateCArraysInTemplateFunctionsPrint(TType(&Array)[SIZE])
{
	wstringstream												Stream;

	Stream << L"ARRAY [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		const TType&											Value=Array[Index];

		if (Index>0)
		{
			Stream << L",";
		}

		Stream << Value;
	}

	Stream << L"] !";

	wcout << Stream.str() << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTION demonstruje ako zasielat C-ARRAYS pomocou REFERENCES. Zasielaju sa ARRAYS o znamej LENGTH.
template<typename TType, size_t SIZE1, size_t SIZE2>
int TemplateCArraysInTemplateFunctionsCompare(TType(&Array1)[SIZE1], TType(&Array2)[SIZE2])
{
	for(size_t Index=0;Index<SIZE1 && Index<SIZE2;Index++)
	{
		const TType&											Value1=Array1[Index];
		const TType&											Value2=Array2[Index];

		if (Value1<Value2)
		{
			return(-1);
		}
		else if (Value2<Value1)
		{
			return(1);
		}
	}

	if (SIZE1<SIZE2)
	{
		return(-1);
	}
	else if (SIZE2<SIZE1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCArraysInTemplateFunctions(void)
{
	PrintLineSeparator();

	{
		wchar_t													Array[]={L'T',L'i',L'm',L'm',L'y'};

		TemplateCArraysInTemplateFunctionsPrint(Array);
	}

	PrintLineSeparator();

	{
		wchar_t													Array1[]={L'T',L'i',L'm',L'm',L'y',L'1'};
		wchar_t													Array2[]={L'T',L'i',L'm',L'm',L'y',L'2'};
		int														Result1=TemplateCArraysInTemplateFunctionsCompare(Array1,Array2);
		int														Result2=TemplateCArraysInTemplateFunctionsCompare(Array2,Array1);

		wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;
		wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wchar_t													Array1[]={L'T',L'i',L'm',L'm',L'y'};
		wchar_t													Array2[]={L'T',L'i',L'm',L'm',L'y',L'!'};
		int														Result1=TemplateCArraysInTemplateFunctionsCompare(Array1,Array2);
		int														Result2=TemplateCArraysInTemplateFunctionsCompare(Array2,Array1);

		wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;
		wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wchar_t													Array1[]={L'T',L'i',L'm',L'm',L'y'};
		wchar_t													Array2[]={L'T',L'i',L'm',L'm',L'y'};
		int														Result=TemplateCArraysInTemplateFunctionsCompare(Array1,Array2);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CArraysInTemplateClassesByValueSizedArray(int Array1[10])
{
	// !!! Vola sa VERZIA [TType*], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-VALUE sa robi DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array1)>::Print();

	int															Array2[10];

	// !!! Vola sa VERZIA [TType[SIZE]], pretoze pre LOCAL VARIABLES TYPE C-ARRAY sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array2)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CArraysInTemplateClassesByValueUnsizedArray(int Array[])
{
	// !!! Vola sa VERZIA [TType*], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-VALUE sa robi DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array)>::Print();

	extern int													ExternArray[];

	// !!! Vola sa VERZIA [TType[]], pretoze pre LOCAL VARIABLES TYPE C-ARRAY sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(ExternArray)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CArraysInTemplateClassesByReferenceSizedArray(int(&Array1)[10])
{
	// !!! Vola sa VERZIA [TType[SIZE]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array1)>::Print();

	int															Array[10];
	int															(&Array2)[10]=Array;

	// !!! Vola sa VERZIA [TType[SIZE]], pretoze pre LOCAL VARIABLES TYPE REFERENCE na C-ARRAY sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array2)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void CArraysInTemplateClassesByReferenceUnsizedArray(int(&Array)[])
{
	// !!! Vola sa VERZIA [TType[]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Array)>::Print();

	int															(&ReferenceToArray)[]=Array;

	// !!! Vola sa VERZIA [TType[]], pretoze pre LOCAL VARIABLES TYPE REFERENCE na C-ARRAY sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(ReferenceToArray)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CArraysInTemplateClassesByValue(TType Value)
{
	// !!! Vola sa VERZIA [TType*], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-VALUE sa robi DECAY na POINTER.
	CCArrayTemplateClass<decltype(Value)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CArraysInTemplateClassesByLValueReference(TType& Value)
{
	// !!! Vola sa VERZIA [TType(&)[]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Value)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CArraysInTemplateClassesByRValueReference(TType&& Value)
{
	// !!! Vola sa VERZIA [TType(&)[]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
	CCArrayTemplateClass<decltype(Value)>::Print();
}
//----------------------------------------------------------------------------------------------------------------------
void TestCArraysInTemplateClasses(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa TEMPLATE CLASS, ktora NIE JE SPECIALIZED pre C-ARRAY.
		CCArrayTemplateClass<int>::Print();
	}

	PrintLineSeparator();

	{
		int														Array[10]={};

		CArraysInTemplateClassesByValueSizedArray(Array);
	}

	PrintLineSeparator();

	{
		int														Array[10]={};

		CArraysInTemplateClassesByValueUnsizedArray(Array);
	}

	PrintLineSeparator();

	{
		int														Array[10]={};

		CArraysInTemplateClassesByReferenceSizedArray(Array);
	}

	PrintLineSeparator();

	{
		int														Array[10]={};

		CArraysInTemplateClassesByReferenceUnsizedArray(Array);
	}

	PrintLineSeparator();

	{
		extern int												ExternArray[];

		// !!! Vola sa VERZIA [TType*], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-VALUE sa robi DECAY na POINTER.
		CArraysInTemplateClassesByValue(ExternArray);
	}

	PrintLineSeparator();

	{
		extern int												ExternArray[];

		// !!! Vola sa VERZIA [TType(&)[]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
		CArraysInTemplateClassesByLValueReference(ExternArray);
	}

	PrintLineSeparator();

	{
		extern int												ExternArray[];

		// !!! Vola sa VERZIA [TType(&)[]], pretoze pre FUNCTION PARAMETER TYPE C-ARRAY prenasany BY-REFERENCE sa NEROBI DECAY na POINTER.
		CArraysInTemplateClassesByRValueReference(ExternArray);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
int																ExternArray[]={1,2,3};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateMethods(void)
{
	PrintLineSeparator();

	{
		CTemplateMethods<double>								OriginalValue(11.22);
		CTemplateMethods<int>									ConvertedValue(10);

		wcout << L"ORIGINAL VALUE [" << OriginalValue.Get() << L"] !" << endl;
		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;

		ConvertedValue=OriginalValue;

		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateMethodsFriends1<double>						OriginalValue(11.22);
		CTemplateMethodsFriends1<int>							ConvertedValue(10);

		wcout << L"ORIGINAL VALUE [" << OriginalValue.Get() << L"] !" << endl;
		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;

		ConvertedValue=OriginalValue;

		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateMethodsFriends2<float,double>					OriginalValue(11.22f,33.44);
		CTemplateMethodsFriends2<int,long>						ConvertedValue(10,20);

		wcout << L"ORIGINAL - VALUE 1 [" << OriginalValue.Get1() << L"] VALUE 2 [" << OriginalValue.Get2() << L"] !" << endl;
		wcout << L"CONVERTED - VALUE 1 [" << ConvertedValue.Get1() << L"] VALUE 2 [" << ConvertedValue.Get2() << L"] !" << endl;

		ConvertedValue=OriginalValue;

		wcout << L"CONVERTED - VALUE 1 [" << ConvertedValue.Get1() << L"] VALUE 2 [" << ConvertedValue.Get2() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateMethodsSpecializations(void)
{
	PrintLineSeparator();

	{
		CTemplateMethodsSpecializations<int>					Object;

		// !!! Vola sa TEMPLATE METHOD.
		Object.NonTemplateMethod(100);

		// !!! Vola sa TEMPLATE METHOD.
		Object.TemplateMethod<double>(100,123.456);
	}

	PrintLineSeparator();

	{
		CTemplateMethodsSpecializations<double>					Object;

		// !!! Vola sa TEMPLATE CLASS SPECIALIZATION METHOD.
		Object.NonTemplateMethod(123.456);

		// !!! Vola sa TEMPLATE CLASS SPECIALIZATION METHOD.
		Object.TemplateMethod<double>(100,123.456);
	}

	PrintLineSeparator();

	{
		CTemplateMethodsSpecializations<double>					Object;

		// !!! Vola sa TEMPLATE CLASS SPECIALIZATION METHOD SPECIALIZATION.
		Object.TemplateMethod<long>(100,200);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateDefaultMethods(void)
{
	PrintLineSeparator();

	{
		CTemplateDefaultMethods<double>							OriginalValue(11.22);
		CTemplateDefaultMethods<int>							ConvertedValue(10);

		wcout << L"ORIGINAL VALUE [" << OriginalValue.Get() << L"] !" << endl;
		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;

		// !!!!! Vola sa USER DEFINED OPERATOR [OPERATOR=].
		ConvertedValue=OriginalValue;

		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CTemplateDefaultMethods<int>							OriginalValue(10);
		CTemplateDefaultMethods<int>							ConvertedValue(20);

		wcout << L"ORIGINAL VALUE [" << OriginalValue.Get() << L"] !" << endl;
		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;

		// !!!!! Vola sa DEFAULT OPERATOR [OPERATOR=], pretoze DEFAULT OPERATOR [OPERATOR=] sa generuje, aj napriek tomu, ze existuje TEMPLATE verzia OPERATOR [OPERATOR=].
		ConvertedValue=OriginalValue;

		wcout << L"CONVERTED VALUE [" << ConvertedValue.Get() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateTemplateDisambiguator(TType1 Value)
{
	CTemplateDisambiguator<TType1>								Object(Value);
	const CTemplateDisambiguator<TType1>*						PointerToObject=&Object;
	TType1														OriginalValue=Object.GetValue();

	// !!!!! G++ COMPILER hodi ERROR, pretoze EXPRESSION [Object] je DEPENDENT NAME, ktora nie je sucastou CURRENT INSTANTIATION, a NIE JE pouzity KEYWORD [template].
	//Object.ConvertValue<TType2>();

	// !!!!! Je NUTNE pouzit KEYWORD [.template].
	TType2														ConvertedValue1=Object.template ConvertValue<TType2>();

	// !!!!! Je NUTNE pouzit KEYWORD [->template].
	TType2														ConvertedValue2=PointerToObject->template ConvertValue<TType2>();

	wcout << L"ORIGINAL VALUE [" << OriginalValue << L"] !" << endl;
	wcout << L"CONVERTED VALUE 1 [" << ConvertedValue1 << L"] !" << endl;
	wcout << L"CONVERTED VALUE 2 [" << ConvertedValue2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateDisambiguator(void)
{
	PrintLineSeparator();

	TemplateTemplateDisambiguator<double,int>(11.22);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateLambdaFunctions(void)
{
	PrintLineSeparator();

	auto														Lambda=[]<typename TType>(const TType& Value1, const TType& Value2) -> int
	{
		if (Value1<Value2)
		{
			return(-1);
		}
		else if (Value1>Value2)
		{
			return(1);
		}
		else
		{
			return(0);
		}
	};

	{
		int															Value=Lambda(10,20);

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int															Value=Lambda(20,10);

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int															Value=Lambda(10.11,20.22);

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int															Value=Lambda(wstring(L"Timmy"),wstring(L"Anderson"));

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}


	/*
	PrintLineSeparator();
	 
	// !!!!! COMPILER hodi ERROR, pretoze TYPE [wchar[6]] sa NEROVNA TYPE [wchar[9]].
	{
		int															Value=Lambda(L"Timmy",L"Anderson");

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	*/

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR.
	{
		int															Value=Lambda(20,10);

		wcout << L"VALUE [" << Value << L"] !" << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateTemplateParameters(void)
{
	PrintLineSeparator();

	{
		// !!!!! Pouziva sa DEFAULT TEMPLATE TEMPLATE PARAMETER.
		CTemplateTemplateParameterOuterClass1<int,double>		Object(10,11.22);
		const CTemplateTemplateParameterInnerClass1<int,double>&	Value=Object.GetInnerObject();

		wcout << L"OBJECT - VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pouziva sa explicitne definovany TEMPLATE TEMPLATE PARAMETER.
		CTemplateTemplateParameterOuterClass1<int,double,CTemplateTemplateParameterInnerClass2>	Object(10,11.22);
		const CTemplateTemplateParameterInnerClass2<int,double>&	Value=Object.GetInnerObject();

		wcout << L"OBJECT - VALUE 1 [" << Value.GetValue1() << L"] VALUE 2 [" << Value.GetValue2() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Pouziva sa explicitne definovany TEMPLATE TEMPLATE PARAMETER.
		CTemplateTemplateParameterOuterClass2<int,double,CTemplateTemplateParameterInnerClass2>	Object(10,11.22);
		CTemplateTemplateParameterOuterClass2<short,int,CTemplateTemplateParameterInnerClass2>	ConvertedObject(0,0);

		// !!! Pouziva sa OPERATOR [OPERATOR=].
		ConvertedObject=Object;

		const CTemplateTemplateParameterInnerClass2<int,double>&	OriginalValue=Object.GetInnerObject();
		const CTemplateTemplateParameterInnerClass2<short,int>&	ConvertedValue=ConvertedObject.GetInnerObject();

		wcout << L"ORIGINAL OBJECT - VALUE 1 [" << OriginalValue.GetValue1() << L"] VALUE 2 [" << OriginalValue.GetValue2() << L"] !" << endl;
		wcout << L"CONVERTED OBJECT - VALUE 1 [" << ConvertedValue.GetValue1() << L"] VALUE 2 [" << ConvertedValue.GetValue2() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateVariables(void)
{
	PrintLineSeparator();

	{
		// !!!!! TEMPLATE VARIABLES s rovnakymi TEMPLATE ARGUMENTS su vytvorene IBA 1 vo VSETKYCH TRANSLATION UNITS.
		wcout << L"VALUE<int> [" << MyTemplateVariable<int> << L"] VALUE<double> [" << MyTemplateVariable<double> << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! Medzi CHARACTER '>' a CHARACTER '=' MUSI byt MEDZERA.
		MyTemplateVariable<int> =100;
		MyTemplateVariable<double> =123.456;

		wcout << L"VALUE<int> [" << MyTemplateVariable<int> << L"] VALUE<double> [" << MyTemplateVariable<double> << L"] !" << endl;

		PrintLineSeparator();

		CompilationUnit1SetValueInt(200);
		CompilationUnit1SetValueDouble(234.567);

		wcout << L"VALUE<int> [" << MyTemplateVariable<int> << L"] VALUE<double> [" << MyTemplateVariable<double> << L"] !" << endl;
		wcout << L"UNIT 1 - VALUE<int> [" << CompilationUnit1GetValueInt() << L"] VALUE<double> [" << CompilationUnit1GetValueDouble() << L"] !" << endl;

		PrintLineSeparator();

		CompilationUnit2SetValueInt(300);
		CompilationUnit2SetValueDouble(345.678);

		wcout << L"VALUE<int> [" << MyTemplateVariable<int> << L"] VALUE<double> [" << MyTemplateVariable<double> << L"] !" << endl;
		wcout << L"UNIT 2 - VALUE<int> [" << CompilationUnit2GetValueInt() << L"] VALUE<double> [" << CompilationUnit2GetValueDouble() << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		wcout << L"VALUE<int> [" << MyTemplateVariableDefault<int> << L"] VALUE<double> [" << MyTemplateVariableDefault<double> << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Pouzije sa DEFAULT TYPE.
		wcout << L"VALUE<> [" << MyTemplateVariableDefaultType<> << L"] VALUE<double> [" << MyTemplateVariableDefaultType<double> << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		const size_t											SIZE=5;

		MyTemplateVariableArray<int,SIZE>[0]=10;
		MyTemplateVariableArray<int,SIZE>[1]=20;
		MyTemplateVariableArray<int,SIZE>[2]=30;
		MyTemplateVariableArray<int,SIZE>[3]=40;
		MyTemplateVariableArray<int,SIZE>[4]=50;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"ARRAY[" << Index << L"] VALUE [" << MyTemplateVariableArray<int,SIZE>[Index] << L"] !" << endl;
		}
	}

	PrintLineSeparator();

	{
		// !!! Pristup ku CONSTANT definovanej ako FIELD.
		wcout << L"SIZE CONSTANT [" << CTemplateVariablesDefinition<int>::SIZE << L"] !" << endl;

		// !!! Pristup ku TEMPLATE VARIABLE, ktora referuje na FIELD.
		wcout << L"SIZE VARIABLE [" << Size<int> << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!! Pristup k VALUE pomocou TYPE TRAIT.
		wcout << L"IS INTEGRAL <int> TYPE TRAIT [" << is_integral<int>::value << L"] !" << endl;

		// !!! Pristup k VALUE pomocou TEMPLATE VARIABLE.
		wcout << L"IS INTEGRAL <int> VARIABLE [" << is_integral_v<int> << L"] !" << endl;

		// !!! Pristup k VALUE pomocou TEMPLATE VARIABLE.
		wcout << L"IS INTEGRAL <double> VARIABLE [" << is_integral_v<double> << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypenameKeyword();
	//TestZeroInitialization();
	//TestThisKeywordInTemplateClass();
	//TestCArraysInTemplateFunctions();
	//TestCArraysInTemplateClasses();
	//TestTemplateMethods();
	//TestTemplateMethodsSpecializations();
	//TestTemplateDefaultMethods();
	//TestTemplateDisambiguator();
	//TestTemplateLambdaFunctions();
	TestTemplateVariables();
	//TestTemplateTemplateParameters();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------