//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <Windows.h>
#include <conio.h>
#include <crtdbg.h>
#include "Debug.h"
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	CoInitialize(NULL);

	GUID														GUID1;
	GUID														GUID2;
	GUID														GUID3;

	CoCreateGuid(&GUID1);
	CoCreateGuid(&GUID2);

	CopyMemory(&GUID3,&GUID1,sizeof(GUID));

	wprintf_s(L"GUID1 [%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x] !\n",GUID1.Data1,GUID1.Data2,GUID1.Data3,GUID1.Data4[0],GUID1.Data4[1],GUID1.Data4[2],GUID1.Data4[3],GUID1.Data4[4],GUID1.Data4[5],GUID1.Data4[6],GUID1.Data4[7]);
	wprintf_s(L"GUID2 [%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x] !\n",GUID2.Data1,GUID2.Data2,GUID2.Data3,GUID2.Data4[0],GUID2.Data4[1],GUID2.Data4[2],GUID2.Data4[3],GUID2.Data4[4],GUID2.Data4[5],GUID2.Data4[6],GUID2.Data4[7]);
	wprintf_s(L"GUID3 [%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x] !\n",GUID3.Data1,GUID3.Data2,GUID3.Data3,GUID3.Data4[0],GUID3.Data4[1],GUID3.Data4[2],GUID3.Data4[3],GUID3.Data4[4],GUID3.Data4[5],GUID3.Data4[6],GUID3.Data4[7]);

	// !!! Volaju sa PRETAZENE OPERATORS.
	wprintf_s(L"GUID1==GUID2 [%d] !\n",GUID1==GUID2);
	wprintf_s(L"GUID1==GUID3 [%d] !\n",GUID1==GUID3);
	wprintf_s(L"GUID1!=GUID2 [%d] !\n",GUID1!=GUID2);
	wprintf_s(L"GUID1!=GUID3 [%d] !\n",GUID1!=GUID3);

	wprintf_s(L"IsEqualGUID(GUID1,GUID2) [%d] !\n",IsEqualGUID(GUID1,GUID2));
	wprintf_s(L"IsEqualGUID(GUID1,GUID3) [%d] !\n",IsEqualGUID(GUID1,GUID3));
	

	CoUninitialize();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------