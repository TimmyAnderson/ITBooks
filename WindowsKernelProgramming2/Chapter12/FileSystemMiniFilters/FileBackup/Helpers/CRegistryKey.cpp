//----------------------------------------------------------------------------------------------------------------------
#include "CRegistryKey.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CRegistryKey::CRegistryKey(HANDLE Key)
	: MKey(Key)
{
}
//----------------------------------------------------------------------------------------------------------------------
CRegistryKey::~CRegistryKey(void)
{
	if (MKey!=nullptr)
	{
		CloseKey();
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::CreateKey(PHANDLE KeyHandle, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes, ULONG TitleIndex, PUNICODE_STRING Class, ULONG CreateOptions, PULONG Disposition)
{
	NTSTATUS													Status=ZwCreateKey(KeyHandle,DesiredAccess,&ObjectAttributes,TitleIndex,Class,CreateOptions,Disposition);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::OpenKey(PHANDLE KeyHandle, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes)
{
	NTSTATUS													Status=ZwOpenKey(KeyHandle,DesiredAccess,&ObjectAttributes);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::CloseKey(void)
{
	NTSTATUS													Status=ZwClose(MKey);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE CRegistryKey::GetKey(void)
{
	return(MKey);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::SetValueKey(UNICODE_STRING& ValueName, ULONG TitleIndex, ULONG Type, PVOID Data, ULONG DataSize)
{
	NTSTATUS													Status=ZwSetValueKey(MKey,&ValueName,TitleIndex,Type,Data,DataSize);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::DeleteValueKey(UNICODE_STRING& ValueName)
{
	NTSTATUS													Status=ZwDeleteValueKey(MKey,&ValueName);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS CRegistryKey::DeleteKey(void)
{
	NTSTATUS													Status=ZwDeleteKey(MKey);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------