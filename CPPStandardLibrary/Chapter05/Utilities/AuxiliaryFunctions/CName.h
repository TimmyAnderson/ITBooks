//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CName
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

	public:
		inline CName& operator=(CName& Other)
		{
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MFirstName=Other.MFirstName;
			MLastName=Other.MLastName;
			MAge=Other.MAge;

			return(*this);
		}

		inline CName& operator=(CName&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			MFirstName=Other.MFirstName;
			MLastName=Other.MLastName;
			MAge=Other.MAge;

			return(*this);
		}

	public:
		CName(std::wstring FirstName, std::wstring LastName, int Age)
			: MFirstName(FirstName), MLastName(LastName), MAge(Age)
		{
		}

		CName(const CName& Other)
			: MFirstName(Other.MFirstName), MLastName(Other.MLastName), MAge(Other.MAge)
		{
			std::wcout << L"COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CName(CName&& Other)
			: MFirstName(Other.MFirstName), MLastName(Other.MLastName), MAge(Other.MAge)
		{
			std::wcout << L"MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------