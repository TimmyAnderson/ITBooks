// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MYUNMANAGEDLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MYUNMANAGEDLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MYUNMANAGEDLIBRARY_EXPORTS
#define MYUNMANAGEDLIBRARY_API __declspec(dllexport)
#else
#define MYUNMANAGEDLIBRARY_API __declspec(dllimport)
#endif
//-------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadMethod(void* Param);
//-------------------------------------------------------------------------------------------------------
extern "C" MYUNMANAGEDLIBRARY_API int PrintStringAndGetLength(const wchar_t* String);
extern "C" MYUNMANAGEDLIBRARY_API int FillString(wchar_t* StringToFill, int Size);
//-------------------------------------------------------------------------------------------------------
typedef int (__stdcall *MyCALLBACK)(wchar_t*);
extern "C" MYUNMANAGEDLIBRARY_API void DoCallback(MyCALLBACK CallbackPointer, wchar_t* Param);
//-------------------------------------------------------------------------------------------------------
typedef int (__stdcall *MyPTRCALLBACK)(void*);
extern "C" MYUNMANAGEDLIBRARY_API void DoCallbackAsPTR(MyPTRCALLBACK CallbackPointer, void* CallbackID);
//-------------------------------------------------------------------------------------------------------
typedef int (__stdcall *MyPTRCALLBACKWITHWRITE)(void*,wchar_t*);
extern "C" MYUNMANAGEDLIBRARY_API void DoCallbackAsPTRWithWrite(MyPTRCALLBACKWITHWRITE CallbackPointer, void* CallbackID, wchar_t* DataBuffer, int DataBufferSize);
//-------------------------------------------------------------------------------------------------------