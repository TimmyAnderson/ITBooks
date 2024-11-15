//----------------------------------------------------------------------------------------------------------------------
#include "TestFixedSizedContext.h"
#include "SFixedContext.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestFixedSizedContextPostCreate(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;
	SFixedContext*												Context;

	// !!! Vytvori sa FILE CONTEXT.
	Status=FltAllocateContext(FltObjects->Filter,FLT_STREAM_CONTEXT,sizeof(SFixedContext),NonPagedPool,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==true)
	{
		Context->MValue=1000;

		// !!!!! FUNCTION sa pokusi nastavit CONTEXT pre FILE STREAM OBJECT a v pripade uspechu inkrementuje INTERNAL COUNTER daneho CONTEXT.
		Status=FltSetStreamContext(FltObjects->Instance,FltObjects->FileObject,FLT_SET_CONTEXT_REPLACE_IF_EXISTS,Context, nullptr);

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!! POST CALLBACK SET CONTEXT for FILE STREAM OBJECT !!!\n"));

			// !!!!!! V pripade, ze SET FUNCTION uspela, je nutne zavolat FUNCTION [FltReleaseContext()], aby sa dekrementoval INTERNAL COUNTER, ktory inkrementovalo uspesne volanie FUNCTION [FltSetStreamContext()].
			// !!!!! Po zavolani FUNCTION [FltReleaseContext()] bude mat INTERNAL COUNTER VALUE [1] cim CONTEXT ostane dalej v MEMORY, kedze je asociovany s FILE STREAM OBJECT.
			FltReleaseContext(Context);
		}
		else
		{
			KdPrint(("!!!!! POST CALLBACK FAILED to SET CONTEXT for FILE STREAM OBJECT with ERROR CODE [%lX] !!!\n",Status));

			// !!!!! V pripade ze SET FUNCTION ZLYHALA, je NUTNE volat FUNCTION [FltReleaseContext()], aby doslo k dekrementacii INTERNAL COUNTER CONTEXT vytvoreneho pomocou FUNCTION [FltAllocateContext()] a CONTEXT mohol byt uvolneny z MEMORY.
			// !!!!! Po zavolani FUNCTION [FltReleaseContext()] bude mat INTERNAL COUNTER VALUE [0] cim sa CONTEXT uvolni.
			FltReleaseContext(Context);
		}
	}
	else
	{
		KdPrint(("!!!!! POST CALLBACK FAILED to ALLOCATE CONTEXT with ERROR CODE [%lX] !!!\n",Status));
	}

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestFixedSizedContextPreRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;
	SFixedContext*												Context;

	// !!!!! FUNCTION sa pokusi ziskat CONTEXT pre FILE STREAM OBJECT a v pripade uspechu inkrementuje INTERNAL COUNTER daneho CONTEXT.
	Status=FltGetStreamContext(FltObjects->Instance,FltObjects->FileObject,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==true && Context!=nullptr)
	{
		KdPrint(("!!!!! PRE CALLBACK GOT CONTEXT for FILE STREAM OBJECT. VALUE [%lu] !!!\n",Context->MValue));

		// !!!!!! V pripade, ze SET FUNCTION uspela, je nutne zavolat FUNCTION [FltReleaseContext()], aby sa dekrementoval INTERNAL COUNTER, ktory inkrementovalo uspesne volanie FUNCTION [FltGetStreamContext()].
		// !!!!! Po zavolani FUNCTION [FltReleaseContext()] bude mat INTERNAL COUNTER VALUE [1] cim CONTEXT ostane dalej v MEMORY, kedze je asociovany s FILE STREAM OBJECT.
		FltReleaseContext(Context);
	}
	else
	{
		KdPrint(("!!!!! PRE CALLBACK FAILED to GET CONTEXT for FILE STREAM OBJECT with ERROR CODE [%lX] !!!\n",Status));
	}

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_WITH_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestFixedSizedContextPostRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;

	// !!!!! FUNCTION odstrani CONTEXT z FILE STREAM OBJECT a dekrementuje INTERNAL COUNTER.
	// !!!!! Po zavolani FUNCTION klesne INTERNAL COUNTER na VALUE [0] a CONTEXT je odstraneny z MEMORY.
	Status=FltDeleteStreamContext(FltObjects->Instance,FltObjects->FileObject,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! POST CALLBACK DELETED CONTEXT for FILE STREAM OBJECT !!!\n"));
	}
	else
	{
		KdPrint(("!!!!! POST CALLBACK FAILED to DELETED CONTEXT for FILE STREAM OBJECT with ERROR CODE [%lX] !!!\n",Status));
	}

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------