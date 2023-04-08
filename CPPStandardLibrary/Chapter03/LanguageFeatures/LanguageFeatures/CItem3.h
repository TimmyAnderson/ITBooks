//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CItem3
{
//-------------------------------------------------------------------------------------------------------
	public:
		int														MValue;

	public:
		// COPY OPERATOR.
		inline CItem3& operator=(const CItem3& Other)
		{
			std::wcout << L"CItem3& operator=(const CItem3& Other) CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

	public:
		inline CItem3(int Value)
			: MValue(Value)
		{
			std::wcout << L"CItem3::CItem3(int Value) CALLED !" << std::endl;
		}

#ifdef _MSC_VER
		inline explicit CItem3(const CItem3& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CItem3::CItem3(const CItem3& Other) CALLED !" << std::endl;
		}
#else
		inline CItem3(const CItem3& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CItem3::CItem3(const CItem3& Other) CALLED !" << std::endl;
		}
#endif
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------