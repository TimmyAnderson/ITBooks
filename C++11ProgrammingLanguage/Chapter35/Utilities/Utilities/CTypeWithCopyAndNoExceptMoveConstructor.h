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
class CTypeWithCopyAndNoExceptMoveConstructor
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
		CTypeWithCopyAndNoExceptMoveConstructor(const wstring& Value)
			: MValue(Value)
		{
		}

		CTypeWithCopyAndNoExceptMoveConstructor(const CTypeWithCopyAndNoExceptMoveConstructor& Other)
			: MValue(Other.MValue)
		{
			wcout << L"CTypeWithCopyAndNoExceptMoveConstructor COPY CONSTRUCTOR USED !\n";
		}

		CTypeWithCopyAndNoExceptMoveConstructor(CTypeWithCopyAndNoExceptMoveConstructor&& Other) noexcept
			: MValue(std::move(Other.MValue))
		{
			wcout << L"CTypeWithCopyAndNoExceptMoveConstructor MOVE CONSTRUCTOR USED !\n";
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------