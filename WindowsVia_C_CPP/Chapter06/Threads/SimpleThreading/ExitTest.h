#pragma once
//------------------------------------------------------------------------------
#include <strsafe.h>
#include <stdio.h>
//------------------------------------------------------------------------------
class CExitTest
{
private:
		wchar_t			MBuffer[1000];

	public:
		CExitTest(wchar_t* Buffer)
		{
			StringCchCopy(MBuffer,_countof(MBuffer),Buffer);

			wprintf_s(L"CONSTRUCTOR - %s !\n",MBuffer);
		}

		~CExitTest(void)
		{
			wprintf_s(L"DESTRUCTOR - %s !\n",MBuffer);
		}
};
//------------------------------------------------------------------------------