//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "UnmanagedCOMObject.h"
#include "Helpers\Lock.h"
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
CUnmanagedCOMObject::CUnmanagedCOMObject(void)
	: MReferenceCounter(0), MCallback(0)
{
}
//------------------------------------------------------------------------------------------------------
CUnmanagedCOMObject::~CUnmanagedCOMObject(void)
{
	MCallback=NULL;

	wprintf_s(L"!!!!!!!!!! COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::RegisterCallback(IUnmanagedCOMServerCallback* Callback)
{
	CLock														Lock(MCS);

	MCallback=Callback;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::UnRegisterCallback(void)
{
	CLock														Lock(MCS);

	MCallback=NULL;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::SendMessageToServer(BSTR Message)
{
	CLock														Lock(MCS);

	bstr_t														MessageFromClient=Message;

	wprintf_s(L"Message from CLIENT [%s] !\n",MessageFromClient.operator const wchar_t *());

	if (MCallback.GetInterface()!=NULL)
	{
		bstr_t													MessageToClient=L"CLIENT MESSAGE [";

		MessageToClient+=MessageFromClient;
		MessageToClient+=bstr_t(L"]");

		MCallback->SendMessageToClient(MessageToClient);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::PrintMessage(BSTR Message)
{
	CLock														Lock(MCS);

	bstr_t														MessageFromClient=Message;

	wprintf_s(L"Message from CLIENT [%s] !\n",MessageFromClient.operator const wchar_t *());

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::LoadName(BSTR* Name, int* Age)
{
	CLock														Lock(MCS);

	*Name=MName.copy();
	*Age=MAge;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::SaveName(BSTR Name, int Age)
{
	CLock														Lock(MCS);

	MName=Name;
	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::ArrayTest1(int ArraySize, int* Array)
{
	CLock														Lock(MCS);

	for(int Index=0;Index<ArraySize;Index++)
	{
		wprintf_s(L"COM - ITEM[%d]=[%d] !\n",Index,Array[Index]);

		Array[Index]+=100;
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::ArrayTest2(SAFEARRAY** Array)
{
	CLock														Lock(MCS);

	wprintf(L"SERVER: METHOD SafeArrayInt() was CALLED !\n");

	// !!! Podporujem iba SAFEARRAYS s 1 DIMENSION.
	if (SafeArrayGetDim(*Array)==1)
	{
		HRESULT													HR=S_OK;
		long													LowerBound;
		long													UpperBound;

		if (SUCCEEDED(HR=SafeArrayGetLBound(*Array,1,&LowerBound)))
		{
			if (SUCCEEDED(HR=SafeArrayGetUBound(*Array,1,&UpperBound)))
			{
				int*											Data=NULL;

				// Ziska sa POINTER na DATA.
				if (SUCCEEDED(HR=SafeArrayAccessData(*Array,(void**) &Data)))
				{
					for (long Index=0;Index<(UpperBound-LowerBound)+1;Index++)
					{
						wprintf(L"SERVER: ITEM [%d]: [%d] !\n",Index,Data[Index]);

						Data[Index]+=100;
					}

					// Uvolni sa POINTER na DATA.
					if (FAILED(HR=SafeArrayUnaccessData(*Array)))
					{
						wprintf_s(L"Can't UNACCESS DATA !\n");
					}
				}
				else
				{
					wprintf_s(L"Can't ACCESS DATA !\n");
				}
			}
			else
			{
				wprintf_s(L"Can't GET UPPER BOUND !\n");
			}
		}
		else
		{
			wprintf_s(L"Can't GET LOWER BOUND !\n");
		}

		return(HR);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CUnmanagedCOMObject::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IUnmanagedCOMServer*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IUnmanagedCOMServer)
	{
		*PointerToObject=static_cast<IUnmanagedCOMServer*>(this);
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
ULONG STDMETHODCALLTYPE CUnmanagedCOMObject::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CUnmanagedCOMObject::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------