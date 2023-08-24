//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CVariadicTemplateClassPackExpansion;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<>
class CVariadicTemplateClassPackExpansion<> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr size_t									SIZE=0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPANSION PACK sa robi pre celu EXPRESSION, ktora predchadza OPERATOR [...].
template<typename TFirst, typename... TTypes>
class CVariadicTemplateClassPackExpansion<TFirst,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename... TLocalTypes>
	friend class CVariadicTemplateClassPackExpansion;

	public:
		static constexpr size_t									SIZE=(1+sizeof...(TTypes));

	private:
		TFirst*													MField;
		CVariadicTemplateClassPackExpansion<TTypes...>			MFields;

	private:
		void PrintInternal(const std::wstring& Text, size_t Index) const;

	public:
		void Print(const std::wstring& Text) const;

	public:
		CVariadicTemplateClassPackExpansion(void);
		// !!!!! EXPANSION PACK sa robi pre celu EXPRESSION, ktora predchadza OPERATOR [...].
		CVariadicTemplateClassPackExpansion(TFirst* First, TTypes*... Types);
		virtual ~CVariadicTemplateClassPackExpansion(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
CVariadicTemplateClassPackExpansion<TFirst,TTypes...>::CVariadicTemplateClassPackExpansion(void)
	: MField(), MFields()
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! EXPANSION PACK sa robi pre celu EXPRESSION, ktora predchadza OPERATOR [...].
template<typename TFirst, typename... TTypes>
CVariadicTemplateClassPackExpansion<TFirst,TTypes...>::CVariadicTemplateClassPackExpansion(TFirst* First, TTypes*... Types)
	: MField(First), MFields(Types...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
CVariadicTemplateClassPackExpansion<TFirst,TTypes...>::~CVariadicTemplateClassPackExpansion(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
void CVariadicTemplateClassPackExpansion<TFirst,TTypes...>::PrintInternal(const std::wstring& Text, size_t Index) const
{
	std::wcout << Text << L" - PARAMETER [" << Index << L"] - TYPE [" << GetTypeInfoName<TFirst>() << L"] - VALUE [" << *MField << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		MFields.PrintInternal(Text,Index+1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFirst, typename... TTypes>
void CVariadicTemplateClassPackExpansion<TFirst,TTypes...>::Print(const std::wstring& Text) const
{
	PrintInternal(Text,1);
}
//----------------------------------------------------------------------------------------------------------------------