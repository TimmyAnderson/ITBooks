#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPFacadePatternAdapterBase.h"
#include "CString.h"
#include "CCRTPFacadePatternAdapterInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCRTPFacadePatternAdapterDerived final : public CCRTPFacadePatternAdapterBase<CCRTPFacadePatternAdapterDerived>
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! INTERFACE CLASS je oznaceny ako FRIEND CLASS, aby mohol pristupovat k PRIVATE METHODS PRIVATE INTERFACE.
	friend class CCRTPFacadePatternAdapterInterface;

	private:
		CString													MPrefix;
		CString													MValue;
		// !!!!! Simuluje ADAPTER PATTERN, ked sa pridaju dodatocne DATA, ktore sa pouzivaju na modifikovanie PRIVATE INTERFACE.
		int														MIntValue;

	private:
		// !!!!! Toto su METHODS, ktore MUSI DERIVED CLASS implementovat, aby splnila INTERFACE, ktory vyuziva BASE CLASS.
		// !!!!! INTERFACE je oznaceny ako PRIVATE.
		CString GetPrefix(void) const;
		CString GetValue(void) const;

	public:
		CCRTPFacadePatternAdapterDerived(const CString& Prefix, const CString& Value, int IntValue);
		virtual ~CCRTPFacadePatternAdapterDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------