//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "GetText2.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "CompositionObject.h"
//------------------------------------------------------------------------------------------------------
CGetText2::CGetText2(void)
	: MCompositionObject(NULL)
{
}
//------------------------------------------------------------------------------------------------------
CGetText2::~CGetText2(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText2::GetText(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 222 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText2::QueryInterface(REFIID RIID, void** PointerToObject)
{
	// !!! METHOD QueryInterface() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->QueryInterface(RIID,PointerToObject));
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CGetText2::AddRef(void)
{
	// !!! METHOD AddRef() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->AddRef());
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CGetText2::Release(void)
{
	// !!! METHOD Release() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->Release());
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void CGetText2::Initialize(CCompositionObject* CompositionObject)
{
	MCompositionObject=CompositionObject;
}
//------------------------------------------------------------------------------------------------------