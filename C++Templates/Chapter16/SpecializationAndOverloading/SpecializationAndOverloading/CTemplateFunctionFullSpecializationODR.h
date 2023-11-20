//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION PRIMARY TEMPLATE FUNCTION.
template<typename TType>
void TemplateFunctionFullSpecializationODR(TType Value)
{
	std::wcout << L"PRIMARY TEMPLATE FUNCTION - ONE DEFINITION RULE - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION SPECIALIZATION.
// !!!!! Odporuca sa aby DECLARATIONS TEMPLATE FUNCTION SPECIALIZATIONS sa nachadzali v TOM ISTOM HEADER FILE, ako DEFINITION PRIMARY TEMPLATE FUNCTION. Vdaka tomu sa zabrani, aby bola TEMPLATE FUNCTION SPECIALIZATION pouzita predtym ako je DECLARED.
template<>
void TemplateFunctionFullSpecializationODR<double>(double Value);
//----------------------------------------------------------------------------------------------------------------------