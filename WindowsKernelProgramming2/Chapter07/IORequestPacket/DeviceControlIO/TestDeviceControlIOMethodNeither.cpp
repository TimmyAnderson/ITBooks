//----------------------------------------------------------------------------------------------------------------------
#include "TestDeviceControlIOMethodNeither.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlIOMethodNeither(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	// !!!!! POINTER sa odkazuje na USER MODE BUFFER, ktory je mozne pouzit iba v USER MODE THREAD, ktory vytvoril IRP a v IRQL [PASSIVE_LEVEL].
	PVOID														InputBuffer=CurrentStackLocation->Parameters.DeviceIoControl.Type3InputBuffer;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

	// !!!!! POINTER sa odkazuje na USER MODE BUFFER, ktory je mozne pouzit iba v USER MODE THREAD, ktory vytvoril IRP a v IRQL [PASSIVE_LEVEL].
	PVOID														OutputBuffer=Irp->UserBuffer;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
	KdPrint(("!!!!!!!!!! METHOD_NEITHER - ROUTINE [%s] INPUT BUFFER [%p] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER [%p] OUTPUT BUFFER LENGTH [%lu] !!!\n",FunctionName,InputBuffer,InputBufferLength,OutputBuffer,OutputBufferLength));

	// !!!!! Simuluje data nacitane z HW DEVICE.
	wchar_t														DataReadFromHWDevice[]=L"Timmy READ - NEITHER.";
	constexpr size_t											DataReadFromHWDeviceSize=sizeof(DataReadFromHWDevice);
	constexpr size_t											MinDataWriteToHWDeviceSize=sizeof(wchar_t);

	do
	{
		// !!!!! Kedze WINDOWS pri MODE [METHOD_NEITHER] nerobi ziadnu kontrolu INPUT BUFFER a OUTPUT BUFFER, je je treba spravit manualne.

		__try
		{
			if (InputBuffer==nullptr)
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			if (OutputBuffer==nullptr)
			{
				Status=STATUS_INVALID_PARAMETER;
				break;
			}

			if (InputBufferLength<DataReadFromHWDeviceSize)
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			if (OutputBufferLength<MinDataWriteToHWDeviceSize)
			{
				Status=STATUS_BUFFER_TOO_SMALL;
				break;
			}

			// !!!!! FUNCTION testuje ci USER MODE BUFFER je ACCESSIBLE pre READ. Ak nie je, FUNCTION hodi EXCEPTION.
			ProbeForRead(InputBuffer,InputBufferLength,1);

			// !!!!! FUNCTION testuje ci USER MODE BUFFER je ACCESSIBLE pre WRITE. Ak nie je, FUNCTION hodi EXCEPTION.
			// !!!!! V DOCUMENTATION sa pise, ze namiesto FUNCTION [ProbeForWrite()] by sa mala pouzivat FUNCTION [ProbeForRead()] aj pre WRITE OPERATIONS.
			ProbeForWrite(OutputBuffer,OutputBufferLength,1);

			// !!!!! INPUT BUFFER sa pretypuje na STRING.
			const wchar_t*										TypedInputBuffer=reinterpret_cast<const wchar_t*>(InputBuffer);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - INPUT DATA [%S] !!!\n",FunctionName,TypedInputBuffer));

			// !!!!! OUTPUT BUFFER sa pretypuje na STRING.
			const wchar_t*										TypedOutputBuffer=reinterpret_cast<const wchar_t*>(OutputBuffer);

			// !!! Skopiruju sa data nacitane z HW DEVICE do OUTPUT BUFFER.
			RtlCopyMemory(OutputBuffer,DataReadFromHWDevice,DataReadFromHWDeviceSize);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - OUTPUT DATA [%S] !!!\n",FunctionName,TypedOutputBuffer));

			Information=DataReadFromHWDeviceSize;
			Status=STATUS_SUCCESS;
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			Status=STATUS_INVALID_PARAMETER;
			Information=0;
		}
	}
	while(false);

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
