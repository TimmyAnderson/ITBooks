//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS na NAMESPACE SCOPE.
template<typename TType>
class CTemplatesOnClassScopeOutOfClassOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! TEMPLATE CLASS na CLASS SCOPE. Je tu iba DECLARATION. DEFINITION je OUT OF CLASS.
		template<typename TInnerType>
		class CTemplatesOnClassScopeOutOfClassInner;

	public:
		// !!! TEMPLATE STATIC FIELD na CLASS SCOPE.
		template<typename TInnerType>
		static TInnerType										MTemplateStaticFieldOnClassScopeOutOfClass;

	private:
		TType													MField1;
		CTemplatesOnClassScopeOutOfClassInner<TType>			MField2;

	public:
		// !!! TEMPLATE METHOD na CLASS SCOPE.
		template<typename TInnerType>
		void TemplateMetodOnClassScopeOutOfClass(TType Value1, TInnerType Value2) const;

	public:
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const TType& GetField1(void) const noexcept;
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const CTemplatesOnClassScopeOutOfClassInner<TType>& GetField2(void) const noexcept;

	public:
		// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE.
		CTemplatesOnClassScopeOutOfClassOuter(TType Value1, CTemplatesOnClassScopeOutOfClassInner<TType> Value2);
		// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE.
		virtual ~CTemplatesOnClassScopeOutOfClassOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassOuter(TType Value1, CTemplatesOnClassScopeOutOfClassInner<TType> Value2)
	: MField1(Value1), MField2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
CTemplatesOnClassScopeOutOfClassOuter<TType>::~CTemplatesOnClassScopeOutOfClassOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE METHOD na CLASS SCOPE definovana OUT OF CLASS.
template<typename TType>
const TType& CTemplatesOnClassScopeOutOfClassOuter<TType>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE METHOD na CLASS SCOPE definovana OUT OF CLASS.
template<typename TType>
const typename CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassInner<TType>& CTemplatesOnClassScopeOutOfClassOuter<TType>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE STATIC FIELD na CLASS SCOPE.
template<typename TType>
template<typename TInnerType>
TInnerType														CTemplatesOnClassScopeOutOfClassOuter<TType>::MTemplateStaticFieldOnClassScopeOutOfClass{};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE METHOD na CLASS SCOPE definovana OUT OF CLASS.
template<typename TType>
template<typename TInnerType>
void CTemplatesOnClassScopeOutOfClassOuter<TType>::TemplateMetodOnClassScopeOutOfClass(TType Value1, TInnerType Value2) const
{
	std::wcout << L"TEMPLATE METHOD ON CLASS SCOPE OUT OF CLASS - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
template<typename TInnerType>
class CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassInner final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TInnerType												MField;

	public:
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const TInnerType& GetField(void) const noexcept;

	public:
		// !!! TEMPLATE CONSTRUCTOR na CLASS SCOPE.
		CTemplatesOnClassScopeOutOfClassInner(TInnerType Value);

		// !!! TEMPLATE DESTRUCTOR na CLASS SCOPE.
		virtual ~CTemplatesOnClassScopeOutOfClassInner(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CONSTRUCTOR na CLASS SCOPE pre INNER TEMPLATE CLASS definovany OUT OF CLASS.
// !!! Ako prvy KEYWORD [template] musi byt pouzity OUTERMOST TEMPLATE.
template<typename TType>
template<typename TInnerType>
CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassInner<TInnerType>::CTemplatesOnClassScopeOutOfClassInner(TInnerType Value)
	: MField(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE DESTRUCTOR na CLASS SCOPE pre INNER TEMPLATE CLASS definovany OUT OF CLASS.
// !!! Ako prvy KEYWORD [template] musi byt pouzity OUTERMOST TEMPLATE.
template<typename TType>
template<typename TInnerType>
CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassInner<TInnerType>::~CTemplatesOnClassScopeOutOfClassInner(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE METHOD na CLASS SCOPE pre INNER TEMPLATE CLASS definovana OUT OF CLASS.
// !!! Ako prvy KEYWORD [template] musi byt pouzity OUTERMOST TEMPLATE.
template<typename TType>
template<typename TInnerType>
const TInnerType& CTemplatesOnClassScopeOutOfClassOuter<TType>::CTemplatesOnClassScopeOutOfClassInner<TInnerType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------