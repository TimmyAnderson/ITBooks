//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CTemplateClassDeductionCopyConstruction final
{
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
	template<typename... TLocalTypes>
	friend class CTemplateClassDeductionCopyConstruction;
#else
	template<typename TLocalType, typename... TLocalTypes>
	friend void CTemplateClassDeductionCopyConstruction<TLocalTypes...>::PrintTypesInternal(size_t Index, std::wstringstream& Stream) const;
#endif

	private:
		template<typename TLocalType, typename... TLocalTypes>
		void PrintTypesInternal(size_t Index, std::wstringstream& Stream) const;

	public:
		void PrintTypes(void) const;

	public:
		CTemplateClassDeductionCopyConstruction(TTypes...);
		CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&);
		virtual ~CTemplateClassDeductionCopyConstruction(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CTemplateClassDeductionCopyConstruction<TTypes...>::CTemplateClassDeductionCopyConstruction(TTypes...)
{
	std::wcout << L"CONSTRUCTOR [TTypes...] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CTemplateClassDeductionCopyConstruction<TTypes...>::CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&)
{
	std::wcout << L"CONSTRUCTOR [const CTemplateClassDeductionCopyConstruction<TTypes...>&] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CTemplateClassDeductionCopyConstruction<TTypes...>::~CTemplateClassDeductionCopyConstruction(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TLocalType, typename... TLocalTypes>
void CTemplateClassDeductionCopyConstruction<TTypes...>::PrintTypesInternal(size_t Index, std::wstringstream& Stream) const
{
	std::wcout << L"\tTYPES - INDEX [" << Index << L"] TYPE [" << GetTypeInfoName<TLocalType>() << L"]." << std::endl;
	
	if constexpr (sizeof...(TLocalTypes)>0)
	{
		PrintTypesInternal<TLocalTypes...>(Index+1,Stream);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void CTemplateClassDeductionCopyConstruction<TTypes...>::PrintTypes(void) const
{
	std::wstringstream											Stream;

	PrintTypesInternal<TTypes...>(1,Stream);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename... TTypes>
CTemplateClassDeductionCopyConstruction(TTypes...) -> CTemplateClassDeductionCopyConstruction<TTypes...>;
//----------------------------------------------------------------------------------------------------------------------
// !!! DEDUCTION GUIDE.
template<typename... TTypes>
CTemplateClassDeductionCopyConstruction(const CTemplateClassDeductionCopyConstruction<TTypes...>&) -> CTemplateClassDeductionCopyConstruction<TTypes...>;
//----------------------------------------------------------------------------------------------------------------------