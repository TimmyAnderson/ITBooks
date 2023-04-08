//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMoveOperationBaseA
{
//-----------------------------------------------------------------------------
	private:
		wchar_t*												MArrayA;
		std::size_t												MLengthA;

	public:
		CMoveOperationBaseA& operator=(CMoveOperationBaseA&& Value)
		{
			std::wcout << L"MOVE OPERATOR= CMoveOperationBaseA CALLED !" << std::endl;

			if (MArrayA!=nullptr)
			{
				delete[](MArrayA);
				MArrayA=nullptr;
			}

			MArrayA=Value.MArrayA;
			MLengthA=Value.MLengthA;

			Value.MArrayA=nullptr;
			Value.MLengthA=0;

			return(*this);
		}

	public:
		wchar_t* GetArrayA(void) const noexcept
		{
			return(MArrayA);
		}

		std::size_t GetLengthA(void) const noexcept
		{
			return(MLengthA);
		}

	public:
		CMoveOperationBaseA(const wchar_t* ArrayA, std::size_t LengthA)
			: MArrayA(new wchar_t[LengthA]), MLengthA(LengthA)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperationBaseA CALLED !" << std::endl;

			for(std::size_t Index=0;Index<LengthA;Index++)
			{
				MArrayA[Index]=ArrayA[Index];
			}
		}

		CMoveOperationBaseA(CMoveOperationBaseA&& Value)
			: MArrayA(Value.GetArrayA()), MLengthA(Value.GetLengthA())
		{
			std::wcout << L"MOVE CONSTRUCTOR CMoveOperationBaseA CALLED !" << std::endl;

			Value.MArrayA=nullptr;
			Value.MLengthA=0;
		}

		virtual ~CMoveOperationBaseA(void)
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperationBaseA CALLED !" << std::endl;

			if (MArrayA!=nullptr)
			{
				delete[](MArrayA);
				MArrayA=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------