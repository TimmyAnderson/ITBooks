//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
class CClassWithMembers
{
//-------------------------------------------------------------------------------------------------------
	public:
		int														MValue;

	public:
		void PrintValue(const wchar_t* Prefix)
		{
			wprintf_s(L"%ls [%d] !\n",Prefix,MValue);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------