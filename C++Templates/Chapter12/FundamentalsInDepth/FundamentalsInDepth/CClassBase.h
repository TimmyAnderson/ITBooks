//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
class CClassBase
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FIELD je UMYSELNE PUBLIC.
	public:
		CString													MField;

	public:
		const CString& GetField(void) const noexcept;

	public:
		CClassBase(const CString& Field);
		virtual ~CClassBase(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------