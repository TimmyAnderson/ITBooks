#include "stdafx.h"
#include "GUIWithConsole.h"
#include <Fcntl.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <ios>
#include <vector>
//------------------------------------------------------------------------------
#define MAX_LOADSTRING 100
//------------------------------------------------------------------------------
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
//------------------------------------------------------------------------------
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL				ConsoleOpened=FALSE;
//------------------------------------------------------------------------------
void CreateConsole(void)
{
	int			ConsoleHandle;
	FILE*		FP;

	if (AllocConsole()==FALSE)
	{
		wprintf_s(L"Can't create NEW CONSOLE !\n");
		return;
	}

	ConsoleOpened=TRUE;

	SetConsoleTitle(L"My Console");

	// Presmerujem STDOUT.
	HANDLE		StdOutHandle=GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleHandle=_open_osfhandle((int) StdOutHandle,_O_TEXT);
	FP=_fdopen(ConsoleHandle,"w");
	*stdout=*FP;
	setvbuf(stdout,NULL,_IONBF,0);

	// Presmerujem STDIN.
	HANDLE		StdInHandle=GetStdHandle(STD_INPUT_HANDLE);

	ConsoleHandle=_open_osfhandle((int) StdInHandle,_O_TEXT);
	FP=_fdopen(ConsoleHandle,"r");
	*stdin=*FP;
	setvbuf(stdin,NULL,_IONBF,0);

	// Presmerujem STDERR.
	HANDLE		StdErrHandle=GetStdHandle(STD_ERROR_HANDLE);

	ConsoleHandle=_open_osfhandle((int) StdErrHandle,_O_TEXT);
	FP=_fdopen(ConsoleHandle,"w");
	*stderr=*FP;
	setvbuf(stderr,NULL,_IONBF,0);

	// Presmerujem cin, cout a dalsie streams.
	std::ios_base::sync_with_stdio();
}
//------------------------------------------------------------------------------
void DestoryConsole(void)
{
	FreeConsole();
	ConsoleOpened=FALSE;
}
//------------------------------------------------------------------------------
void WriteConsole(void)
{
	if (ConsoleOpened==FALSE)
		return;

	wprintf_s(L"Output to STD OUT !\n");
	fwprintf_s(stderr,L"Output to STD ERR !\n");
}
//------------------------------------------------------------------------------
void ReadConsole(void)
{
	if (ConsoleOpened==FALSE)
		return;

	wprintf_s(L"\nInsert some char and press ENTER !\n");

	std::wstring	Text(L"");

	while(true)
	{
		wint_t		CI=fgetwc(stdin);
		wchar_t		Char=CI;

		if (Char!='\a' && Char!='\n')
			Text+=Char;

		if (Char=='\n')
			break;
	}

	wprintf_s(L"\nChar inserted [%s] !\n",Text.c_str());
}
//------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUIWITHCONSOLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return(FALSE);
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUIWITHCONSOLE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return((int) msg.wParam);
}
//------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUIWITHCONSOLE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUIWITHCONSOLE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return(RegisterClassEx(&wcex));
}
//------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
      return(FALSE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return(TRUE);
}
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				}
				break;

				case IDM_EXIT:
				{
					DestroyWindow(hWnd);
				}
				break;

				case ID_CONSOLE_RUN:
				{
					CreateConsole();
				}
				break;

				case ID_CONSOLE_DESTORY:
				{
					DestoryConsole();
				}
				break;


				case ID_CONSOLE_WRITEMESSAGE:
				{
					WriteConsole();
				}
				break;

				case ID_CONSOLE_READMESSAGE:
				{
					ReadConsole();
				}
				break;

				default:
					return(DefWindowProc(hWnd, message, wParam, lParam));
			}
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
			return(DefWindowProc(hWnd, message, wParam, lParam));
	}

	return(0);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
		case WM_INITDIALOG:
			return((INT_PTR)TRUE);

		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return((INT_PTR)TRUE);
			}
		}
		break;
	}

	return((INT_PTR)FALSE);
}
//------------------------------------------------------------------------------