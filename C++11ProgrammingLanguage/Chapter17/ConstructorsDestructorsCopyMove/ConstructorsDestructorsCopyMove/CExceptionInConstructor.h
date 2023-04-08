//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <utility>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CExceptionInConstructor final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CExceptionInConstructor(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CALLED !" << std::endl;

			throw(std::wstring(L"SOME EXCEPTION !"));
		}

		~CExceptionInConstructor(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------