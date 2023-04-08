//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CItem1
{
//-------------------------------------------------------------------------------------------------------
	public:
		int														MValue;

	public:
		inline CItem1(int Value)
			: MValue(Value)
		{
			std::wcout << L"CItem1::CItem1(int Value) CALLED !" << std::endl;
		}

		inline CItem1(const CItem1& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CItem1::CItem1(const CItem1& Other) CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------