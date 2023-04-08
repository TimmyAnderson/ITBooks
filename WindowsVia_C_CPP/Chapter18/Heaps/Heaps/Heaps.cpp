#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "MyDebug.h"
#include "MyClass.h"
//------------------------------------------------------------------------------
LONG WINAPI MyFilterFunction(void)
{
	return(EXCEPTION_EXECUTE_HANDLER);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE		Heap=HeapCreate(0,100,200);
	BYTE*		Pointer=NULL;

	// Alokujem 1 BYTE.
	Pointer=(BYTE*) HeapAlloc(Heap,0,1);

	*Pointer=100;

	wprintf_s(L"Value at address [%p] is [%d] !\n",Pointer,*Pointer);

	HeapFree(Heap,0,Pointer);

	HeapDestroy(Heap);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	const int		HEAP_MAX_SIZE=20;

	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);

	// HEAP pri prekroceni velkosti HODI EXCEPTION.
	HANDLE			Heap=HeapCreate(HEAP_GENERATE_EXCEPTIONS,10,HEAP_MAX_SIZE);
	BYTE*			Pointer=NULL;

	// Alokujem 1 BYTE.
	Pointer=(BYTE*) HeapAlloc(Heap,0,1);

	*Pointer=100;

	wprintf_s(L"Value at address [%p] is [%d] !\n",Pointer,*Pointer);

	__try
	{
		int		Size1=HEAP_MAX_SIZE+5;

		// !!! Alokujem pamat vacsiu ako maximalna dlzka HEAP.
		Pointer=(BYTE*) HeapAlloc(Heap,0,Size1);

		// Zbehne OK, pretoze v skutocnosti HEAP alokuje MINIMALNE JEDNU PAGE.
		wprintf_s(L"Memory [%d bytes] was successfully allocated !\n",Size1);

		int		Size2=SI.dwPageSize+1;

		// !!! Alokujem pamat vacsiu ako maximalna dlzka HEAP i velkost PAGE.
		Pointer=(BYTE*) HeapAlloc(Heap,0,Size2);

		wprintf_s(L"Memory [%d bytes] was successfully allocated !\n",Size2);
	}
	__except(MyFilterFunction())
	{
		wprintf_s(L"Can't allocate memory !\n");
	}

	HeapFree(Heap,0,Pointer);

	HeapDestroy(Heap);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	HANDLE		Heap=HeapCreate(0,100,200);
	BYTE*		Pointer1=NULL;
	BYTE*		Pointer2=NULL;

	// Alokujem 1 BYTE.
	Pointer1=(BYTE*) HeapAlloc(Heap,0,1);

	// Alokujem 10 BYTES.
	Pointer2=(BYTE*) HeapAlloc(Heap,0,10);

	wprintf_s(L"Block size at address [%p] is [%d] !\n",Pointer1,HeapSize(Heap,0,Pointer1));
	wprintf_s(L"Block size at address [%p] is [%d] !\n",Pointer2,HeapSize(Heap,0,Pointer2));

	HeapFree(Heap,0,Pointer1);
	HeapFree(Heap,0,Pointer2);

	HeapDestroy(Heap);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	wprintf_s(L"Number of HEAPS is [%d] !\n",GetProcessHeaps(0,NULL));

	CMyClass	*Data1=new CMyClass(100);
	CMyClass	*Data2=new CMyClass(200);
	CMyClass	Data3(300);

	wprintf_s(L"Data1: [%d] !\n",Data1->GetData());
	wprintf_s(L"Data2: [%d] !\n",Data2->GetData());
	wprintf_s(L"Data3: [%d] !\n",Data3.GetData());

	wprintf_s(L"Number of HEAPS is [%d] !\n",GetProcessHeaps(0,NULL));

	delete(Data1);
	delete(Data2);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	//Test3();
	Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------