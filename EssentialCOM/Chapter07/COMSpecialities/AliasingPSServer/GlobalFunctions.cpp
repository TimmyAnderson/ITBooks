//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "..\AliasingServer\AliasingServer_h.h"
//------------------------------------------------------------------------------------------------------
// !!! PROTOTYPE tejto FUNCTION je uvedeny v [AliasingServer_h.h].
HRESULT STDMETHODCALLTYPE IAliasingTest_FillArray_Proxy(IAliasingTest* This, int ArraySize, int* ArrayLength, int* Array)
{
	wprintf(L"!!! SERVER: METHOD IAliasingTest_FillArray_Proxy() was CALLED !\n");

	// !!!!! Tu sa mozu PRISPOSOBIT PARAMETERS tak, aby boli PRENOSITELNE z LOCAL do REMOTE METHOD.

	// !!! FUNCTION IAliasingTest_RemoteFillArray_Proxy() je definovana v 'AliasingServer\AliasingServer_h.h'.
	HRESULT														HR=IAliasingTest_RemoteFillArray_Proxy(This,ArraySize,ArrayLength,Array);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
// !!! PROTOTYPE tejto FUNCTION je uvedeny v [AliasingServer_h.h].
HRESULT STDMETHODCALLTYPE IAliasingTest_FillArray_Stub(IAliasingTest* This, int ArraySize, int *ArrayLength, int* Array)
{
	wprintf(L"!!! SERVER: METHOD IAliasingTest_FillArray_Proxy() was CALLED !\n");

	// !!!!! Tu sa mozu PRISPOSOBIT PARAMETERS tak, aby boli PRENOSITELNE z REMOTE METHOD do LOCAL.

	// !!!!! Vola sa METHOD COM INTERFACE.
	HRESULT														HR=This->FillArray(ArraySize,ArrayLength,Array);

	return(HR);
}
//------------------------------------------------------------------------------------------------------