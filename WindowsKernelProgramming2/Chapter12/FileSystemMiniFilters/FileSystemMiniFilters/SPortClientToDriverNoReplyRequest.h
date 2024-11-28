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
struct SPortClientToDriverNoReplyRequest final : public SPortClientToDriverBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													MValue;

	public:
		SPortClientToDriverNoReplyRequest(ULONG Value)
			: SPortClientToDriverBase(EPortClientToDriverMessageType::E_NO_REPLY), MValue(Value)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------