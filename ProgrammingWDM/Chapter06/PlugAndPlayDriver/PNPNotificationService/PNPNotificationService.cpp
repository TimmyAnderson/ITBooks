//-------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <stdio.h>
#include <Strsafe.h>
#include <Dbt.h>
//-------------------------------------------------------------------------------------------------------
// !!! DRIVER DEVICE INTERFACE.
GUID															GUID_DEVINTERFACE_PLUG_AND_PLAY_DRIVER={0x68ec006bL, 0x45b3, 0x424b, 0xb1, 0x1, 0x12, 0xd9, 0x2f, 0x2, 0x1e, 0x39};
//-------------------------------------------------------------------------------------------------------
// Cislo musi sediet s ID PARAMETEROM v [RegisterEventSource.bat].
DWORD															EVENT_ID=802;
//-------------------------------------------------------------------------------------------------------
WCHAR															SERVICE_NAME[]=L"PNPNotificationService";
SERVICE_STATUS													GServiceStatus;
SERVICE_STATUS_HANDLE											GServiceStatusHandle;
HANDLE															GServiceStopEvent=NULL;
HDEVNOTIFY														GDeviceNotification=NULL;
//-------------------------------------------------------------------------------------------------------
void ReportServiceStatus(DWORD CurrentState, DWORD Win32ExitCode, DWORD WaitHint);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Zapisuje MESSAGE do EVENT LOG.
void WriteToEventLog(WORD EventType, LPWSTR Message)
{ 
	const int													BUFFER_SIZE=1024;
    WCHAR														Buffer[BUFFER_SIZE+1];
    LPCWSTR														Strings[2];
    HANDLE														EventSource=RegisterEventSource(NULL,SERVICE_NAME);

    if (EventSource!=NULL)
    {
		StringCchPrintf(Buffer,BUFFER_SIZE,L"DRIVER [%s] MESSAGE [%s] !",SERVICE_NAME,Message);

        Strings[0]=Buffer;

        if (ReportEvent(EventSource,EventType,0,EVENT_ID,NULL,1,0,Strings,NULL)==0)
		{
			wprintf_s(L"Can't REPORT EVENT !\n");
		}

        if (DeregisterEventSource(EventSource)==FALSE)
		{
			wprintf_s(L"Can't UNREGISTER EVENT SOURCE !\n");
			return;
		}
    }
	else
	{
		wprintf_s(L"Can't REGISTER EVENT SOURCE !\n");
		return;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Instaluje SERVICE.
void ServiceInstall(void)
{
	WCHAR														FileName[MAX_PATH+1];

	ZeroMemory(FileName,sizeof(FileName));

    if (GetModuleFileName(NULL,FileName,MAX_PATH)==0)
    {
        wprintf_s(L"Can't get FILENAME !\n");
        return;
    }

	SC_HANDLE													SCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if (SCManager==NULL)
	{
		wprintf_s(L"Can't OPEN SERVICE MANAGER !\n");
		return;
	}

	SC_HANDLE													Service=CreateService(SCManager,SERVICE_NAME,SERVICE_NAME,SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,FileName,NULL,NULL,NULL,NULL,NULL);

    if (Service==NULL) 
    {
        printf("Can't INSTALL SERVICE !\n");
        CloseServiceHandle(SCManager);
        return;
    }
    else
	{
		printf("SERVICE INSTALLED SUCCESSFULLY !\n");
	}

	if (CloseServiceHandle(Service)==FALSE)
	{
		wprintf_s(L"Can't CLOSE SERVICE !\n");
	}

	if (CloseServiceHandle(SCManager)==FALSE)
	{
		wprintf_s(L"Can't CLOSE SERVICE MANAGER !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
// Odinstaluje SERVICE.
void ServiceUninstall(void)
{
	SC_HANDLE													SCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if (SCManager==NULL)
	{
		wprintf_s(L"Can't OPEN SERVICE MANAGER !\n");
		return;
	}

	SC_HANDLE													Service=OpenService(SCManager,SERVICE_NAME,SC_MANAGER_ALL_ACCESS);

    if (Service==NULL) 
    {
        printf("Can't OPEN SERVICE !\n");
        CloseServiceHandle(SCManager);
        return;
    }

	if (DeleteService(Service)==FALSE)
	{
		wprintf_s(L"Can't UNINSTALL SERVICE !\n");
	}
	else
	{
		printf("SERVICE UNINSTALLED SUCCESSFULLY !\n");
	}

	if (CloseServiceHandle(Service)==FALSE)
	{
		wprintf_s(L"Can't CLOSE SERVICE !\n");
	}

	if (CloseServiceHandle(SCManager)==FALSE)
	{
		wprintf_s(L"Can't CLOSE SERVICE MANAGER !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Zasiela do SERVICE CONTROL MANAGER SERVICE STATUS.
void ReportServiceStatus(DWORD CurrentState, DWORD Win32ExitCode, DWORD WaitHint)
{
    static DWORD												CheckPoint=1;

	// !!! Nastavi sa SERVICE STATE.
    GServiceStatus.dwCurrentState=CurrentState;
	// EXIT CODE.
    GServiceStatus.dwWin32ExitCode=Win32ExitCode;
	// HINT ako dlho bude operacia trvat.
    GServiceStatus.dwWaitHint=WaitHint;

    if (CurrentState==SERVICE_START_PENDING)
	{
		// !!! Kedze SERVICE sa spusta, SERVICE CONTROL MANAGER NESMIE v COMPUTER MANAGEMENT zobrazit ZIADEN BUTTON, pretoze SERVICE nie je naprogramovany tak, ze by dokazal byt zastaveny ci zapauzovany, ak sa prave spusta.
        GServiceStatus.dwControlsAccepted=0;
	}
    else
	{
		// !!! Kedze SERVICE je SPUSTENY, SERVICE CONTROL MANAGER moze v COMPUTER MANAGEMENT zobrazit STOP BUTTON.
		GServiceStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP;
	}

    if ((CurrentState==SERVICE_RUNNING) || (CurrentState==SERVICE_STOPPED))
	{
        GServiceStatus.dwCheckPoint=0;
	}
    else
	{
		GServiceStatus.dwCheckPoint=CheckPoint++;
	}

	// !!! Zasle STATUS daneho SERVICE do SERVICE CONTROL MANAGER.
    SetServiceStatus(GServiceStatusHandle,&GServiceStatus);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ServiceInit(DWORD Argc, LPWSTR* Argv)
{
	GServiceStopEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

    if (GServiceStopEvent==NULL)
    {
        WriteToEventLog(EVENTLOG_ERROR_TYPE,L"FUNCTION CreateEvent() FAILED !");

		// !!! SERVICE STATE sa nastavi na STATE [STOPPED].
        ReportServiceStatus(SERVICE_STOPPED,NO_ERROR,0);
        return;
    }

	DEV_BROADCAST_DEVICEINTERFACE							DeviceInterfaceNotification;

	ZeroMemory(&DeviceInterfaceNotification,sizeof(DeviceInterfaceNotification));

	DeviceInterfaceNotification.dbcc_size=sizeof(DeviceInterfaceNotification);
	DeviceInterfaceNotification.dbcc_devicetype=DBT_DEVTYP_DEVICEINTERFACE;
	// !!! GUID DRIVER DEVICE INTERFACE, ktory ma byt monitorovany.
	DeviceInterfaceNotification.dbcc_classguid=GUID_DEVINTERFACE_PLUG_AND_PLAY_DRIVER;

	// !!! Zaregistruje sa DRIVER DEVICE INTERFACE NOTIFICATION.
	GDeviceNotification=RegisterDeviceNotification(GServiceStatusHandle,&DeviceInterfaceNotification,DEVICE_NOTIFY_SERVICE_HANDLE);

	if (GDeviceNotification==NULL)
	{
        WriteToEventLog(EVENTLOG_ERROR_TYPE,L"FUNCTION RegisterDeviceNotification() FAILED !");

		// !!! SERVICE STATE sa nastavi na STATE [STOPPED].
        ReportServiceStatus(SERVICE_STOPPED,NO_ERROR,0);
        return;
	}

	// !!! SERVICE STATE sa nastavi na STATE [RUNNING].
    ReportServiceStatus(SERVICE_RUNNING,NO_ERROR,0);

	WriteToEventLog(EVENTLOG_INFORMATION_TYPE,L"SERVICE is STARTED !");

    while(TRUE)
    {
		// Kontrola ci neprisla poziadavka na zastavenie SERVICE.
        WaitForSingleObject(GServiceStopEvent,INFINITE);

		// !!! SERVICE STATE sa nastavi na STATE [STOPPED].
        ReportServiceStatus(SERVICE_STOPPED,NO_ERROR,0);
        return;
    }
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! CALLBACK FUNCTION, ktoru SERVICE CONTROL MANAGER vola pri vzniku nejakeho EVENT.
DWORD WINAPI ServiceControlHandler(DWORD Control, DWORD EventType, LPVOID EventData, LPVOID Context)
{
	const int													BUFFER_SIZE=1024;
	WCHAR														Buffer[BUFFER_SIZE+1];

	switch(Control)
	{
		case SERVICE_CONTROL_STOP:
		{
			// !!! SERVICE STATE sa nastavi na STATE [STOP_PENDING].
			ReportServiceStatus(SERVICE_STOP_PENDING,NO_ERROR,0);

			SetEvent(GServiceStopEvent);

			// !!! SERVICE STATE sa nastavi na STATE [GServiceStatus.dwCurrentState].
			ReportServiceStatus(GServiceStatus.dwCurrentState,NO_ERROR,0);

	        WriteToEventLog(EVENTLOG_INFORMATION_TYPE,L"SERVICE is STOPPED !");

			return(NO_ERROR);
		}
 
		case SERVICE_CONTROL_INTERROGATE:
		{
			return(NO_ERROR);
		}

		// !!! Ak SERVICE chce ZABRANIT, aby WINDOWS odstranil DRIVER musi zo SERVICE CALLBACK ROUTINE vratit ERROR CODE ako RETURN VALUE. Ak sa naopak ma DRIVER ODSTRANIT, musi SERVICE CALLBACK ROUTINE vratit ako RETURN VALUE hodnotu [NO_ERROR].
		case SERVICE_CONTROL_DEVICEEVENT:
		{
			WCHAR*												Text=L"UNKNOWN VALUE !";

			if (EventType==DBT_CONFIGCHANGECANCELED)
			{
				Text=L"VALUE [DBT_CONFIGCHANGECANCELED] !";
			}
			else if (EventType==DBT_CONFIGCHANGED)
			{
				Text=L"VALUE [DBT_CONFIGCHANGED] !";
			}
			else if (EventType==DBT_CUSTOMEVENT)
			{
				Text=L"VALUE [DBT_CUSTOMEVENT] !";
			}
			else if (EventType==DBT_DEVICEARRIVAL)
			{
				Text=L"VALUE [DBT_DEVICEARRIVAL] !";
			}
			else if (EventType==DBT_DEVICEQUERYREMOVE)
			{
				Text=L"VALUE [DBT_DEVICEQUERYREMOVE] !";
			}
			else if (EventType==DBT_DEVICEQUERYREMOVEFAILED)
			{
				Text=L"VALUE [DBT_DEVICEQUERYREMOVEFAILED] !";
			}
			else if (EventType==DBT_DEVICEREMOVECOMPLETE)
			{
				Text=L"VALUE [DBT_DEVICEREMOVECOMPLETE] !";
			}
			else if (EventType==DBT_DEVICEREMOVEPENDING)
			{
				Text=L"VALUE [DBT_DEVICEREMOVEPENDING] !";
			}
			else if (EventType==DBT_DEVICETYPESPECIFIC)
			{
				Text=L"VALUE [DBT_DEVICETYPESPECIFIC] !";
			}
			else if (EventType==DBT_DEVNODES_CHANGED)
			{
				Text=L"VALUE [DBT_DEVNODES_CHANGED] !";
			}
			else if (EventType==DBT_QUERYCHANGECONFIG)
			{
				Text=L"VALUE [DBT_QUERYCHANGECONFIG] !";
			}
			else if (EventType==DBT_USERDEFINED)
			{
				Text=L"VALUE [DBT_USERDEFINED] !";
			}

			StringCchPrintf(Buffer,BUFFER_SIZE,L"DRIVER [%s] DEVICE CONTROL EVENT - EVENT TYPE [%d], EVENT TYPE STRING [%s] !",SERVICE_NAME,EventType,Text);

	        WriteToEventLog(EVENTLOG_INFORMATION_TYPE,Buffer);

			return(NO_ERROR);
		}

		default:
		{
			return(ERROR_CALL_NOT_IMPLEMENTED);
		}
	} 
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// SERVICE MAIN FUNCTION.
void WINAPI ServiceMain(DWORD Argc, LPTSTR* Argv)
{
	// !!! Zaregistruje sa CALLBACK FUNCTION, ktora spracovava EVENTS zaslane SERVICE CONTROL MANAGER.
	// !!! Vrateny HANDLER NEMUSI byt uzatvoreny.
	GServiceStatusHandle=RegisterServiceCtrlHandlerEx(SERVICE_NAME,ServiceControlHandler,NULL);
	
    if (GServiceStatusHandle==NULL)
    { 
        WriteToEventLog(EVENTLOG_ERROR_TYPE,L"FUNCTION RegisterServiceCtrlHandler() FAILED !");
        return; 
    } 

    GServiceStatus.dwServiceType=SERVICE_WIN32_OWN_PROCESS; 
    GServiceStatus.dwServiceSpecificExitCode=0;    

	// !!! SERVICE STATE sa nastavi na STATE [START_PENDING].
	// Posledny PARAMETER je HINT, ako dlho by asi malo trvat nastartovanie SERVICE.
    ReportServiceStatus(SERVICE_START_PENDING,NO_ERROR,3000);

	// SERVICE SPECIFIC inicializacia.
    ServiceInit(Argc,Argv);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int wmain(int argc, WCHAR* argv[])
{
	if (argc==2)
	{
		if (wcscmp(argv[1],L"install")==0)
		{
			wprintf_s(L"INSTALLING SERVICE !\n");

			ServiceInstall();
			return(0);
		}
		else if (wcscmp(argv[1],L"uninstall")==0)
		{
			wprintf_s(L"UNINSTALLING SERVICE !\n");

			ServiceUninstall();
			return(0);
		}
		else
		{
			wprintf_s(L"UNSUPPORTED PARAMETER [%s] ! SUPPORTED PARAMETERS are [install] and [uninstall] !\n",argv[1]);
		}
	}

    // Zoznam vsetkych SERVICES, ktore PROCESS obsahuje.
    SERVICE_TABLE_ENTRY											DispatchTable[]=
    {
        {SERVICE_NAME,(LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL,NULL}
    };

	// !!! FUNCTION StartServiceCtrlDispatcher() spusta SERVICE. Ked sa FUNCTION ukonci, znamena to, ze SERVICE CONTROL MANAGER ukoncil SERVICE a PROCESS sa moze ukoncit.
    if (StartServiceCtrlDispatcher(DispatchTable)==FALSE)
    { 
        WriteToEventLog(EVENTLOG_ERROR_TYPE,L"FUNCTION StartServiceCtrlDispatcher() FAILED !");
    } 

	if (GDeviceNotification!=NULL)
	{
		if (UnregisterDeviceNotification(GDeviceNotification)==FALSE)
		{
	        WriteToEventLog(EVENTLOG_ERROR_TYPE,L"FUNCTION UnregisterDeviceNotification() FAILED !");
		}
	}

	if (GServiceStopEvent!=NULL)
	{
		CloseHandle(GServiceStopEvent);
		GServiceStopEvent=NULL;
	}

	return(0);
}
//-------------------------------------------------------------------------------------------------------