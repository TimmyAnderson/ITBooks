#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers\CSpinLockGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CDeviceHelpers final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CSpinLockGlobal											MSpinLock;
		PDRIVER_DISPATCH										MMajorFunctions[IRP_MJ_MAXIMUM_FUNCTION+1];
	    PDRIVER_UNLOAD											MDriverUnload;
		PDRIVER_OBJECT											MDriverObject;

	public:
		void Init(void);

	public:
		bool SetDevice(PDRIVER_OBJECT DriverObject, PDRIVER_DISPATCH MajorFunction, PDRIVER_UNLOAD DriverUnload);
		bool ClearDevice(void);

	public:
		NTSTATUS CallOriginalDispatchRoutine(DEVICE_OBJECT* DeviceObject, IRP* Irp);
		void CallOriginalDriverUnloadRoutine(PDRIVER_OBJECT DriverObject);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------