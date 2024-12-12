//----------------------------------------------------------------------------------------------------------------------
#include "CRegistryKeyCreate.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CRegistryKeyCreate::CRegistryKeyCreate(NTSTATUS& Status, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes, ULONG TitleIndex, PUNICODE_STRING Class, ULONG CreateOptions, PULONG Disposition)
	: CRegistryKey(InitializeKey(Status,DesiredAccess,ObjectAttributes,TitleIndex,Class,CreateOptions,Disposition))
{
}
//----------------------------------------------------------------------------------------------------------------------
CRegistryKeyCreate::~CRegistryKeyCreate(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE CRegistryKeyCreate::InitializeKey(NTSTATUS& Status, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes, ULONG TitleIndex, PUNICODE_STRING Class, ULONG CreateOptions, PULONG Disposition)
{
	HANDLE														Key;

	Status=CreateKey(&Key,DesiredAccess,ObjectAttributes,TitleIndex,Class,CreateOptions,Disposition);

	if (NT_SUCCESS(Status)==true)
	{
		return(Key);
	}
	else
	{
		return(nullptr);
	}
}
//----------------------------------------------------------------------------------------------------------------------