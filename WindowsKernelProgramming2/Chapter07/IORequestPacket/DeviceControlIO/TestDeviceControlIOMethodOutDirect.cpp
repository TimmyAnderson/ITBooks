//----------------------------------------------------------------------------------------------------------------------
#include "TestDeviceControlIOMethodOutDirect.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlIOMethodOutDirect(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	PVOID														InputBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

	PMDL														MdlToOutputBuffer=Irp->MdlAddress;

	// !!!!! Vykona sa mapovanie LIST STRUCTURES [MDL] do KERNEL MODE SYSTEM ADDRESS SPACE.
	PVOID														OutputBuffer=MmGetSystemAddressForMdlSafe(MdlToOutputBuffer,MM_PAGE_PRIORITY::NormalPagePriority);
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;

	if (OutputBuffer!=nullptr)
	{
		KdPrint(("!!!!!!!!!! METHOD_OUT_DIRECT - ROUTINE [%s] INPUT BUFFER [%p] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER [%p] OUTPUT BUFFER LENGTH [%lu] !!!\n",FunctionName,InputBuffer,InputBufferLength,OutputBuffer,OutputBufferLength));

		// !!!!! Simuluje data nacitane z HW DEVICE.
		wchar_t													DataReadFromHWDevice[]=L"Timmy READ - OUT_DIRECT.";
		constexpr size_t										DataReadFromHWDeviceSize=sizeof(DataReadFromHWDevice);
		constexpr size_t										MinDataWriteToHWDeviceSize=sizeof(wchar_t);

		do
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
		while(false);
	}
	else
	{
		KdPrint(("!!!!!!!!!! METHOD_OUT_DIRECT - ROUTINE [%s] FAILED to MAP MDL to KERNEL MODE SYSTEM ADDRESS SPACE !!!\n",FunctionName));

		Information=0;
		Status=STATUS_INVALID_PARAMETER;
	}

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------