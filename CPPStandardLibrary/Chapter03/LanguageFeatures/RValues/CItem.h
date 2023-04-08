//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CItem
{
//-------------------------------------------------------------------------------------------------------
	public:
		static int												MCounter;

	public:
		size_t													MSize;
		int*													MData;

	public:
		inline CItem(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		// COPY CONSTRUCTOR.
		inline CItem(const CItem& Other)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"COPY CONSTRUCTOR CItem(const CItem& Other) CALLED !" << std::endl;

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}
		}

		// !!!!! MOVE CONSTRUCTOR by mal mat aplikovany KEYWORD [noexcept].
		inline CItem(CItem&& Other) noexcept
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"!!!!!!!!!! MOVE CONSTRUCTOR CItem(CItem&& Other) CALLED !" << std::endl;

			MCounter++;

			// !!!!! Ulohou MOVE CONSTRUCTOR je VYBRAT OBSAH VARIABLE [Other], ktora ma byt MOVED cim sa povodna VARIABLE stane NEPOUZITELNA.
			MSize=Other.MSize;
			MData=Other.MData;

			// !!!!! EXTREMNE DOLEZITE je nastavit POVODNU VARIABLE [Other] RESETNUT, kedze jej OBSAH sa presunul do NOVEJ VARIABLE vytvorenej v tomto CONSTRUCTOR.
			Other.MSize=0;
			Other.MData=nullptr;
		}

		inline ~CItem(void)
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