//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <locale>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMyMoneyPunctByNameFacetFalse final : public std::moneypunct_byname<wchar_t,false>
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

		virtual string_type do_curr_symbol(void) const override
		{
			return(L"XXX");
		}

		virtual string_type do_positive_sign(void) const override
		{
			// !!! 1. CHARACTER sa vypise na mieste kde ma byt POSITIVE SIGN a ostavajuce CHARACTERS sa vypisu za vsetkymi ostatnymi castami MONETARY VALUE.
			return(L"ABCD");
		}

		virtual string_type do_negative_sign(void) const override
		{
			// !!! 1. CHARACTER sa vypise na mieste kde ma byt NEGATIVE SIGN a ostavajuce CHARACTERS sa vypisu za vsetkymi ostatnymi castami MONETARY VALUE.
			return(L"DCBA");
		}

		virtual int do_frac_digits(void) const override
		{
			return(2);
		}

		virtual money_base::pattern do_pos_format(void) const override
		{
			money_base::pattern									Patterns;
			
			// Na 1. POSITION sa NESMIE nachadzat VALUE [money_base::space] a VALUE [money_base::none].
			Patterns.field[0]=money_base::symbol;
			Patterns.field[1]=money_base::value;
			Patterns.field[2]=money_base::space;
			// Na LAST POSITION sa NESMIE nachadzat VALUE [money_base::space].
			Patterns.field[3]=money_base::sign;

			return(Patterns);
		}

		virtual money_base::pattern do_neg_format(void) const override
		{
			money_base::pattern									Patterns;

			// Na 1. POSITION sa NESMIE nachadzat VALUE [money_base::space] a VALUE [money_base::none].
			Patterns.field[0]=money_base::sign;
			Patterns.field[1]=money_base::symbol;
			Patterns.field[2]=money_base::space;
			// Na LAST POSITION sa NESMIE nachadzat VALUE [money_base::space].
			Patterns.field[3]=money_base::value;

			return(Patterns);
		}

	public:
		CMyMoneyPunctByNameFacetFalse(const std::string& Name)
			: moneypunct_byname(Name)
		{
			std::wcout << "CONSTRUCTOR CMyMoneyPunctByNameFacetFalse CALLED !" << std::endl;
		}

		virtual ~CMyMoneyPunctByNameFacetFalse(void) override
		{
			std::wcout << "DESTRUCTOR CMyMoneyPunctByNameFacetFalse CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------