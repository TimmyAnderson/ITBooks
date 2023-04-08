//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "ConnectionPointsServer_h.h"
//------------------------------------------------------------------------------------------------------
struct SConnectionPointsEntry
{
	DWORD														CookieInGIT;
};
//------------------------------------------------------------------------------------------------------
class CConnectionPointsManager
{
	private:
		static const int										MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES=4;

	private:
		CCriticalSectionWrapper									MCS;
		SConnectionPointsEntry									MEntries[MAX_NUMBER_OF_CONNECTION_POINTS_ENTRIES];

	public:
        HRESULT Advise(IMyConnectionPointsCallback* Callback, DWORD* Cookie);
        HRESULT Unadvise(DWORD Cookie);
        void FireCallback(bstr_t MessageToClient);

	public:
		CConnectionPointsManager(void);
		virtual ~CConnectionPointsManager(void);
};
//------------------------------------------------------------------------------------------------------