#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPFacadePatternBase.h"
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCRTPFacadePatternDerived final : public CCRTPFacadePatternBase<CCRTPFacadePatternDerived>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MPrefix;
		CString													MValue;

	public:
		// !!!!! Toto su METHODS, ktore MUSI DERIVED CLASS implementovat, aby splnila INTERFACE, ktory vyuziva BASE CLASS.
		CString GetPrefix(void) const;
		CString GetValue(void) const;

	public:
		// !!!!! Toto su METHODS, ktore MUSI DERIVED CLASS implementovat, aby splnila INTERFACE, ktory vyuziva BASE CLASS.
		CString GetPrefix(void);
		CString GetValue(void);

	public:
		CCRTPFacadePatternDerived(const CString& Prefix, const CString& Value);
		virtual ~CCRTPFacadePatternDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------