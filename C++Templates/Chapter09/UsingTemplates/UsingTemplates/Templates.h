//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
void NonTemplateFunction(double Parameter);
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE [.H] obsahuje IBA TEMPLATE DECLARATION, ale NIE TEMPLATE DEFINITION.
template<typename TType>
void TemplateFunction1(TType Parameter);
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE [.H] obsahuje IBA TEMPLATE DECLARATION, ale NIE TEMPLATE DEFINITION.
template<typename TType>
void TemplateFunction2(TType Parameter);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE [.H] obsahuje TEMPLATE DECLARATION aj TEMPLATE DEFINITION.
// !!!!! TEMPLATE DECLARATION.
template<typename TType>
void TemplateFunction3(TType Parameter);
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DEFINITION.
template<typename TType>
void TemplateFunction3(TType Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunction3(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DECLARATION a DEFINITION.
template<typename TType>
void TemplateFunctionSpecialization1(TType Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunctionSpecialization1(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER NEHODI ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION ma DEFINITION az vo FILE [.CPP].
template<>
void TemplateFunctionSpecialization1<int>(int Parameter);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DECLARATION a DEFINITION.
template<typename TType>
void TemplateFunctionSpecialization2(TType Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunctionSpecialization2(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER NEHODI ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION JE oznacena pomocou KEYWORD [inline].
template<>
inline void TemplateFunctionSpecialization2<int>(int Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunctionSpecialization2<int>(int Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! TEMPLATE DECLARATION a DEFINITION.
template<typename TType>
void TemplateFunctionSpecialization3(TType Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunctionSpecialization3(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION NIE JE oznacena pomocou KEYWORD [inline] a C++ jej DEFINITION vlozi do vsetkych COMPILATION UNITS, ktore vlozia tento FILE pomocou INCLUDE.
template<>
void TemplateFunctionSpecialization3<int>(int Parameter)
{
	std::wcout << L"FUNCTION [void TemplateFunctionSpecialization3<int>(int Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << std::endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------