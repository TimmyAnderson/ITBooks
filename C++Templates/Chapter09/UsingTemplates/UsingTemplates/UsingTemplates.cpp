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
#include "Templates.h"
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
void TestBadTemplateOrganization(void)
{
	PrintLineSeparator();

	{
		NonTemplateFunction(123.456);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! LINKER hodi ERROR, pretoze TEMPLATE FUNCTION [template<typename TType> void TemplateFunction1(TType Parameter)] pre TYPE [double] nebola INSTANCED. Tym padom FUNCTION [void TemplateFunction1(double Parameter)] NEBOLA VYGENEROVANA a LINKER ju NENASIEL.
		TemplateFunction1(123.456);
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! COMPILER i LINKER zbehnu spravne. Je to vsak IBA PRETO, lebo vo FILE [Templates.cpp] je volana TEMPLATE FUNCTION [template<typename TType> void TemplateFunction2(TType Parameter)] pre TYPE [double] a tym padom je pre nu vykonana INSTANTIATION. LINKER teda NAJDE FUNCTION [void TemplateFunction2(double Parameter)].
		TemplateFunction2(123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestGoodTemplateOrganization(void)
{
	PrintLineSeparator();

	{
		// !!!!! COMPILER i LINKER zbehnu spravne, pretoze TEMPLATE FUNCTION DECLARATION i TEMPLATE FUNCTION DEFINITION sa nachadza vo FILE [.H].
		TemplateFunction3(123.456);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTemplateSpecializationsOrganization(void)
{
	PrintLineSeparator();

	{
		// !!!!! COMPILER NEHODI ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION ma DEFINITION az vo FILE [.CPP].
		TemplateFunctionSpecialization1(123.456);

		TemplateFunctionSpecialization1(100);
	}

	PrintLineSeparator();

	{
		// !!!!! COMPILER NEHODI ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION JE oznacena pomocou KEYWORD [inline].
		TemplateFunctionSpecialization2(123.456);

		TemplateFunctionSpecialization2(100);
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION NIE JE oznacena pomocou KEYWORD [inline] a C++ jej DEFINITION vlozi do vsetkych COMPILATION UNITS, ktore vlozia tento FILE pomocou INCLUDE.
		TemplateFunctionSpecialization3(123.456);

		TemplateFunctionSpecialization3(100);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestBadTemplateOrganization();
	//TestGoodTemplateOrganization();
	TestTemplateSpecializationsOrganization();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------