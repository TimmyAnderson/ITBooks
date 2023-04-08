//------------------------------------------------------------------------------------------------------
#include <Windows.h>
//------------------------------------------------------------------------------------------------------
// This function will register a component.
HRESULT RegisterServer(const wchar_t* ModuleName, REFCLSID CLSID, const wchar_t* FriendlyName, const wchar_t* VerIndProgID, const wchar_t* ProgID, const wchar_t* ThreadingModel);
//------------------------------------------------------------------------------------------------------
// This function will unregister a component.
HRESULT UnregisterServer(REFCLSID CLSID, const wchar_t* VerIndProgID, const wchar_t* ProgID, REFGUID LIBID);
//------------------------------------------------------------------------------------------------------