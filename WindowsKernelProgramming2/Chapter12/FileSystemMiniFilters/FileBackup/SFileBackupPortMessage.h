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
struct SFileBackupPortMessage
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		USHORT													MFileNameLength;
		WCHAR													MFileName[1];
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------