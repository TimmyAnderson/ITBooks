#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "Helpers\CFastMutex.h"
#include "SNote.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CPlaybackState final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		LIST_ENTRY												MHead;
		CFastMutex												MLock;
		PAGED_LOOKASIDE_LIST									MLookaside;
		KSEMAPHORE												MCounter;
		KEVENT													MStopEvent;
		HANDLE													MThread;

	private:
		static void PlayMelodyThread(PVOID Context);

	private:
		void PlayMelody(void);

	public:
		NTSTATUS Start(PVOID IoObject);
		void Stop(void);
		NTSTATUS AddNotes(const SNote* Notes, ULONG Count);

	public:
		CPlaybackState(void);
		~CPlaybackState(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------