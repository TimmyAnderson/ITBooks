//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "NameOperations.h"
//-------------------------------------------------------------------------------------------------------
class CNamePrivate
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;
//-------------------------------------------------------------------------------------------------------
	// !!! Pre FRIEND su PRISTUPOVE PRAVE IGNOROVANE, kedze je to iba ODKAZ na CLASSES, METHODS a OPERATORS definovane mimo tejto CLASS.
	public:
		// !!! MEMBER METHOD inej CLASS je definovana ako FRIEND.
		friend void CNameOperations::MofifyName(CNamePrivate& Name, std::wstring FirstName, std::wstring LastName, int Age);
		// !!! GLOBALNA FUNKCIA je definovana ako FRIEND.
		friend void ClearName(CNamePrivate& Name);
//-------------------------------------------------------------------------------------------------------
	public:
		std::wstring& GetFirstName(void);
		std::wstring& GetLastName(void);
		int& GetAge(void);
//-------------------------------------------------------------------------------------------------------
	public:
		void PrintFullName(void);
		std::wstring GetFullName(void);
//-------------------------------------------------------------------------------------------------------
	public:
		CNamePrivate(void);
		CNamePrivate(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CNamePrivate(void);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
// !!! FRIEND FUNKCIA, moze pristupovat k PRIVATE a PROTECTED MEMBERS.
void ClearName(CNamePrivate& Name);
//-------------------------------------------------------------------------------------------------------