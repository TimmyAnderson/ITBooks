//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "GetText2.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText2::GetText(int BufferSize, wchar_t** Text)
{
	// !!! Vola ABSTRACT METHOD.
	return(GetText2(BufferSize,Text));
}
//------------------------------------------------------------------------------------------------------