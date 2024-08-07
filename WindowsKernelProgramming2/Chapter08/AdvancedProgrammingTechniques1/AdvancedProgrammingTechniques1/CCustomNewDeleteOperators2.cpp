//----------------------------------------------------------------------------------------------------------------------
#include "CCustomNewDeleteOperators2.h"
#include "Helpers\MyKernelHelpers.h"
#include "SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators2::CCustomNewDeleteOperators2(void)
	: MValue1(), MValue2()
{
	KdPrint(("!!!!! DEFAULT CONSTRUCTOR [CCustomNewDeleteOperators2] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators2::CCustomNewDeleteOperators2(SHORT Value1, LONG Value2)
	: MValue1(Value1), MValue2(Value2)
{
	KdPrint(("!!!!! NON-DEFAULT CONSTRUCTOR [CCustomNewDeleteOperators2] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators2::~CCustomNewDeleteOperators2(void) noexcept
{
	KdPrint(("!!!!! DESTRUCTOR [CCustomNewDeleteOperators2] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SHORT CCustomNewDeleteOperators2::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
LONG CCustomNewDeleteOperators2::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* CCustomNewDeleteOperators2::operator new(size_t Size, POOL_FLAGS Pool, ULONG Tag)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR CCustomNewDeleteOperators2::new(size_t Size, POOL_TYPE Pool, ULONG Tag)] CALLED !!!\n"));

	void*														Buffer=ExAllocatePool2(Pool,Size,Tag);

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCustomNewDeleteOperators2::operator delete(void* Buffer)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR CCustomNewDeleteOperators2::delete(void* Buffer)] CALLED !!!\n"));

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------