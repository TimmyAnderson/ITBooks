#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "Helpers\CFastMutex.h"
#include "SNote.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CPlaybackStateSafe final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CFastMutex												MLockThread;
		CFastMutex												MLockList;
		LIST_ENTRY												MHead;
		PAGED_LOOKASIDE_LIST									MLookaside;
		KSEMAPHORE												MCounter;
		KEVENT													MStopEvent;
		HANDLE													MThread;

	private:
		static void PlayMelodyThread(PVOID Context);

	private:
		void PlayMelody(void);

	public:
		NTSTATUS Start(PVOID IoObject, HANDLE SystemProcessHandle);
		void Stop(void);
		NTSTATUS AddNotes(const SNote* Notes, ULONG Count);

	public:
		CPlaybackStateSafe(void);
		~CPlaybackStateSafe(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------