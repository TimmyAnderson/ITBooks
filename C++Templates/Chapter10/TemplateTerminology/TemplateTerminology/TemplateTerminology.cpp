//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include "MyDebug.h"
#include "CTemplateSpecializations.h"
#include "CDeclarationsVsDefinitions.h"
#include "CCompleteVsIncompleteTypes.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
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
void TemplateTemplateInstantiation(TType Parameter)
{
	wcout << L"TYPE [" << GetTypeInfoName<TType>() << L"] VALUE [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateInstantiation(void)
{
	PrintLineSeparator();

	{
		// !!! IMPLICIT INSTANTIATION.
		TemplateTemplateInstantiation(123.456);
	}

	PrintLineSeparator();

	{
		// !!! EXPLICIT INSTANTIATION.
		TemplateTemplateInstantiation<int>(10);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE je PRIMARY TEMPLATE z ktorej su vytvorene SPECIALIZATIONS.
template<typename TType1, typename TType2>
void TemplateTemplateSpecializations(TType1 Parameter1, TType2 Parameter2)
{
	wcout << L"PRIMARY TEMPLATE - TYPE 1 [" << GetTypeInfoName<TType1>() << L"] TYPE 2 [" << GetTypeInfoName<TType2>() << L"] VALUE 1 [" << Parameter1 << L"] VALUE 2 [" << Parameter2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE je FULL TEMPLATE SPECIALIZATION.
template<>
void TemplateTemplateSpecializations<int,int>(int Parameter1, int Parameter2)
{
	wcout << L"FULL TEMPLATE SPECIALIZATION - VALUE 1 [" << Parameter1 << L"] VALUE 2 [" << Parameter2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateSpecializations(void)
{
	PrintLineSeparator();

	{
		// !!! Pouzije sa PRIMARY TEMPLATE.
		double													Parameter1=123.456;
		double													Parameter2=456.789;

		TemplateTemplateSpecializations(Parameter1,Parameter2);
	}

	PrintLineSeparator();

	{
		// !!! Pouzije sa FULL TEMPLATE SPECIALIZATION.
		int														Parameter1=100;
		int														Parameter2=200;

		TemplateTemplateSpecializations(Parameter1,Parameter2);
	}

	PrintLineSeparator();

	{
		CTemplateSpecializations<double,double>					Object(123.456,456.789);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CTemplateSpecializations<double,int>					Object(123.456,100);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CTemplateSpecializations<int,int>						Object(100,200);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDeclarationsVsDefinitions(void)
{
	PrintLineSeparator();

	{
		wcout << L"VARIABLE - VALUE [" << DeclarationsVsDefinitionsVariable << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"TEMPLATE VARIABLE - VALUE [" << DeclarationsVsDefinitionsVariableTemplate<int> << L"]." << endl;
	}

	PrintLineSeparator();

	{
		DeclarationsVsDefinitionsPrint(100);
	}

	PrintLineSeparator();

	{
		DeclarationsVsDefinitionsPrintTemplate(123.456);
	}

	PrintLineSeparator();

	{
		CDeclarationsVsDefinitions								Object(100);

		Object.Print();
	}

	PrintLineSeparator();

	{
		CDeclarationsVsDefinitionsTemplate<double>				Object(123.456);

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCompleteVsIncompleteTypes(void)
{
	PrintLineSeparator();

	{
		size_t													ArraySize=MY_ARRAY_SIZE;

		for(size_t Index=0;Index<ArraySize;Index++)
		{
			int													ArrayItem=MyArray[Index];

			wcout << L"ITEM [" << ArrayItem << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		size_t													ArraySize=size(ArrayToCompleteVsIncompleteTypes);

		for(size_t Index=0;Index<ArraySize;Index++)
		{
			const CCompleteVsIncompleteTypes&					ArrayItem=ArrayToCompleteVsIncompleteTypes[Index];

			ArrayItem.Print();
		}
	}

	PrintLineSeparator();

	{
		CCompleteVsIncompleteTypes								Object(100);
		
		PointerToCompleteVsIncompleteTypes=&Object;

		PointerToCompleteVsIncompleteTypes->Print();
	}

	PrintLineSeparator();



	{
		ECompleteVsIncompleteTypes								Value1=ECompleteVsIncompleteTypes::E_ONE;
		ECompleteVsIncompleteTypes								Value2=ECompleteVsIncompleteTypes::E_TWO;

		wcout << L"VALUE 1 [" << int(Value1) << L"]." << endl;
		wcout << L"VALUE 2 [" << int(Value2) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CCompleteVsIncompleteTypes								Object(100);
		
		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION obsahuje TEMPLATE PARAMETER 'TType1' a TEMPLATE PARAMETER 'TType2'.
template<typename TType1, typename TType2>
void TemplateFunctionTemplateParametersVsTemplateArguments1(TType1 Value1, TType2 Value2)
{
	wcout << L"FUNCTION 1 - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE FUNCTION obsahuje TEMPLATE PARAMETER 'TType1', TEMPLATE PARAMETER 'TType2' a TEMPLATE PARAMETER 'TType3'.
template<typename TType1, typename TType2, typename TType3>
void TemplateFunctionTemplateParametersVsTemplateArguments2(TType1 Value1, TType2 Value2, TType3 Value3)
{
	wcout << L"FUNCTION 2 - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"]." << endl;

	// !!!!! TEMPLATE PARAMETER 'TType1' a TEMPLATE PARAMETER 'TType2' su pouzite ako TEMPLATE ARGUMENTS.
	TemplateFunctionTemplateParametersVsTemplateArguments1<TType1,TType2>(Value1,Value2);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateParametersVsTemplateArguments(void)
{
	PrintLineSeparator();

	{
		// !!!!! TEMPLATE ARGUMENTS su definovane IMPLICITNE.
		TemplateFunctionTemplateParametersVsTemplateArguments1(100,123.456);
	}

	PrintLineSeparator();

	{
		// !!!!! TEMPLATE ARGUMENTS su definovane EXPLICITNE.
		// !!!!! ELEMENT 'TemplateFunctionTemplateParametersVsTemplateArguments2<int,double,wstring>' predstavuje TEMPLATE ID.
		TemplateFunctionTemplateParametersVsTemplateArguments2<int,double,wstring>(100,123.456,L"Timmy");
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateInstantiation();
	//TestTemplateSpecializations();
	//TestDeclarationsVsDefinitions();
	//TestCompleteVsIncompleteTypes();
	TestTemplateParametersVsTemplateArguments();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------