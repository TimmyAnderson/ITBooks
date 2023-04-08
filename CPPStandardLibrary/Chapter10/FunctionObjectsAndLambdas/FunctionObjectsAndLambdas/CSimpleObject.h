//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <utility>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CSimpleObject final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		void PrintValue(void) const
		{
			std::wcout << L"VALUE [" << MValue << L"] !" << std::endl;
		}

		void PrintValuePrefixPostfix(std::wstring Prefix, std::wstring Postfix) const
		{
			std::wcout << L"PREFIX [" << Prefix << L"] VALUE [" << MValue << L"] POSTFIX [" << Postfix << L"] !" << std::endl;
		}

		void AddAndPrintValue(int Value)
		{
			MValue+=Value;

			std::wcout << L"VALUE [" << MValue << L"] !" << std::endl;
		}

	public:
		CSimpleObject(void)
		{
		}

		CSimpleObject(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------