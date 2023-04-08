//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "GetText1.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "CompositionObject.h"
//------------------------------------------------------------------------------------------------------
CGetText1::CGetText1(void)
	: MCompositionObject(NULL)
{
}
//------------------------------------------------------------------------------------------------------
CGetText1::~CGetText1(void)
{
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText1::GetText(int BufferSize, wchar_t** Text)
{
	CLock														Lock(MCS);

	wcscpy_s(*Text,BufferSize,L"Text 111 !");
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CGetText1::QueryInterface(REFIID RIID, void** PointerToObject)
{
	// !!! METHOD QueryInterface() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->QueryInterface(RIID,PointerToObject));
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CGetText1::AddRef(void)
{
	// !!! METHOD AddRef() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->AddRef());
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CGetText1::Release(void)
{
	// !!! METHOD Release() robi FORWARDING do COM OBJECT.
	return(MCompositionObject->Release());
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void CGetText1::Initialize(CCompositionObject* CompositionObject)
{
	MCompositionObject=CompositionObject;
}
//------------------------------------------------------------------------------------------------------