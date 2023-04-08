//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <utility>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CNameWithSwap
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;

	public:
		const std::wstring& GetFirstName(void) const
		{
			return(MFirstName);
		}

		const std::wstring& GetLastName(void) const
		{
			return(MLastName);
		}

		int GetAge(void) const
		{
			return(MAge);
		}

		// !!! Implementacia FUNCTION swap().
		void swap(CNameWithSwap& Other)
		{
			std::swap(MFirstName,Other.MFirstName);
			std::swap(MLastName,Other.MLastName);
			std::swap(MAge,Other.MAge);
		}

	public:
		inline CNameWithSwap& operator=(CNameWithSwap& Other)
		{
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MFirstName=Other.MFirstName;
			MLastName=Other.MLastName;
			MAge=Other.MAge;

			return(*this);
		}

		inline CNameWithSwap& operator=(CNameWithSwap&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			MFirstName=Other.MFirstName;
			MLastName=Other.MLastName;
			MAge=Other.MAge;

			return(*this);
		}

	public:
		CNameWithSwap(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
		}

		CNameWithSwap(const CNameWithSwap& Other)
			: MFirstName(Other.MFirstName), MLastName(Other.MLastName), MAge(Other.MAge)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CNameWithSwap(CNameWithSwap&& Other)
			: MFirstName(Other.MFirstName), MLastName(Other.MLastName), MAge(Other.MAge)
		{
			std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Implementacia standardizovanej FUNCTION swap().
void swap(CNameWithSwap& Value1, CNameWithSwap& Value2)
{
	std::wcout << L"CUSTOM FUNCTION swap() CALLED !" << std::endl;

	Value1.swap(Value2);
}
//-------------------------------------------------------------------------------------------------------