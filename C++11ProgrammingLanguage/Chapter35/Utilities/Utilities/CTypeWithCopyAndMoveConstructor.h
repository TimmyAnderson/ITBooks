//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <functional>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CTypeWithCopyAndMoveConstructor
{
//-------------------------------------------------------------------------------------------------------
	private:
		wstring													MValue;

	public:
		const wstring& GetValue(void) noexcept
		{
			return(MValue);
		}

	public:
		CTypeWithCopyAndMoveConstructor(const wstring& Value)
			: MValue(Value)
		{
		}

		CTypeWithCopyAndMoveConstructor(const CTypeWithCopyAndMoveConstructor& Other)
			: MValue(Other.MValue)
		{
			wcout << L"CTypeWithCopyAndMoveConstructor COPY CONSTRUCTOR USED !\n";
		}

		CTypeWithCopyAndMoveConstructor(CTypeWithCopyAndMoveConstructor&& Other)
			: MValue(std::move(Other.MValue))
		{
			wcout << L"CTypeWithCopyAndMoveConstructor MOVE CONSTRUCTOR USED !\n";
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------