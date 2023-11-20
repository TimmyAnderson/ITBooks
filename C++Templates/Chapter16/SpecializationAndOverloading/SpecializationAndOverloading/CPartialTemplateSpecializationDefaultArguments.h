//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS.
template<typename TType1, typename TType2=double>
class CPartialTemplateSpecializationDefaultArguments final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationDefaultArguments(TType1 Field1, TType2 Field2);
		virtual ~CPartialTemplateSpecializationDefaultArguments(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPartialTemplateSpecializationDefaultArguments<TType1,TType2>::CPartialTemplateSpecializationDefaultArguments(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPartialTemplateSpecializationDefaultArguments<TType1,TType2>::~CPartialTemplateSpecializationDefaultArguments(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecializationDefaultArguments<TType1,TType2>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - TYPE 1 [" << GetTypeInfoName<decltype(MField1)>() << L"] FIELD 1 [" << MField1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(MField2)>() << L"] FIELD 2 [" << MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS moze mat INY POCET TEMPLATE PARAMETERS ako PRIMARY TEMPLATE CLASS.
template<typename TType>
// !!!!! Do PRIMARY TEMPLATE vsak je NUTNE vlozit aj INY POCET TEMPLATE PARAMETERS, ktore PRIMARY TEMPLATE CLASS ocakava, ak su ostavajuce TEMPLATE PARAMETERS nahradene DEFAULT TEMPLATE ARGUMENTS.
class CPartialTemplateSpecializationDefaultArguments<TType*> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType*													MField;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationDefaultArguments(TType* Field);
		virtual ~CPartialTemplateSpecializationDefaultArguments(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationDefaultArguments<TType*>::CPartialTemplateSpecializationDefaultArguments(TType* Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationDefaultArguments<TType*>::~CPartialTemplateSpecializationDefaultArguments(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecializationDefaultArguments<TType*>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION <TType*> - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"] DEREFERENCED FIELD [" << *MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------