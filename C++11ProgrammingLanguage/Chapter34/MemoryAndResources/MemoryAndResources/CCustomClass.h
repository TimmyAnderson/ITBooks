//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <cstdio>
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
class CCustomClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const
		{
			return(MValue);
		}

	public:
		CCustomClass(void)
			: MValue(L"")
		{
			wprintf_s(L"CONSTRUCTOR [CCustomClass] with VALUE [%ls] CALLED !\n",MValue.c_str());
		}

		CCustomClass(std::wstring Value)
			: MValue(Value)
		{
			wprintf_s(L"CONSTRUCTOR [CCustomClass] with VALUE [%ls] CALLED !\n",MValue.c_str());
		}

		CCustomClass(std::wstring Value, bool)
			: MValue(Value)
		{
			wprintf_s(L"!!!!! CONSTRUCTOR [CCustomClass] with VALUE [%ls] will THROW EXCEPTION !\n",MValue.c_str());

			throw(CException(L"CONSTRUCTOR [CCustomClass] has THROWN EXCEPTION !"));
		}

		~CCustomClass(void)
		{
			wprintf_s(L"DESTRUCTOR [CCustomClass] with VALUE [%ls] CALLED !\n",MValue.c_str());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------