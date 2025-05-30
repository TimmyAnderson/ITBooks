//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "EPortClientToDriverMessageType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SPortClientToDriverBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		EPortClientToDriverMessageType							MMessageType;

	public:
		SPortClientToDriverBase(EPortClientToDriverMessageType MessageType)
			: MMessageType(MessageType)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------