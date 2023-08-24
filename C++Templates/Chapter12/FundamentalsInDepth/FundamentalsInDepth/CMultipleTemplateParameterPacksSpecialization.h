//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CVariadicTemplate1.h"
#include "CVariadicTemplate2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale nie DEFINITION PRIMARY TEMPLATE.
template<typename TType1, typename TType2>
class CMultipleTemplateParameterPacksSpecialization;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
// !!!!! PARTIAL TEMPLATE CLASS SPECIALIZATIONS MOZU mat viacero TEMPLATE PARAMETERS PACKS, pretoze TEMPLATE PARAMETERS vo viacerych TEMPLATE PARAMETERS PACKS mozu byt jednoznacne identifikovane pomocou TEMPLATE PARAMETER DEDUCTION.
template<typename... TTypes1, typename... TTypes2>
class CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CVariadicTemplate1<TTypes1...>							MField1;
		CVariadicTemplate2<TTypes2...>							MField2;

	public:
		void Print(const std::wstring& Text) const;

	public:
		CMultipleTemplateParameterPacksSpecialization(void);
		CMultipleTemplateParameterPacksSpecialization(const CVariadicTemplate1<TTypes1...>& Field1, const CVariadicTemplate2<TTypes2...>& Field2);
		virtual ~CMultipleTemplateParameterPacksSpecialization(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>::CMultipleTemplateParameterPacksSpecialization(void)
	: MField1(), MField2()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>::CMultipleTemplateParameterPacksSpecialization(const CVariadicTemplate1<TTypes1...>& Field1, const CVariadicTemplate2<TTypes2...>& Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>::~CMultipleTemplateParameterPacksSpecialization(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes1, typename... TTypes2>
void CMultipleTemplateParameterPacksSpecialization<CVariadicTemplate1<TTypes1...>,CVariadicTemplate2<TTypes2...>>::Print(const std::wstring& Text) const
{
	std::wcout << Text << L" - FIELD 1 - TYPE [" << GetTypeInfoName<decltype(MField1)>() << L"]." << std::endl;

	MField1.Print(L"TEMPLATE CLASS - FIELD 1");

	PrintLineSeparator();

	std::wcout << Text << L" - FIELD 2 - TYPE [" << GetTypeInfoName<decltype(MField2)>() << L"]." << std::endl;

	MField2.Print(L"TEMPLATE CLASS - FIELD 2");
}
//----------------------------------------------------------------------------------------------------------------------