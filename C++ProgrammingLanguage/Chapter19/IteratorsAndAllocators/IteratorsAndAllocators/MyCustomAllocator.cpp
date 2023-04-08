//-------------------------------------------------------------------------------------------------------
#include "MyCustomAllocator.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
CMyCustomAllocator<TItem>::CMyCustomAllocator(void)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
CMyCustomAllocator<TItem>::CMyCustomAllocator(const CMyCustomAllocator& Other)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
CMyCustomAllocator<TItem>::~CMyCustomAllocator(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
template<class TOther>
CMyCustomAllocator<TItem>& CMyCustomAllocator<TItem>::operator=(const CMyCustomAllocator<TOther>&)
{
	wprintf_s(L"Method operator=() CALLED !\n");

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
TItem* CMyCustomAllocator<TItem>::allocate(size_type Count)
{
	wprintf_s(L"Method allocate() CALLED !\n");

	void*														Pointer=::operator new(Count*sizeof(TItem));
	TItem*														Ret=(TItem*) Pointer;
	
	return(Ret);
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
TItem* CMyCustomAllocator<TItem>::allocate(size_type Count, const void*)
{
	wprintf_s(L"Method allocate() CALLED !\n");

	void*														Pointer=::operator new(Count*sizeof(TItem));
	TItem*														Ret=(TItem*) Pointer;

	return(Ret);
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
void CMyCustomAllocator<TItem>::deallocate(pointer Pointer, size_type)
{
	wprintf_s(L"Method deallocate() CALLED !\n");

	::operator delete(Pointer);
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
size_t CMyCustomAllocator<TItem>::max_size(void) const
{	
	wprintf_s(L"Method max_size() CALLED !\n");

	// Nejaka HAUSNUMER hodnota.
	size_t														Count=10000000/sizeof(TItem);

	return (Count);
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
void CMyCustomAllocator<TItem>::destroy(pointer Pointer)
{
	wprintf_s(L"Method destroy() CALLED !\n");

	Pointer->~TItem();
}
//-------------------------------------------------------------------------------------------------------
template<typename TItem>
template<class TOther>
void CMyCustomAllocator<TItem>::construct(pointer Pointer, TOther&& Value)
{
	wprintf_s(L"Method construct() CALLED !\n");

	::new ((void*) Pointer) TItem((Value));
}
//-------------------------------------------------------------------------------------------------------