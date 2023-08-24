//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonTemplateMembersClassOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! NON-TEMPLATE INNER CLASS.
		class CNonTemplateMembersClassInner;

	public:
		// !!! NON-TEMPLATE STATIC FIELD na CLASS SCOPE.
		static double											MNonTemplateStaticFieldOnClassScopeOutOfClass;

	private:
		TType													MField1;
		CNonTemplateMembersClassInner							MField2;

	public:
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		TType GetField1(void) const noexcept;
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const CNonTemplateMembersClassInner& GetField2(void) const noexcept;

	public:
		// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE.
		CNonTemplateMembersClassOuter(TType Value1, CNonTemplateMembersClassInner Value2);
		// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE.
		virtual ~CNonTemplateMembersClassOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassOuter(TType Value1, CNonTemplateMembersClassInner Value2)
	: MField1(Value1), MField2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
CNonTemplateMembersClassOuter<TType>::~CNonTemplateMembersClassOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE METHOD na CLASS SCOPE definovana OUT OF CLASS.
template<typename TType>
TType CNonTemplateMembersClassOuter<TType>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE METHOD na CLASS SCOPE definovana OUT OF CLASS.
template<typename TType>
const typename CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassInner& CNonTemplateMembersClassOuter<TType>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE STATIC FIELD na CLASS SCOPE definovany OUT OF CLASS.
template<typename TType>
double															CNonTemplateMembersClassOuter<TType>::MNonTemplateStaticFieldOnClassScopeOutOfClass=123.456;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE INNER CLASS definovana OUT OF CLASS.
template<typename TType>
class CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassInner
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const noexcept;

	public:
		CNonTemplateMembersClassInner(int Value);
		virtual ~CNonTemplateMembersClassInner(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE INNER CLASS METHOD definovana OUT OF CLASS.
template<typename TType>
CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassInner::CNonTemplateMembersClassInner(int Value)
	: MField(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!! NON-TEMPLATE INNER CLASS METHOD definovana OUT OF CLASS.
template<typename TType>
CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassInner::~CNonTemplateMembersClassInner(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
int CNonTemplateMembersClassOuter<TType>::CNonTemplateMembersClassInner::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------