#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <strsafe.h>
//-----------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf_s(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf_s(L"Expression: %s !\n\n\n", Expression);
}
//-----------------------------------------------------------------------------
void SafeMain(void)
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);
}
//-----------------------------------------------------------------------------
void ShowExitLine(void)
{
	wprintf_s(L"\nPress any key to EXIT !\n");
	_getch();
}
//-----------------------------------------------------------------------------
void WriteTextWithTime(wchar_t* Text, bool Day, bool Miliseconds)
{
	SYSTEMTIME		ST;

	GetLocalTime(&ST);

	wchar_t			Buffer[1024];
	wchar_t			*Data=Buffer;
	int				Size=_countof(Buffer);
	size_t			Length;
	
	if (Day==true)
	{
		StringCchPrintf(Data,Size,L"%02d-%02d-%04d ",ST.wDay,ST.wMonth,ST.wYear);

		StringCchLength(Data,Size,&Length);
		Data+=Length;
	}

	StringCchPrintf(Data,Size,L"%02d:%02d:%02d",ST.wHour,ST.wMinute,ST.wSecond);

	StringCchLength(Data,Size,&Length);
	Data+=Length;

	if (Miliseconds==true)
		StringCchPrintf(Data,Size,L".%03d",ST.wMilliseconds);

	wprintf_s(L"%s - %s",Buffer,Text);
}
//-----------------------------------------------------------------------------
void WriteTextWithTime(wchar_t* Text)
{
	WriteTextWithTime(Text,false,true);
}
//-----------------------------------------------------------------------------
void WriteDebugText(wchar_t* Text)
{
	wchar_t			Buffer[1024];
	int				Size=_countof(Buffer);
	size_t			Length1;
	size_t			Length2;
	
	StringCchPrintf(Buffer,Size,L"[%d] - ",GetCurrentThreadId());
	StringCchLength(Buffer,Size,&Length1);
	StringCchLength(Text,Size,&Length2);

	size_t			ToPrintSize=Length1+Length2+1;
	wchar_t*		ToPrint=new wchar_t[ToPrintSize];

	StringCchPrintf(ToPrint,ToPrintSize,L"%s%s",Buffer,Text);

	WriteTextWithTime(ToPrint,false,true);

	delete[](ToPrint);
	ToPrint=NULL;
}
//-----------------------------------------------------------------------------