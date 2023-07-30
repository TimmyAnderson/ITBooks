//----------------------------------------------------------------------------------------------------------------------
#include "Templates.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void NonTemplateFunction(double Parameter)
{
	wcout << L"FUNCTION [void NonTemplateFunction(double Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE [.CPP] obsahuje IBA TEMPLATE DECLARATION, ale NIE TEMPLATE DEFINITION.
template<typename TType>
void TemplateFunction1(TType Parameter)
{
	wcout << L"FUNCTION [void TemplateFunction1(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE [.CPP] obsahuje IBA TEMPLATE DECLARATION, ale NIE TEMPLATE DEFINITION.
template<typename TType>
void TemplateFunction2(TType Parameter)
{
	wcout << L"FUNCTION [void TemplateFunction2(TType Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void DummyFunction(void)
{
	// !!!!! FUNCTION zavola TEMPLATE FUNCTION [template<typename TType> void TemplateFunction2(TType Parameter)] pre TYPE [double] a prinuti tak COMPILER vygenerovat CODE pre FUNCTION [void TemplateFunction2(double Parameter)], ktora sa vola vo FILE [UsingTemplates.cpp].
	TemplateFunction2(11.22);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER NEHODI ERROR, pretoze TEMPLATE FUNCTION SPECIALIZATION ma DEFINITION az vo FILE [.CPP].
template<>
void TemplateFunctionSpecialization1<int>(int Parameter)
{
	wcout << L"FUNCTION [void TemplateFunctionSpecialization1<int>(int Parameter)] CALLED with PARAMETER [" << Parameter << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------