//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <sstream>
#include "CBaseClass.h"
//-----------------------------------------------------------------------------
class CDerivedClass : public CBaseClass
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MDerivedField1;
		int														MDerivedField2;

	public:
		const std::wstring& GetDerivedField1(void) const noexcept
		{
			return(MDerivedField1);
		}

		int GetDerivedField2(void) const noexcept
		{
			return(MDerivedField2);
		}

		std::wstring PrintDerivedClassFields(void) const
		{
			std::wstringstream									Stream;

			Stream << L"DERIVED FIELD 1 [" << MDerivedField1 << L"] DERIVED FIELD 2 [" << MDerivedField2 << L"] !";

			return(Stream.str());
		}

		std::wstring PrintAllFields(void) const
		{
			std::wstringstream									Stream;

			Stream << PrintBaseClassFields();
			Stream << " ";
			Stream << PrintDerivedClassFields();

			return(Stream.str());
		}

	public:
		CDerivedClass(const std::wstring& BaseField1, int BaseField2, const std::wstring& DerivedField1, int DerivedField2)
			: CBaseClass(BaseField1,BaseField2), MDerivedField1(DerivedField1), MDerivedField2(DerivedField2)
		{
		}

		virtual ~CDerivedClass(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------