//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstddef>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
template<typename TType>
class CMyAllocator2
{
//-----------------------------------------------------------------------------
	public:
		using													value_type=TType;
		using													propagate_on_container_copy_assignment=std::true_type;
		using													propagate_on_container_move_assignment=std::true_type;
		using													propagate_on_container_swap=std::true_type;

	public:
		TType* allocate(std::size_t NumberOfElements)
		{
			wprintf_s(L"ALLOCATOR 2 - METHOD ALLOCATE CALLED !\n");

			TType*												Memory=static_cast<TType*>(::operator new(NumberOfElements*sizeof(TType)));

			return(Memory);
		}

		void deallocate(TType* Pointer, std::size_t)
		{
			wprintf_s(L"ALLOCATOR 2 - METHOD DEALLOCATE CALLED !\n");

			::operator delete(Pointer);
		}

		template<class... TParameters>
		void construct(TType* Pointer, TParameters&&... Parameters)
		{
			wprintf_s(L"ALLOCATOR 2 - METHOD CONSTRUCT CALLED !\n");

			// !!! Vola sa CONSTRUCTOR cez OPERATOR NEW PLACEMENT SYNTAX.
			::new((void *)Pointer) TType(std::forward<TParameters>(Parameters)...);
		}

		void destroy(TType* Pointer)
		{
			wprintf_s(L"ALLOCATOR 2 - METHOD DESTROY CALLED !\n");

			// !!! Vola sa DESTRUCTOR.
			Pointer->~TType();
		}

		CMyAllocator2 select_on_container_copy_construction(void) const
		{
			return(CMyAllocator2());
		}

	public:
		CMyAllocator2(void) noexcept
		{
		}

		template<typename TLocalType>
		CMyAllocator2(const CMyAllocator2<TLocalType>&) noexcept
		{
		}

		~CMyAllocator2(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator==(const CMyAllocator2<TType1>&, const CMyAllocator2<TType2>&) noexcept
{
	return(true);
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator!=(const CMyAllocator2<TType1>&, const CMyAllocator2<TType2>&) noexcept
{
	return(false);
}
//-----------------------------------------------------------------------------