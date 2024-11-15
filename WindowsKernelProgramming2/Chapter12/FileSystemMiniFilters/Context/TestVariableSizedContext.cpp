//----------------------------------------------------------------------------------------------------------------------
#include "TestVariableSizedContext.h"
#include "SVariableContext.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestVariableSizedContextPostCreate(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;
	SVariableContext*											Context;

	// !!! Vytvori sa FILE CONTEXT.
	Status=FltAllocateContext(FltObjects->Filter,FLT_FILE_CONTEXT,sizeof(SVariableContext),NonPagedPool,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==true)
	{
		Context->MValue1=111;
		Context->MValue2=222;

		// !!!!! FUNCTION sa pokusi nastavit CONTEXT pre FILE OBJECT a v pripade uspechu inkrementuje INTERNAL COUNTER daneho CONTEXT.
		Status=FltSetFileContext(FltObjects->Instance,FltObjects->FileObject,FLT_SET_CONTEXT_REPLACE_IF_EXISTS,Context, nullptr);

		if (NT_SUCCESS(Status)==true)
		{
			KdPrint(("!!!!! POST CALLBACK SET CONTEXT for FILE OBJECT !!!\n"));

			// !!!!!! V pripade, ze SET FUNCTION uspela, je nutne zavolat FUNCTION [FltReleaseContext()], aby sa dekrementoval INTERNAL COUNTER, ktory inkrementovalo uspesne volanie FUNCTION [FltSetFileContext()].
			// !!!!! Po zavolani FUNCTION [FltReleaseContext()] bude mat INTERNAL COUNTER VALUE [1] cim CONTEXT ostane dalej v MEMORY, kedze je asociovany s FILE OBJECT.
			FltReleaseContext(Context);
		}
		else
		{
			KdPrint(("!!!!! POST CALLBACK FAILED to SET CONTEXT for FILE OBJECT with ERROR CODE [%lX] !!!\n",Status));

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
FLT_PREOP_CALLBACK_STATUS TestVariableSizedContextPreRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;
	SVariableContext*											Context;

	// !!!!! FUNCTION sa pokusi ziskat CONTEXT pre FILE OBJECT a v pripade uspechu inkrementuje INTERNAL COUNTER daneho CONTEXT.
	Status=FltGetFileContext(FltObjects->Instance,FltObjects->FileObject,(PFLT_CONTEXT*)&Context);

	if (NT_SUCCESS(Status)==true && Context!=nullptr)
	{
		KdPrint(("!!!!! PRE CALLBACK GOT CONTEXT for FILE OBJECT. VALUE 1 [%lu] VALUE 2 [%lu] !!!\n",Context->MValue1,Context->MValue2));

		// !!!!!! V pripade, ze SET FUNCTION uspela, je nutne zavolat FUNCTION [FltReleaseContext()], aby sa dekrementoval INTERNAL COUNTER, ktory inkrementovalo uspesne volanie FUNCTION [FltGetFileContext()].
		// !!!!! Po zavolani FUNCTION [FltReleaseContext()] bude mat INTERNAL COUNTER VALUE [1] cim CONTEXT ostane dalej v MEMORY, kedze je asociovany s FILE OBJECT.
		FltReleaseContext(Context);
	}
	else
	{
		KdPrint(("!!!!! PRE CALLBACK FAILED to GET CONTEXT for FILE OBJECT with ERROR CODE [%lX] !!!\n",Status));
	}

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_WITH_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------
FLT_POSTOP_CALLBACK_STATUS TestVariableSizedContextPostRead(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PCFLT_RELATED_OBJECTS FltObjects)
{
	UNREFERENCED_PARAMETER(FltObjects);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! POST CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	NTSTATUS													Status;

	// !!!!! FUNCTION odstrani CONTEXT z FILE OBJECT a dekrementuje INTERNAL COUNTER.
	// !!!!! Po zavolani FUNCTION klesne INTERNAL COUNTER na VALUE [0] a CONTEXT je odstraneny z MEMORY.
	Status=FltDeleteFileContext(FltObjects->Instance,FltObjects->FileObject,nullptr);

	if (NT_SUCCESS(Status)==true)
	{
		KdPrint(("!!!!! POST CALLBACK DELETED CONTEXT for FILE OBJECT !!!\n"));
	}
	else
	{
		KdPrint(("!!!!! POST CALLBACK FAILED to DELETED CONTEXT for FILE OBJECT with ERROR CODE [%lX] !!!\n",Status));
	}

	FLT_POSTOP_CALLBACK_STATUS									CallbackStatus=FLT_POSTOP_FINISHED_PROCESSING;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------