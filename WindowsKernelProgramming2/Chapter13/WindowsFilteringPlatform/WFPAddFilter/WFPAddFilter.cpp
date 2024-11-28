//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fwpmu.h>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! WINDOWS FILTERING PLATFORM USER MODE PROGRAMS MUSIA mat vlozenu LIBRARY [Fwpuclnt.lib].
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
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
static const GUID												MyIPv4FilterGuid={ 0x23851e71, 0x4998, 0x4a17, { 0xb2, 0x7f, 0x63, 0x78, 0x18, 0x51, 0xc4, 0x97 } };
static const GUID												MyIPv6FilterGuid={ 0x44016370, 0xa1d3, 0x4d68, { 0x90, 0xe0, 0xf7, 0xee, 0xa2, 0xdf, 0xf2, 0x2 } };
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	SafeMain();

	PrintLineSeparator();

	HANDLE														HandleEngine;
	DWORD														Result=FwpmEngineOpen(nullptr,RPC_C_AUTHN_DEFAULT,nullptr,nullptr,&HandleEngine);

	if (Result==ERROR_SUCCESS)
	{
		// !!! PATH na CHROME.
		WCHAR													Filename[]=LR"(C:\Program Files (x86)\Google\Chrome\Application\chrome.exe)";
		FWP_BYTE_BLOB*											AppId;

		// !!! Ziska APP ID z PROGRAM PATH. MEMORY MUSI byt uvolnena volani FUNCTION [FwpmFreeMemory()].
		Result=FwpmGetAppIdFromFileName(Filename,&AppId);

		if (Result==ERROR_SUCCESS)
		{
			bool												MyFilterIPv4Created=false;
			bool												MyFilterIPv6Created=false;

			{
				FWPM_FILTER										Filter{};
				WCHAR											FilterName[]=L"My Filter IPv4";

				Filter.filterKey=MyIPv4FilterGuid;

				Filter.displayData.name=FilterName;

				// !!! FILTER pre IPv4.
				Filter.layerKey=FWPM_LAYER_ALE_AUTH_CONNECT_V4;
				Filter.action.type=FWP_ACTION_BLOCK;

				FWPM_FILTER_CONDITION							Condition;

				Condition.fieldKey=FWPM_CONDITION_ALE_APP_ID;
				Condition.matchType=FWP_MATCH_EQUAL;
				Condition.conditionValue.type=FWP_BYTE_BLOB_TYPE;
				Condition.conditionValue.byteBlob=AppId;

				Filter.filterCondition=&Condition;
				Filter.numFilterConditions=1;

				Result=FwpmFilterAdd(HandleEngine,&Filter,nullptr,nullptr);

				if (Result==ERROR_SUCCESS)
				{
					MyFilterIPv4Created=true;

					wcout << L"MY IPv4 FILTER ADDED." << endl;
				}
				else
				{
					wcout << L"FAILED to ADD MY IPv4 FILTER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}

			{
				FWPM_FILTER										Filter{};
				WCHAR											FilterName[]=L"My Filter IPv6";

				Filter.filterKey=MyIPv6FilterGuid;

				Filter.displayData.name=FilterName;

				// !!! FILTER pre IPv6.
				Filter.layerKey=FWPM_LAYER_ALE_AUTH_CONNECT_V6;
				Filter.action.type=FWP_ACTION_BLOCK;

				FWPM_FILTER_CONDITION							Condition;

				Condition.fieldKey=FWPM_CONDITION_ALE_APP_ID;
				Condition.matchType=FWP_MATCH_EQUAL;
				Condition.conditionValue.type=FWP_BYTE_BLOB_TYPE;
				Condition.conditionValue.byteBlob=AppId;

				Filter.filterCondition=&Condition;
				Filter.numFilterConditions=1;

				Result=FwpmFilterAdd(HandleEngine,&Filter,nullptr,nullptr);

				if (Result==ERROR_SUCCESS)
				{
					MyFilterIPv6Created=true;

					wcout << L"MY IPv6 FILTER ADDED." << endl;
				}
				else
				{
					wcout << L"FAILED to ADD MY IPv6 FILTER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}

			if (MyFilterIPv4Created==true && MyFilterIPv6Created==true)
			{
				wcout << L"CHROME is now BLOCKED. Press any KEY to UNBLOCK." << endl;

				(void)_getch();
			}

			if (MyFilterIPv4Created==true)
			{
				Result=FwpmFilterDeleteByKey(HandleEngine,&MyIPv4FilterGuid);

				if (Result==ERROR_SUCCESS)
				{
					wcout << L"MY IPv4 FILTER REMOVED." << endl;
				}
				else
				{
					wcout << L"FAILED to REMOVE MY IPv4 FILTER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}

			if (MyFilterIPv6Created==true)
			{
				Result=FwpmFilterDeleteByKey(HandleEngine,&MyIPv6FilterGuid);

				if (Result==ERROR_SUCCESS)
				{
					wcout << L"MY IPv6 FILTER REMOVED." << endl;
				}
				else
				{
					wcout << L"FAILED to REMOVE MY IPv6 FILTER with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
				}
			}

			FwpmFreeMemory((void**)&AppId);
		}
		else
		{
			wcout << L"FAILED to GET APPLICATION ID with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
		}

		FwpmEngineClose(HandleEngine);
	}
	else
	{
		wcout << L"FAILED to OPEN FILTER ENGINE with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
	}

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------