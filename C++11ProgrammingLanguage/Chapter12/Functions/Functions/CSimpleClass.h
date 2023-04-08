//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
class CSimpleClass
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept
		{
			return(MValue);
		}

		void SetValue(const std::wstring& Value)
		{
			MValue=Value;
		}

	public:
		CSimpleClass& operator=(const CSimpleClass& Other)
		{
			std::wcout << L"CSimpleClass COPY OPERATOR= - VALUE [" << MValue << L"] !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CSimpleClass& operator=(CSimpleClass&& Other)
		{
			std::wcout << L"CSimpleClass MOVE OPERATOR= - VALUE [" << MValue << L"] !" << std::endl;

			MValue=std::move(Other.MValue);

			return(*this);
		}

	public:
		CSimpleClass(const std::wstring& Value)
			: MValue(Value)
		{
			std::wcout << L"CSimpleClass CONSTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}

		CSimpleClass(const CSimpleClass& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CSimpleClass COPY CONSTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}

		CSimpleClass(CSimpleClass&& Other)
			: MValue(std::move(Other.MValue))
		{
			std::wcout << L"CSimpleClass MOVE CONSTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}

		~CSimpleClass(void)
		{
			std::wcout << L"CSimpleClass DESTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------