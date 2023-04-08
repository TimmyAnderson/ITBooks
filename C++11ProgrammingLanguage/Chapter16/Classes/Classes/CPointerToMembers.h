//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CPointerToMembers final
{
//-----------------------------------------------------------------------------
	friend void TestPointerToMemberVariables(void);

	private:
		std::wstring											MStringValue1;
		std::wstring											MStringValue2;
		int														MIntValue1;
		int														MIntValue2;

	public:
		int operator+(int Value) const noexcept
		{
			return(MIntValue1+MIntValue2+Value);
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
		CPointerToMembers(const std::wstring& StringValue1, const std::wstring& StringValue2, int IntValue1, int IntValue2)
			: MStringValue1(StringValue1), MStringValue2(StringValue2), MIntValue1(IntValue1), MIntValue2(IntValue2)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------