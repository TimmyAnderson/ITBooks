//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#ifdef IS_KERNEL
#include <ntddk.h>
#else
#include <Windows.h>
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SProcessData final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		ULONG													MID;
		LONG64													MRegistrySetValueOperations;
		LONG64													MRegistryCreateKeyOperations;
		LONG64													MRegistryRenameOperations;
		LONG64													MRegistryDeleteOperations;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------