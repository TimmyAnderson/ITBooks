//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingClassBase1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CStructuredBindingClassDerived2 final : public CStructuredBindingClassBase1
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CString													MPublicFieldDerived1;
		int														MPublicFieldDerived2;

	public:
		const CString& GetPublicFieldDerived1(void) const noexcept;
		int GetPublicFieldDerived2(void) const noexcept;

	public:
		CStructuredBindingClassDerived2(const CString& PublicFieldDerived1, int PublicFieldDerived2, const CString& PublicFieldBase1, int PublicFieldBase2);
		virtual ~CStructuredBindingClassDerived2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------