//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CNonTypeTemplateClass.h"
#include "CNonTypeTemplateClassAuto.h"
#include "EEnum.h"
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
void TestTemplateClassNonTypeTemplateParameters(void)
{
	PrintLineSeparator();

	CNonTypeTemplateClass<int,5>								Template;

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=static_cast<int>((Index+1)*10);

		Template.SetValue(Index,Value);
	}

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=Template.GetValue(Index);

		wcout << L"VALUES[" << Index << L"] [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE FUNCTIONS mat NON TYPE PARAMETERS.
template<typename TType, size_t SIZE>
size_t TemplateFunctionNonTypeTemplateParameters1(TType Value)
{
	if (sizeof(Value)>SIZE)
	{
		return(sizeof(Value));
	}
	else
	{
		return(SIZE);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON TYPE PARAMETERS mozu mat DEFAULT VALUE.
template<typename TType, size_t SIZE=10>
size_t TemplateFunctionNonTypeTemplateParameters2(TType Value)
{
	if (sizeof(Value)>SIZE)
	{
		return(sizeof(Value));
	}
	else
	{
		return(SIZE);
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON TEMPLATE PARAMETER moze mat ten isty TYPE ako TEMPLATE PARAMETER.
template<typename TType, TType VALUE>
TType TemplateFunctionNonTypeTemplateParameters3(TType Value)
{
	TType														Result=(Value+VALUE);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParameters(void)
{
	PrintLineSeparator();

	{
		int														Value=0;
		size_t													Result=TemplateFunctionNonTypeTemplateParameters1<int,6>(Value);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		double													Value=0.0;
		size_t													Result=TemplateFunctionNonTypeTemplateParameters1<double,6>(Value);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		double													Value=0.0;

		// !!! Pouzije sa DEFAULT VALUE za NON TEMPLATE PARAMETER.
		size_t													Result=TemplateFunctionNonTypeTemplateParameters2<double>(Value);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		int														Value=10;
		int														Result=TemplateFunctionNonTypeTemplateParameters3<int,6>(Value);

		wcout << L"RESULT [" << Result << L"] !" << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<int VALUE>
void TemplateNonTypeTemplateParametersTypesInt(void)
{
	wcout << L"INT - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<EEnum VALUE>
void TemplateNonTypeTemplateParametersTypesEnum(void)
{
	wcout << L"ENUM - VALUE [" << static_cast<int>(VALUE) << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<int* VALUE>
void TemplateNonTypeTemplateParametersTypesPointerToValue(void)
{
	wcout << L"POINTER TO VALUE - VALUE [" << *VALUE << L"] !" << endl;

	*VALUE=111;

	wcout << L"POINTER TO VALUE - VALUE [" << *VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<int& VALUE>
void TemplateNonTypeTemplateParametersTypesReferenceToValue(void)
{
	wcout << L"REFERENCE TO VALUE - VALUE [" << VALUE << L"] !" << endl;

	VALUE=111;

	wcout << L"REFERENCE TO VALUE - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<const wchar_t* VALUE>
void TemplateNonTypeTemplateParametersTypesPointerToWChar(void)
{
	wcout << L"POINTER TO WCHAR - VALUE [" << VALUE << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestNonTypeTemplateParametersTypes(void)
{
	PrintLineSeparator();

	{
		TemplateNonTypeTemplateParametersTypesInt<10>();
	}

	PrintLineSeparator();

	{
		TemplateNonTypeTemplateParametersTypesEnum<EEnum::E_VALUE>();
	}

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		TemplateNonTypeTemplateParametersTypesPointerToValue<&Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	{
		int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		// !!!!! COMPILER hodi ERROR, pretoze VARIABLE 'Value' nie je STATIC.
		TemplateNonTypeTemplateParametersTypesPointerToValue<&Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static int												Value=100;

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;

		TemplateNonTypeTemplateParametersTypesReferenceToValue<Value>();

		wcout << L"STATIC VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! VAIRABALE MUSI byt STATIC.
		static const wchar_t									Value[]=L"Timmy";

		TemplateNonTypeTemplateParametersTypesPointerToWChar<Value>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<int VALUE1, bool VALUE2>
void TemplateNonTypeTemplateParametersTypesExpression(void)
{
	wcout << L"INT VALUE [" << VALUE1 << L"] !" << endl;

	wcout << L"BOOL VALUE [" << VALUE2 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestNonTypeTemplateParametersExpressions(void)
{
	PrintLineSeparator();

	{
		// !!! EXPRESSION '1>2' MUSI byt v ZATVORKACH, aby si CHARACTER '>' COMPILER nepomylil s ukoncenim TEMPLATE ARGUMENTS.
		TemplateNonTypeTemplateParametersTypesExpression<1+2,(3>2)>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateClassNonTypeTemplateParametersAuto(void)
{
	PrintLineSeparator();

	CNonTypeTemplateClassAuto<int,5U>							Template;

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=static_cast<int>((Index+1)*10);

		Template.SetValue(Index,Value);
	}

	for(size_t Index=0;Index<Template.VALUES_SIZE;Index++)
	{
		int														Value=Template.GetValue(Index);

		wcout << L"VALUES[" << Index << L"] [" << Value << L"] !" << endl;
	}

	wcout << L"TEMPLATE - TYPE [" << GetTypeInfoName<decltype(Template)>() << L"] !" << endl;
	wcout << L"TEMPLATE - TYPE.VALUES_SIZE [" << GetTypeInfoName<decltype(Template.VALUES_SIZE)>() << L"] !" << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre definiciu NON-TYPE TEMPLATE PARAMETER je mozne pouzit aj KEYWORD [auto].
template<auto SIZE>
void TemplateFunctionNonTypeTemplateParametersAuto(void)
{
	using														SIZE_TYPE=decltype(SIZE);

	wcout << L"SIZE [" << SIZE << L"] !" << endl;

	wcout << L"SIZE TYPE [" << GetTypeInfoName<decltype(SIZE)>() << L"] !" << endl;
	wcout << L"SIZE_TYPE [" << GetTypeInfoName<SIZE_TYPE>() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParametersAuto(void)
{
	PrintLineSeparator();

	TemplateFunctionNonTypeTemplateParametersAuto<10U>();

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre definiciu NON-TYPE TEMPLATE PARAMETER je mozne pouzit aj KEYWORD [decltype(auto)].
template<decltype(auto) SIZE>
void TemplateFunctionNonTypeTemplateParametersDecltypeAuto(void)
{
	using														SIZE_TYPE=decltype(SIZE);

	wcout << L"SIZE [" << SIZE << L"] !" << endl;

	wcout << L"SIZE TYPE [" << GetTypeInfoName<decltype(SIZE)>() << L"] !" << endl;
	wcout << L"SIZE_TYPE [" << GetTypeInfoName<SIZE_TYPE>() << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateFunctionNonTypeTemplateParametersDecltypeAuto(void)
{
	PrintLineSeparator();

	{
		TemplateFunctionNonTypeTemplateParametersDecltypeAuto<10U>();
	}

	PrintLineSeparator();

	{
		static int												Variable=100;

		// !!!!!  TEMPLATE ARGUMENTS musia byt uzatvorene v ZATVORKACH [()].
		TemplateFunctionNonTypeTemplateParametersDecltypeAuto<(Variable)>();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTemplateClassNonTypeTemplateParameters();
	//TestTemplateFunctionNonTypeTemplateParameters();
	//TestNonTypeTemplateParametersTypes();
	//TestNonTypeTemplateParametersExpressions();
	//TestTemplateClassNonTypeTemplateParametersAuto();
	//TestTemplateFunctionNonTypeTemplateParametersAuto();
	TestTemplateFunctionNonTypeTemplateParametersDecltypeAuto();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------