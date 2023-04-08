//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <winreg.h>
#include <regstr.h>
#include <objbase.h>
#include <conio.h>
//-------------------------------------------------------------------------------------------------------
// Vlozi LIBRARY SetupAPI.DLL.
#pragma comment(lib,"SetupAPI")
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
BOOL HexaToByte(LPCWSTR& String, PBYTE PResult)
{
	BYTE														Result=0;

	for (int Index=0;Index<2;Index++)
	{
		wchar_t													Char=*String++;
		BYTE													Hexa;

		if (Char>=L'0' && Char<=L'9')
		{
			Hexa=BYTE(Char-L'0');
		}
		else if (Char>=L'a' && Char<=L'f')
		{
			Hexa=BYTE(Char-(L'a'-10));
		}
		else if (Char>=L'A' && Char<=L'F')
		{
			Hexa=BYTE(Char-(L'A'-10));
		}
		else
		{
			return(FALSE);
		}

		Result<<=4;
		Result|=Hexa;
	}

	*PResult=Result;

	return(TRUE);
}
//-------------------------------------------------------------------------------------------------------
BOOL HexaToWord(LPCWSTR& String, PWORD PResult)
{
	WORD														Result=0;

	for (int Index=0;Index<4;Index++)
	{
		wchar_t													Char=*String++;
		BYTE													Hexa;

		if (Char>=L'0' && Char<=L'9')
		{
			Hexa=BYTE(Char-L'0');
		}
		else if (Char>=L'a' && Char<=L'f')
		{
			Hexa=BYTE(Char-(L'a'-10));
		}
		else if (Char>=L'A' && Char<=L'F')
		{
			Hexa=BYTE(Char-(L'A'-10));
		}
		else
		{
			return(FALSE);
		}

		Result<<=4;
		Result|=Hexa;
	}

	*PResult=Result;

	return(TRUE);
}
//-------------------------------------------------------------------------------------------------------
BOOL HexaToDoubleWord(LPCWSTR& String, PDWORD PResult)
{
	DWORD														Result=0;

	for (int Index=0;Index<8;Index++)
	{
		wchar_t													Char=*String++;
		BYTE													Hexa;

		if (Char>=L'0' && Char<=L'9')
		{
			Hexa=BYTE(Char-L'0');
		}
		else if (Char>=L'a' && Char<=L'f')
		{
			Hexa=BYTE(Char-(L'a'-10));
		}
		else if (Char>=L'A' && Char<=L'F')
		{
			Hexa=BYTE(Char-(L'A'-10));
		}
		else
		{
			return(FALSE);
		}

		Result<<=4;
		Result|=Hexa;
	}

	*PResult=Result;

	return(TRUE);
}
//-------------------------------------------------------------------------------------------------------
BOOL GuidFromString(GUID* Guid, LPCWSTR String)
{
	return(*String++==L'{' && HexaToDoubleWord(String,&Guid->Data1) && *String++==L'-' && HexaToWord(String, &Guid->Data2) && *String++ == L'-' && HexaToWord(String, &Guid->Data3) && *String++ == L'-' && HexaToByte(String,&Guid->Data4[0]) && HexaToByte(String,&Guid->Data4[1]) && *String++ == L'-' && HexaToByte(String,&Guid->Data4[2]) && HexaToByte(String,&Guid->Data4[3]) && HexaToByte(String,&Guid->Data4[4]) && HexaToByte(String,&Guid->Data4[5]) && HexaToByte(String,&Guid->Data4[6]) && HexaToByte(String,&Guid->Data4[7]) && *String++==L'}' && *String==0);
}
//-------------------------------------------------------------------------------------------------------
LPCWSTR InterfaceGuidName(GUID* Guid)
{
	#undef DEFINE_GUID
	#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } } ;
	
	#include "StandardInterfaces.xxx"

	#undef DEFINE_GUID
	#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) {&name, TEXT(#name)},

	struct
	{
		GUID*													Guid;
		LPCWSTR													Name;
	} GuidName[] =
	{
		#include "StandardInterfaces.xxx"
	};

	for (int Index=0;Index<_countof(GuidName);Index++)
	{
		if (*GuidName[Index].Guid==*Guid)
		{
			return(GuidName[Index].Name);
		}
	}

	return(L"UNKNOWN INTERFACE GUID !");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HKEY														HKey;

	// !!! DEVICE INTERFACE CLASSES su ulozene v KEY [HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\DeviceClasses].
	DWORD														Code=RegOpenKey(HKEY_LOCAL_MACHINE,REGSTR_PATH_DEVICE_CLASSES,&HKey);

	if (Code==ERROR_SUCCESS)
	{
		wchar_t													KeyName[256];
		DWORD													DeviceIndex;

		// !!! Spusti sa enumeracia DEVICE INTERFACE CLASSES, ktore su ulozene v [HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\DeviceClasses].
		for (DWORD KeyIndex=0;RegEnumKey(HKey,KeyIndex,KeyName,256)==ERROR_SUCCESS;KeyIndex++)
		{
			GUID												InterfaceGUID;

			if (GuidFromString(&InterfaceGUID,KeyName)==FALSE)
			{
				continue;
			}

			wprintf_s(L"\nKEY [%s], NAME [%s]:\n",KeyName,InterfaceGuidName(&InterfaceGUID));

			// !!! Otvori sa DEVICE INFORMATION SET, ktory umoznuje enumerovat DEVICE INTERFACES, ktore su zaregistrovane pre dany DEVICE INTERFACE CLASS.
			HDEVINFO											InfoSet=SetupDiGetClassDevs(&InterfaceGUID,NULL,NULL,DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

			if (InfoSet==INVALID_HANDLE_VALUE)
			{
				wprintf_s(L"\tNO DEVICES !\n");
				continue;
			}

			SP_DEVICE_INTERFACE_DATA							InterfaceData={sizeof(SP_DEVICE_INTERFACE_DATA)};

			// !!! Enumeruju sa DEVICE INTERFACES pre definovany DEVICE INTERFACE CLASS (InterfaceGUID).
			for (DeviceIndex=0;SetupDiEnumDeviceInterfaces(InfoSet,NULL,&InterfaceGUID,DeviceIndex,&InterfaceData)==TRUE;DeviceIndex++)
			{
				SP_DEVINFO_DATA									DeviceData={sizeof(SP_DEVINFO_DATA)};

				// !!! Ziskaju sa detailne INFORMATION o DEVICE INTERFACE.
				if (SetupDiGetDeviceInterfaceDetail(InfoSet,&InterfaceData,NULL,0,NULL,&DeviceData)==TRUE || GetLastError()!=ERROR_INSUFFICIENT_BUFFER)
				{
					continue;
				}

				wchar_t											InterfaceName[512];

				InterfaceName[0]='\0';

				// !!! Otvori sa KEY obsahujuci informacie o DEVICE INTERFACE.
				HKEY											InterfaceKey=SetupDiOpenDeviceInterfaceRegKey(InfoSet,&InterfaceData,0,KEY_READ);

				if (InterfaceKey!=INVALID_HANDLE_VALUE)
				{
					DWORD										Size=sizeof(InterfaceName);

					// Ziska sa FRIENDLY NAME daneho DEVICE.
					RegQueryValueEx(InterfaceKey,L"FriendlyName",0,NULL,(BYTE*)InterfaceName,&Size);

					RegCloseKey(InterfaceKey);

					if (InterfaceName[0]!=NULL)
					{
						wcscat_s((LPWSTR)InterfaceName,_countof(InterfaceName),L"/");
					}
				}

				BYTE											DeviceName[512];

				// !!! Ziska sa DEVICE INTERFACE PROPERTY NAME 'SPDRP_FRIENDLYNAME' z DEVICE INTERFACE.
				if (SetupDiGetDeviceRegistryProperty(InfoSet,&DeviceData,SPDRP_FRIENDLYNAME,NULL,DeviceName,sizeof(DeviceName),NULL)==TRUE || SetupDiGetDeviceRegistryProperty(InfoSet,&DeviceData,SPDRP_DEVICEDESC,NULL,DeviceName,sizeof(DeviceName),NULL)==TRUE)
				{
					wprintf_s(L"\t%s%s !\n",InterfaceName,(wchar_t*)DeviceName);
				}
			}

			// !!! Uvolni DEVICE INFORMATION SET.
			SetupDiDestroyDeviceInfoList(InfoSet);

			if (DeviceIndex==0)
			{
				wprintf_s(L"\tNO DEVICES !\n");
				continue;
			}
		}

		RegCloseKey(HKey);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HKEY														HKey;

	// !!! DEVICE INTERFACE CLASSES su ulozene v KEY [HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\DeviceClasses].
	DWORD														Code=RegOpenKey(HKEY_LOCAL_MACHINE,REGSTR_PATH_DEVICE_CLASSES,&HKey);

	if (Code==ERROR_SUCCESS)
	{
		wchar_t													KeyName[256];
		DWORD													DeviceIndex;

		// !!! Spusti sa enumeracia DEVICE INTERFACE CLASSES, ktore su ulozene v [HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\DeviceClasses].
		for (DWORD KeyIndex=0;RegEnumKey(HKey,KeyIndex,KeyName,256)==ERROR_SUCCESS;KeyIndex++)
		{
			GUID												InterfaceGUID;

			if (GuidFromString(&InterfaceGUID,KeyName)==FALSE)
			{
				continue;
			}

			wprintf_s(L"\nKEY [%s], NAME [%s]:\n",KeyName,InterfaceGuidName(&InterfaceGUID));

			// !!! Otvori sa DEVICE INFORMATION SET, ktory umoznuje enumerovat DEVICE INTERFACES, ktore su zaregistrovane pre dany DEVICE INTERFACE CLASS.
			HDEVINFO											InfoSet=SetupDiGetClassDevs(&InterfaceGUID,NULL,NULL,DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

			if (InfoSet==INVALID_HANDLE_VALUE)
			{
				wprintf_s(L"\tNO DEVICES !\n");
				continue;
			}

			SP_DEVICE_INTERFACE_DATA							InterfaceData={sizeof(SP_DEVICE_INTERFACE_DATA)};

			// !!! Enumeruju sa DEVICE INTERFACES pre definovany DEVICE INTERFACE CLASS (InterfaceGUID).
			for (DeviceIndex=0;SetupDiEnumDeviceInterfaces(InfoSet,NULL,&InterfaceGUID,DeviceIndex,&InterfaceData)==TRUE;DeviceIndex++)
			{
				SP_DEVINFO_DATA									DeviceData={sizeof(SP_DEVINFO_DATA)};
				const int										BUFFER_SIZE=1000;
				wchar_t											DetailDataBuffer[BUFFER_SIZE+sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA)];
				SP_DEVICE_INTERFACE_DETAIL_DATA*				DetailData=(SP_DEVICE_INTERFACE_DETAIL_DATA*)&DetailDataBuffer;

				DetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

				// !!! Ziskaju sa detailne INFORMATION o DEVICE INTERFACE.
				if (SetupDiGetDeviceInterfaceDetail(InfoSet,&InterfaceData,DetailData,BUFFER_SIZE,NULL,&DeviceData)==FALSE)
				{
					wprintf_s(L"Can't get DEVICE INTERFACE DETAILS !\n");
					continue;
				}

				// !!!!! Obsahuje SYMBOLIC LINK na DEVICE OBJECT, ktory je mozne pouzit vo FUNCTION CreateFile() na ziskanie HANDLE na DEVICE.
				wprintf_s(L"DEVICE INTERFACE PATH [%s] !\n",DetailData->DevicePath);
			}

			// !!! Uvolni DEVICE INFORMATION SET.
			SetupDiDestroyDeviceInfoList(InfoSet);

			if (DeviceIndex==0)
			{
				wprintf_s(L"\tNO DEVICES !\n");
				continue;
			}
		}

		RegCloseKey(HKey);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int __cdecl wmain(int, wchar_t*)
{
	//Test1();
	Test2();

	wprintf_s(L"Press any KEY to EXIT !");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------