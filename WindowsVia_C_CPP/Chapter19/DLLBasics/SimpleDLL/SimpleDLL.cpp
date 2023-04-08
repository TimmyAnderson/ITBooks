#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <StrSafe.h>
#include <stdlib.h>
#include "SimpleDLL.h"
//------------------------------------------------------------------------------
SIMPLEDLL_API int					DLL_SomeValue=0;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CSimpleDLL::CSimpleDLL()
{
	wprintf_s(L"CSimpleDLL CONSTRUCTOR CALLED !\n");
}
//------------------------------------------------------------------------------
CSimpleDLL::~CSimpleDLL()
{
	wprintf_s(L"CSimpleDLL DESTRUCTOR CALLED !\n");
}
//------------------------------------------------------------------------------
wchar_t* CSimpleDLL::GetBuffer(void)
{
	return(MBuffer);
}
//------------------------------------------------------------------------------
void CSimpleDLL::SetBuffer(wchar_t* Text)
{
	StringCchCopy(MBuffer,_countof(MBuffer),Text);
}
//------------------------------------------------------------------------------