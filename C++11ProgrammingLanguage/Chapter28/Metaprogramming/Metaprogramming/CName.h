//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <stdio.h>
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
			wprintf_s(L"COPY OPERATOR= CALLED !\n");

			MFirstName=Other.MFirstName;
			MLastName=Other.MLastName;
			MAge=Other.MAge;

			return(*this);
		}

		inline CName& operator=(CName&& Other)
		{
			wprintf_s(L"MOVE OPERATOR= CALLED !\n");

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
			wprintf_s(L"COPY CONSTRUCTOR CALLED !\n");
		}

		CName(CName&& Other)
			: MFirstName(Other.MFirstName), MLastName(Other.MLastName), MAge(Other.MAge)
		{
			wprintf_s(L"MOVE CONSTRUCTOR CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------