//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
typedef void (*FMyFunctionPointer)(wchar_t*,int);
//-------------------------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) void PrintMessage(wchar_t* Message)
{
	wprintf_s(L"DLL LIBRARY - MESSAGE [%s] !\n",Message);
}
//-------------------------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) void ExecuteCallback(FMyFunctionPointer MyFunctionPointer)
{
	wchar_t													Message[]=L"STRING FROM CALLBACK";
	int														Length=_countof(Message);

	MyFunctionPointer(L"STRING FROM CALLBACK",Length);
}
//-------------------------------------------------------------------------------------------------------