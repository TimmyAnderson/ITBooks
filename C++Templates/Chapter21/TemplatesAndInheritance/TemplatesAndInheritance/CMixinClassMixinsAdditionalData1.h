//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! ADDITIONAL CLASS sluziaca na rozsirenie MIXIN CLASS. CLASS NIE je DERIVED z MIXIN CLASS.
// !!!!! ADDITIONAL CLASS v MIXIN PATTERN predstavuje BASE CLASS, ktoru dedi MIXIN (DERIVED) CLASS.
class CMixinClassMixinsAdditionalData1
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MValueString1;
		CString													MValueString2;

	public:
		const CString& GetValueString1(void) const;
		void SetValueString1(const CString& Value);
		const CString& GetValueString2(void) const;
		void SetValueString2(const CString& Value);

	public:
		CMixinClassMixinsAdditionalData1(void);
		virtual ~CMixinClassMixinsAdditionalData1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------