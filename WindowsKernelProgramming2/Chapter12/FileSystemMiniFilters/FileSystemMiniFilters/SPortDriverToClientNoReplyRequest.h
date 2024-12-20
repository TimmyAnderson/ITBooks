//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_KERNEL
#include <ntddk.h>
#else
#include <Windows.h>
#endif
#include "SPortDriverToClientBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SPortDriverToClientNoReplyRequest final : public SPortDriverToClientBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													MValue;

	public:
		SPortDriverToClientNoReplyRequest(ULONG Value)
			: SPortDriverToClientBase(EPortDriverToClientMessageType::E_NO_REPLY), MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------