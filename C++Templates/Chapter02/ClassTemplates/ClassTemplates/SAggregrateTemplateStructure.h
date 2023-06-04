//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
// !!!!! AGGREGATE CLASS je CLASS, alebo STRUCTURE, ktora USER PROVIDED, EXPLICIT alebo INHERITED CONSTRUCTORS, nema PRIVATE, alebo PROTECTED DATA MEMBERS, nema VIRTUAL METHODS a nema VIRTUAL, PRIVATE, alebo PROTECTED BASE CLASSES.
template<typename TType>
struct SAggregrateTemplateStructure
{
//----------------------------------------------------------------------------------------------------------------------
	TType														MValue;
	std::wstring												MText;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE DEDUCTION GUIDE je mozne aplikovat aj na AGGREGATE TEMPLATE CLASS.
// !!!!! TEMPLATE DEDUCTION GUIDE je definovany ako PSEUDO CONSTRUCTOR s 2 PARAMETERS.
SAggregrateTemplateStructure(const wchar_t* Parameter1, const wchar_t* Parameter2) -> SAggregrateTemplateStructure<std::wstring>;
//----------------------------------------------------------------------------------------------------------------------