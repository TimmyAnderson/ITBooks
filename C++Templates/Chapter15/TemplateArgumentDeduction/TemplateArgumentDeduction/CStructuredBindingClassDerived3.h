//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingClassBase1.h"
#include "CStructuredBindingClassBase2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CStructuredBindingClassDerived3 final : public CStructuredBindingClassBase1, public CStructuredBindingClassBase2
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CString													MPublicFieldDerived1;
		int														MPublicFieldDerived2;

	public:
		const CString& GetPublicFieldDerived1(void) const noexcept;
		int GetPublicFieldDerived2(void) const noexcept;

	public:
		CStructuredBindingClassDerived3(const CString& PublicFieldDerived1, int PublicFieldDerived2, const CString& PublicFieldBase11, int PublicFieldBase12, double PublicFieldBase21, const CString& PublicFieldBase22);
		virtual ~CStructuredBindingClassDerived3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------