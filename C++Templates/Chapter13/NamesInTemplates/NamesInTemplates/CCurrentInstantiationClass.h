//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE.
template<typename TType>
class CCurrentInstantiationClass final
{
//----------------------------------------------------------------------------------------------------------------------
	using														MyType=TType;

	private:
		CString													MField;

	private:
		// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
		CCurrentInstantiationClass*								MField1;
		// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
		CCurrentInstantiationClass<MyType>*						MField2;
		// !!! Toto je UNKNOWN SPECIALIZATION INJECTED CLASS NAME.
		CCurrentInstantiationClass<TType*>*						MField3;

	public:
		const CString& GetField(void) const noexcept;
		const CCurrentInstantiationClass* GetField1(void) const noexcept;
		const CCurrentInstantiationClass<MyType>* GetField2(void) const noexcept;
		const CCurrentInstantiationClass<TType*>* GetField3(void) const noexcept;

	public:
		void SetFields(CCurrentInstantiationClass* Field1, CCurrentInstantiationClass<MyType>* Field2, CCurrentInstantiationClass<TType*>* Field3);

	public:
		void Print(void) const;

	public:
		CCurrentInstantiationClass(const CString& Field);
		virtual ~CCurrentInstantiationClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationClass<TType>::CCurrentInstantiationClass(const CString& Field)
	: MField(Field), MField1(nullptr), MField2(nullptr), MField3(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationClass<TType>::~CCurrentInstantiationClass(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CString& CCurrentInstantiationClass<TType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationClass<TType>* CCurrentInstantiationClass<TType>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationClass<typename CCurrentInstantiationClass<TType>::MyType>* CCurrentInstantiationClass<TType>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationClass<TType*>* CCurrentInstantiationClass<TType>::GetField3(void) const noexcept
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationClass<TType>::SetFields(CCurrentInstantiationClass* Field1, CCurrentInstantiationClass<MyType>* Field2, CCurrentInstantiationClass<TType*>* Field3)
{
	MField1=Field1;
	MField2=Field2;
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationClass<TType>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARTIAL TEMPLATE SPECIALIZATION.
template<typename TType>
class CCurrentInstantiationClass<TType*> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MField;

	public:
		const CString& GetField(void) const noexcept;

	public:
		void Print(void) const;

	public:
		CCurrentInstantiationClass(const CString& Field);
		virtual ~CCurrentInstantiationClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationClass<TType*>::CCurrentInstantiationClass(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationClass<TType*>::~CCurrentInstantiationClass(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CString& CCurrentInstantiationClass<TType*>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationClass<TType*>::Print(void) const
{
	std::wcout << L"PARTIAL TEMPLATE SPECIALIZATION - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------