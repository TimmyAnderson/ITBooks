//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION, ale nie DEFINITION PRIMARY TEMPLATE.
template<typename TType1, typename TType2, template<typename,typename> typename... TTypes>
class CTemplateClassPackTemplateTemplateParameters;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre 0 PARAMETERS.
template<typename TType1, typename TType2>
class CTemplateClassPackTemplateTemplateParameters<TType1,TType2> final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre 1-N PARAMETERS.
template<typename TType1, typename TType2, template<typename,typename> typename TFirst,template<typename,typename> typename... TTypes>
class CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TFirst,TTypes...> final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! V TEMPLATE CLASS pre 'M' PARAMETERS spravi FRIEND TEMPLATE CLASS pre 'N' PARAMETERS.
	template<typename TLocalType1, typename TLocalType2, template<typename,typename> typename... TLocalTypes>
	friend class CTemplateClassPackTemplateTemplateParameters;

	private:
		TFirst<TType1,TType2>									MField;
		CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TTypes...>	MFields;

	private:
		void PrintInternal(size_t Index) const;

	public:
		void Print(void) const;

	public:
		CTemplateClassPackTemplateTemplateParameters(TFirst<TType1,TType2> First, TTypes<TType1,TType2>... Values);
		virtual ~CTemplateClassPackTemplateTemplateParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TFirst,template<typename,typename> typename... TTypes>
CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TFirst,TTypes...>::CTemplateClassPackTemplateTemplateParameters(TFirst<TType1,TType2> First, TTypes<TType1,TType2>... Values)
	: MField(First), MFields(Values...)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TFirst,template<typename,typename> typename... TTypes>
CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TFirst,TTypes...>::~CTemplateClassPackTemplateTemplateParameters(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TFirst,template<typename,typename> typename... TTypes>
void CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TFirst,TTypes...>::PrintInternal(size_t Index) const
{
	std::wcout << L"TEMPLATE TYPE PARAMETERS - PARAMETER [" << Index << L"] - VALUE [" << MField << L"]." << std::endl;

	if constexpr (sizeof...(TTypes)>0)
	{
		MFields.PrintInternal(Index+1);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TFirst,template<typename,typename> typename... TTypes>
void CTemplateClassPackTemplateTemplateParameters<TType1,TType2,TFirst,TTypes...>::Print(void) const
{
	PrintInternal(1);
}
//----------------------------------------------------------------------------------------------------------------------