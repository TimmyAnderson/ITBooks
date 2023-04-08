//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CCopyAndMoveConstructor
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		inline CCopyAndMoveConstructor(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CCopyAndMoveConstructor(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		// COPY CONSTRUCTOR.
		inline CCopyAndMoveConstructor(const CCopyAndMoveConstructor& Other)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"COPY CONSTRUCTOR CCopyAndMoveConstructor(const CCopyAndMoveConstructor& Other) CALLED !" << std::endl;

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}
		}

		// !!!!! MOVE CONSTRUCTOR by mal mat aplikovany KEYWORD [noexcept].
		inline CCopyAndMoveConstructor(CCopyAndMoveConstructor&& Other) noexcept
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"!!!!!!!!!! MOVE CONSTRUCTOR CCopyAndMoveConstructor(CCopyAndMoveConstructor&& Other) CALLED !" << std::endl;

			// !!!!! Ulohou MOVE CONSTRUCTOR je VYBRAT OBSAH VARIABLE [Other], ktora ma byt MOVED cim sa povodna VARIABLE stane NEPOUZITELNA.
			MSize=Other.MSize;
			MData=Other.MData;

			// !!!!! EXTREMNE DOLEZITE je nastavit POVODNU VARIABLE [Other] RESETNUT, kedze jej OBSAH sa presunul do NOVEJ VARIABLE vytvorenej v tomto CONSTRUCTOR.
			Other.MSize=0;
			Other.MData=nullptr;
		}

		inline ~CCopyAndMoveConstructor(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			std::wcout << L"DESTRUCTOR ~CCopyAndMoveConstructor(void) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------