//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <objbase.h>
#include <assert.h>
#include "registry.h"
//------------------------------------------------------------------------------------------------------
// Set the given key and its value.
BOOL SetKeyAndValue(const wchar_t* Path, const wchar_t* SubKeyName, const wchar_t* Value);
//------------------------------------------------------------------------------------------------------
// Open a key and set a value.
BOOL SetValueInKey(const wchar_t* KeyName, const wchar_t* NamedValue, const wchar_t* Value);
//------------------------------------------------------------------------------------------------------
// Convert a CLSID into a wchar_t string.
void CLSIDToChar(REFCLSID CLSID, wchar_t* CLSIDString, int Length);
//------------------------------------------------------------------------------------------------------
// Delete KeyNameChild and all of its descendents.
LONG RecursiveDeleteKey(HKEY HandleKeyParent, const wchar_t* KeyNameChild);
//------------------------------------------------------------------------------------------------------
// Size of a CLSID as a string
const int														CLSID_STRING_SIZE=39;
//------------------------------------------------------------------------------------------------------
// Register the component in the registry.
HRESULT RegisterServer(const wchar_t* ModuleName, REFCLSID CLSID, const wchar_t* FriendlyName, const wchar_t* VerIndProgID, const wchar_t* ProgID, const wchar_t* ThreadingModel)
{
	// Get server location.
	wchar_t														Module[512];
	HMODULE														HandleModule=GetModuleHandle(ModuleName);
	DWORD														Result=GetModuleFileName(HandleModule,Module,sizeof(Module)/sizeof(wchar_t));

	// Convert the CLSID into a wchar_t.
	wchar_t														CLSIDString[CLSID_STRING_SIZE];
	
	CLSIDToChar(CLSID,CLSIDString,sizeof(CLSIDString)/sizeof(wchar_t));

	// Build the key CLSID\\{...}.
	wchar_t														KeyName[64];

	wcscpy_s(KeyName,L"CLSID\\");
	wcscat_s(KeyName,CLSIDString);
  
	// Add the CLSID to the registry.
	SetKeyAndValue(KeyName,NULL,FriendlyName);

	// Add the server filename subkey under the CLSID key.
	if (wcsstr(ModuleName, L".exe")==NULL)
	{
		SetKeyAndValue(KeyName,L"InprocServer32",Module);

		wchar_t													Inproc[64];

		wcscpy_s(Inproc,KeyName);
		wcscat_s(Inproc,L"\\InprocServer32");

		SetValueInKey(Inproc,L"ThreadingModel",ThreadingModel);
	}
	else
	{
		SetKeyAndValue(KeyName,L"LocalServer32",Module);
	}

	// Add the ProgID subkey under the CLSID key.
	SetKeyAndValue(KeyName,L"ProgID",ProgID);

	// Add the version-independent ProgID subkey under CLSID key.
	SetKeyAndValue(KeyName,L"VersionIndependentProgID",VerIndProgID);

	// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
	SetKeyAndValue(VerIndProgID,NULL,FriendlyName); 
	SetKeyAndValue(VerIndProgID,L"CLSID",CLSIDString);
	SetKeyAndValue(VerIndProgID,L"CurVer",ProgID);

	// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
	SetKeyAndValue(ProgID,NULL,FriendlyName); 
	SetKeyAndValue(ProgID,L"CLSID",CLSIDString);

	HRESULT														HR=S_OK;

	if (wcsstr(ModuleName, L".exe")==NULL)
	{
		wchar_t													DLLPath[1024];

		// Zisti nazov .DLL.
		GetModuleFileName(HandleModule,DLLPath,sizeof(DLLPath));

		wchar_t*												Position=wcsstr(DLLPath,L".dll");

		if (Position==NULL)
		{
			return(E_FAIL);
		}

		// Zmeni .DLL za .TLB. Predpoklada sa, ze DLL a TLB su v TOM ISTOM DIRECTORY.
		Position[1]='t';
		Position[2]='l';
		Position[3]='b';

		ITypeLib*												TypeLib=NULL;

		// !!! Zaregistruje TYPE LIBRARY.
		if (SUCCEEDED(HR=LoadTypeLibEx(DLLPath,REGKIND_REGISTER,&TypeLib)))
		{
			TypeLib->Release();
		}
	}

	return(HR);
}
//------------------------------------------------------------------------------------------------------
// Remove the component from the registry.
LONG UnregisterServer(REFCLSID CLSID, const wchar_t* VerIndProgID, const wchar_t* ProgID, REFGUID LIBID)
{
	// Convert the CLSID into a wchar_t.
	wchar_t														CLSIDString[CLSID_STRING_SIZE];
	
	CLSIDToChar(CLSID,CLSIDString,sizeof(CLSIDString)/sizeof(wchar_t));

	// Build the key CLSID\\{...}.
	wchar_t														KeyName[64];
	
	wcscpy_s(KeyName,L"CLSID\\");
	wcscat_s(KeyName,CLSIDString);

	// Delete the CLSID Key - CLSID\{...}.
	LONG														Result=RecursiveDeleteKey(HKEY_CLASSES_ROOT,KeyName);

	// Delete the version-independent ProgID Key.
	Result=RecursiveDeleteKey(HKEY_CLASSES_ROOT,VerIndProgID);

	// Delete the ProgID key.
	Result=RecursiveDeleteKey(HKEY_CLASSES_ROOT,ProgID);

	HRESULT														HR;

	// !!! Odregistruje TYPE LIBRARY.
	HR=UnRegisterTypeLib(LIBID,1,0,LANG_NEUTRAL,SYS_WIN64);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
// Convert a CLSID to a wchar_t string.
void CLSIDToChar(REFCLSID CLSID, wchar_t* CLSIDString, int Length)
{
	// Get CLSID.
	LPOLESTR													CLSIDWideString=NULL;
	HRESULT														HR=StringFromCLSID(CLSID,&CLSIDWideString);
	
	// Covert from wide characters to non-wide.
	wcscpy_s(CLSIDString,Length,CLSIDWideString);

	// Free memory.
	CoTaskMemFree(CLSIDWideString);
}
//------------------------------------------------------------------------------------------------------
// Delete a key and all of its descendents.
LONG RecursiveDeleteKey(HKEY HandleKeyParent, const wchar_t* KeyNameChild)
{
	// Open the child.
	HKEY														HandleKeyChild;
	LONG														Result=RegOpenKeyEx(HandleKeyParent,KeyNameChild,0,KEY_ALL_ACCESS,&HandleKeyChild);
	
	if (Result!=ERROR_SUCCESS)
	{
		return(Result);
	}

	// Enumerate all of the decendents of this child.
	FILETIME													Time;
	wchar_t														Buffer[256];
	DWORD														Size=256;

	while(RegEnumKeyEx(HandleKeyChild,0,Buffer,&Size,NULL,NULL,NULL,&Time)==S_OK)
	{
		// Delete the decendents of this child.
		Result=RecursiveDeleteKey(HandleKeyChild,Buffer);

		if(Result!=ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(HandleKeyChild);

			return(Result);
		}

		Size=256;
	}

	// Close the child.
	RegCloseKey(HandleKeyChild);

	// Delete this child.
	return(RegDeleteKey(HandleKeyParent,KeyNameChild));
}
//------------------------------------------------------------------------------------------------------
// Create a key and set its value.
BOOL SetKeyAndValue(const wchar_t* KeyName, const wchar_t* SubKeyName, const wchar_t* Value)
{
	HKEY														HandleKey;
	wchar_t														KeyNameBuf[1024];

	// Copy keyname into buffer.
	wcscpy_s(KeyNameBuf,KeyName);

	// Add subkey name to buffer.
	if (SubKeyName!=NULL)
	{
		wcscat_s(KeyNameBuf,L"\\");
		wcscat_s(KeyNameBuf,SubKeyName);
	}

	// Create and open key and subkey.
	long														Result=RegCreateKeyEx(HKEY_CLASSES_ROOT,KeyNameBuf,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&HandleKey,NULL);

	if (Result!=ERROR_SUCCESS)
	{
		return(FALSE);
	}

	// Set the Value.
	if (Value!=NULL)
	{
		RegSetValueEx(HandleKey,NULL,0,REG_SZ,(BYTE*) Value,DWORD((wcslen(Value)+1)*sizeof(wchar_t)));
	}

	RegCloseKey(HandleKey);

	return(TRUE);
}
//------------------------------------------------------------------------------------------------------
// Open a key and set a value.
BOOL SetValueInKey(const wchar_t* KeyName, const wchar_t* NamedValue, const wchar_t* Value)
{
	HKEY														HandleKey;
	wchar_t														KeyNameBuf[1024];

	// Copy keyname into buffer.
	wcscpy_s(KeyNameBuf,KeyName);

	// Create and open key and subkey.
	long														Result=RegOpenKeyEx(HKEY_CLASSES_ROOT,KeyNameBuf,0,KEY_SET_VALUE,&HandleKey);

	if (Result!=ERROR_SUCCESS)
	{
		return(FALSE);
	}

    // Set the Value.
	if (Value!=NULL)
	{
		RegSetValueEx(HandleKey,NamedValue,0,REG_SZ,(BYTE*) Value,DWORD((wcslen(Value)+1)*sizeof(wchar_t)));
	}

	RegCloseKey(HandleKey);

	return(TRUE);
}
//------------------------------------------------------------------------------------------------------