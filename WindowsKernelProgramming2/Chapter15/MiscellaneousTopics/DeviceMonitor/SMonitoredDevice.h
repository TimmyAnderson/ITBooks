//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SMonitoredDevice final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		UNICODE_STRING											MDeviceName;
		PDEVICE_OBJECT											MDeviceObject;
		PDEVICE_OBJECT											MLowerDeviceObject;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------