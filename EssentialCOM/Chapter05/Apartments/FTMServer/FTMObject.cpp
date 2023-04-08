//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "FTMObject.h"
#include "Helpers\Lock.h"
//------------------------------------------------------------------------------------------------------
CFTMObject::CFTMObject(void)
	: MReferenceCounter(0), MValue(0), MFTM(NULL), MGIT(NULL), MSTAObjectCookie(0)
{
	// !!! Vytvori sa FREE THREADED MARSHALER.
	if (SUCCEEDED(CoCreateFreeThreadedMarshaler(this,&MFTM)))
	{
		if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &MGIT)))
		{
			CSmartCOMPointer<IObjectUsedByFTMTest>				ObjectUsedByFTM=NULL;

			// !!! Vytvori sa POINTER na STA COM OBJECT, ktory demonstruje problemy FTM pri pouzivani STA COM OBJECTS z COM OBJECTS implementujucich FTM.
			if (SUCCEEDED(CoCreateInstance(CLSID_ObjectUsedByFTMObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IObjectUsedByFTMTest),(void**) &ObjectUsedByFTM)))
			{
				// !!!! REGISTRUJE POINTER na STA COM OBJECT v GIT.
				if (FAILED(MGIT->RegisterInterfaceInGlobal(ObjectUsedByFTM.GetInterface(),__uuidof(IObjectUsedByFTMTest),&MSTAObjectCookie)))
				{
					wprintf_s(L"CAN'T REGISTER POINTER to GIT !\n");
				}

				// !!! Kedze POINTER na STA COM POINTER IObjectUsedByFTMTest mam ulozeny v GIT, mozem ho UVOLNIT.
				ObjectUsedByFTM=NULL;
			}
			else
			{
				wprintf_s(L"CAN'T CREATE ObjectUsedByFTM !\n");
			}
		}
		else
		{
			wprintf_s(L"CAN'T CREATE GIT !\n");
		}
	}
	else
	{
		wprintf_s(L"CAN'T CREATE FTM !\n");
	}
}
//------------------------------------------------------------------------------------------------------
CFTMObject::~CFTMObject(void)
{
	// !!! Uvolni sa COOKIE na STA COM OBJECT, ktory demonstruje riesenie problemov FTM pri pouzivani STA COM OBJECTS z COM OBJECTS implementujucich FTM.
	if (MSTAObjectCookie!=0)
	{
		if (FAILED(MGIT->RevokeInterfaceFromGlobal(MSTAObjectCookie)))
		{
			wprintf_s(L"CAN'T REVOKE POINTER from GIT !\n");
		}

		MSTAObjectCookie=0;
	}

	// Uvolni sa GLOBAL INTERFACE TABLE.
	MGIT=NULL;

	// !!! Uvolni sa FREE THREADED MARSHALER.
	MFTM=NULL;

	wprintf_s(L"!!!!!!!!!! COM OBJECT [CFTMObject] DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFTMObject::IncrementValue(void)
{
	CLock														Lock(MCS);

	MValue++;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFTMObject::GetValue(long* Value)
{
	CLock														Lock(MCS);

	*Value=MValue;

	wprintf_s(L"!!!!! SERVER VALUE [CFTMObject]: [%d] !\n",MValue);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFTMObject::IncrementValueToRemoteObject(void)
{
	// !!! Umyselne NEDAM LOCK, aby sa ukazalo, ze INTERNE STA COM OBJECTS pri pouziti FTM, MUSIA byt MARSHALLED.
	HRESULT														HR;
	CSmartCOMPointer<IObjectUsedByFTMTest>						ObjectUsedByFTMTest;

	// !!!!! Pri KAZDOM VOLANI STA COM OBJECT MUSIM POINTER nan ziskat z GIT, aby v pripade potreby bol MARSHALLED do SPRAVNEHO APARTMENT.
	if (SUCCEEDED(HR=MGIT->GetInterfaceFromGlobal(MSTAObjectCookie,__uuidof(IObjectUsedByFTMTest),(void**) &ObjectUsedByFTMTest)))
	{
		HR=ObjectUsedByFTMTest->IncrementValue();

		// !!! STA COM OBJECT sa po skonceni kazdeho volania UVOLNI.
		ObjectUsedByFTMTest=NULL;
	}

	return(HR);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFTMObject::GetValueFromRemoteObject(long* Value)
{
	// !!! Umyselne NEDAM LOCK, aby sa ukazalo, ze INTERNE STA COM OBJECTS pri pouziti FTM, MUSIA byt MARSHALLED.
	HRESULT														HR;
	CSmartCOMPointer<IObjectUsedByFTMTest>						ObjectUsedByFTMTest;

	// !!!!! Pri KAZDOM VOLANI STA COM OBJECT MUSIM POINTER nan ziskat z GIT, aby v pripade potreby bol MARSHALLED do SPRAVNEHO APARTMENT.
	if (SUCCEEDED(HR=MGIT->GetInterfaceFromGlobal(MSTAObjectCookie,__uuidof(IObjectUsedByFTMTest),(void**) &ObjectUsedByFTMTest)))
	{
		HR=ObjectUsedByFTMTest->GetValue(Value);

		// !!! STA COM OBJECT sa po skonceni kazdeho volania UVOLNI.
		ObjectUsedByFTMTest=NULL;
	}

	wprintf_s(L"!!!!! SERVER VALUE [CObjectUsedByFTMObject] from [CFTMObject]: [%d] !\n",*Value);

	return(HR);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CFTMObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IFTMTest*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IFTMTest)
	{
		*PointerToObject=static_cast<IFTMTest*>(this);
		AddRef();
		return(S_OK);
	}
	// !!! Ak je dotaz na IMarshal, vola sa QueryInterface() FTM.
	else if (RIID==IID_IMarshal)
	{
		return(MFTM->QueryInterface(RIID,PointerToObject));
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CFTMObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CFTMObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------