//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_KERNEL
#include <ntddk.h>
#else
#include <Windows.h>
#endif
#include "SPortClientToDriverBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SPortClientToDriverRequestReplyRequest final : public SPortClientToDriverBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													MValue;

	public:
		SPortClientToDriverRequestReplyRequest(ULONG Value)
			: SPortClientToDriverBase(EPortClientToDriverMessageType::E_REQUEST_REPLY), MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------