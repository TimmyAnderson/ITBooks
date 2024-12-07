//----------------------------------------------------------------------------------------------------------------------
#include "CDeviceHelpers.h"
#include "Helpers\CLocker.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CDeviceHelpers::Init(void)
{
	MSpinLock.Init();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CDeviceHelpers::SetDevice(PDRIVER_OBJECT DriverObject, PDRIVER_DISPATCH MajorFunction, PDRIVER_UNLOAD DriverUnload)
{
	CLocker														Locker(MSpinLock);

	{
		if (MDriverObject==nullptr)
		{
			for(UCHAR Index=0;Index<=IRP_MJ_MAXIMUM_FUNCTION;Index++)
			{
				MMajorFunctions[Index]=static_cast<PDRIVER_DISPATCH>(InterlockedExchangePointer((PVOID*)&DriverObject->MajorFunction[Index],MajorFunction));

				KdPrint(("!!!!! SET - MAJOR FUNCTION [%hhu] DISPATCH ROUTINE [%p] !!!\n",Index,MMajorFunctions[Index]));
			}

			MDriverUnload=static_cast<PDRIVER_UNLOAD>(InterlockedExchangePointer((PVOID*)&DriverObject->DriverUnload,DriverUnload));

			MDriverObject=DriverObject;

			return(true);
		}
		else
		{
			return(false);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
bool CDeviceHelpers::ClearDevice(void)
{
	CLocker														Locker(MSpinLock);

	{
		if (MDriverObject!=nullptr)
		{
			for(UCHAR Index=0;Index<=IRP_MJ_MAXIMUM_FUNCTION;Index++)
			{
				InterlockedExchangePointer((PVOID*)&MDriverObject->MajorFunction[Index],MMajorFunctions[Index]);

				KdPrint(("!!!!! CLEAR - MAJOR FUNCTION [%hhu] DISPATCH ROUTINE [%p] !!!\n",Index,MMajorFunctions[Index]));
			}

			InterlockedExchangePointer((PVOID*)&MDriverObject->DriverUnload,MDriverUnload);

			// !!! Uvolni sa ziskany POINTER na DRIVER OBJECT.
			ObDereferenceObject(MDriverObject);
			MDriverObject=nullptr;

			return(true);
		}
		else
		{
			return(false);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CDeviceHelpers::CallOriginalDispatchRoutine(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	CLocker														Locker(MSpinLock);

	{
		if (MDriverObject!=nullptr)
		{
			IO_STACK_LOCATION*									CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
			UCHAR												MajorFunction=CurrentStackLocation->MajorFunction;
			NTSTATUS											Status=MMajorFunctions[MajorFunction](DeviceObject,Irp);

			return(Status);
		}
		else
		{
			return(STATUS_SUCCESS);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
void CDeviceHelpers::CallOriginalDriverUnloadRoutine(PDRIVER_OBJECT DriverObject)
{
	CLocker														Locker(MSpinLock);

	{
		if (MDriverObject!=nullptr)
		{
			MDriverUnload(DriverObject);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------