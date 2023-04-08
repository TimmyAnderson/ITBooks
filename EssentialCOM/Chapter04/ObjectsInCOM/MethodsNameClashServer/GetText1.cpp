//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "GetText1.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText1::GetText(int BufferSize, wchar_t** Text)
{
	// !!! Vola ABSTRACT METHOD.
	return(GetText1(BufferSize,Text));
}
//------------------------------------------------------------------------------------------------------