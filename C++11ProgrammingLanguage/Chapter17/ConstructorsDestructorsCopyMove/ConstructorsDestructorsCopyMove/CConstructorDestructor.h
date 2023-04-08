//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <utility>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CConstructorDestructor final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CConstructorDestructor& operator=(const CConstructorDestructor& Value)
		{
			MValue=Value.MValue;

			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			return(*this);
		}

		CConstructorDestructor& operator=(CConstructorDestructor&& Value)
		{
			MValue=std::move(Value.MValue);

			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			return(*this);
		}

	public:
		const std::wstring& GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CConstructorDestructor(void)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CConstructorDestructor(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CALLED !" << std::endl;
		}

		CConstructorDestructor(const CConstructorDestructor& Value)
			: MValue(Value.MValue)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CConstructorDestructor(CConstructorDestructor&& Value)
			: MValue(std::move(Value.MValue))
		{

			std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;
		}

		~CConstructorDestructor(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------