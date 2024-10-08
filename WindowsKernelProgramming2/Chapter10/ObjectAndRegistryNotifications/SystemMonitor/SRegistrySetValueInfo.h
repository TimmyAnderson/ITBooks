//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "SItemHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SRegistrySetValueInfo final : public SItemHeader
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													MProcessID;
		ULONG													MThreadID;
		USHORT													MKeyNameOffset;
		USHORT													MValueNameOffset;
		ULONG													MDataType;
		ULONG													MDataSize;
		USHORT													MDataOffset;
		USHORT													MProvidedDataSize;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------