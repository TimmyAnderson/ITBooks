//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CCustomCollection4
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		// !!! METHOD begin() MUSI vracat ITERATOR. POINTER je ITERATOR, lebo MA OPERATOR++.
		inline int* begin(void)
		{
			std::wcout << L"int* CCustomCollection4::begin(void) CALLED !" << std::endl;

			return(&MData[0]);
		}

		// !!! METHOD end() MUSI vracat ITERATOR. POINTER je ITERATOR, lebo MA OPERATOR++.
		inline int* end(void)
		{
			std::wcout << L"int* CCustomCollection4::end(void) CALLED !" << std::endl;

			// !!! ITERATOR musi vracat 1 POZICIU ZA KONCOM COLLECTION.
			return(&MData[MSize]);
		}

	public:
		inline CCustomCollection4(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CCollection::CCollection(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		inline ~CCustomCollection4(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------