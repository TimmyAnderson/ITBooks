//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <metahost.h>
#include <mscoree.h>
#include <CorError.h>
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "BagFileRecord.h"
#include "BagFileRecords.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
struct SBagRecord
{
	wchar_t														FileName[MAX_PATH];
	DWORD														FileSize;
	bool														IsEXE;
	DWORD														BagOffset;
	wchar_t														AssemblyIdentity[1024];
};
//-------------------------------------------------------------------------------------------------------
struct SBagRecords
{
	size_t														NumberOfBagRecords;
	wchar_t														BagExecutable[1024];
	wchar_t														RunnableType[1024];
};
//-------------------------------------------------------------------------------------------------------
CSmartCOMPointer<ICLRAssemblyIdentityManager> GetCLRAssemblyIdentityManager(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRAssemblyIdentityManager>				AssemblyIdentityManager=NULL;

	try
	{
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		HRESULT (__stdcall *GetCLRIdentityManagerProc)(REFIID, IUnknown **);

		// !!!!! Ziskam POINTER na GLOBAL FUNCTION GetCLRIdentityManager().
		// !!!!! Aj ked dokumentacia uvadza, ze FUNCTION je DEPRECATED, tak sa mi podarilo ziskat POINTER na nu.
		if (FAILED(HR=RuntimeInfo->GetProcAddress("GetCLRIdentityManager", (void **)&GetCLRIdentityManagerProc)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetProcAddress() FAILED.",HR));
		}

		// !!!!! Ziskam POINTER na ICLRAssemblyIdentityManager.
		if (FAILED(HR=GetCLRIdentityManagerProc(__uuidof(ICLRAssemblyIdentityManager),(IUnknown**) &AssemblyIdentityManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRIdentityManager() FAILED.",HR));
		}
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;

	return(AssemblyIdentityManager);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CreateBag(wstring BagDirectory, wstring BagName, wstring BagExecutable, wstring RunnableType)
{
	CSmartCOMPointer<ICLRAssemblyIdentityManager>				AssemblyIdentityManager=GetCLRAssemblyIdentityManager();

	wstring														SearchString=BagDirectory;

	SearchString+=L"\\*";

	WIN32_FIND_DATA												FileData;
	HANDLE														FindHandle=FindFirstFile(SearchString.c_str(),&FileData);
	BYTE*														Memory=NULL;

	if (FindHandle==INVALID_HANDLE_VALUE)
	{
		throw(wstring(L"FindFirstFile() FAILED."));
	}

	try
	{
		vector<SBagRecord>										BagRecords;
		DWORD													BagOffset=0;
		DWORD													TotalSize=0;

		while(FindNextFile(FindHandle,&FileData)!=0)
		{
			wstring												FileName=wstring(FileData.cFileName);
			bool												IsEXE=(FileName.find(L".exe")!=wstring::npos);
			bool												IsDLL=(FileName.find(L".dll")!=wstring::npos);
			wstring												FilePath=BagDirectory;

			FilePath+=L"\\";
			FilePath+=FileName;

			wchar_t												AssemblyIdentity[1024];
			DWORD												AssemblyIdentitySize=_countof(AssemblyIdentity);
			HRESULT												HR;

			// !!!!! Ziskam ASSEMBLY IDENTITY.
			// !!!!! Ak chcem ziskat velkost potrebneho BUFFERA, je mozne volat METHOD GetBindingIdentityFromFile() s NULL hodnotou namiesto AssemblyIdentity a vtedy AssemblyIdentitySize bude obsahovat potrebnu dlzku BUFFERA.
			if (FAILED(HR=AssemblyIdentityManager->GetBindingIdentityFromFile(FilePath.c_str(),CLR_ASSEMBLY_IDENTITY_FLAGS_DEFAULT,AssemblyIdentity,&AssemblyIdentitySize)))
			{
				// !!! Ak FUNCTION ZLYHA, tak sa NEJEDNA o ASSEMBLY FILE.
				continue;
			}

			// !!! Do BAG vkladam iba EXE a DLL FILES.
			if (IsEXE==true || IsDLL==true)
			{
				SBagRecord										BagRecord;

				wcscpy_s(BagRecord.FileName,FileData.cFileName);

				BagRecord.FileSize=FileData.nFileSizeLow;
				BagRecord.IsEXE=IsEXE;
				BagRecord.BagOffset=BagOffset;

				wcscpy_s(BagRecord.AssemblyIdentity,AssemblyIdentity);

				BagOffset+=FileData.nFileSizeLow;
				TotalSize+=FileData.nFileSizeLow;

				BagRecords.push_back(BagRecord);

				wprintf_s(L"FILE [%s] is ADDED to BAG !\n",FileData.cFileName);
			}
		}

		BYTE*													Memory=new BYTE[TotalSize];

		for (vector<SBagRecord>::iterator Iterator=BagRecords.begin();Iterator!=BagRecords.end();Iterator++)
		{
			wstring												FileName=BagDirectory;

			FileName+=L"\\";
			FileName+=Iterator->FileName;

			HANDLE												FileHandle=CreateFile(FileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

			if (FileHandle==INVALID_HANDLE_VALUE)
			{
				throw(wstring(L"CreateFile() FAILED."));
			}

			try
			{
				DWORD											NumberOfBytesRead;
				BYTE*											PointerToMemory=&Memory[Iterator->BagOffset];

				if (ReadFile(FileHandle,PointerToMemory,Iterator->FileSize,&NumberOfBytesRead,NULL)==FALSE)
				{
					throw(wstring(L"ReadFile() FAILED."));
				}

				CloseHandle(FileHandle);
			}
			catch(...)
			{
				CloseHandle(FileHandle);

				throw;
			}
		}

		wstring													BagFileName=BagDirectory;

		BagFileName+=L"\\";
		BagFileName+=BagName;

		HANDLE													BagFileHandle=CreateFile(BagFileName.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		if (BagFileHandle==INVALID_HANDLE_VALUE)
		{
			throw(wstring(L"CreateFile() FAILED."));
		}

		try
		{
			DWORD												NumberOfBytesWritten;
			SBagRecords											BagRecordsHeader;

			BagRecordsHeader.NumberOfBagRecords=BagRecords.size();
			wcscpy_s(BagRecordsHeader.BagExecutable,BagExecutable.c_str());
			wcscpy_s(BagRecordsHeader.RunnableType,RunnableType.c_str());

			if (WriteFile(BagFileHandle,&BagRecordsHeader,sizeof(SBagRecords),&NumberOfBytesWritten,NULL)==FALSE)
			{
				throw(wstring(L"WriteFile() FAILED."));
			}

			for (vector<SBagRecord>::iterator Iterator=BagRecords.begin();Iterator!=BagRecords.end();Iterator++)
			{
				const SBagRecord&								BagRecord=*Iterator;

				if (WriteFile(BagFileHandle,&BagRecord,sizeof(SBagRecord),&NumberOfBytesWritten,NULL)==FALSE)
				{
					throw(wstring(L"WriteFile() FAILED."));
				}
			}

			if (WriteFile(BagFileHandle,Memory,TotalSize,&NumberOfBytesWritten,NULL)==FALSE)
			{
				throw(wstring(L"WriteFile() FAILED."));
			}

			CloseHandle(BagFileHandle);
		}
		catch(...)
		{
			CloseHandle(BagFileHandle);

			throw;
		}

		if (Memory!=NULL)
		{
			delete[](Memory);
			Memory=NULL;
		}

		FindClose(FindHandle);
	}
	catch(...)
	{
		if (Memory!=NULL)
		{
			delete[](Memory);
			Memory=NULL;
		}

		FindClose(FindHandle);

		throw;
	}
}
//-------------------------------------------------------------------------------------------------------
void ExtractBag(wstring BagDirectory, wstring BagName)
{
	wstring														BagFileName=BagDirectory;

	BagFileName+=L"\\";
	BagFileName+=BagName;

	HANDLE														BagFileHandle=CreateFile(BagFileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (BagFileHandle==INVALID_HANDLE_VALUE)
	{
		throw(wstring(L"CreateFile() FAILED."));
	}

	try
	{
		DWORD													NumberOfBytesRead;
		SBagRecords												BagRecordsHeader;

		if (ReadFile(BagFileHandle,&BagRecordsHeader,sizeof(SBagRecords),&NumberOfBytesRead,NULL)==FALSE)
		{
			throw(wstring(L"ReadFile() FAILED."));
		}

		vector<SBagRecord>										BagRecords;

		for (int Index=0;Index<BagRecordsHeader.NumberOfBagRecords;Index++)
		{
			SBagRecord											BagRecord;

			if (ReadFile(BagFileHandle,&BagRecord,sizeof(SBagRecord),&NumberOfBytesRead,NULL)==FALSE)
			{
				throw(wstring(L"ReadFile() FAILED."));
			}

			BagRecords.push_back(BagRecord);
		}

		for (vector<SBagRecord>::iterator Iterator=BagRecords.begin();Iterator!=BagRecords.end();Iterator++)
		{
			wstring												FileName=BagDirectory;

			FileName+=L"\\";
			FileName+=Iterator->FileName;

			HANDLE												FileHandle=CreateFile(FileName.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

			if (FileHandle==INVALID_HANDLE_VALUE)
			{
				throw(wstring(L"CreateFile() FAILED."));
			}

			BYTE*												Memory=NULL;

			try
			{
				Memory=new BYTE[Iterator->FileSize];

				if (ReadFile(BagFileHandle,Memory,Iterator->FileSize,&NumberOfBytesRead,NULL)==FALSE)
				{
					throw(wstring(L"ReadFile() FAILED."));
				}

				if (WriteFile(FileHandle,Memory,Iterator->FileSize,&NumberOfBytesRead,NULL)==FALSE)
				{
					throw(wstring(L"WriteFile() FAILED."));
				}

				if (Memory!=NULL)
				{
					delete[](Memory);
					Memory=NULL;
				}

				CloseHandle(FileHandle);

				wprintf_s(L"FILE [%s] EXTRACTED !\n",Iterator->FileName);
			}
			catch(...)
			{
				if (Memory!=NULL)
				{
					delete[](Memory);
					Memory=NULL;
				}

				CloseHandle(FileHandle);

				throw;
			}
		}

		CloseHandle(BagFileHandle);
	}
	catch(...)
	{
		CloseHandle(BagFileHandle);

		throw;
	}
}
//-------------------------------------------------------------------------------------------------------
void ReadBag(wstring BagDirectory, wstring BagName, CBagFileRecords& BagFileRecords)
{
	wstring														BagFileName=BagDirectory;

	BagFileName+=L"\\";
	BagFileName+=BagName;

	HANDLE														BagFileHandle=CreateFile(BagFileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (BagFileHandle==INVALID_HANDLE_VALUE)
	{
		throw(wstring(L"CreateFile() FAILED."));
	}

	try
	{
		DWORD													NumberOfBytesRead;
		SBagRecords												BagRecordsHeader;

		if (ReadFile(BagFileHandle,&BagRecordsHeader,sizeof(SBagRecords),&NumberOfBytesRead,NULL)==FALSE)
		{
			throw(wstring(L"ReadFile() FAILED."));
		}

		BagFileRecords.SetBagExecutable(BagRecordsHeader.BagExecutable);
		BagFileRecords.SetRunnableType(BagRecordsHeader.RunnableType);

		vector<SBagRecord>										BagRecords;

		for (int Index=0;Index<BagRecordsHeader.NumberOfBagRecords;Index++)
		{
			SBagRecord											BagRecord;

			if (ReadFile(BagFileHandle,&BagRecord,sizeof(SBagRecord),&NumberOfBytesRead,NULL)==FALSE)
			{
				throw(wstring(L"ReadFile() FAILED."));
			}

			BagRecords.push_back(BagRecord);
		}

		for (vector<SBagRecord>::iterator Iterator=BagRecords.begin();Iterator!=BagRecords.end();Iterator++)
		{
			CBagFileRecord*										BagFileRecord=NULL;

			try
			{
				BagFileRecord=new CBagFileRecord(Iterator->FileName,Iterator->FileSize,Iterator->IsEXE,Iterator->AssemblyIdentity);

				if (ReadFile(BagFileHandle,BagFileRecord->GetFileData(),Iterator->FileSize,&NumberOfBytesRead,NULL)==FALSE)
				{
					throw(wstring(L"ReadFile() FAILED."));
				}

				BagFileRecords.GetBagFileRecords().push_back(BagFileRecord);
			}
			catch(...)
			{
				if (BagFileRecord!=NULL)
				{
					delete(BagFileRecord);
					BagFileRecord=NULL;
				}

				throw;
			}
		}

		CloseHandle(BagFileHandle);
	}
	catch(...)
	{
		CloseHandle(BagFileHandle);

		BagFileRecords.GetBagFileRecords().clear();

		throw;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Vytvori BAG FILE.
void CreateBagFile(void)
{
	wchar_t														CurrentDirectory[1024];
	wstring														BagDirectory;

	try
	{
		if (GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory)==0)
		{
			throw(wstring(L"GetCurrentDirectory() FAILED."));
		}

		BagDirectory=CurrentDirectory;
		BagDirectory+=L"\\..\\!Bag";

		CreateBag(BagDirectory,L"MyBag.bag",L"BagExecutable.exe",L"BagExecutable.Program");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! Vytvori ASSEMBLY FILES z BAG FILE.
void ExtractBagFile(void)
{
	wchar_t														CurrentDirectory[1024];
	wstring														BagDirectory;

	try
	{
		if (GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory)==0)
		{
			throw(wstring(L"GetCurrentDirectory() FAILED."));
		}

		BagDirectory=CurrentDirectory;
		BagDirectory+=L"\\..\\!Bag";

		ExtractBag(BagDirectory,L"MyBag.bag");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! Nacita data z BAG FILE.
void ReadBagFile(void)
{
	wchar_t														CurrentDirectory[1024];
	wstring														BagDirectory;
	CBagFileRecords												BagFileRecords;

	try
	{
		if (GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory)==0)
		{
			throw(wstring(L"GetCurrentDirectory() FAILED."));
		}

		BagDirectory=CurrentDirectory;
		BagDirectory+=L"\\..\\!Bag";

		ReadBag(BagDirectory,L"MyBag.bag",BagFileRecords);

		vector<CBagFileRecord*>									Vector=BagFileRecords.GetBagFileRecords();

		for (vector<CBagFileRecord*>::iterator Iterator=Vector.begin();Iterator!=Vector.end();Iterator++)
		{
			wprintf_s(L"FILE [%s], SIZE [%d], IsEXE [%d], AssemblyIdentity [%s] !\n",(*Iterator)->GetFileName().c_str(),(*Iterator)->GetFileSize(),(*Iterator)->GetIsEXE(),(*Iterator)->GetAssemblyIdentity().c_str());
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	//CreateBagFile();
	//ExtractBagFile();
	ReadBagFile();

	CHelpers::ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------