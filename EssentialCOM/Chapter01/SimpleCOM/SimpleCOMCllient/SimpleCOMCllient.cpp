//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <Windows.h>
#include <conio.h>
#include <crtdbg.h>
#include "IMySimpleInterface.h"
#include "Debug.h"
//------------------------------------------------------------------------------------------------------
const CLSID CLSID_SimpleCOM={0xfd021f4d, 0x5841, 0x4d44, 0x96, 0xe3, 0xe9, 0xc4, 0x1d, 0xa5, 0x47, 0xf};
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	CoInitialize(NULL);

	IMySimpleInterface*											Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_SimpleCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IMySimpleInterface),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		int														Value1;
		int														Value2;

		Interface->GetInt(&Value1);

		wprintf_s(L"Value: [%d] !\n",Value1);

		Interface->SetInt(20);

		Interface->GetInt(&Value2);

		wprintf_s(L"Value: [%d] !\n",Value2);

		BSTR													String1;

		Interface->GetString(&String1);

		wprintf_s(L"Value: [%s] !\n",String1);

		Interface->SetString(L"Jenny Thompson");

		BSTR													String2;

		Interface->GetString(&String2);

		wprintf_s(L"Value: [%s] !\n",String2);

		Interface->Release();
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}

	CoUninitialize();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------