//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "MultiInterfaceCOM.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
CMultiInterfaceCOM::CMultiInterfaceCOM(void)
	: MReferenceCounter(0), MFirstName(NULL), MLastName(NULL), MAge(0), MText(), MName(), MUnionAge(), MVariant(), MProperty(0)
{
}
//------------------------------------------------------------------------------------------------------
CMultiInterfaceCOM::~CMultiInterfaceCOM(void)
{
	if (MFirstName!=NULL)
	{
		delete[](MFirstName);
		MFirstName=NULL;
	}

	if (MLastName!=NULL)
	{
		delete[](MLastName);
		MLastName=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetFirstName(wchar_t* FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		delete[](MFirstName);
		MFirstName=NULL;
	}

	size_t														Length=wcslen(FirstName)+1;

	MFirstName=new wchar_t[Length];
	wcscpy_s(MFirstName,Length,FirstName);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetLastName(wchar_t* LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		delete[](MLastName);
		MLastName=NULL;
	}

	size_t														Length=wcslen(LastName)+1;

	MLastName=new wchar_t[Length];
	wcscpy_s(MLastName,Length,LastName);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetAge(int Age)
{
	CLock														Lock(MCS);

	MAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetFirstName(int BufferSize, wchar_t** FirstName)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wcscpy_s(*FirstName,BufferSize,MFirstName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetLastName(int BufferSize, wchar_t** LastName)
{
	CLock														Lock(MCS);

	if (MLastName!=NULL)
	{
		wcscpy_s(*LastName,BufferSize,MLastName);
	}
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetAge(int *Age)
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
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::ToString(void)
{
	CLock														Lock(MCS);

	if (MFirstName!=NULL)
	{
		wprintf_s(L"FirstName [%s] !\n",MFirstName);
	}

	if (MLastName!=NULL)
	{
		wprintf_s(L"LastName [%s] !\n",MLastName);
	}

	if (MAge>0)
	{
		wprintf_s(L"Age [%d] !\n",MAge);
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetString(BSTR Text)
{
	CLock														Lock(MCS);

	MText=Text;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetString(BSTR* Text)
{
	CLock														Lock(MCS);

	*Text=MText.copy();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetName(struct SName Name)
{
	CLock														Lock(MCS);

	MName=Name;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetName(struct SName *Name)
{
	CLock														Lock(MCS);

	*Name=MName;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetUnion(int DiscriminatorField, union UAge Age)
{
	CLock														Lock(MCS);

	MUnionAge=Age;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetUnion(int DiscriminatorField, union UAge *Age)
{
	CLock														Lock(MCS);

	*Age=MUnionAge;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::SetVariant(VARIANT Value)
{
	CLock														Lock(MCS);

	MVariant=Value;
	
	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::GetVariant(VARIANT* Value)
{
	CLock														Lock(MCS);

	*Value=MVariant;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::Print1(IToString* Interface)
{
	CLock														Lock(MCS);

	Interface->ToString();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::Print2(REFIID InterfaceID, IUnknown* Interface)
{
	CLock														Lock(MCS);

	if (InterfaceID==IID_IToString)
	{
		IToString*											TypedInterface=(IToString*) Interface;

		TypedInterface->ToString();
	}
	else
	{
		wprintf_s(L"UNEXPECTED INTERFACE !\n");
	}

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::put_MyProperty(int Value)
{
	CLock														Lock(MCS);

	MProperty=Value;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::get_MyProperty(int* Value)
{
	CLock														Lock(MCS);

	*Value=MProperty;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::ThrowException(boolean Throw)
{
	CLock														Lock(MCS);

	if (Throw!=0)
	{
		CSmartCOMPointer<ICreateErrorInfo>						ErrorInfoFactory;

		if (SUCCEEDED(CreateErrorInfo(&ErrorInfoFactory)))
		{
			ErrorInfoFactory->SetDescription(L"This is ERROR from COM !");
			ErrorInfoFactory->SetGUID(IID_IExceptionTest);

			CSmartCOMPointer<IErrorInfo>						ErrorInfo;

			if (SUCCEEDED(ErrorInfoFactory->QueryInterface(IID_IErrorInfo,(void**) &ErrorInfo)))
			{
				SetErrorInfo(0,ErrorInfo.GetInterface());
				ErrorInfo=NULL;
			}

			ErrorInfoFactory=NULL;
		}

		return(E_FAIL);
	}
	else
	{
		return(S_OK);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::InterfaceSupportsErrorInfo(__RPC__in REFIID RIID)
{
	if (RIID==IID_IExceptionTest)
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMultiInterfaceCOM::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IName*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IName)
	{
		*PointerToObject=static_cast<IName*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IToString)
	{
		*PointerToObject=static_cast<IToString*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ITest)
	{
		*PointerToObject=static_cast<ITest*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IExceptionTest)
	{
		*PointerToObject=static_cast<IExceptionTest*>(this);
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_ISupportErrorInfo)
	{
		*PointerToObject=static_cast<ISupportErrorInfo*>(this);
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
ULONG STDMETHODCALLTYPE CMultiInterfaceCOM::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CMultiInterfaceCOM::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------