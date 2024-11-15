//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CRegistryKey : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		HANDLE													MKey;

	protected:
		static NTSTATUS CreateKey(PHANDLE KeyHandle, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes, ULONG TitleIndex, PUNICODE_STRING Class, ULONG CreateOptions, PULONG Disposition);
		static NTSTATUS OpenKey(PHANDLE KeyHandle, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes);

	private:
		NTSTATUS CloseKey(void);

	public:
		HANDLE GetKey(void);

	public:
		NTSTATUS SetValueKey(UNICODE_STRING& ValueName, ULONG TitleIndex, ULONG Type, PVOID Data, ULONG DataSize);
		NTSTATUS DeleteValueKey(UNICODE_STRING& ValueName);
		NTSTATUS DeleteKey(void);

	protected:
		CRegistryKey(HANDLE Key);
		~CRegistryKey(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------