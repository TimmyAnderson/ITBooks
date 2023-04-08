//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
//------------------------------------------------------------------------------------------------------
class CBagFileRecord
{
	private:
		std::wstring												MFileName;
		DWORD														MFileSize;
		bool														MIsEXE;
		std::wstring												MAssemblyIdentity;
		BYTE*														MFileData;

	public:
		std::wstring GetFileName(void);
		DWORD GetFileSize(void);
		bool GetIsEXE(void);
		std::wstring GetAssemblyIdentity(void);
		BYTE* GetFileData(void);

	public:
		CBagFileRecord(std::wstring FileName, DWORD FileSize, bool IsEXE, std::wstring AssemblyIdentity);
		~CBagFileRecord(void);
};
//------------------------------------------------------------------------------------------------------