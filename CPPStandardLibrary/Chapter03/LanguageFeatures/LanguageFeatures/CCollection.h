//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CCollection
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		void Print(void)
		{
			for(size_t Index=0;Index<MSize;Index++)
			{
				std::wcout << L"MData[" << Index << L"]=[" << MData[Index] << L"] !" << std::endl;
			}
		}

	public:
		inline CCollection(int Value1, int Value2)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CCollection::CCollection(int Value1, int Value2) CALLED !" << std::endl;

			MSize=2;
			MData=new int[MSize];

			MData[0]=Value1;
			MData[1]=Value2;
		}

		inline CCollection(initializer_list<int> Values)
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

		inline CCollection(wstring Dummy, initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CCollection::CCollection(wstring Dummy, initializer_list<int> Values) with Dummy [" << Dummy.c_str() << L"] CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		inline ~CCollection(void)
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