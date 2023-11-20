//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CPartialTemplateSpecializationNumberOfParametersTest final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CString ToString1(int Parameter) const;
		CString ToString2(double Parameter) const;

	public:
		CPartialTemplateSpecializationNumberOfParametersTest(int Value);
		virtual ~CPartialTemplateSpecializationNumberOfParametersTest(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS.
template<typename TType1, typename TType2>
class CPartialTemplateSpecializationNumberOfParameters final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationNumberOfParameters(TType1 Field1, TType2 Field2);
		virtual ~CPartialTemplateSpecializationNumberOfParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPartialTemplateSpecializationNumberOfParameters<TType1,TType2>::CPartialTemplateSpecializationNumberOfParameters(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPartialTemplateSpecializationNumberOfParameters<TType1,TType2>::~CPartialTemplateSpecializationNumberOfParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecializationNumberOfParameters<TType1,TType2>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - TYPE 1 [" << GetTypeInfoName<decltype(MField1)>() << L"] FIELD 1 [" << MField1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(MField2)>() << L"] FIELD 2 [" << MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS moze mat INY POCET TEMPLATE PARAMETERS ako PRIMARY TEMPLATE CLASS.
template<typename TType>
// !!!!! Do PRIMARY TEMPLATE vsak je NUTNE vlozit taky pocet TEMPLATE PARAMETERS, ktore PRIMARY TEMPLATE CLASS ocakava. V tomto pripade su to 2.
class CPartialTemplateSpecializationNumberOfParameters<TType,TType*> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField1;
		TType*													MField2;

	public:
		void Print(void) const;

	public:
		CPartialTemplateSpecializationNumberOfParameters(TType Field1, TType* Field2);
		virtual ~CPartialTemplateSpecializationNumberOfParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationNumberOfParameters<TType,TType*>::CPartialTemplateSpecializationNumberOfParameters(TType Field1, TType* Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPartialTemplateSpecializationNumberOfParameters<TType,TType*>::~CPartialTemplateSpecializationNumberOfParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecializationNumberOfParameters<TType,TType*>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION 1 <TType,TType*> - TYPE 1 [" << GetTypeInfoName<decltype(MField1)>() << L"] FIELD 1 [" << MField1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(MField2)>() << L"] FIELD 2 [" << MField2 << L"] DEREFERENCED FIELD 2 [" << *MField2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS moze mat INY POCET TEMPLATE PARAMETERS ako PRIMARY TEMPLATE CLASS.
template<typename TClassName, typename TReturnType, typename TParameterType1, typename TParameterType2>
// !!!!! Do PRIMARY TEMPLATE vsak je NUTNE vlozit taky pocet TEMPLATE PARAMETERS, ktore PRIMARY TEMPLATE CLASS ocakava. V tomto pripade su to 2.
class CPartialTemplateSpecializationNumberOfParameters<TReturnType(TClassName::*)(TParameterType1) const,TReturnType(TClassName::*)(TParameterType2) const> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		const TClassName&										MObject;
		TReturnType												(TClassName::*MMethod1)(TParameterType1) const;
		TReturnType												(TClassName::*MMethod2)(TParameterType2) const;

	public:
		void Print(TParameterType1 Parameter1, TParameterType2 Parameter2) const;

	public:
		CPartialTemplateSpecializationNumberOfParameters(const TClassName& Object, TReturnType(TClassName::*Method1)(TParameterType1) const, TReturnType(TClassName::*Method2)(TParameterType2) const);
		virtual ~CPartialTemplateSpecializationNumberOfParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName, typename TReturnType, typename TParameterType1, typename TParameterType2>
CPartialTemplateSpecializationNumberOfParameters<TReturnType(TClassName::*)(TParameterType1) const,TReturnType(TClassName::*)(TParameterType2) const>::CPartialTemplateSpecializationNumberOfParameters(const TClassName& Object, TReturnType(TClassName::*Method1)(TParameterType1) const, TReturnType(TClassName::*Method2)(TParameterType2) const)
	: MObject(Object), MMethod1(Method1), MMethod2(Method2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName, typename TReturnType, typename TParameterType1, typename TParameterType2>
CPartialTemplateSpecializationNumberOfParameters<TReturnType(TClassName::*)(TParameterType1) const,TReturnType(TClassName::*)(TParameterType2) const>::~CPartialTemplateSpecializationNumberOfParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TClassName, typename TReturnType, typename TParameterType1, typename TParameterType2>
void CPartialTemplateSpecializationNumberOfParameters<TReturnType(TClassName::*)(TParameterType1) const,TReturnType(TClassName::*)(TParameterType2) const>::Print(TParameterType1 Parameter1, TParameterType2 Parameter2) const
{
	TReturnType													ReturnValue1=(MObject.*MMethod1)(Parameter1);
	TReturnType													ReturnValue2=(MObject.*MMethod2)(Parameter2);

	std::wcout << L"TEMPLATE CLASS PARTIAL SPECIALIZATION 2 [TReturnType(TClassName::*)(TParameterType1) const,TReturnType(TClassName::*)(TParameterType2) const] CALLED. VALUE 1 [" << ReturnValue1 << L"] VALUE 2 [" << ReturnValue2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------