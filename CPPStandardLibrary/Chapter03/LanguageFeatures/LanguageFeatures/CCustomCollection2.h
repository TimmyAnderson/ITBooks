//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CCustomCollection2
{
//-------------------------------------------------------------------------------------------------------
	private:
		vector<int>												MCollection;

	public:
		// !!! METHOD begin() MUSI vracat ITERATOR.
		inline vector<int>::iterator begin(void)
		{
			std::wcout << L"vector<int>::iterator CCustomCollection2::begin(void) CALLED !" << std::endl;

			return(MCollection.begin());
		}

		// !!! METHOD end() MUSI vracat ITERATOR.
		inline vector<int>::iterator end(void)
		{
			std::wcout << L"vector<int>::iterator CCustomCollection2::end(void) CALLED !" << std::endl;

			return(MCollection.end());
		}

	public:
		inline CCustomCollection2(initializer_list<int> Data)
		{
			MCollection=Data;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------