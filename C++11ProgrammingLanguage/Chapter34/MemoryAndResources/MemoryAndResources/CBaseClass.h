//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBaseClass
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual const std::wstring& GetValue(void) const=0;

	public:
		CBaseClass(void)
		{
			wprintf_s(L"CONSTRUCTOR [CBaseClass] CALLED !\n");
		}

		virtual ~CBaseClass(void)
		{
			wprintf_s(L"DESTRUCTOR [CBaseClass] CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------