//----------------------------------------------------------------------------------------------------------------------
#include "TestMemoryOperators.h"
#include "Helpers\CHelpers.h"
#include "CTestClass1.h"
#include "CTestClass2.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS TestMemoryOperators(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;

	{
		KdPrint(("!!!!! ROUTINE [%s] - CTestClass1 - SIZEOF [%I64u] !!!\n",FunctionName,sizeof(CTestClass1)));

		CTestClass1*											Object=new (EPoolFlags::E_POOL_FLAG_PAGED) CTestClass1(true,100,-1000000,1000000000);
	
		KdPrint(("!!!!! ROUTINE [%s] - CTestClass1 - VALUE 1 [%hhd] VALUE 2 [%hd] VALUE 3 [%ld] VALUE 4 [%I64u] !!!\n",FunctionName,Object->GetValue1(),Object->GetValue2(),Object->GetValue3(),Object->GetValue4()));

		delete(Object);
		Object=nullptr;
	}

	{
		KdPrint(("!!!!! ROUTINE [%s] - CTestClass1 - SIZEOF [%I64u] !!!\n",FunctionName,sizeof(CTestClass2)));

		CTestClass2*											Object=new (EPoolFlags::E_POOL_FLAG_NON_PAGED) CTestClass2(true,200,-2000000,2000000000,-3000000000,4000000000);
	
		KdPrint(("!!!!! ROUTINE [%s] - CTestClass1 - VALUE 1 [%hhd] VALUE 2 [%hd] VALUE 3 [%ld] VALUE 4 [%I64u] VALUE 5 [%I64d] VALUE 6 [%I64u] !!!\n",FunctionName,Object->GetValue1(),Object->GetValue2(),Object->GetValue3(),Object->GetValue4(),Object->GetValue5(),Object->GetValue6()));

		delete(Object);
		Object=nullptr;
	}

	Status=CHelpers::CompleteIRP(Irp,Status,Information);

	return(Status);
}
//----------------------------------------------------------------------------------------------------------------------