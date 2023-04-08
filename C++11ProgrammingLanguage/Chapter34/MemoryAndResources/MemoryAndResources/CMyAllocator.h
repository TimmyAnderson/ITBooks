//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstddef>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
template<typename TType>
class CMyAllocator
{
//-----------------------------------------------------------------------------
	public:
		using													value_type=TType;

	public:
		template<typename TOtherType>
		struct rebind
		{
			using												other=CMyAllocator<TOtherType>;
		};

	public:
		TType* allocate(std::size_t NumberOfElements)
		{
			wprintf_s(L"METHOD ALLOCATE CALLED !\n");

			TType*												Memory=static_cast<TType*>(::operator new(NumberOfElements*sizeof(TType)));

			return(Memory);
		}

		void deallocate(TType* Pointer, std::size_t)
		{
			wprintf_s(L"METHOD DEALLOCATE CALLED !\n");

			::operator delete(Pointer);
		}

		template<class... TParameters>
		void construct(TType* Pointer, TParameters&&... Parameters)
		{
			wprintf_s(L"METHOD CONSTRUCT CALLED !\n");

			// !!! Vola sa CONSTRUCTOR cez OPERATOR NEW PLACEMENT SYNTAX.
			::new((void *)Pointer) TType(std::forward<TParameters>(Parameters)...);
		}

		void destroy(TType* Pointer)
		{
			wprintf_s(L"METHOD DESTROY CALLED !\n");

			// !!! Vola sa DESTRUCTOR.
			Pointer->~TType();
		}

	public:
		CMyAllocator(void) noexcept
		{
		}

		template<typename TLocalType>
		CMyAllocator(const CMyAllocator<TLocalType>&) noexcept
		{
		}

		~CMyAllocator(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator==(const CMyAllocator<TType1>&, const CMyAllocator<TType2>&) noexcept
{
	return(true);
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator!=(const CMyAllocator<TType1>&, const CMyAllocator<TType2>&) noexcept
{
	return(false);
}
//-----------------------------------------------------------------------------