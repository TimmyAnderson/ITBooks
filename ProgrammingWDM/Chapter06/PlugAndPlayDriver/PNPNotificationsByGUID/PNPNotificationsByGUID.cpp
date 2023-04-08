//-------------------------------------------------------------------------------------------------------
#include "Resource.h"
#include <Windows.h>
#include <Dbt.h>
//-------------------------------------------------------------------------------------------------------
// !!! DRIVER DEVICE INTERFACE.
GUID															GUID_DEVINTERFACE_PLUG_AND_PLAY_DRIVER={0x68ec006bL, 0x45b3, 0x424b, 0xb1, 0x1, 0x12, 0xd9, 0x2f, 0x2, 0x1e, 0x39};
//-------------------------------------------------------------------------------------------------------
HINSTANCE														GHInstance;
HWND															GHWND;
HWND															GHWNDListBox;
WCHAR															GTitle[]=L"PNPNotificationsByGUID";
WCHAR															GWindowClass[]=L"PNPNotificationsByGUID";
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
	WCEX.hIcon=LoadIcon(HInstance,MAKEINTRESOURCE(IDI_PNPNOTIFICATIONSBYGUID));
	WCEX.hCursor=LoadCursor(NULL,IDC_ARROW);
	WCEX.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WCEX.lpszMenuName=MAKEINTRESOURCE(IDC_PNPNOTIFICATIONSBYGUID);
	WCEX.lpszClassName=GWindowClass;
	WCEX.hIconSm=LoadIcon(WCEX.hInstance,MAKEINTRESOURCE(IDI_SMALL));

	return(RegisterClassEx(&WCEX));
}
//-------------------------------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE HInstance, int CmdShow)
{
	HWND														HWnd;

	GHInstance=HInstance;

	GHWND=HWnd=CreateWindow(GWindowClass,GTitle,WS_OVERLAPPED | WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,510,330,NULL,NULL,HInstance,NULL);

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

	DEV_BROADCAST_DEVICEINTERFACE								DeviceInterfaceNotification;

	ZeroMemory(&DeviceInterfaceNotification,sizeof(DeviceInterfaceNotification));

	DeviceInterfaceNotification.dbcc_size=sizeof(DeviceInterfaceNotification);
	DeviceInterfaceNotification.dbcc_devicetype=DBT_DEVTYP_DEVICEINTERFACE;
	// !!! GUID DRIVER DEVICE INTERFACE, ktory ma byt monitorovany.
	DeviceInterfaceNotification.dbcc_classguid=GUID_DEVINTERFACE_PLUG_AND_PLAY_DRIVER;

	// !!! Zaregistruje sa DRIVER DEVICE INTERFACE NOTIFICATION.
	HDEVNOTIFY													DeviceNotification=RegisterDeviceNotification(GHWND,&DeviceInterfaceNotification,DEVICE_NOTIFY_WINDOW_HANDLE);

	if (DeviceNotification==NULL)
	{
		MessageBox(NULL,L"DRIVER DEVICE INTERFACE NOTIFICATION FAILED to REGISTER !",L"PNP NOTIFICATION",MB_OK);
	}

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