//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fwpmu.h>
#include <vector>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! Tento HEADER MUSI byt vlozeny, aby MACRO [DEFINE_GUID()] vykonalo DEFINITION daneho GUID.
#include <initguid.h>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\MyCallout\SharedHeader.h"
#include "SCalloutSettings.h"
#include "SFilterSettings.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! WINDOWS FILTERING PLATFORM USER MODE PROGRAMS MUSIA mat vlozenu LIBRARY [Fwpuclnt.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DEFINE_GUID(GUID_MY_WINDOWS_FILTERING_PLATFORM_PROVIDER, 0x17fb4a74, 0x5d73, 0x4369, 0x87, 0xbb, 0xf8, 0x11, 0x29, 0x6d, 0xc, 0xe8);
//----------------------------------------------------------------------------------------------------------------------
DEFINE_GUID(GUID_MY_FILTER_BLOCK_V4, 0x18651c8b, 0x2172, 0x4485, 0x9e, 0xe6, 0x7c, 0x49, 0xb5, 0xe4, 0xbf, 0x8d);
DEFINE_GUID(GUID_MY_FILTER_BLOCK_V6, 0x8d47f9d0, 0x500e, 0x4564, 0x9c, 0x9b, 0x28, 0x3, 0x64, 0xe, 0x9a, 0x3a);
DEFINE_GUID(GUID_MY_FILTER_BLOCK_UDP_V4, 0xefa3e4b2, 0x55ea, 0x4e6d, 0xa4, 0x79, 0x1b, 0xbb, 0x1a, 0x58, 0x53, 0x54);
DEFINE_GUID(GUID_MY_FILTER_BLOCK_UDP_V6, 0xb810904, 0x54ad, 0x4302, 0x97, 0x9a, 0x42, 0xb3, 0x82, 0x44, 0xb1, 0x3e);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_BLOCK_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,BLOCK_PROCESS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_PERMIT_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,PERMIT_PROCESS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_PROCESSES CTL_CODE(FILE_DEVICE_UNKNOWN,CLEAR_PROCESSES,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DWORD RegisterProvider(const GUID& ProviderID, wchar_t* ProviderName)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		FWPM_PROVIDER*											Provider;

		// !!!!! Zistuje sa ci PROVIDER je zaregistrovany.
		Result=FwpmProviderGetByKey(HandleEngine,&ProviderID,&Provider);

		// !!!!! PROVIDER uz bol najdeny a tak ho netreba opat registrovat.
		if (Result==ERROR_SUCCESS)
		{
			wcout << L"REGISTER PROVIER - PROVIDER was FOUND." << endl;

			FwpmFreeMemory((void**)&Provider);
		}
		// !!!!! PROVIDER nebol najdeny, a preto musi byt zaregistrovany.
		else
		{
			wcout << L"REGISTER PROVIER - PROVIDER was NOT FOUND." << endl;
			//wcout << L"REGISTER PROVIER - PROVIDER was NOT FOUND with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;

			FWPM_PROVIDER										ProviderData{};

			ProviderData.displayData.name=ProviderName;
			ProviderData.providerKey=ProviderID;
			ProviderData.flags=FWPM_PROVIDER_FLAG_PERSISTENT;

			Result=FwpmProviderAdd(HandleEngine,&ProviderData,nullptr);

			if (Result==ERROR_SUCCESS)
			{
				wcout << L"REGISTER PROVIER - PROVIDER was ADDED to SYSTEM." << endl;
			}
			else
			{
				wcout << L"REGISTER PROVIER - PROVIDER was NOT ADDED to SYSTEM with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
			}
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"REGISTER PROVIER - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
DWORD UnregisterProvider(const GUID& ProviderID)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		FWPM_PROVIDER*											Provider;

		// !!!!! Zistuje sa ci PROVIDER je zaregistrovany.
		Result=FwpmProviderGetByKey(HandleEngine,&ProviderID,&Provider);

		if (Result==ERROR_SUCCESS)
		{
			wcout << L"UNREGISTER PROVIER - PROVIDER was FOUND." << endl;

			FwpmFreeMemory((void**)&Provider);

			Result=FwpmProviderDeleteByKey(HandleEngine,&ProviderID);

			if (Result==ERROR_SUCCESS)
			{
				wcout << L"UNREGISTER PROVIER - PROVIDER was UNREGISTERED." << endl;
			}
			else
			{
				wcout << L"UNREGISTER PROVIER - FAILED to UNREGISTER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
			}
		}
		else
		{
			wcout << L"UNREGISTER PROVIER - PROVIDER was NOT FOUND with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"UNREGISTER PROVIER - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DWORD AddCallouts(const vector<SCalloutSettings>& CalloutSettings, const GUID& ProviderID)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		Result=FwpmTransactionBegin(HandleEngine,0);

		if (Result==ERROR_SUCCESS)
		{
			for(const SCalloutSettings& CalloutSetting : CalloutSettings)
			{
				FWPM_CALLOUT*									ExistingCallout;

				Result=FwpmCalloutGetByKey(HandleEngine,CalloutSetting.MGuid,&ExistingCallout);

				if (Result==ERROR_SUCCESS)
				{
					wcout << L"ADD CALLOUTS - CALLOUT DRIVER [" << CalloutSetting.MName << L"] is ALREADY REGISTERED." << endl;

					FwpmFreeMemory((void**)&ExistingCallout);
				}
				else
				{
					FWPM_CALLOUT								Callout{};

					Callout.applicableLayer=*CalloutSetting.MLayer;
					Callout.calloutKey=*CalloutSetting.MGuid;
					Callout.displayData.name=(wchar_t*)CalloutSetting.MName;
					Callout.providerKey=(GUID*)&ProviderID;

					Result=FwpmCalloutAdd(HandleEngine,&Callout,nullptr,nullptr);

					if (Result==ERROR_SUCCESS)
					{
						wcout << L"ADD CALLOUTS - CALLOUT DRIVER [" << CalloutSetting.MName << L"] ADDED to SYSTEM." << endl;
					}
					else
					{
						wcout << L"ADD CALLOUTS - FAILED to ADD CALLOUT DRIVER [" << CalloutSetting.MName << L"] with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
						break;
					}
				}
			}

			if (Result==ERROR_SUCCESS)
			{
				Result=FwpmTransactionCommit(HandleEngine);

				if (Result!=ERROR_SUCCESS)
				{
					wcout << L"ADD CALLOUTS - FAILED to COMMIT TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}
			else
			{
				DWORD											LocalResult=FwpmTransactionAbort(HandleEngine);

				if (LocalResult!=ERROR_SUCCESS)
				{
					wcout << L"ADD CALLOUTS - FAILED to ABORT TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}
		}
		else
		{
			wcout << L"ADD CALLOUTS - FAILED to BEGIN TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"ADD CALLOUTS - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
DWORD DeleteCallouts(const vector<SCalloutSettings>& CalloutSettings)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		for(const SCalloutSettings& CalloutSetting : CalloutSettings)
		{
			DWORD												LocalResult=FwpmCalloutDeleteByKey(HandleEngine,CalloutSetting.MGuid);

			if (LocalResult==ERROR_SUCCESS)
			{
				wcout << L"DELETE CALLOUTS - CALLOUT DRIVER [" << CalloutSetting.MName << L"] was DELETED from SYSTEM." << endl;
			}
			else
			{
				wcout << L"DELETE CALLOUTS - FAILED to DELETE CALLOUT DRIVER [" << CalloutSetting.MName << L"] with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;

				Result=LocalResult;
			}
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"DELETE CALLOUTS - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DWORD AddFilters(const vector<SFilterSettings>& FilterSettings, const GUID& ProviderID)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		Result=FwpmTransactionBegin(HandleEngine,0);

		if (Result==ERROR_SUCCESS)
		{
			for(const SFilterSettings& FilterSetting : FilterSettings)
			{
				FWPM_FILTER*									ExistingFilter;

				Result=FwpmFilterGetByKey(HandleEngine,FilterSetting.MGuid,&ExistingFilter);

				if (Result==ERROR_SUCCESS)
				{
					wcout << L"ADD FILTERS - FILTER [" << FilterSetting.MName << L"] is ALREADY REGISTERED." << endl;

					FwpmFreeMemory((void**)&ExistingFilter);
				}
				else
				{
					FWPM_FILTER									Filter{};

					Filter.filterKey=*FilterSetting.MGuid;
					Filter.providerKey=(GUID*)&ProviderID;
					Filter.displayData.name=(wchar_t*)FilterSetting.MName;
					Filter.weight.uint8=8;
					Filter.weight.type=FWP_UINT8;
					Filter.layerKey=*FilterSetting.MLayer;
					Filter.action.type=FWP_ACTION_CALLOUT_UNKNOWN;
					Filter.action.calloutKey=*FilterSetting.MCallout;

					Result=FwpmFilterAdd(HandleEngine,&Filter,nullptr,nullptr);

					if (Result==ERROR_SUCCESS)
					{
						wcout << L"ADD FILTERS - FILTER [" << FilterSetting.MName << L"] ADDED to SYSTEM." << endl;
					}
					else
					{
						wcout << L"ADD FILTERS - FAILED to ADD FILTER [" << FilterSetting.MName << L"] with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
						break;
					}
				}
			}

			if (Result==ERROR_SUCCESS)
			{
				Result=FwpmTransactionCommit(HandleEngine);

				if (Result!=ERROR_SUCCESS)
				{
					wcout << L"ADD FILTERS - FAILED to COMMIT TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}
			else
			{
				DWORD											LocalResult=FwpmTransactionAbort(HandleEngine);

				if (LocalResult!=ERROR_SUCCESS)
				{
					wcout << L"ADD FILTERS - FAILED to ABORT TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}
		}
		else
		{
			wcout << L"ADD FILTERS - FAILED to BEGIN TRANSACTION with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"ADD FILTERS - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
DWORD DeleteFilters(const vector<SFilterSettings>& FilterSettings)
{
	DWORD														Result;
	HANDLE														HandleEngine;

	Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		for(const SFilterSettings& FilterSetting : FilterSettings)
		{
			DWORD												LocalResult=FwpmFilterDeleteByKey(HandleEngine,FilterSetting.MGuid);

			if (LocalResult==ERROR_SUCCESS)
			{
				wcout << L"DELETE FILTERS - FILTER [" << FilterSetting.MName << L"] was DELETED from SYSTEM." << endl;
			}
			else
			{
				wcout << L"DELETE FILTERS - FAILED to DELETE FILTER [" << FilterSetting.MName << L"] with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;

				Result=LocalResult;
			}
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"DELETE FILTERS - FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void BlockProcess(HANDLE DeviceHandle, ULONG PID)
{
	DWORD														BytesReturned;

	if (DeviceIoControl(DeviceHandle,IOCTL_BLOCK_PROCESS,&PID,sizeof(PID),nullptr,0,&BytesReturned,NULL)!=FALSE)
	{
		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [BLOCK_PROCESS] SUCCEEDED - BYTES RETURNED [" << BytesReturned << L"] !" << endl;

		wcout << L"MAIN - PROGRAM [" << PID << L"] is now BLOCKED." << endl;
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [BLOCK_PROCESS] FAILED - ERROR [" << Error << L"] !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void PermitProcess(HANDLE DeviceHandle, ULONG PID)
{
	DWORD														BytesReturned;

	if (DeviceIoControl(DeviceHandle,IOCTL_PERMIT_PROCESS,&PID,sizeof(PID),nullptr,0,&BytesReturned,NULL)!=FALSE)
	{
		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [PERMIT_PROCESS] SUCCEEDED - BYTES RETURNED [" << BytesReturned << L"] !" << endl;

		wcout << L"MAIN - PROGRAM [" << PID << L"] is now PERMITTED." << endl;
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [PERMIT_PROCESS] FAILED - ERROR [" << Error << L"] !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void ClearProcesses(HANDLE DeviceHandle)
{
	DWORD														BytesReturned;

	if (DeviceIoControl(DeviceHandle,IOCTL_CLEAR_PROCESSES,nullptr,0,nullptr,0,&BytesReturned,NULL)!=FALSE)
	{
		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [CLEAR_PROCESSES] SUCCEEDED - BYTES RETURNED [" << BytesReturned << L"] !" << endl;

		wcout << L"MAIN - ALL PROGRAMS are now PERMITTED." << endl;
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"MAIN - OPERATION DEVICE IO CONTROL [CLEAR_PROCESSES] FAILED - ERROR [" << Error << L"] !" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintMenu(void)
{
	wcout << L"--------------------------------------------------------------------------------" << endl;

	wcout << L"COMMANDS: block [PID] | permit [PID] | clear | exit." << endl;

	wcout << L"--------------------------------------------------------------------------------" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteMenu(HANDLE DeviceHandle)
{
	constexpr size_t											BUFFER_SIZE=200;

	wchar_t														Buffer[BUFFER_SIZE];

	while(true)
	{
		PrintMenu();

		wchar_t*												Result=fgetws(Buffer,BUFFER_SIZE,stdin);

		fseek(stdin,SEEK_END,0);

		wistringstream											CommandStream(Buffer);
		wstring													CommandID;

		CommandStream >> CommandID;

		if (CommandID==L"block")
		{
			ULONG												PID;

			CommandStream >> PID;

			if (CommandStream.good()==true)
			{
				BlockProcess(DeviceHandle,PID);
			}
			else
			{
				wcout << L"PID can't be PARSED !" << endl;
			}
		}
		else if (CommandID==L"permit")
		{
			ULONG												PID;

			CommandStream >> PID;

			if (CommandStream.good()==true)
			{
				PermitProcess(DeviceHandle,PID);
			}
			else
			{
				wcout << L"PID can't be PARSED !" << endl;
			}
		}
		else if (CommandID==L"clear")
		{
			ClearProcesses(DeviceHandle);
		}
		else if (CommandID==L"exit")
		{
			break;
		}
		else
		{
			wcout << L"UNSUPPORTED COMMAND !" << endl;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	SafeMain();

	PrintLineSeparator();

	GUID														ProviderGuid=GUID_MY_WINDOWS_FILTERING_PLATFORM_PROVIDER;

	vector<SCalloutSettings>									CalloutSettings;

	CalloutSettings.push_back(SCalloutSettings{L"CALLOUT BLOCK IPv4",&GUID_MY_CALLOUT_DRIVER_BLOCK_V4,&FWPM_LAYER_ALE_AUTH_CONNECT_V4});
	CalloutSettings.push_back(SCalloutSettings{L"CALLOUT BLOCK IPv6",&GUID_MY_CALLOUT_DRIVER_BLOCK_V6,&FWPM_LAYER_ALE_AUTH_CONNECT_V6});
	CalloutSettings.push_back(SCalloutSettings{L"CALLOUT BLOCK UDP IPv4",&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V4,&FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4});
	CalloutSettings.push_back(SCalloutSettings{L"CALLOUT BLOCK UDP IPv6",&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V6,&FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6});

	vector<SFilterSettings>										FilterSettings;

	FilterSettings.push_back(SFilterSettings{L"FILTER BLOCK IPv4",&GUID_MY_FILTER_BLOCK_V4,&FWPM_LAYER_ALE_AUTH_CONNECT_V4,&GUID_MY_CALLOUT_DRIVER_BLOCK_V4});
	FilterSettings.push_back(SFilterSettings{L"FILTER BLOCK IPv6",&GUID_MY_FILTER_BLOCK_V6,&FWPM_LAYER_ALE_AUTH_CONNECT_V6,&GUID_MY_CALLOUT_DRIVER_BLOCK_V6});
	FilterSettings.push_back(SFilterSettings{L"FILTER BLOCK UDP IPv4",&GUID_MY_FILTER_BLOCK_UDP_V4,&FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4,&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V4});
	FilterSettings.push_back(SFilterSettings{L"FILTER BLOCK UDP IPv6",&GUID_MY_FILTER_BLOCK_UDP_V6,&FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6,&GUID_MY_CALLOUT_DRIVER_BLOCK_UDP_V6});

	const wchar_t*												SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

	HANDLE														DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		DWORD													Result;

		Result=RegisterProvider(ProviderGuid,(wchar_t*)L"My PROVIDER");

		if (Result==ERROR_SUCCESS)
		{
			Result=AddCallouts(CalloutSettings,ProviderGuid);

			if (Result==ERROR_SUCCESS)
			{
				Result=AddFilters(FilterSettings,ProviderGuid);

				if (Result==ERROR_SUCCESS)
				{
					ExecuteMenu(DeviceHandle);

					Result=DeleteFilters(FilterSettings);

					if (Result!=ERROR_SUCCESS)
					{
						wcout << L"MAIN - FAILED to DELETE FILTERS with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
					}
				}
				else
				{
					wcout << L"MAIN - FAILED to REGISTER FILTERS with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}

				Result=DeleteCallouts(CalloutSettings);

				if (Result!=ERROR_SUCCESS)
				{
					wcout << L"MAIN - FAILED to DELETE CALLOUT DRIVERS with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}
			else
			{
				wcout << L"MAIN - FAILED to REGISTER CALLOUT DRIVERS with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
			}

			Result=UnregisterProvider(ProviderGuid);

			if (Result!=ERROR_SUCCESS)
			{
				wcout << L"MAIN - FAILED to UNREGISTER PROVIDER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
			}
		}
		else
		{
			wcout << L"MAIN - FAILED to REGISTER PROVIDER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
		}
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------