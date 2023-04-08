//-------------------------------------------------------------------------------------------------------
#include <wdm.h>
//-------------------------------------------------------------------------------------------------------
// DriverEntry() is not used in a kernel-mode DLL such as this one. It's only here to satisfy the build script.
#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT, PUNICODE_STRING)
{
	// !!!!! Toto NIE JE SKUTOCNY DRIVER iba DRIVER DLL.

	// Never entered, actually.
	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
// DllInitialize() is called when this module is first loaded. This function was added in version 1.7, part of SP-9. Note that RegistryPath just names a bogus service key that doesn't necessarily exist -- HKLM\...\Services\Generic.
#ifndef WIN98SAFE
#pragma PAGEDCODE
extern "C" NTSTATUS DllInitialize(PUNICODE_STRING)
{
	KdPrint(("GENERIC - DllInitialize !\n"));

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
// DllUnload() is called when all references to this module disappear. This function was added in version 1.7, part of SP-9.
#pragma PAGEDCODE
//-------------------------------------------------------------------------------------------------------
extern "C" NTSTATUS DllUnload()
{
	KdPrint(("GENERIC - DllUnload !\n"));

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------