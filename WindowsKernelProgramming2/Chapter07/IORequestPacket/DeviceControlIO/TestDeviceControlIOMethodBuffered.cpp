//----------------------------------------------------------------------------------------------------------------------
#include "TestDeviceControlIOMethodBuffered.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestDeviceControlIOMethodBuffered(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);

	// !!!!! INPUT BUFFER aj OUTPUT BUFFER su zlucene do 1 BUFFER, ktory je alokovany v KERNEL MODE NON-PAGED MEMORY POOL.
	PVOID														InputBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;

	// !!!!! INPUT BUFFER aj OUTPUT BUFFER su zlucene do 1 BUFFER, ktory je alokovany v KERNEL MODE NON-PAGED MEMORY POOL.
	PVOID														OutputBuffer=Irp->AssociatedIrp.SystemBuffer;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
	KdPrint(("!!!!!!!!!! METHOD_BUFFERED - ROUTINE [%s] INPUT BUFFER [%p] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER [%p] OUTPUT BUFFER LENGTH [%lu] !!!\n",FunctionName,InputBuffer,InputBufferLength,OutputBuffer,OutputBufferLength));

	// !!!!! Simuluje data nacitane z HW DEVICE.
	wchar_t														DataReadFromHWDevice[]=L"Timmy READ - BUFFERED.";
	constexpr size_t											DataReadFromHWDeviceSize=sizeof(DataReadFromHWDevice);
	constexpr size_t											MinDataWriteToHWDeviceSize=sizeof(wchar_t);

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
		const wchar_t*											TypedInputBuffer=reinterpret_cast<const wchar_t*>(InputBuffer);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INPUT DATA [%S] !!!\n",FunctionName,TypedInputBuffer));

		// !!!!! OUTPUT BUFFER sa pretypuje na STRING.
		const wchar_t*											TypedOutputBuffer=reinterpret_cast<const wchar_t*>(OutputBuffer);

		// !!! Skopiruju sa data nacitane z HW DEVICE do OUTPUT BUFFER.
		RtlCopyMemory(OutputBuffer,DataReadFromHWDevice,DataReadFromHWDeviceSize);

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - OUTPUT DATA [%S] !!!\n",FunctionName,TypedOutputBuffer));

		Information=DataReadFromHWDeviceSize;
		Status=STATUS_SUCCESS;
	}
	while(false);


	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------