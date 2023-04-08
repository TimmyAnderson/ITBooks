#include "stdafx.h"
#include "MySimpleDLL.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// !!!!! MUSI BYT extern "C", aby meno funkcie nebolo MANGLED.
extern "C" MYSIMPLEDLL_API void MySimplePrintFunction(wchar_t* Text)
{
	wprintf_s(L"%s\n",Text);
}
//-------------------------------------------------------------------------------------------------------