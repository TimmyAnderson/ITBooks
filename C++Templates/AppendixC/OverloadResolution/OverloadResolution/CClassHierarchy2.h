//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CClassHierarchy1.h"
//----------------------------------------------------------------------------------------------------------------------
class CClassHierarchy2 : public CClassHierarchy1
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CClassHierarchy2(const std::wstring& Value);
		virtual ~CClassHierarchy2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------