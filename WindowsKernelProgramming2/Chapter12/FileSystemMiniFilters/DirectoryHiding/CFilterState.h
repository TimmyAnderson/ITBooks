//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include <fltKernel.h>
#include "Helpers\MyKernelHelpers.h"
#include "Helpers\CExecutiveResourceGlobal.h"
#include "CBasicString.h"
#include "CVector.h"
#include "EPoolType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFilterState final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! MEMORY MUSI byt alokovana na NON-PAGED MEMORY, pretoze sa pouziva v POST OPERATION CALLBACK, ktora moze byt volana na IRQL [IRQL<=DISPATCH_LEVEL].
		using													TString=KTL::CBasicString<wchar_t,EPoolType::NonPaged,MY_TAG>;
		using													TVector=KTL::CVector<TString,EPoolType::NonPaged,MY_TAG>;

	public:
		PDRIVER_OBJECT											MDriverObject;
		PFLT_FILTER												MFilter;
		TVector													MFiles;
		CExecutiveResourceGlobal								MLock;

	public:
		CFilterState(PDRIVER_OBJECT DriverObject);
		~CFilterState(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------