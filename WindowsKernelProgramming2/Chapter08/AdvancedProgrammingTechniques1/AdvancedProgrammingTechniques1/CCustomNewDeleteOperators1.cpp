//----------------------------------------------------------------------------------------------------------------------
#include "CCustomNewDeleteOperators1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators1::CCustomNewDeleteOperators1(void)
	: MValue1(), MValue2()
{
	KdPrint(("!!!!! DEFAULT CONSTRUCTOR [CCustomNewDeleteOperators1] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators1::CCustomNewDeleteOperators1(SHORT Value1, LONG Value2)
	: MValue1(Value1), MValue2(Value2)
{
	KdPrint(("!!!!! NON-DEFAULT CONSTRUCTOR [CCustomNewDeleteOperators1] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
CCustomNewDeleteOperators1::~CCustomNewDeleteOperators1(void) noexcept
{
	KdPrint(("!!!!! DESTRUCTOR [CCustomNewDeleteOperators1] CALLED !!!\n"));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SHORT CCustomNewDeleteOperators1::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
LONG CCustomNewDeleteOperators1::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* CCustomNewDeleteOperators1::operator new(size_t, void* Buffer)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR CCustomNewDeleteOperators1::new(size_t Size, void* Buffer)] CALLED !!!\n"));

	// !!!!! Nealokuje MEMORY. Iba vrati POINTER uz na alokovanu MEMORY.

	return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCustomNewDeleteOperators1::operator delete(void*)
{
	KdPrint(("!!!!! OPERATOR [OPERATOR CCustomNewDeleteOperators1::delete(void* Buffer)] CALLED !!!\n"));

	// !!!!! Nedealokuje MEMORY.
}
//----------------------------------------------------------------------------------------------------------------------