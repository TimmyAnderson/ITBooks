//----------------------------------------------------------------------------------------------------------------------
#include "CRegistryKeyOpen.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CRegistryKeyOpen::CRegistryKeyOpen(NTSTATUS& Status, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes)
	: CRegistryKey(InitializeKey(Status,DesiredAccess,ObjectAttributes))
{
}
//----------------------------------------------------------------------------------------------------------------------
CRegistryKeyOpen::~CRegistryKeyOpen(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
HANDLE CRegistryKeyOpen::InitializeKey(NTSTATUS& Status, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES& ObjectAttributes)
{
	HANDLE														Key;

	Status=OpenKey(&Key,DesiredAccess,ObjectAttributes);

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