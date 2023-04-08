//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
#include "Driver.h"
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CThread
{
//-------------------------------------------------------------------------------------------------------
	private:
		_Function_class_(KSTART_ROUTINE)
		static void ThreadFunction(PVOID Parameter);

	public:
		static bool StartThread(PDEVICE_EXTENSION DeviceExtension);
		static void StopThread(PDEVICE_EXTENSION DeviceExtension);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------