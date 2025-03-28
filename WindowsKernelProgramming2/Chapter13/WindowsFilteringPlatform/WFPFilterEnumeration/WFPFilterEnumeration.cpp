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
wstring GuidToString(const GUID& Guid)
{
	WCHAR														GuidString[64];

	if (StringFromGUID2(Guid,GuidString,_countof(GuidString))>0)
	{
		wstring													Result(GuidString);

		return(Result);
	}
	else
	{
		return(L"");
	}
}
//----------------------------------------------------------------------------------------------------------------------
const wchar_t* ActionToString(const FWPM_ACTION& Action)
{
	if (Action.type==FWP_ACTION_BLOCK)
	{
		return(L"Block");
	}
	else if (Action.type==FWP_ACTION_PERMIT)
	{
		return(L"Permit");
	}
	else if (Action.type==FWP_ACTION_CALLOUT_TERMINATING)
	{
		return(L"Callout Terminating");
	}
	else if (Action.type==FWP_ACTION_CALLOUT_INSPECTION)
	{
		return(L"Callout Inspection");
	}
	else if (Action.type==FWP_ACTION_CALLOUT_UNKNOWN)
	{
		return(L"Callout Unknown");
	}
	else if (Action.type==FWP_ACTION_CONTINUE)
	{
		return(L"Continue");
	}
	else if (Action.type==FWP_ACTION_NONE)
	{
		return(L"None");
	}
	else if (Action.type==FWP_ACTION_NONE_NO_MATCH)
	{
		return(L"None (No Match)");
	}
	else
	{
		return(L"");
	}
}
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
		HANDLE													HandleEnum;

		Result=FwpmFilterCreateEnumHandle(HandleEngine,nullptr,&HandleEnum);

		if (Result==ERROR_SUCCESS)
		{
			UINT32												NumberOfFiltersReturned;
			FWPM_FILTER**										Filters;

			Result=FwpmFilterEnum(HandleEngine,HandleEnum,8192,&Filters,&NumberOfFiltersReturned);

			if (Result==ERROR_SUCCESS)
			{
				for (UINT32 Index=0;Index<NumberOfFiltersReturned;Index++)
				{
					FWPM_FILTER*								Filter=Filters[Index];
					wstring										Guid=GuidToString(Filter->filterKey);
					wstring										FilterAction=ActionToString(Filter->action);

					wcout << L"[" << (Index+1) << L"]. FILTER [" << Filter->displayData.name << L"] - GUID [" << Guid << L"] ID [" << Filter->filterId << L"] NUMBER OF CONDITIONS [" << Filter->numFilterConditions << L"] FILER ACTION [" << FilterAction << L"]." << endl;
				}

				FwpmFreeMemory((void**)&Filters);
			}
			else
			{
				wcout << L"FAILED to ENUMERATE FILTER OBJECTS with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
			}

			FwpmFilterDestroyEnumHandle(HandleEngine,HandleEnum);
		}
		else
		{
			wcout << L"FAILED to OPEN FILTER ENUMERATION OBJECT with ERROR [" << format(L"0x{:08X}",Result) << L"]." << endl;
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