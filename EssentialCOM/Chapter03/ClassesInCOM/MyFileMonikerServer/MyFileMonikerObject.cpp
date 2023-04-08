//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MyFileMonikerObject.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
CMyFileMonikerObject::CMyFileMonikerObject(void)
	: MReferenceCounter(0), MFirstName(), MLastName(), MAge(0), MRegistredObjects()
{
}
//------------------------------------------------------------------------------------------------------
CMyFileMonikerObject::~CMyFileMonikerObject(void)
{
	CSmartCOMPointer<IRunningObjectTable>						ROT;

	// !!! Odregistrujem COM OBJECTS s ROT TABLE.
	if (SUCCEEDED(GetRunningObjectTable(0,&ROT)))
	{
		for (list<DWORD>::iterator Iterator=MRegistredObjects.begin();Iterator!=MRegistredObjects.end();Iterator++)
		{
			DWORD												RegistrationID=*Iterator;

			if (SUCCEEDED(ROT->Revoke(RegistrationID)))
			{
				wprintf_s(L"REVOKE SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"REVOKE FAILED !\n");
			}
		}

		ROT=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::SetFirstName(wchar_t* FirstName)
{
	CLock														Lock(MCS);

	MFirstName=FirstName;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::SetLastName(wchar_t* LastName)
{
	CLock														Lock(MCS);

	MLastName=LastName;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::GetFirstName(int BufferSize, wchar_t** FirstName)
{
	CLock														Lock(MCS);

	*FirstName=MFirstName.copy();
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::GetLastName(int BufferSize, wchar_t** LastName)
{
	CLock														Lock(MCS);

	*LastName=MLastName.copy();
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::GetAge(int *Age)
{
	CLock														Lock(MCS);

	if (MAge!=0)
	{
		*Age=MAge;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::IsDirty(void)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::Load(__RPC__in LPCOLESTR FileName, DWORD Mode)
{
	FILE*														File=NULL;
	HRESULT														HR=E_FAIL;
	wchar_t														BufferFirstName[1024];	
	wchar_t														BufferLastName[1024];	
	int															BufferAge=0;

	if (_wfopen_s(&File,FileName,L"r")==0)
	{
		if (fgetws(BufferFirstName,_countof(BufferFirstName),File)==NULL)
		{
			return(E_FAIL);
		}

		for (int Index=0;BufferFirstName[Index]!='\0';Index++)
		{
			if (BufferFirstName[Index]=='\r' || BufferFirstName[Index]=='\n')
			{
				BufferFirstName[Index]='\0';
				break;
			}
		}

		if (fgetws(BufferLastName,_countof(BufferLastName),File)==NULL)
		{
			return(E_FAIL);
		}

		for (int Index=0;BufferLastName[Index]!='\0';Index++)
		{
			if (BufferLastName[Index]=='\r' || BufferLastName[Index]=='\n')
			{
				BufferLastName[Index]='\0';
				break;
			}
		}

		if (fwscanf_s(File,L"%d",&BufferAge)!=1)
		{
			return(E_FAIL);
		}

		SetFirstName(BufferFirstName);
		SetLastName(BufferLastName);
		SetAge(BufferAge);

		fclose(File);

		CSmartCOMPointer<IRunningObjectTable>					ROT;

		if (SUCCEEDED(GetRunningObjectTable(0,&ROT)))
		{
			CSmartCOMPointer<IMoniker>						FileMoniker;

			if (SUCCEEDED(CreateFileMoniker(FileName,&FileMoniker)))
			{
				DWORD										RegistrationID;

				if (SUCCEEDED(ROT->Register(0,(IMyFileMonikerName*) this,FileMoniker.GetInterface(),&RegistrationID)))
				{
					MRegistredObjects.push_back(RegistrationID);
					HR=S_OK;
				}

				FileMoniker=NULL;
			}

			ROT=NULL;
		}

		return(HR);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::Save(__RPC__in_opt LPCOLESTR FileName, BOOL Remember)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::SaveCompleted(__RPC__in_opt LPCOLESTR FileName)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::GetCurFile(__RPC__deref_out_opt LPOLESTR* FileName)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::GetClassID(__RPC__out CLSID* ClassID)
{
	return(E_NOTIMPL);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMyFileMonikerObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IMyFileMonikerName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IMyFileMonikerName)
	{
		*PointerToObject=static_cast<IMyFileMonikerName*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IPersistFile)
	{
		*PointerToObject=static_cast<IPersistFile*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IPersist)
	{
		*PointerToObject=static_cast<IPersist*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyFileMonikerObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMyFileMonikerObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------