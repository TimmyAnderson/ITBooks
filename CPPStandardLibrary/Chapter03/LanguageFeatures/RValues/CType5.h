//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CType5
{
//-------------------------------------------------------------------------------------------------------
	public:
		size_t													MSize;
		int*													MData;

	public:
		bool IsEmpty(void)
		{
			if (MSize==0)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		inline CType5& operator=(CType5& Other)
		{
			std::wcout << L"COPY OPERATOR= CType5& operator=(CType5& Other) CALLED !" << std::endl;

			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}

			return(*this);
		}

		// !!! MOVE OPERATOR= by mal mat aplikovany KEYWORD [noexcept].
		inline CType5& operator=(CType5&& Other) noexcept
		{
			std::wcout << L"MOVE OPERATOR= CType5& operator=(CType5&& Other) CALLED !" << std::endl;

			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			// !!!!! Ulohou MOVE OPERATOR= je VYBRAT OBSAH VARIABLE [Other], ktora ma byt MOVED cim sa povodna VARIABLE stane NEPOUZITELNA.
			MSize=Other.MSize;
			MData=Other.MData;

			// !!!!! EXTREMNE DOLEZITE je nastavit POVODNU VARIABLE [Other] RESETNUT, kedze jej OBSAH sa presunul do NOVEJ VARIABLE vytvorenej v tomto CONSTRUCTOR.
			Other.MSize=0;
			Other.MData=nullptr;

			return(*this);
		}

	public:
		inline CType5(void)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CType5(void) CALLED !" << std::endl;
		}

		inline CType5(initializer_list<int> Values)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"CONSTRUCTOR CType5(initializer_list<int> Values) CALLED !" << std::endl;

			MSize=Values.size();
			MData=new int[MSize];

			for(initializer_list<int>::iterator Iterator=Values.begin();Iterator!=Values.end();Iterator++)
			{
				MData[Iterator-Values.begin()]=*Iterator;
			}
		}

		// COPY CONSTRUCTOR.
		inline CType5(const CType5& Other)
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"COPY CONSTRUCTOR CType5(const CType5& Other) CALLED !" << std::endl;

			MSize=Other.MSize;
			MData=new int[MSize];

			for(size_t Index=0;Index<MSize;Index++)
			{
				MData[Index]=Other.MData[Index];
			}
		}

		// !!!!! MOVE CONSTRUCTOR by mal mat aplikovany KEYWORD [noexcept].
		inline CType5(CType5&& Other) noexcept
			: MSize(0), MData(nullptr)
		{
			std::wcout << L"!!!!!!!!!! MOVE CONSTRUCTOR CType5(CType5&& Other) CALLED !" << std::endl;

			// !!!!! Ulohou MOVE CONSTRUCTOR je VYBRAT OBSAH VARIABLE [Other], ktora ma byt MOVED cim sa povodna VARIABLE stane NEPOUZITELNA.
			MSize=Other.MSize;
			MData=Other.MData;

			// !!!!! EXTREMNE DOLEZITE je nastavit POVODNU VARIABLE [Other] RESETNUT, kedze jej OBSAH sa presunul do NOVEJ VARIABLE vytvorenej v tomto CONSTRUCTOR.
			Other.MSize=0;
			Other.MData=nullptr;
		}

		inline ~CType5(void)
		{
			if (MData!=nullptr)
			{
				delete[](MData);
				MData=nullptr;
			}

			std::wcout << L"DESTRUCTOR ~CType5(void) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------