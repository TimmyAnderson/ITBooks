//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "MethodsNameClashServer_h.h"
//------------------------------------------------------------------------------------------------------
class CGetText1 : public IGetText1
{
	public:
		// !!! Implementuje METHOD COM INTERFACE.
        virtual HRESULT STDMETHODCALLTYPE GetText(int BufferSize, wchar_t** Text);

	public:
		// !!! Doplnim ABSTRACT METHOD, ktora je volana z GetText().
        virtual HRESULT STDMETHODCALLTYPE GetText1(int BufferSize, wchar_t** Text)=0;
};
//------------------------------------------------------------------------------------------------------