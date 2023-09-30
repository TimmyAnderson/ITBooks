//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
class CTemplateArgumentEquivalence final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MField;

	public:
		CTemplateArgumentEquivalence<TType,VALUE>& operator=(const CTemplateArgumentEquivalence<TType,VALUE>& Other);

	public:
		std::wstring ToString(void) const;

	public:
		CTemplateArgumentEquivalence(TType Field);
		CTemplateArgumentEquivalence(const CTemplateArgumentEquivalence<TType,VALUE>& Other);
		virtual ~CTemplateArgumentEquivalence(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
CTemplateArgumentEquivalence<TType,VALUE>::CTemplateArgumentEquivalence(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
CTemplateArgumentEquivalence<TType,VALUE>::CTemplateArgumentEquivalence(const CTemplateArgumentEquivalence<TType,VALUE>& Other)
	: MField(Other.MField)
{
	std::wcout << L"COPY CONSTRUCTOR CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
CTemplateArgumentEquivalence<TType,VALUE>::~CTemplateArgumentEquivalence(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
CTemplateArgumentEquivalence<TType,VALUE>& CTemplateArgumentEquivalence<TType,VALUE>::operator=(const CTemplateArgumentEquivalence<TType,VALUE>& Other)
{
	MField=Other.MField;

	std::wcout << L"COPY OPERATOR [OPERATOR=] CALLED." << std::endl;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int VALUE>
std::wstring CTemplateArgumentEquivalence<TType,VALUE>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << L"TEMPLATE - FIELD [" << MField << L"] VALUE [" << VALUE << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------