//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <utility>
#include <scoped_allocator>
#include "MyDebug.h"
#include "CException.h"
#include "CMyAllocator.h"
#include "CMyAllocator1.h"
#include "CMyAllocator2.h"
#include "CMyAllocator3.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardAllocator(void)
{
	PrintLineSeparator();

	vector<int>													VectorNoAllocator;

	VectorNoAllocator.push_back(10);
	VectorNoAllocator.push_back(20);
	VectorNoAllocator.push_back(30);

	for(int Value : VectorNoAllocator)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! VECTOR pouziva ALLOCATOR z LIST.
	vector<int,list<int>::allocator_type>						VectorWithAllocator;

	VectorWithAllocator.push_back(10);
	VectorWithAllocator.push_back(20);
	VectorWithAllocator.push_back(30);

	for(int Value : VectorWithAllocator)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! ALLOCATORS je mozne porovnavat.
	wcout << L"ALLOCATORS are [" << ((VectorNoAllocator.get_allocator()==VectorWithAllocator.get_allocator()) ? L"SAME" : L"DIFFERENT") << L"] !" << endl;

	bool														AreSameCompatible=uses_allocator<vector<int>,list<wstring>::allocator_type>::value;

	wcout << L"ALLOCATORS are [" << ((AreSameCompatible==true) ? L"COMPATIBLE" : L"DIFFERENT") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomAllocator(void)
{
	PrintLineSeparator();

	{
		vector<wstring,CMyAllocator<wstring>>					VectorWithCustomAllocator;

		VectorWithCustomAllocator.push_back(L"AAA 10");
		VectorWithCustomAllocator.push_back(L"BBB 20");
		VectorWithCustomAllocator.push_back(L"CCC 30");

		for(wstring Value : VectorWithCustomAllocator)
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();

		wcout << L"ALLOCATORS are [" << ((VectorWithCustomAllocator.get_allocator()==VectorWithCustomAllocator.get_allocator()) ? L"SAME" : L"DIFFERENT") << L"] !" << endl;
		wcout << L"ALLOCATORS are [" << ((VectorWithCustomAllocator.get_allocator()!=VectorWithCustomAllocator.get_allocator()) ? L"DIFFERENT" : L"SAME") << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomScopedAllocatorAdaptors(void)
{
	PrintLineSeparator();
	
	wcout << L"TEST is STARTING !" << endl;

	PrintLineSeparator();

	{
		PrintLineSeparator();

		wcout << L"TEST is ENTERING SCOPE !" << endl;

		PrintLineSeparator();

		using													TAllocator1=CMyAllocator1<wstring>;
		using													TCollection1=deque<wstring,TAllocator1>;

		using													TAllocator2=scoped_allocator_adaptor<CMyAllocator2<TCollection1>,TAllocator1>;
		using													TCollection2=list<TCollection1,TAllocator2>;

		using													TAllocator3=scoped_allocator_adaptor<CMyAllocator3<TCollection2>,TAllocator2,TAllocator1>;
		using													TCollection3=list<TCollection2,TAllocator3>;

		TCollection1											Collection11;
		TCollection1											Collection12;
		TCollection1											Collection13;
		TCollection1											Collection14;

		PrintLineSeparator();

		Collection11.push_back(L"AAA");
		Collection11.push_back(L"BBB");

		Collection12.push_back(L"CCC");
		Collection12.push_back(L"DDD");

		Collection13.push_back(L"EEE");
		Collection13.push_back(L"FFF");

		Collection14.push_back(L"GGG");
		Collection14.push_back(L"HHH");

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 1 were ADDED !" << endl;

		PrintLineSeparator();

		TCollection2											Collection21;
		TCollection2											Collection22;

		Collection21.push_back(Collection11);
		Collection21.push_back(Collection12);

		Collection22.push_back(Collection13);
		Collection22.push_back(Collection14);

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 2 were ADDED !" << endl;

		PrintLineSeparator();

		TCollection3											Collection3;

		Collection3.push_back(Collection21);
		Collection3.push_back(Collection22);

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 3 were ADDED !" << endl;

		PrintLineSeparator();

		using													TIterator1=list<deque<wstring,CMyAllocator1<wstring>>,scoped_allocator_adaptor<CMyAllocator2<deque<wstring,CMyAllocator1<wstring>>>,CMyAllocator1<wstring>>>;
		using													TIterator2=deque<wstring,CMyAllocator1<wstring>>;

		for(const TIterator1& Item1 : Collection3)
		{
			for(const TIterator2& Item2 : Item1)
			{
				for(const wstring& Value : Item2)
				{
					wcout << L"VALUE [" << Value << L"] !" << endl;;
				}
			}
		}

		PrintLineSeparator();

		wcout << L"TEST is LEAVING SCOPE !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"TEST is ENDING !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAllocatorRebind(void)
{
	PrintLineSeparator();

	vector<wstring>::allocator_type								Allocator;

	wstring*													StringMemory=Allocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << StringMemory << L"] !" << endl;

	Allocator.deallocate(StringMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();

	// !!! Tento ALLOCATOR je schopny alokovat INTEGERS.
	vector<wstring>::allocator_type::rebind<int>::other			RebindAllocator;

	int*														IntMemory=RebindAllocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << IntMemory << L"] !" << endl;

	RebindAllocator.deallocate(IntMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomAllocatorRebind(void)
{
	PrintLineSeparator();

	CMyAllocator<wstring>										Allocator;

	wstring*													StringMemory=Allocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << StringMemory << L"] !" << endl;

	Allocator.deallocate(StringMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();

	// !!! Tento ALLOCATOR je schopny alokovat INTEGERS.
	CMyAllocator<wstring>::rebind<int>::other					RebindAllocator;

	int*														IntMemory=RebindAllocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << IntMemory << L"] !" << endl;

	RebindAllocator.deallocate(IntMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedFill(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															Values[NUMBER_OF_ITEMS];

	uninitialized_fill(Values,Values+3,10);

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wcout << L"VALUE [" << Values[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedCopy(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															InitializedValues[NUMBER_OF_ITEMS]{1,2,3};
	int															UninitializedValues[NUMBER_OF_ITEMS];

	uninitialized_copy(InitializedValues,InitializedValues+3,UninitializedValues);

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wcout << L"VALUE [" << UninitializedValues[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRawStorageIterator(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															InitializedValues[NUMBER_OF_ITEMS]{1,2,3};
	int															UninitializedValues[NUMBER_OF_ITEMS];

	copy(InitializedValues,InitializedValues+3,raw_storage_iterator<int*,int>(UninitializedValues));

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wcout << L"VALUE [" << UninitializedValues[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemporaryBuffer(void)
{
	PrintLineSeparator();

	// !!! FUNCTION NEMUSI alokovat celu pozadovanu MEMORY.
	pair<int*,ptrdiff_t>										Buffer=get_temporary_buffer<int>(100);

	wcout << L"MEMORY [" << Buffer.first << L"], NUMBER of ELEMENTS [" << Buffer.second << L"] !" << endl;

	return_temporary_buffer<int>(Buffer.first);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestStandardAllocator();
	//TestCustomAllocator();
	//TestCustomScopedAllocatorAdaptors();
	//TestAllocatorRebind();
	TestCustomAllocatorRebind();
	//TestUninitializedFill();
	//TestUninitializedCopy();
	//TestRawStorageIterator();
	//TestTemporaryBuffer();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------