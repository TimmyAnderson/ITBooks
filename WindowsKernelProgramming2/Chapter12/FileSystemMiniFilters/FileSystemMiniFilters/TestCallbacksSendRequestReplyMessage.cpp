//----------------------------------------------------------------------------------------------------------------------
#include "TestCallbacksSendRequestReplyMessage.h"
#include "Helpers\MyKernelHelpers.h"
#include "SPortDriverToClientRequestReplyRequest.h"
#include "SPortDriverToClientRequestReplyReply.h"
#include "SPortDriverToClientRequestReplyReplyWithHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
FLT_PREOP_CALLBACK_STATUS TestCallbacksSendRequestReplyMessagePreOperation(const PFLT_FILE_NAME_INFORMATION FileNameInformation, PFLT_FILTER Filter, PFLT_PORT ClientPort)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! PRE CALLBACK - FUNCTION [%s] FILE [%wZ] VOLUME [%wZ] PARENT DIRECTORY [%wZ] EXTENSION [%wZ] !!!\n",FunctionName,FileNameInformation->Name,FileNameInformation->Volume,FileNameInformation->ParentDir,FileNameInformation->Extension));

	if (ClientPort!=nullptr)
	{
		SPortDriverToClientRequestReplyRequest*					RequestMessage=(SPortDriverToClientRequestReplyRequest*)ExAllocatePool2(POOL_FLAG_PAGED,sizeof(SPortDriverToClientRequestReplyRequest),MY_TAG);

		if (RequestMessage!=nullptr)
		{
			SPortDriverToClientRequestReplyReply*				ReplyMessage=(SPortDriverToClientRequestReplyReply*)ExAllocatePool2(POOL_FLAG_PAGED,sizeof(SPortDriverToClientRequestReplyReply),MY_TAG);

			if (ReplyMessage!=nullptr)
			{
				RequestMessage->MMessageType=EPortDriverToClientMessageType::E_REQUEST_REPLY;
				RequestMessage->MValue=100;

				LARGE_INTEGER									Timeout;

				Timeout.QuadPart=(-10000*1000);

				ULONG											ReplyLength=sizeof(SPortDriverToClientRequestReplyReply);

				// !!!!! Caka sa na prichod REPLY MESSAGE. Ak nepride do urceneho TIME, vrati sa RETURN VALUE [STATUS_TIMEOUT], ktora je vsak SUCCESS STATE.
				NTSTATUS										Status=FltSendMessage(Filter,&ClientPort,RequestMessage,sizeof(SPortDriverToClientRequestReplyRequest),ReplyMessage,&ReplyLength,&Timeout);

				if (NT_SUCCESS(Status)==true)
				{
					if (Status!=STATUS_TIMEOUT)
					{
						KdPrint(("!!!!! DRIVER SUCCESSFULLY SENT REQUEST REPLY MESSAGE to CLIENT with CODE [%lX]. REPLY LENGTH [%lu] REQUEST VALUE [%lu] REPLY VALUE 1 [%lu] REPLY VALUE 2 [%lu] !!!\n",Status,ReplyLength,RequestMessage->MValue,ReplyMessage->MValue1,ReplyMessage->MValue2));
					}
					else
					{
						KdPrint(("!!!!! DRIVER SUCCESSFULLY SENT REQUEST REPLY MESSAGE to CLIENT with CODE [%lX]. REQUEST VALUE [%lu] !!!\n",Status,RequestMessage->MValue));
					}
				}
				else
				{
					KdPrint(("!!!!! DRIVER FAILED to SEND MESSAGE with ERROR CODE [%lX] !!!\n",Status));
				}

				ExFreePoolWithTag(ReplyMessage,MY_TAG);
			}

			ExFreePoolWithTag(RequestMessage,MY_TAG);
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