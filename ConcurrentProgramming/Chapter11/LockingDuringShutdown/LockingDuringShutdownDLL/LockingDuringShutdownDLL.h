#include <windows.h>
//------------------------------------------------------------------------------
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOCKINGDURINGSHUTDOWNDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOCKINGDURINGSHUTDOWNDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOCKINGDURINGSHUTDOWNDLL_EXPORTS
#define LOCKINGDURINGSHUTDOWNDLL_API __declspec(dllexport)
#else
#define LOCKINGDURINGSHUTDOWNDLL_API __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
CRITICAL_SECTION						GCS;
BOOL									GIgnoreCS;
HANDLE									GMutex;
//------------------------------------------------------------------------------
#ifdef USE_SWR
SRWLOCK									GRWL;
#endif
//------------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE HInstDLL, DWORD FDWReason, LPVOID LPReserved);
LOCKINGDURINGSHUTDOWNDLL_API DWORD WINAPI GetAndBlock(LPVOID LPParameter);
LOCKINGDURINGSHUTDOWNDLL_API VOID WINAPI IgnoreCriticalSection();
//------------------------------------------------------------------------------