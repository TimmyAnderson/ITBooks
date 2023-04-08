//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!!!! Toto NIE JE KOMPLETNA IMPLEMENTACIA ALLOCATOR. Su implementovane iba tie METODY, ktore boli nevyhnutne potrebne pre jednoduchy prechod cez VECTOR. 
template<typename TItem>
class CMyCustomAllocator
{
	public:
		typedef typename TItem									value_type;
		typedef value_type*										pointer;
		typedef value_type&										reference;
		typedef const value_type*								const_pointer;
		typedef const value_type&								const_reference;
		typedef size_t											size_type;
		typedef size_t											difference_type;
		
	public:
		template<typename TInnerItem>
		struct rebind
		{
			typedef CMyCustomAllocator<TInnerItem>				other;
		};

	public:
		template<class TOther>
		CMyCustomAllocator<TItem>& operator=(const CMyCustomAllocator<TOther>&);

	public:
		pointer allocate(size_type Count);
		pointer allocate(size_type Count, const void*);
		void deallocate(pointer Pointer, size_type);
		size_t max_size(void) const;
		void destroy(pointer Pointer);

	public:
		template<class TOther>
		void construct(pointer Pointer, TOther&& Value);

	public:
		CMyCustomAllocator(void);
		CMyCustomAllocator(const CMyCustomAllocator& Other);
		~CMyCustomAllocator(void);

	public:
		// CONSTRUCTOR, ako TEMPLATE MEMBER FUNKCIA.
		template<class TOther>
		CMyCustomAllocator(const CMyCustomAllocator<TOther>&)
		{
		}
};
//-------------------------------------------------------------------------------------------------------