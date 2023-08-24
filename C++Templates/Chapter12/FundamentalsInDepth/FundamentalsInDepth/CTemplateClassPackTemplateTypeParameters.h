//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale nie DEFINITION PRIMARY TEMPLATE.
template<typename... TTypes>
class CTemplateClassPackTemplateTypeParameters;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre 0 PARAMETERS.
template<>
class CTemplateClassPackTemplateTypeParameters<> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre 1-N PARAMETERS.
template<typename TFirst, typename... TTypes>
class CTemplateClassPackTemplateTypeParameters<TFirst,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! V TEMPLATE CLASS pre 'M' PARAMETERS spravi FRIEND TEMPLATE CLASS pre 'N' PARAMETERS.
	template<typename... TLocalTypes>
	friend class CTemplateClassPackTemplateTypeParameters;

	private:
		TFirst													MField;
		CTemplateClassPackTemplateTypeParameters<TTypes...>		MFields;

	private:
		void PrintInternal(size_t Index) const;

	public:
		void Print(void) const;

	public:
		CTemplateClassPackTemplateTypeParameters(TFirst First, TTypes... Types);
		virtual ~CTemplateClassPackTemplateTypeParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
CTemplateClassPackTemplateTypeParameters<TFirst,TTypes...>::CTemplateClassPackTemplateTypeParameters(TFirst First, TTypes... Types)
	: MField(First), MFields(Types...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
CTemplateClassPackTemplateTypeParameters<TFirst,TTypes...>::~CTemplateClassPackTemplateTypeParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
void CTemplateClassPackTemplateTypeParameters<TFirst,TTypes...>::PrintInternal(size_t Index) const
{
	std::wcout << L"TEMPLATE TYPE PARAMETERS - PARAMETER [" << Index << L"] - TYPE [" << GetTypeInfoName<TFirst>() << L"] - VALUE [" << MField << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		MFields.PrintInternal(Index+1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
void CTemplateClassPackTemplateTypeParameters<TFirst,TTypes...>::Print(void) const
{
	PrintInternal(1);
}
//----------------------------------------------------------------------------------------------------------------------