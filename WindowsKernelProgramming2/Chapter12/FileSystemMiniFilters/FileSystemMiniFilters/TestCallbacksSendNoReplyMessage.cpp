//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksSendNoReplyMessage.h"
#include "Helpers\MyKernelHelpers.h"
#include "SPortDriverToClientNoReplyRequest.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksSendNoReplyMessagePreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_FILTER Filter, PFLT_PORT ClientPort)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	if (ClientPort!=nullptr)
	{
		SPortDriverToClientNoReplyRequest*						Message=(SPortDriverToClientNoReplyRequest*)ExAllocatePool2(POOL_FLAG_PAGED,sizeof(SPortDriverToClientNoReplyRequest),MY_TAG);

		if (Message!=nullptr)
		{
			Message->MMessageType=EPortDriverToClientMessageType::E_NO_REPLY;
			Message->MValue=100;

			LARGE_INTEGER										Timeout;

			Timeout.QuadPart=(-10000*1000);

			NTSTATUS											Status=FltSendMessage(Filter,&ClientPort,Message,sizeof(SPortDriverToClientNoReplyRequest),nullptr,nullptr,&Timeout);

			if (NT_SUCCESS(Status)==true)
			{
				KdPrint(("!!!!! DRIVER SUCCESSFULLY SENT NO REPLY MESSAGE to CLIENT with VALUE [%lu] !!!\n",Message->MValue));
			}
			else
			{
				KdPrint(("!!!!! DRIVER FAILED to SEND MESSAGE with ERROR CODE [%lX] !!!\n",Status));
			}

			ExFreePoolWithTag(Message,MY_TAG);
		}
		else
		{
			KdPrint(("!!!!! DRIVER FAILED to ALLOCATE MESSAGE !!!\n"));
		}
	}

	FLT_PREOP_CALLBACK_STATUS									CallbackStatus=FLT_PREOP_SUCCESS_NO_CALLBACK;

	return(CallbackStatus);
}
//----------------------------------------------------------------------------------------------------------------------