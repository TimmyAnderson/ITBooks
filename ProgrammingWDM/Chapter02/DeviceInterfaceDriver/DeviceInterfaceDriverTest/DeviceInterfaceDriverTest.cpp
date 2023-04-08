//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <guiddef.h>
#include <Setupapi.h>
//-------------------------------------------------------------------------------------------------------
// Vlozi LIBRARY SetupAPI.DLL.
#pragma comment(lib,"SetupAPI")
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
// Definuje DEVICE INTERFACE CLASS.
static const GUID												GUID_DEVINTERFACE_DEVICE_INTERFACE_DRIVER={0x8cb5b8d9L, 0x92ff, 0x4c76, 0xb9, 0x76, 0x30, 0xee, 0x14, 0x8, 0x9c, 0xe2};
//-------------------------------------------------------------------------------------------------------
const wchar_t*													DRIVER_NAME=L"\\\\.\\DeviceInterfaceDriver";
//-------------------------------------------------------------------------------------------------------
// !!! Otvori DRIVER pomocou SYMBOLIC LINK na DEVICE OBJECT.
void OpenDeviceByDeviceInterface(const wchar_t* DeviceInterfaceName)
{
	HANDLE														Handle=CreateFile(DeviceInterfaceName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[]="My name is Timmy Anderson !";
		DWORD													NumberOfBytesWritten;

		if (WriteFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[512];
		BYTE													OutputBuffer[1024];
		DWORD													BytesReturned=0;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));
		ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

		sprintf_s(InputBuffer,_countof(InputBuffer),"My name is Jenny Thompson !");
		wprintf_s(L"InputBuffer [%p], OutputBuffer [%p] !\n",InputBuffer,OutputBuffer);
		printf_s("InputBuffer [%s] !\n",InputBuffer);

		if (DeviceIoControl(Handle,IOCTL_SIMPLE_TEST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT - BytesReturned [%d], OutputBuffer [%s] !\n",BytesReturned,(wchar_t*)OutputBuffer);
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[]="My name is Timmy Anderson !";
		DWORD													NumberOfBytesWritten;

		if (WriteFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	GUID														InterfaceGUID=GUID_DEVINTERFACE_DEVICE_INTERFACE_DRIVER;

	wprintf_s(L"DEVICE INTERFACE GUID [%08X-%04X-%04X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X] !\n",InterfaceGUID.Data1,InterfaceGUID.Data2,InterfaceGUID.Data3,InterfaceGUID.Data4[0],InterfaceGUID.Data4[1],InterfaceGUID.Data4[2],InterfaceGUID.Data4[3],InterfaceGUID.Data4[4],InterfaceGUID.Data4[5],InterfaceGUID.Data4[6],InterfaceGUID.Data4[7]);

	// !!! Otvori sa DEVICE INFORMATION SET, ktory umoznuje enumerovat DEVICE INTERFACES, ktore su zaregistrovane pre dany DEVICE INTERFACE CLASS.
	HDEVINFO													InfoSet=SetupDiGetClassDevs(&InterfaceGUID,NULL,NULL,DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (InfoSet==INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"NO DEVICES for specified GUID !\n");
		return;
	}

	SP_DEVICE_INTERFACE_DATA									InterfaceData={sizeof(SP_DEVICE_INTERFACE_DATA)};
	DWORD														DeviceIndex=0;

	// !!! Enumeruju sa DEVICE INTERFACES pre definovany DEVICE INTERFACE CLASS (InterfaceGUID).
	while(true)
	{
		if (SetupDiEnumDeviceInterfaces(InfoSet,NULL,&InterfaceGUID,DeviceIndex,&InterfaceData)==FALSE)
		{
			break;
		}

		DeviceIndex++;

		SP_DEVINFO_DATA											DeviceData={sizeof(SP_DEVINFO_DATA)};
		const int												BUFFER_SIZE=1000;
		wchar_t													DetailDataBuffer[BUFFER_SIZE+sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA)];
		SP_DEVICE_INTERFACE_DETAIL_DATA*						DetailData=(SP_DEVICE_INTERFACE_DETAIL_DATA*)&DetailDataBuffer;

		DetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		// !!! Ziskaju sa detailne INFORMATION o DEVICE INTERFACE CLASS.
		if (SetupDiGetDeviceInterfaceDetail(InfoSet,&InterfaceData,DetailData,BUFFER_SIZE,NULL,&DeviceData)==FALSE)
		{
			wprintf_s(L"Can't get DEVICE INTERFACE DETAILS !\n");
			continue;
		}

		// !!!!! Obsahuje SYMBOLIC LINK na DEVICE OBJECT, ktory je mozne pouzit vo FUNCTION CreateFile() na ziskanie HANDLE na DEVICE.
		wprintf_s(L"DEVICE INTERFACE PATH [%s] !\n",DetailData->DevicePath);

		// !!!!! Pomocou FUNCTION CreateFile() ziska HANDLE na DRIVER a vykona FUNCTION WriteFile().
		OpenDeviceByDeviceInterface(DetailData->DevicePath);
	}

	// !!! Uvolni DEVICE INFORMATION SET.
	SetupDiDestroyDeviceInfoList(InfoSet);

	if (DeviceIndex==0)
	{
		wprintf_s(L"NO DEVICES were FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int wmain(int argc, wchar_t* argv[])
{
	wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");

	for(;;)
	{
		char													Buffer[100];

		fgets(Buffer,_countof(Buffer),stdin);

		if (strcmp(Buffer,"q\n")==0)
		{
			break;
		}
		else if (strcmp(Buffer,"1\n")==0)
		{
			Test1();
		}
		else if (strcmp(Buffer,"2\n")==0)
		{
			Test2();
		}
		else if (strcmp(Buffer,"3\n")==0)
		{
			Test3();
		}
		else if (strcmp(Buffer,"x1\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test1();
			}
		}
		else if (strcmp(Buffer,"x2\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test2();
			}
		}
		else if (strcmp(Buffer,"x3\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test3();
			}
		}
		else
		{
			system("cls");
			wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");
		}
	}

	wprintf_s(L"Press any KEY to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------