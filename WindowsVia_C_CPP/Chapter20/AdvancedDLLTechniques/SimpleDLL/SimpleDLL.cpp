#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <StrSafe.h>
#include <stdlib.h>
#include "SimpleDLL.h"
//------------------------------------------------------------------------------
SIMPLEDLL_API void DLL_ConvertToUpper(wchar_t* Text)
{
	wprintf_s(L"DLL_ConvertToUpper() CALLED !\n");

	while(*Text!='\0')
	{
		if (*Text>='a' && *Text<='z')
			*Text=*Text-'a'+'A';

		Text++;
	}
}
//------------------------------------------------------------------------------
SIMPLEDLL_API void DLL_ConvertToLower(wchar_t* Text)
{
	wprintf_s(L"DLL_ConvertToLower() CALLED !\n");

	while(*Text!='\0')
	{
		if (*Text>='A' && *Text<='Z')
			*Text=*Text-'A'+'a';

		Text++;
	}
}
//------------------------------------------------------------------------------