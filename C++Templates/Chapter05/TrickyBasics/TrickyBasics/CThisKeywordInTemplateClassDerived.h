//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CThisKeywordInTemplateClassBase.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CThisKeywordInTemplateClassDerived final : public CThisKeywordInTemplateClassBase<TType>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void MethodInDerivedClass(void) const;

	public:
		void TestMethod(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CThisKeywordInTemplateClassDerived<TType>::MethodInDerivedClass(void) const
{
	std::wcout << L"METHOD [void MethodInDerivedClass(void) const] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CThisKeywordInTemplateClassDerived<TType>::TestMethod(void) const
{
	std::wcout << L"METHOD [void TestMethod(void) const] CALLED !" << std::endl;

	MethodInDerivedClass();

	/*
	// !!!!! COMPILER hodi ERROR, a to aj napriek tomu, ze METHOD je definovana v PUBLIC BASE CLASS ako PUBLIC METHOD.
	MethodInBaseClass();
	*/

	// !!! Tento CODE uz COMPILER akceptuje.
	this->MethodInBaseClass();

	// !!! Tento CODE uz COMPILER akceptuje.
	CThisKeywordInTemplateClassBase<TType>::MethodInBaseClass();
}
//----------------------------------------------------------------------------------------------------------------------