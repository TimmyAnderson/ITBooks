#pragma once
#include "resource.h"
#include "MyCOM_i.h"
//-------------------------------------------------------------------------------------------------------
using namespace ATL;
//-------------------------------------------------------------------------------------------------------
class ATL_NO_VTABLE CBasicMathClass :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CBasicMathClass, &CLSID_BasicMathClass>,
	public IDispatchImpl<IBasicMathClass, &IID_IBasicMathClass, &LIBID_MyCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CBasicMathClass()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BASICMATHCLASS)


BEGIN_COM_MAP(CBasicMathClass)
	COM_INTERFACE_ENTRY(IBasicMathClass)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(Add)(LONG A, LONG B, LONG* Result);
};
//-------------------------------------------------------------------------------------------------------
OBJECT_ENTRY_AUTO(__uuidof(BasicMathClass), CBasicMathClass)
//-------------------------------------------------------------------------------------------------------