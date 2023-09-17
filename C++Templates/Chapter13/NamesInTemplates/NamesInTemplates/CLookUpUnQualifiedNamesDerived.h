//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CLookUpUnQualifiedNamesBase.h"
//----------------------------------------------------------------------------------------------------------------------
class CLookUpUnQualifiedNamesDerived final : public CLookUpUnQualifiedNamesBase
{
//----------------------------------------------------------------------------------------------------------------------
	protected:
		CString													MDerivedField;
		CString													MSharedField;

	public:
		void TestClassMethodLookUpUnQualifiedNames1(void) const;
		void TestClassMethodLookUpUnQualifiedNames2(const CString& BaseField, const CString& DerivedField, const CString& SharedField) const;

	public:
		CLookUpUnQualifiedNamesDerived(const CString& BaseField, const CString& SharedFieldBase, const CString& DerivedField, const CString& SharedFieldDerived);
		virtual ~CLookUpUnQualifiedNamesDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------