//----------------------------------------------------------------------------------------------------------------------
#include "CGlobals.h"
#include "Helpers/CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CGlobals::CGlobals(void)
	: MProcessesLock(), MProcesses()
{
}
//----------------------------------------------------------------------------------------------------------------------
CGlobals::~CGlobals(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CGlobals::AddProcess(ULONG PID)
{
	NTSTATUS													Status;
	PEPROCESS													Process;
	HANDLE														PIDAsHandle=ULongToHandle(PID);

	Status=PsLookupProcessByProcessId(PIDAsHandle,&Process);

	if (NT_SUCCESS(Status)==true)
	{
		CLocker													Locker(MProcessesLock);

		{
			if(MProcesses.Contains(PID)==false)
			{
				MProcesses.Add(PID);
			}
		}

		ObDereferenceObject(Process);
	}

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CGlobals::DeleteProcess(ULONG PID)
{
	CLocker														Locker(MProcessesLock);

	{
		if (MProcesses.Remove(PID)==true)
		{
			return(STATUS_SUCCESS);
		}
		else
		{
			return(STATUS_NOT_FOUND);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CGlobals::ClearProcesses(void)
{
	CLocker														Locker(MProcessesLock);

	{
		MProcesses.Clear();
	}

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CGlobals::IsProcessBlocked(ULONG PID) const
{
	CLocker														Locker(MProcessesLock);

	{
		bool													HasPID=MProcesses.Contains(PID);

		return(HasPID);
	}
}
//----------------------------------------------------------------------------------------------------------------------