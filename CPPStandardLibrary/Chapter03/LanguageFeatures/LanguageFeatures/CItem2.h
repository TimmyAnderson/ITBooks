//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CItem2
{
//-------------------------------------------------------------------------------------------------------
	public:
		int														MValue;

	public:
		inline CItem2(int Value)
			: MValue(Value)
		{
			std::wcout << L"CItem2::CItem2(int Value) CALLED !" << std::endl;
		}

#ifdef _MSC_VER
		inline explicit CItem2(const CItem2& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CItem2::CItem2(const CItem2& Other) CALLED !" << std::endl;
		}
#else
		// !!! V G++ MUSI byt CONSTRUCTOR NON-EXPLICIT.
		inline CItem2(const CItem2& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CItem2::CItem2(const CItem2& Other) CALLED !" << std::endl;
		}
#endif
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------