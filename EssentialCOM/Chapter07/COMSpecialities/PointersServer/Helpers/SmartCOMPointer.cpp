//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "SmartCOMPointer.h"
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
bool															CSmartCOMPointer<IInterface>::MWriteLog=true;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
CSmartCOMPointer<IInterface>::CSmartCOMPointer(void)
	: MInterface(NULL)
{
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
CSmartCOMPointer<IInterface>::CSmartCOMPointer(IInterface* Interface)
	: MInterface(Interface)
{ 
	InternalAddRef();
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
CSmartCOMPointer<IInterface>::CSmartCOMPointer(const CSmartCOMPointer<IInterface>& Interface)
{
	MInterface=Interface.MInterface;
	InternalAddRef();
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
CSmartCOMPointer<IInterface>::~CSmartCOMPointer(void)
{
	InternalRelease();
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
IInterface* CSmartCOMPointer<IInterface>::operator->(void) const
{ 
	if (MInterface==NULL)
	{
		throw(CCOMException(L"Can't CALL operator->() on NULL INTERFACE !",E_POINTER));
	}

	return(MInterface); 
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
IInterface** CSmartCOMPointer<IInterface>::operator&(void)
{
	InternalRelease();

	return(&MInterface);
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
CSmartCOMPointer<IInterface>& CSmartCOMPointer<IInterface>::operator=(IInterface* Interface)
{
    if (MInterface!=Interface)
	{
        IInterface*												OldInterface=MInterface;

        MInterface=Interface;

        InternalAddRef();

        if (OldInterface!=NULL)
		{
            ULONG												Result=OldInterface->Release();

			OldInterface=NULL;

			if (MWriteLog==true)
			{
				wprintf_s(L"!!!!! operator=() - RESULT [%d] !\n",Result);
			}
        }
    }

    return(*this);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
void CSmartCOMPointer<IInterface>::InternalAddRef(void)
{ 
	if (MInterface!=NULL)
	{
		ULONG													Result=MInterface->AddRef();

		if (MWriteLog==true)
		{
			wprintf_s(L"!!!!! InternalAddRef() - RESULT [%d] !\n",Result);
		}
	}
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
void CSmartCOMPointer<IInterface>::InternalRelease(void)
{
	if (MInterface!=NULL)
	{
		ULONG													Result=MInterface->Release();

		MInterface=NULL;

		if (MWriteLog==true)
		{
			wprintf_s(L"!!!!! InternalRelease() - RESULT [%d] !\n",Result);
		}
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
ULONG CSmartCOMPointer<IInterface>::AddRef(void)
{ 
	if (MInterface==NULL)
	{
		throw(CCOMException(L"Can't CALL AddRef() on NULL INTERFACE !",E_POINTER));
	}
	else
	{
		ULONG													Result=MInterface->AddRef();

		if (MWriteLog==true)
		{
			wprintf_s(L"!!!!! AddRef() - RESULT [%d] !\n",Result);
		}

		return(Result);
	}
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
ULONG CSmartCOMPointer<IInterface>::Release(void)
{
	if (MInterface==NULL)
	{
		throw(CCOMException(L"Can't CALL Release() on NULL INTERFACE !",E_POINTER));
	}
	else
	{
		ULONG													Result=MInterface->Release();

		MInterface=NULL;

		if (MWriteLog==true)
		{
			wprintf_s(L"!!!!! Release() - RESULT [%d] !\n",Result);
		}

		return(Result);
	}
}
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
IInterface* CSmartCOMPointer<IInterface>::GetInterface(void)
{
	return(MInterface);
}
//------------------------------------------------------------------------------------------------------