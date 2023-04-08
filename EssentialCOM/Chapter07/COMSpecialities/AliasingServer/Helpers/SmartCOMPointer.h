//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include "COMException.h"
//------------------------------------------------------------------------------------------------------
template<typename IInterface>
class CSmartCOMPointer
{
	private:
		static bool												MWriteLog;

	private:
		IInterface*												MInterface;

	public:
		IInterface* operator->(void) const;
		IInterface** operator&(void);
		CSmartCOMPointer<IInterface>& operator=(IInterface* Interface);

	private:
		void InternalAddRef(void);
		void InternalRelease(void);

	public:
		ULONG AddRef(void);
		ULONG Release(void);
		IInterface* GetInterface(void);

	public:
		CSmartCOMPointer(void);
		CSmartCOMPointer(IInterface* Interface);
		CSmartCOMPointer(const CSmartCOMPointer<IInterface>& Interface);
		~CSmartCOMPointer(void);
};
//------------------------------------------------------------------------------------------------------