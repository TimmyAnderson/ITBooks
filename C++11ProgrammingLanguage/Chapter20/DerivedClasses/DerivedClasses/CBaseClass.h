//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <sstream>
//-----------------------------------------------------------------------------
class CBaseClass
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MBaseField1;
		int														MBaseField2;

	public:
		const std::wstring& GetBaseField1(void) const noexcept
		{
			return(MBaseField1);
		}

		int GetBaseField2(void) const noexcept
		{
			return(MBaseField2);
		}

		std::wstring PrintBaseClassFields(void) const
		{
			std::wstringstream									Stream;

			Stream << L"BASE FIELD 1 [" << MBaseField1 << L"] BASE FIELD 2 [" << MBaseField2 << L"] !";

			return(Stream.str());
		}

	public:
		CBaseClass(const std::wstring& BaseField1, int BaseField2)
			: MBaseField1(BaseField1), MBaseField2(BaseField2)
		{
		}

		virtual ~CBaseClass(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------