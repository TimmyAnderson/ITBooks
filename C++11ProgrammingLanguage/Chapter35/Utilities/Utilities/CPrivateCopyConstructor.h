//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CPrivateCopyConstructor
{
//-----------------------------------------------------------------------------
	private:
		int														Field1;
		std::wstring											Field2;

	public:
		// !!! Aj ked sa TYPE TRAIT [is_copy_constructible<T>] vola z METHOD, tak vrati FALSE, pretoze TYPE TRAIT [is_copy_constructible<T>] ako aj mnoho inych NEROBI ACCESS CHECK a kontrolu ci TYPE ma COPY CONSTRUCTOR VZDY robi ako keby bol volany z NON-MEMBER FUNCTION.
		bool IsCopyConstructible(void)
		{
			return(std::is_copy_constructible<CPrivateCopyConstructor>::value);
		}

	public:
		CPrivateCopyConstructor(void)
		{
		}

	private:
		// !!! COPY CONSTRUCTOR je UMYSELNE PRIVATE.
		CPrivateCopyConstructor(const CPrivateCopyConstructor&)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------