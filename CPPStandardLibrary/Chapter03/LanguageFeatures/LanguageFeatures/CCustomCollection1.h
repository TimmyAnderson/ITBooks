//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CCustomCollection1
{
//-------------------------------------------------------------------------------------------------------
	public:
		vector<int>												MCollection;

	public:
		inline CCustomCollection1(initializer_list<int> Data)
		{
			MCollection=Data;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------