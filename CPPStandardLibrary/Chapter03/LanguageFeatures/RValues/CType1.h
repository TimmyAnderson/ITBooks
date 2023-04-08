//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CType1
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		inline CType1(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CType1(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		inline ~CType1(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			std::wcout << L"DESTRUCTOR ~CType1(void) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------