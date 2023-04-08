//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
//-------------------------------------------------------------------------------------------------------
// !!! Pseudo implementacia ALLOCATOR, kde CLASS iba ZDEDI zo STANDARDNEHO allocator<TItem> CLASS.
template<typename TItem>
class CPrimitiveCustomAllocator : public std::allocator<TItem>
{
	public:
		CPrimitiveCustomAllocator(void);
		~CPrimitiveCustomAllocator(void);
};
//-------------------------------------------------------------------------------------------------------