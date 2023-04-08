//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CType2
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		inline CType2(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CType2(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		// COPY CONSTRUCTOR.
		inline CType2(const CType2& Other)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"COPY CONSTRUCTOR CType2(const CType2& Other) CALLED !" << std::endl;

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}
		}

		inline ~CType2(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			std::wcout << L"DESTRUCTOR ~CType2(void) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------