//-------------------------------------------------------------------------------------------------------
#include "Resource.h"
#include <Windows.h>
#include <Strsafe.h>
#include <Dbt.h>
//-------------------------------------------------------------------------------------------------------
// !!! DRIVER NAME.
const wchar_t*													DRIVER_NAME=L"\\\\.\\PlugAndPlayDriver";
//-------------------------------------------------------------------------------------------------------
// !!! CUSTOM NOTIFICATION GUID.
GUID															GUID_MY_CUSTOM_PNP_EVENT={0x28ce01a2L, 0x9436, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6};
//-------------------------------------------------------------------------------------------------------
HINSTANCE														GHInstance;
HWND															GHWND;
HWND															GHWNDListBox;
WCHAR															GTitle[]=L"PNPNotificationsByHandle";
WCHAR															GWindowClass[]=L"PNPNotificationsByHandle";
//-------------------------------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE HInstance);
BOOL InitInstance(HINSTANCE,int);
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE HInstance)
{
	WNDCLASSEX													WCEX;

	WCEX.cbSize=sizeof(WNDCLASSEX);
	WCEX.style=(CS_HREDRAW | CS_VREDRAW);
	WCEX.lpfnWndProc=WindowProcedure;
	WCEX.cbClsExtra=0;
	WCEX.cbWndExtra=0;
	WCEX.hInstance=HInstance;
	WCEX.hIcon=LoadIcon(HInstance,MAKEINTRESOURCE(IDI_PNPNOTIFICATIONSBYHANDLE));
	WCEX.hCursor=LoadCursor(NULL,IDC_ARROW);
	WCEX.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WCEX.lpszMenuName=MAKEINTRESOURCE(IDC_PNPNOTIFICATIONSBYHANDLE);
	WCEX.lpszClassName=GWindowClass;
	WCEX.hIconSm=LoadIcon(WCEX.hInstance,MAKEINTRESOURCE(IDI_SMALL));

	return(RegisterClassEx(&WCEX));
}
//-------------------------------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE HInstance, int CmdShow)
{
	HWND														HWnd;

	GHInstance=HInstance;

	GHWND=HWnd=CreateWindow(GWindowClass,GTitle,WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,500,300,NULL,NULL,HInstance,NULL);

	if (HWnd==NULL)
	{
		return(FALSE);
	}

	RECT														ClientArea={};

	if (GetClientRect(HWnd,&ClientArea)==FALSE)
	{
		DestroyWindow(HWnd);
		HWnd=NULL;

		return(FALSE);
	}

	GHWNDListBox=CreateWindowEx(WS_EX_CLIENTEDGE,L"LISTBOX",NULL,(WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL),ClientArea.left+10,ClientArea.top+15,ClientArea.right-ClientArea.left-(2*10),ClientArea.bottom-ClientArea.top-(2*15),HWnd,NULL,HInstance,NULL);

	if (GHWNDListBox==NULL)
	{
		DestroyWindow(HWnd);
		HWnd=NULL;

		return(FALSE);
	}

	ShowWindow(HWnd,CmdShow);
	UpdateWindow(HWnd);

	return(TRUE);
}
//-------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowProcedure(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	int															ID;
	int															Event;
	PAINTSTRUCT													PS;
	HDC															HDC;

	switch(Message)
	{
		case WM_COMMAND:
		{
			ID=LOWORD(WParam);
			Event=HIWORD(WParam);

			switch(ID)
			{
				case ID_FILE_CLEAR:
				{
					SendMessage(GHWNDListBox,LB_RESETCONTENT,0,0);
					break;
				}

				case IDM_EXIT:
				{
					DestroyWindow(HWnd);
					break;
				}

				default:
				{
					return(DefWindowProc(HWnd,Message,WParam,LParam));
				}
			}
		}
		break;

		case WM_PAINT:
		{
			HDC=BeginPaint(HWnd,&PS);
			EndPaint(HWnd,&PS);
			break;
		}
	
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_DEVICECHANGE:
		{
			WCHAR*												Text=L"UNKNOWN VALUE !";

			if (WParam==DBT_CONFIGCHANGECANCELED)
			{
				Text=L"VALUE [DBT_CONFIGCHANGECANCELED] !";
			}
			else if (WParam==DBT_CONFIGCHANGED)
			{
				Text=L"VALUE [DBT_CONFIGCHANGED] !";
			}
			else if (WParam==DBT_CUSTOMEVENT)
			{
				Text=L"VALUE [DBT_CUSTOMEVENT] !";
			}
			else if (WParam==DBT_DEVICEARRIVAL)
			{
				Text=L"VALUE [DBT_DEVICEARRIVAL] !";
			}
			else if (WParam==DBT_DEVICEQUERYREMOVE)
			{
				Text=L"VALUE [DBT_DEVICEQUERYREMOVE] !";
			}
			else if (WParam==DBT_DEVICEQUERYREMOVEFAILED)
			{
				Text=L"VALUE [DBT_DEVICEQUERYREMOVEFAILED] !";
			}
			else if (WParam==DBT_DEVICEREMOVECOMPLETE)
			{
				Text=L"VALUE [DBT_DEVICEREMOVECOMPLETE] !";
			}
			else if (WParam==DBT_DEVICEREMOVEPENDING)
			{
				Text=L"VALUE [DBT_DEVICEREMOVEPENDING] !";
			}
			else if (WParam==DBT_DEVICETYPESPECIFIC)
			{
				Text=L"VALUE [DBT_DEVICETYPESPECIFIC] !";
			}
			else if (WParam==DBT_DEVNODES_CHANGED)
			{
				Text=L"VALUE [DBT_DEVNODES_CHANGED] !";
			}
			else if (WParam==DBT_QUERYCHANGECONFIG)
			{
				Text=L"VALUE [DBT_QUERYCHANGECONFIG] !";
			}
			else if (WParam==DBT_USERDEFINED)
			{
				Text=L"VALUE [DBT_USERDEFINED] !";
			}

			SendMessage(GHWNDListBox,LB_ADDSTRING,0,(LPARAM) Text);

			if (WParam==DBT_DEVICEQUERYREMOVE)
			{
				if (MessageBox(NULL,L"Remove DEVICE from SYSTEM ?",L"REMOVE DEVICE",MB_YESNO)==IDYES)
				{
					MessageBox(NULL,L"DRIVER will be REMOVED from SYSTEM !",L"REMOVE DEVICE",MB_OK);

					// !!! Umozni ostranenie DRIVER z MEMORY.
					return(TRUE);
				}
				else
				{
					MessageBox(NULL,L"DRIVER won't be REMOVED from SYSTEM !",L"REMOVE DEVICE",MB_OK);

					// !!! Zabrani odstraneniu DRIVER z MEMORY.
					return(BROADCAST_QUERY_DENY);
				}
			}

			if (WParam==DBT_CUSTOMEVENT)
			{
				DEV_BROADCAST_HDR*								Header=(DEV_BROADCAST_HDR*) LParam;
				
				if (Header->dbch_devicetype==DBT_DEVTYP_HANDLE)
				{
					DEV_BROADCAST_HANDLE*						Handle=(DEV_BROADCAST_HANDLE*) Header;

					if (Handle->dbch_eventguid==GUID_MY_CUSTOM_PNP_EVENT)
					{
						const int								BUFFER_SIZE=1024;
						wchar_t									Buffer[BUFFER_SIZE];
						
						StringCchPrintf(Buffer,BUFFER_SIZE,L"!!! CUSTOM EVENT - OFFSET [%d] DATA [%s] !",Handle->dbch_nameoffset,&Handle->dbch_data[Handle->dbch_nameoffset]);
						
						SendMessage(GHWNDListBox,LB_ADDSTRING,0,(LPARAM) Buffer);
					}
				}
			}
		}
		break;
	
		default:
		{
			return(DefWindowProc(HWnd,Message,WParam,LParam));
		}
	}

	return(0);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int APIENTRY wWinMain(HINSTANCE HInstance, HINSTANCE PreveviousInstance, LPWSTR CmdLine, int CmdShow)
{
	UNREFERENCED_PARAMETER(PreveviousInstance);
	UNREFERENCED_PARAMETER(CmdLine);

	MSG															Message;

	MyRegisterClass(HInstance);

	if (InitInstance(HInstance,CmdShow)==FALSE)
	{
		return(FALSE);
	}

	HANDLE														DriverHandle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (DriverHandle==INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,L"DRIVER NOT FOUND !",L"DRIVER",MB_OK);

		return(FALSE);
	}

	DEV_BROADCAST_HANDLE										HandleNotification;

	ZeroMemory(&HandleNotification,sizeof(HandleNotification));

	HandleNotification.dbch_size=sizeof(HandleNotification);
	HandleNotification.dbch_devicetype=DBT_DEVTYP_HANDLE;
	// !!! GUID DRIVER DEVICE INTERFACE, ktory ma byt monitorovany.
	HandleNotification.dbch_handle=DriverHandle;

	// !!! Zaregistruje sa DRIVER DEVICE INTERFACE NOTIFICATION.
	HDEVNOTIFY													DeviceNotification=RegisterDeviceNotification(GHWND,&HandleNotification,DEVICE_NOTIFY_WINDOW_HANDLE);

	if (DeviceNotification==NULL)
	{
		MessageBox(NULL,L"DRIVER DEVICE INTERFACE NOTIFICATION FAILED to REGISTER !",L"PNP NOTIFICATION",MB_OK);
	}

	CloseHandle(DriverHandle);
	DriverHandle=NULL;

	while(GetMessage(&Message,NULL,0,0)>0)
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	// !!! Odregistruje sa DRIVER DEVICE INTERFACE NOTIFICATION.
	if (UnregisterDeviceNotification(DeviceNotification)==FALSE)
	{
		MessageBox(NULL,L"DRIVER DEVICE INTERFACE NOTIFICATION FAILED to UNREGISTER !",L"PNP NOTIFICATION",MB_OK);
	}

	int															Return=(int)Message.wParam;

	return(Return);
}
//-------------------------------------------------------------------------------------------------------