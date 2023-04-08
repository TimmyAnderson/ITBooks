//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "NameBase.h"
//-------------------------------------------------------------------------------------------------------
class CNameDerived : public CNameBase
{
	public:
		virtual std::wstring DerivedClassGetFullName(void);

	public:
		virtual std::wstring VirtualMethod(void);

	public:
		CNameDerived(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CNameDerived(void);
};
//-------------------------------------------------------------------------------------------------------