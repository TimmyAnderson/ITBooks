//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CStructuredBindingClassBase1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CStructuredBindingClassDerived1 final : public CStructuredBindingClassBase1
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CStructuredBindingClassDerived1(const CString& PublicFieldBase1, int PublicFieldBase2);
		virtual ~CStructuredBindingClassDerived1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------