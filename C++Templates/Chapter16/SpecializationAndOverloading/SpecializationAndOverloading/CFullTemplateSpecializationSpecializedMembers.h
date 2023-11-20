//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFullTemplateSpecializationSpecializedMembers final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		template<typename TInnerType>
		class CFullTemplateSpecializationSpecializedMembersInner final
		{
//----------------------------------------------------------------------------------------------------------------------
			public:
				static TInnerType								MMyInnerStaticField;

			public:
				void MyInnerMethod(TInnerType Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		static TType											MMyStaticField;

	public:
		void MyMethod(TType Parameter) const;

	public:
		CFullTemplateSpecializationSpecializedMembers(TType Field);
		virtual ~CFullTemplateSpecializationSpecializedMembers(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! STATIC FIELD TEMPLATE CLASS.
template<typename TType>
TType															CFullTemplateSpecializationSpecializedMembers<TType>::MMyStaticField=TType();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR TEMPLATE CLASS.
template<typename TType>
CFullTemplateSpecializationSpecializedMembers<TType>::CFullTemplateSpecializationSpecializedMembers(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DESTRUCTOR TEMPLATE CLASS.
template<typename TType>
CFullTemplateSpecializationSpecializedMembers<TType>::~CFullTemplateSpecializationSpecializedMembers(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD TEMPLATE CLASS.
template<typename TType>
void CFullTemplateSpecializationSpecializedMembers<TType>::MyMethod(TType Parameter) const
{
	std::wcout << L"PRIMARY TEMPLATE METHOD - TYPE [" << GetTypeInfoName<decltype(MField)>() << L"] FIELD [" << MField << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! STATIC FIELD INNER TEMPLATE CLASS.
template<typename TType>
template<typename TInnerType>
TInnerType														CFullTemplateSpecializationSpecializedMembers<TType>::CFullTemplateSpecializationSpecializedMembersInner<TInnerType>::MMyInnerStaticField=TType();
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD INNER TEMPLATE CLASS.
template<typename TType>
template<typename TInnerType>
void CFullTemplateSpecializationSpecializedMembers<TType>::CFullTemplateSpecializationSpecializedMembersInner<TInnerType>::MyInnerMethod(TInnerType Parameter) const
{
	std::wcout << L"PRIMARY TEMPLATE INNER CLASS METHOD - TYPE [" << GetTypeInfoName<TInnerType>() << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE VARIABLE SPECIALIZATION DECLARATION.
template<>
double											CFullTemplateSpecializationSpecializedMembers<double>::MMyStaticField;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-TEMPLATE METHOD SPECIALIZATION DECLARATION.
template<>
void CFullTemplateSpecializationSpecializedMembers<double>::MyMethod(double Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION STATIC FIELD INNER TEMPLATE CLASS SPECIALIZATION.
// !!!!! STATIC FIELD INNER TEMPLATE CLASS SPECIALIZATION MUSI mat aplikovanu SYNTAX [template<>].
template<>
template<>
double															CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>::MMyInnerStaticField;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR.
// !!!!! TEMPLATE SPECIALIZATION INNER CLASS MEMBERS NIE JE mozny bez TEMPLATE SPECIALIZATION samotnej INNER TEMPLATE CLASS.
template<typename TType>
template<>
void CFullTemplateSpecializationSpecializedMembers<TType>::CFullTemplateSpecializationSpecializedMembersInner<double>::MyInnerMethod(double Parameter) const
{
	std::wcout << L"TEMPLATE SPECIALIZATION INNER CLASS METHOD <double> - TYPE [" << GetTypeInfoName<double>() << L"] PARAMETER [" << Parameter << L"]." << std::endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION NON-TEMPLATE INNER CLASS METHOD SPECIALIZATION.
template<>
template<>
void CFullTemplateSpecializationSpecializedMembers<short>::CFullTemplateSpecializationSpecializedMembersInner<double>::MyInnerMethod(double Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION.
template<>
class CFullTemplateSpecializationSpecializedMembers<long> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static long												MMyStaticField;

	public:
		void MyMethod(long Parameter) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------