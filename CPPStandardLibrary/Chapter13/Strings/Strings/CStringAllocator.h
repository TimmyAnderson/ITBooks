//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstddef>
#include <string>
#include <iostream>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
template<typename TType>
class CStringAllocator
{
//-----------------------------------------------------------------------------
	public:
		using													value_type=typename std::char_traits<TType>::char_type;
		using													size_type=typename std::basic_string<TType>::size_type;
		using													difference_type=typename std::basic_string<TType>::difference_type;
		using													pointer=typename std::basic_string<TType>::pointer;
		using													const_pointer=typename std::basic_string<TType>::const_pointer;
		using													reference=typename std::basic_string<TType>::reference;
		using													const_reference=typename std::basic_string<TType>::const_reference;

	public:
		template<typename TOtherType>
		struct rebind
		{
			using												other=CStringAllocator<TOtherType>;
		};

	public:
		TType* allocate(std::size_t NumberOfElements)
		{
			std::wcout << L"METHOD ALLOCATE CALLED !" << std::endl;

			TType*												Memory=static_cast<TType*>(::operator new(NumberOfElements*sizeof(TType)));

			return(Memory);
		}

		void deallocate(TType* Pointer, std::size_t)
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
		CStringAllocator(void) noexcept
		{
		}

		template<typename TLocalType>
		CStringAllocator(const CStringAllocator<TLocalType>&) noexcept
		{
		}

		~CStringAllocator(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator==(const CStringAllocator<TType1>&, const CStringAllocator<TType2>&) noexcept
{
	return(true);
}
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
bool operator!=(const CStringAllocator<TType1>&, const CStringAllocator<TType2>&) noexcept
{
	return(false);
}
//-----------------------------------------------------------------------------