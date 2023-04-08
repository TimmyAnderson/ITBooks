//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstddef>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
template<typename TType>
class CMyAllocator3
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
			wprintf_s(L"ALLOCATOR 3 - METHOD ALLOCATE CALLED !\n");

			TType*												Memory=static_cast<TType*>(::operator new(NumberOfElements*sizeof(TType)));

			return(Memory);
		}

		void deallocate(TType* Pointer, std::size_t)
		{
			wprintf_s(L"ALLOCATOR 3 - METHOD DEALLOCATE CALLED !\n");

			::operator delete(Pointer);
		}

		template<class... TParameters>
		void construct(TType* Pointer, TParameters&&... Parameters)
		{
			wprintf_s(L"ALLOCATOR 3 - METHOD CONSTRUCT CALLED !\n");

			// !!! Vola sa CONSTRUCTOR cez OPERATOR NEW PLACEMENT SYNTAX.
			::new((void *)Pointer) TType(std::forward<TParameters>(Parameters)...);
		}

		void destroy(TType* Pointer)
		{
			wprintf_s(L"ALLOCATOR 3 - METHOD DESTROY CALLED !\n");

			// !!! Vola sa DESTRUCTOR.
			Pointer->~TType();
		}

		CMyAllocator3 select_on_container_copy_construction(void) const
		{
			return(CMyAllocator3());
		}

	public:
		CMyAllocator3(void) noexcept
		{
		}

		template<typename TLocalType>
		CMyAllocator3(const CMyAllocator3<TLocalType>&) noexcept
		{
		}

		~CMyAllocator3(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator==(const CMyAllocator3<TType1>&, const CMyAllocator3<TType2>&) noexcept
{
	return(true);
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator!=(const CMyAllocator3<TType1>&, const CMyAllocator3<TType2>&) noexcept
{
	return(false);
}
//-----------------------------------------------------------------------------