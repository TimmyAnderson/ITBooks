// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CREATEREMOTETHREADDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CREATEREMOTETHREADDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CREATEREMOTETHREADDLL_EXPORTS
#define CREATEREMOTETHREADDLL_API __declspec(dllexport)
#else
#define CREATEREMOTETHREADDLL_API __declspec(dllimport)
#endif
//------------------------------------------------------------------------------
extern "C" CREATEREMOTETHREADDLL_API void DLLLoadTest(void);
extern "C" CREATEREMOTETHREADDLL_API DWORD WINAPI RemoteThreadFunction(LPVOID Parameter);
//------------------------------------------------------------------------------