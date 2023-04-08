#include <Windows.h>
#include "MyUnmanagedLibrary.h"
#include <stdio.h>
#include <process.h>
//-------------------------------------------------------------------------------------------------------
// Je to iba priklad a samozrejme NIE JE TRHEAD SAFE.
MyCALLBACK														GCallbackPointer;
MyPTRCALLBACK													GPTRCallbackPointer;
MyPTRCALLBACKWITHWRITE											GPTRCallbackPointerWithWrite;
wchar_t*														GParam;
void*															GCallbackID;
wchar_t*														GDataBuffer;
int																GDataBufferSize;
//-------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadMethod(void* Param)
{
	wprintf_s(L"NATIVE CODE - WORKER THREAD - BEFORE SLEEP - GParam: [%s] !\n",GParam);

	Sleep(3*1000);

	wprintf_s(L"NATIVE CODE - WORKER THREAD - AFTER SLEEP - GParam: [%s] !\n",GParam);

	GCallbackPointer(GParam);

	wprintf_s(L"NATIVE CODE - WORKER THREAD - AFTER CALLBACK - GParam : [%s] !\n",GParam);

	return(0);
}
//-------------------------------------------------------------------------------------------------------
unsigned int __stdcall PTRThreadMethod(void* Param)
{
	wprintf_s(L"NATIVE CODE - !!! WORKER THREAD - BEFORE SLEEP !\n");

	Sleep(3*1000);

	wprintf_s(L"NATIVE CODE - !!! WORKER THREAD - AFTER SLEEP !\n");

	GPTRCallbackPointer(GCallbackID);

	wprintf_s(L"NATIVE CODE - !!! WORKER THREAD - AFTER CALLBACK !\n");

	return(0);
}
//-------------------------------------------------------------------------------------------------------
unsigned int __stdcall PTRThreadWithWriteDataMethod(void* Param)
{
	wprintf_s(L"NATIVE CODE - WORKER THREAD - BEFORE SLEEP !\n");

	Sleep(3*1000);

	wprintf_s(L"NATIVE CODE - WORKER THREAD - AFTER SLEEP !\n");

	wprintf_s(L"NATIVE CODE - WORKER THREAD DataBuffer - BEFORE CHANGE: [%s] !\n",GDataBuffer);

	// !!! Zapisu sa data do PINNED BUFFER, ktory poslat MANAGED CODE.
	wcscpy_s(GDataBuffer,GDataBufferSize,L"Timmy Anderson");

	wprintf_s(L"NATIVE CODE - WORKER THREAD DataBuffer - AFTER CHANGE: [%s] !\n",GDataBuffer);

	wprintf_s(L"NATIVE CODE - GCallbackID: [%p] !\n",GCallbackID);
	wprintf_s(L"NATIVE CODE - GDataBuffer: [%s] !\n",GDataBuffer);
	wprintf_s(L"NATIVE CODE - GDataBufferSize: [%d] !\n",GDataBufferSize);
	wprintf_s(L"NATIVE CODE - GPTRCallbackPointerWithWrite: [%p] !\n",GPTRCallbackPointerWithWrite);

	GPTRCallbackPointerWithWrite(GCallbackID,GDataBuffer);

	wprintf_s(L"NATIVE CODE - WORKER THREAD - AFTER CALLBACK !\n");

	return(0);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
MYUNMANAGEDLIBRARY_API int PrintStringAndGetLength(const wchar_t* String)
{
	wprintf_s(L"NATIVE CODE - String from MANAGED CODE: [%s] !\n",String);

	int															Size=(int) wcslen(String);
	
	return(Size);
}
//-------------------------------------------------------------------------------------------------------
MYUNMANAGEDLIBRARY_API int FillString(wchar_t* StringToFill, int Size)
{
	wchar_t*													TextToFill=L"Jennifer Thompson";
	int															OutSize=(int) wcslen(TextToFill);

	wcscpy_s(StringToFill,Size,TextToFill);

	wprintf_s(L"NATIVE CODE - String from UNMANAGED CODE: [%s] !\n",StringToFill);

	return(OutSize);
}
//-------------------------------------------------------------------------------------------------------
MYUNMANAGEDLIBRARY_API void DoCallback(MyCALLBACK CallbackPointer, wchar_t* Param)
{
	GCallbackPointer=CallbackPointer;
	GParam=Param;

	//GCallbackPointer(GParam);

	wprintf_s(L"NATIVE CODE - GParam in PRIMARY THREAD: [%s] !\n",GParam);

	HANDLE														HThread=(HANDLE)_beginthreadex(NULL,0,&ThreadMethod,NULL,0,NULL);

	CloseHandle(HThread);
}
//-------------------------------------------------------------------------------------------------------
// Posledny PARAMETER sluzi ako ID pre MANAGED CODE.
MYUNMANAGEDLIBRARY_API void DoCallbackAsPTR(MyPTRCALLBACK CallbackPointer, void* CallbackID)
{
	GPTRCallbackPointer=CallbackPointer;
	GCallbackID=CallbackID;

	// !!! Kedze CallbackID prenesiem ako GCHandleType.Normal, tak k NEMU NESMIEM v NATIVE CODE PRISTUPOVAT, IBA ho ZASLAT SPAT do MANAGED CODE cez CALLBACK.
	//wprintf_s(L"NATIVE CODE - CallbackID in PRIMARY THREAD: [%s] !\n",CallbackID);

	HANDLE														HThread=(HANDLE)_beginthreadex(NULL,0,&PTRThreadMethod,NULL,0,NULL);

	CloseHandle(HThread);
}
//-------------------------------------------------------------------------------------------------------
// !!! PARAMETER CallbackID sluzi ako CALLBACK ID a kedze bol preneseny ako GCHandleType.Normal NATIVE CODE NESMIE pristupovat k jeho MEMORY a moze ho pouzivat IBA ako OPAQUE HANDLE, ktory moze preniest spat do MANAGED CODE.
// !!!!! PARAMETER DataBuffer bol preneseny ako GCHandleType.Pinned a preto NATIVE CODE MOZE k jeho MEMORY PRISTUPOVAT.
MYUNMANAGEDLIBRARY_API void DoCallbackAsPTRWithWrite(MyPTRCALLBACKWITHWRITE CallbackPointer, void* CallbackID, wchar_t* DataBuffer, int DataBufferSize)
{
	GPTRCallbackPointerWithWrite=CallbackPointer;
	GCallbackID=CallbackID;
	GDataBuffer=DataBuffer;
	GDataBufferSize=DataBufferSize;

	// !!! Kedze CallbackID prenesiem ako GCHandleType.Normal, tak k NEMU NESMIEM v NATIVE CODE PRISTUPOVAT, IBA ho ZASLAT SPAT do MANAGED CODE cez CALLBACK.
	//wprintf_s(L"NATIVE CODE - CallbackID in PRIMARY THREAD: [%s] !\n",CallbackID);

	// !!!!! Kedze DataBuffer je preneseny ako GCHandleType.Pinned, tak k nemu v NATIVE CODE je MOZNE PRISTUPOVAT.
	wprintf_s(L"NATIVE CODE - PRIMARY THREAD DataBuffer: [%s] !\n",DataBuffer);

	HANDLE														HThread=(HANDLE)_beginthreadex(NULL,0,&PTRThreadWithWriteDataMethod,NULL,0,NULL);

	CloseHandle(HThread);
}
//-------------------------------------------------------------------------------------------------------