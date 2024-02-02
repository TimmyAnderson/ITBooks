#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPFacadePatternHiddenInterfaceBase.h"
#include "CString.h"
#include "CCRTPFacadePatternHiddenInterfaceInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCRTPFacadePatternHiddenInterfaceDerived final : public CCRTPFacadePatternHiddenInterfaceBase<CCRTPFacadePatternHiddenInterfaceDerived>
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! INTERFACE CLASS je oznaceny ako FRIEND CLASS, aby mohol pristupovat k PRIVATE METHODS PRIVATE INTERFACE.
	friend class CCRTPFacadePatternHiddenInterfaceInterface;

	private:
		CString													MPrefix;
		CString													MValue;

	private:
		// !!!!! Toto su METHODS, ktore MUSI DERIVED CLASS implementovat, aby splnila INTERFACE, ktory vyuziva BASE CLASS.
		// !!!!! INTERFACE je oznaceny ako PRIVATE.
		CString GetPrefix(void) const;
		CString GetValue(void) const;

	public:
		CCRTPFacadePatternHiddenInterfaceDerived(const CString& Prefix, const CString& Value);
		virtual ~CCRTPFacadePatternHiddenInterfaceDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------