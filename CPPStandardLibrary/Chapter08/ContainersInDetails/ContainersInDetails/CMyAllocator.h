//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstddef>
#include <iostream>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
template<typename TType>
class CMyAllocator
{
//-----------------------------------------------------------------------------
	public:
		using													value_type=TType;

	public:
		TType* allocate(std::size_t NumberOfElements)
		{
			std::wcout << L"METHOD ALLOCATE CALLED !" << std::endl;

			TType*												Memory=static_cast<TType*>(::operator new(NumberOfElements*sizeof(TType)));

			return(Memory);
		}

		void deallocate(TType* Pointer,std::size_t)
		{
			std::wcout << L"METHOD DEALLOCATE CALLED !" << std::endl;

			::operator delete(Pointer);
		}

		template<class... TParameters>
		void construct(TType* Pointer, TParameters&&... Parameters)
		{
			std::wcout << L"METHOD CONSTRUCT CALLED !" << std::endl;

			// !!! Vola sa CONSTRUCTOR cez OPERATOR NEW PLACEMENT SYNTAX.
			::new((void *)Pointer) TType(std::forward<TParameters>(Parameters)...);
		}

		void destroy(TType* Pointer)
		{
			std::wcout << L"METHOD DESTROY CALLED !" << std::endl;

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