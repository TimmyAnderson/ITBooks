//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "Helpers\CExecutiveResourceGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CGlobals final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static constexpr int									MAX_PIDS=256;

	private:
		CExecutiveResourceGlobal								MLock;
		PVOID													MRegistrationHandle;
		ULONG													MPIDsCount;
		ULONG													MPIDs[MAX_PIDS];

	public:
		void Init(void);
		void Delete(void);

	public:
		PVOID GetRegistrationHandle(void);
		void SetRegistrationHandle(PVOID RegistrationHandle);
		CExecutiveResourceGlobal& GetLock(void);
		void IncrementPIDsCount(ULONG Value);
		void DecrementPIDsCount(ULONG Value);
		ULONG GetPIDsCount(void);
		void SetPIDsCount(ULONG Value);
		ULONG GetPID(int Index);
		void SetPID(int Index, ULONG PID);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------