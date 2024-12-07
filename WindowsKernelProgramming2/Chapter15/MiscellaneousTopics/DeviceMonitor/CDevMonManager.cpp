//----------------------------------------------------------------------------------------------------------------------
#include "CDevMonManager.h"
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CLocker.h"
#include "SDeviceExtension.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CDevMonManager::RemoveDevice(int Index)
{
	if (Index<0 || Index>=MAX_MONITORED_DEVICES)
	{
		return(false);
	}

	SMonitoredDevice&											Device=MDevices[Index];

	if (Device.MDeviceObject==nullptr)
	{
		return(false);
	}

	ExFreePoolWithTag(Device.MDeviceName.Buffer,MY_TAG);

	IoDetachDevice(Device.MLowerDeviceObject);

	IoDeleteDevice(Device.MDeviceObject);

	Device.MDeviceObject=nullptr;

	MMonitoredDeviceCount--;

	return(true);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const PDEVICE_OBJECT CDevMonManager::GetFilterDeviceObject(void) const
{
	return(MFilterDeviceObject);
}
//----------------------------------------------------------------------------------------------------------------------
void CDevMonManager::SetFilterDeviceObject(PDEVICE_OBJECT FilterDeviceObject)
{
	MFilterDeviceObject=FilterDeviceObject;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CDevMonManager::Init(PDRIVER_OBJECT Driver)
{
	MLock.Init();

	MDriverObject=Driver;
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CDevMonManager::AddDevice(PCWSTR Name)
{
	CLocker														Locker(MLock);

	{
		if (MMonitoredDeviceCount==MAX_MONITORED_DEVICES)
		{
			return(STATUS_BUFFER_TOO_SMALL);
		}

		int														DeviceIndex=FindDevice(Name);

		if (DeviceIndex>=0)
		{
			return(STATUS_SUCCESS);
		}

		for(int Index=0;Index<MAX_MONITORED_DEVICES;Index++)
		{
			if (MDevices[Index].MDeviceObject!=nullptr)
			{
				continue;
			}

			UNICODE_STRING										TargetName;

			RtlInitUnicodeString(&TargetName,Name);

			PFILE_OBJECT										FileObject;
			PDEVICE_OBJECT										LowerDeviceObject=nullptr;

			NTSTATUS											Status=IoGetDeviceObjectPointer(&TargetName,FILE_READ_DATA,&FileObject,&LowerDeviceObject);

			if (NT_SUCCESS(Status)==false)
			{
				KdPrint(("!!!!! DRIVER FAILED to FIND TARGET DEVICE OBJECT with ERROR CODE [%lX] !!!\n",Status));
				return(Status);
			}

			PDEVICE_OBJECT										DeviceObject=nullptr;
			WCHAR*												Buffer=nullptr;

			do
			{
				Status=IoCreateDevice(MDriverObject,sizeof(SDeviceExtension),nullptr,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!! DRIVER FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",Status));
					break;
				}

				Buffer=(WCHAR*)ExAllocatePool2(POOL_FLAG_NON_PAGED,TargetName.Length,MY_TAG);

				if (Buffer==nullptr)
				{
					KdPrint(("!!!!! DRIVER FAILED to ALLOCATE BUFFER !!!\n"));
					Status=STATUS_INSUFFICIENT_RESOURCES;
					break;
				}

				SDeviceExtension*								DeviceExtension=(SDeviceExtension*)DeviceObject->DeviceExtension;

				DeviceObject->Flags|=(LowerDeviceObject->Flags & (DO_BUFFERED_IO | DO_DIRECT_IO));
				DeviceObject->DeviceType=LowerDeviceObject->DeviceType;

				MDevices[Index].MDeviceName.Buffer=Buffer;
				MDevices[Index].MDeviceName.MaximumLength=TargetName.Length;

				RtlCopyUnicodeString(&MDevices[Index].MDeviceName,&TargetName);

				MDevices[Index].MDeviceObject=DeviceObject;

				// !!!!! Volanie FUNCTION OKAMZITE generuje INTERRUPT REQUEST PACKETS s MAJOR FUNCTION [IRP_MJ_CREATE] a MAJOR FUNCTION [IRP_MJ_CLEANUP], a kedze DISPATCH ROUTINES, ak chcu posielat tieto INTERRUPT REQUEST PACKETS do DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK, MUSIA mat uz k dispozicii POINTER na DEVICE OBJECT NIZSIE v DEVICE OBJECT STACK. Preto PARAMETER [PDEVICE_OBJECT* AttachedDevice] sa MUSI ukladat do VARIABLE, ktora je pristupna z DISPATCH ROUTINES.
				// !!!!! VARIABLE [DeviceExtension->MLowerDeviceObject] sa pouziva v DISPATCH ROUTINE, takze je to OK.
				Status=IoAttachDeviceToDeviceStackSafe(DeviceObject,LowerDeviceObject,&DeviceExtension->MLowerDeviceObject);

				if (NT_SUCCESS(Status)==false)
				{
					KdPrint(("!!!!! DRIVER FAILED to ATTACH to DEVICE OBJECT with ERROR CODE [%lX] !!!\n",Status));
					break;
				}

				MDevices[Index].MLowerDeviceObject=DeviceExtension->MLowerDeviceObject;

				DeviceObject->Flags|=DO_POWER_PAGABLE;
				DeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

				MMonitoredDeviceCount++;
			}
			while(false);

			if (NT_SUCCESS(Status)==false)
			{
				if (Buffer!=nullptr)
				{
					ExFreePoolWithTag(Buffer,MY_TAG);
				}

				if (DeviceObject!=nullptr)
				{
					IoDeleteDevice(DeviceObject);
				}

				MDevices[Index].MDeviceObject=nullptr;
			}

			if (LowerDeviceObject!=nullptr)
			{
				ObDereferenceObject(FileObject);
			}

			return(Status);
		}

		return(STATUS_UNSUCCESSFUL);
	}
}
//----------------------------------------------------------------------------------------------------------------------
int CDevMonManager::FindDevice(PCWSTR Name) const
{
	UNICODE_STRING												UName;

	RtlInitUnicodeString(&UName,Name);

	for (int Index=0;Index<MAX_MONITORED_DEVICES;Index++)
	{
		const SMonitoredDevice&									Device=MDevices[Index];

		if (Device.MDeviceObject!=nullptr)
		{
			if (RtlEqualUnicodeString(&Device.MDeviceName,&UName,TRUE)==TRUE)
			{
				return(Index);
			}
		}
	}

	return(-1);
}
//----------------------------------------------------------------------------------------------------------------------
bool CDevMonManager::RemoveDevice(PCWSTR Name)
{
	CLocker														Locker(MLock);

	{
		int														Index=FindDevice(Name);

		if (Index<0)
		{
			KdPrint(("!!!!! DRIVER FAILED to FIND TARGET DEVICE OBJECT !!!\n"));

			return(false);
		}

		bool													Removed=RemoveDevice(Index);

		return(Removed);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void CDevMonManager::RemoveAllDevices(void)
{
	CLocker														Locker(MLock);

	{
		for(int Index=0;Index<MAX_MONITORED_DEVICES;Index++)
		{
			RemoveDevice(Index);
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------