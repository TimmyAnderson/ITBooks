//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "CBaseClass.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedClass : public CBaseClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CDerivedClass(std::wstring Value)
			: MValue(Value)
		{
			wprintf_s(L"CONSTRUCTOR [CDerivedClass] with VALUE [%ls] CALLED !\n",MValue.c_str());
		}

		virtual ~CDerivedClass(void)
		{
			wprintf_s(L"DESTRUCTOR [CDerivedClass] with VALUE [%ls] CALLED !\n",MValue.c_str());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------