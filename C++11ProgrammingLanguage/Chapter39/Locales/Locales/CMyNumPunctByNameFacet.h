//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <locale>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMyNumPunctByNameFacet final : public std::numpunct_byname<wchar_t>
{
//-----------------------------------------------------------------------------
	protected:
		virtual char_type do_decimal_point(void) const override
		{
			return(L'~');
		}

		virtual char_type do_thousands_sep(void) const override
		{
			return(L'_');
		}

		virtual std::string do_grouping(void) const override
		{
			return("\2\3\1");
		}

		virtual string_type do_truename(void) const override
		{
			return(L"TRUE");
		}

		virtual string_type do_falsename(void) const override
		{
			return(L"FALSE");
		}

	public:
		CMyNumPunctByNameFacet(const std::string& Name)
			: numpunct_byname(Name)
		{
			std::wcout << "CONSTRUCTOR CMyNumPunctByNameFacet CALLED !" << std::endl;
		}

		virtual ~CMyNumPunctByNameFacet(void) override
		{
			std::wcout << "DESTRUCTOR CMyNumPunctByNameFacet CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------