//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ConnectionPointsManager.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CConnectionPointsManager::CConnectionPointsManager(void)
{
	for (int Index=0;Index<MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES;Index++)
	{
		MEntries[Index].CookieInGIT=0;
	}
}
//------------------------------------------------------------------------------------------------------
CConnectionPointsManager::~CConnectionPointsManager(void)
{
	CSmartCOMPointer<IGlobalInterfaceTable>						GIT;

	if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
	{
		for (int Index=0;Index<MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES;Index++)
		{
			if (MEntries[Index].CookieInGIT!=0)
			{
				if (FAILED(GIT->RevokeInterfaceFromGlobal(MEntries[Index].CookieInGIT)))
				{
					wprintf_s(L"!!!!! ERROR - Can't remote entry from GIT !\n");
				}

				MEntries[Index].CookieInGIT=0;
			}
		}

		GIT=NULL;
	}
	else
	{
		wprintf_s(L"!!!!! ERROR - Can't create GIT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT CConnectionPointsManager::Advise(IMyConnectionPointsCallback* Callback, DWORD* Cookie)
{
	CLock														Lock(MCS);
	int															IndexToAdd=-1;

	for (int Index=0;Index<MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES;Index++)
	{
		if (MEntries[Index].CookieInGIT==0)
		{
			IndexToAdd=Index;
			break;
		}
	}

	if (IndexToAdd!=-1)
	{
		HRESULT													HR;
		CSmartCOMPointer<IGlobalInterfaceTable>					GIT;

		if (SUCCEEDED(HR=CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
		{
			if (SUCCEEDED(HR=GIT->RegisterInterfaceInGlobal(Callback,__uuidof(IMyConnectionPointsCallback),&MEntries[IndexToAdd].CookieInGIT)))
			{
				*Cookie=MEntries[IndexToAdd].CookieInGIT;
				HR=S_OK;
			}
			else
			{
				wprintf_s(L"!!!!! ERROR - Can't ADD entry from GIT !\n");
			}

			GIT=NULL;

			return(HR);
		}
		else
		{
			wprintf_s(L"!!!!! ERROR - Can't create GIT !\n");

			return(HR);
		}
	}
	else
	{
		wprintf_s(L"!!!!! ERROR - No space to ADVISE CALLBACK COM INTERFACE !\n");

		return(CONNECT_E_ADVISELIMIT);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT CConnectionPointsManager::Unadvise(DWORD Cookie)
{
	CLock														Lock(MCS);
	int															IndexToRemove=-1;

	for (int Index=0;Index<MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES;Index++)
	{
		if (MEntries[Index].CookieInGIT!=0 && MEntries[Index].CookieInGIT==Cookie)
		{
			IndexToRemove=Index;
			break;
		}
	}

	if (IndexToRemove!=-1)
	{
		HRESULT													HR;
		CSmartCOMPointer<IGlobalInterfaceTable>					GIT;

		if (SUCCEEDED(HR=CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
		{
			if (SUCCEEDED(HR=GIT->RevokeInterfaceFromGlobal(MEntries[IndexToRemove].CookieInGIT)))
			{
				MEntries[IndexToRemove].CookieInGIT=0;
				HR=S_OK;
			}
			else
			{
				wprintf_s(L"!!!!! ERROR - Can't REMOVE entry from GIT !\n");
			}

			GIT=NULL;

			return(HR);
		}
		else
		{
			wprintf_s(L"!!!!! ERROR - Can't create GIT !\n");

			return(HR);
		}
	}
	else
	{
		wprintf_s(L"!!!!! ERROR - INVALID COOKIE !\n");

		return(E_POINTER);
	}
}
//------------------------------------------------------------------------------------------------------
void CConnectionPointsManager::FireCallback(bstr_t MessageToClient)
{
	CLock														Lock(MCS);
	CSmartCOMPointer<IGlobalInterfaceTable>						GIT;

	if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
	{
		for (int Index=0;Index<MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES;Index++)
		{
			if (MEntries[Index].CookieInGIT!=0)
			{
				CSmartCOMPointer<IMyConnectionPoints>			Callback;

				if (SUCCEEDED(GIT->GetInterfaceFromGlobal(MEntries[Index].CookieInGIT,__uuidof(IMyConnectionPointsCallback),(void**) &Callback)))
				{
					if (FAILED(Callback->SendMessageToServer(MessageToClient)))
					{
						wprintf_s(L"!!!!! ERROR - Can't call CALLBACK COM INTERFACE for INDEX [%d] !\n",Index);
					}

					Callback=NULL;
				}
				else
				{
					wprintf_s(L"!!!!! ERROR - Can't UNMARSHAL CALLBACK COM INTERFACE for INDEx [%d] !\n",Index);
				}
			}
		}

		GIT=NULL;
	}
	else
	{
		wprintf_s(L"!!!!! ERROR - Can't create GIT !\n");
	}
}
//------------------------------------------------------------------------------------------------------