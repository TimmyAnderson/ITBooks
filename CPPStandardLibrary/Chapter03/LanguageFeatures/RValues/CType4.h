//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CType4
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		inline CType4(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CType4(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		// COPY CONSTRUCTOR.
		inline CType4(const CType4& Other)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"COPY CONSTRUCTOR CType4(const CType4& Other) CALLED !" << std::endl;

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}
		}

		// !!!!! MOVE CONSTRUCTOR by mal mat aplikovany KEYWORD [noexcept].
		inline CType4(CType4&& Other) noexcept
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"!!!!!!!!!! MOVE CONSTRUCTOR CType4(CType4&& Other) CALLED !" << std::endl;

			// !!!!! Ulohou MOVE CONSTRUCTOR je VYBRAT OBSAH VARIABLE [Other], ktora ma byt MOVED cim sa povodna VARIABLE stane NEPOUZITELNA.
			MSize=Other.MSize;
			MData=Other.MData;

			// !!!!! EXTREMNE DOLEZITE je nastavit POVODNU VARIABLE [Other] RESETNUT, kedze jej OBSAH sa presunul do NOVEJ VARIABLE vytvorenej v tomto CONSTRUCTOR.
			Other.MSize=0;
			Other.MData=nullptr;
		}

		inline ~CType4(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			std::wcout << L"DESTRUCTOR ~CType4(void) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------