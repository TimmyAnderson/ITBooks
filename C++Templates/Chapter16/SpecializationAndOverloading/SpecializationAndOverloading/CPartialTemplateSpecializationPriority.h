//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CPartialTemplateSpecializationPriorityTest final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		void Print1(void) const;
		void Print2(void) const;

	public:
		CString ToString1(void) const;
		CString ToString2(void) const;

	public:
		CPartialTemplateSpecializationPriorityTest(int Value);
		virtual ~CPartialTemplateSpecializationPriorityTest(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS.
template<typename TType>
class CPartialTemplateSpecializationPriority final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationPriority(TType Field);
		virtual ~CPartialTemplateSpecializationPriority(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationPriority<TType>::CPartialTemplateSpecializationPriority(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationPriority<TType>::~CPartialTemplateSpecializationPriority(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecializationPriority<TType>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName>
class CPartialTemplateSpecializationPriority<void(TClassName::*)(void) const> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TClassName&										MObject;
		void													(TClassName::*MMethod)(void) const;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationPriority(const TClassName& Object, void(TClassName::*Method)(void) const);
		virtual ~CPartialTemplateSpecializationPriority(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName>
CPartialTemplateSpecializationPriority<void(TClassName::*)(void) const>::CPartialTemplateSpecializationPriority(const TClassName& Object, void(TClassName::*Method)(void) const)
	: MObject(Object), MMethod(Method)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName>
CPartialTemplateSpecializationPriority<void(TClassName::*)(void) const>::~CPartialTemplateSpecializationPriority(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName>
void CPartialTemplateSpecializationPriority<void(TClassName::*)(void) const>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS SPECIALIZATION 1 [void(TClassName::*)(void) const] CALLED." << std::endl;

	(MObject.*MMethod)();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS moze mat INY POCET TEMPLATE PARAMETERS ako PRIMARY TEMPLATE CLASS.
template<typename TReturnType, typename TClassName>
class CPartialTemplateSpecializationPriority<TReturnType(TClassName::*)(void) const> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TClassName&										MObject;
		TReturnType												(TClassName::*MMethod)(void) const;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationPriority(const TClassName& Object, TReturnType(TClassName::*Method)(void) const);
		virtual ~CPartialTemplateSpecializationPriority(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnType, typename TClassName>
CPartialTemplateSpecializationPriority<TReturnType(TClassName::*)(void) const>::CPartialTemplateSpecializationPriority(const TClassName& Object, TReturnType(TClassName::*Method)(void) const)
	: MObject(Object), MMethod(Method)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnType, typename TClassName>
CPartialTemplateSpecializationPriority<TReturnType(TClassName::*)(void) const>::~CPartialTemplateSpecializationPriority(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnType, typename TClassName>
void CPartialTemplateSpecializationPriority<TReturnType(TClassName::*)(void) const>::Print(void) const
{
	TReturnType													ReturnValue=(MObject.*MMethod)();

	std::wcout << L"TEMPLATE CLASS SPECIALIZATION 2 [TReturnType(TClassName::*)(void) const] CALLED. VALUE [" << ReturnValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------