//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CPointerToMemberOperators final
{
//-----------------------------------------------------------------------------
	friend void TestPointerToMemberOperators(void);

	private:
		std::wstring											MStringValue1;
		std::wstring											MStringValue2;
		int														MIntValue1;
		int														MIntValue2;

	public:
		// !!!!! OPERATOR->* ak je OVERLOADED tak NEMA SPECIALNY VYZNAM a je to OBYCAJNY OPERATOR podobne ako napriklad OPERATOR+.
		double operator->*(double Value)
		{
			std::wcout << "MEMBER OPERATOR->* CALLED !" << std::endl;

			return(Value+MIntValue1+MIntValue2);
		}

	public:
		const std::wstring& GetStringValue1(void) const noexcept
		{
			return(MStringValue1);
		}

		const std::wstring& GetStringValue2(void) const noexcept
		{
			return(MStringValue2);
		}

		int GetIntValue1(void) const noexcept
		{
			return(MIntValue1);
		}

		int GetIntValue2(void) const noexcept
		{
			return(MIntValue2);
		}

	public:
		CPointerToMemberOperators(const std::wstring& StringValue1, const std::wstring& StringValue2, int IntValue1, int IntValue2)
			: MStringValue1(StringValue1), MStringValue2(StringValue2), MIntValue1(IntValue1), MIntValue2(IntValue2)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! OPERATOR->* ak je OVERLOADED tak NEMA SPECIALNY VYZNAM a je to OBYCAJNY OPERATOR podobne ako napriklad OPERATOR+.
double operator->*(double Left, const CPointerToMemberOperators& Right)
{
	std::wcout << "NON-MEMBER OPERATOR->* CALLED !" << std::endl;

	return(Left+Right.GetIntValue1()+Right.GetIntValue2());
}
//-----------------------------------------------------------------------------