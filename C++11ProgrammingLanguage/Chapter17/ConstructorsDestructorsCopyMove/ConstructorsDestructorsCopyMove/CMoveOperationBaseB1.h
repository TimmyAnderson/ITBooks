//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CMoveOperationBaseA.h"
#include "CMoveOperationVirtualBaseA.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMoveOperationBaseB1 : public virtual CMoveOperationVirtualBaseA, public CMoveOperationBaseA
{
//-----------------------------------------------------------------------------
	private:
		wchar_t*												MArrayB1;
		std::size_t												MLengthB1;

	public:
		CMoveOperationBaseB1& operator=(CMoveOperationBaseB1&& Value)
		{
			std::wcout << L"MOVE OPERATOR= CMoveOperationBaseB1 CALLED !" << std::endl;

			CMoveOperationVirtualBaseA::operator=(std::move(Value));
			CMoveOperationBaseA::operator=(std::move(Value));

			if (MArrayB1!=nullptr)
			{
				delete[](MArrayB1);
				MArrayB1=nullptr;
			}

			MArrayB1=Value.MArrayB1;
			MLengthB1=Value.MLengthB1;

			Value.MArrayB1=nullptr;
			Value.MLengthB1=0;

			return(*this);
		}

	public:
		wchar_t* GetArrayB1(void) const noexcept
		{
			return(MArrayB1);
		}

		std::size_t GetLengthB1(void) const noexcept
		{
			return(MLengthB1);
		}

	public:
		CMoveOperationBaseB1(const wchar_t* ArrayVA, std::size_t LengthVA, const wchar_t* ArrayA, std::size_t LengthA, const wchar_t* ArrayB1, std::size_t LengthB1)
			: CMoveOperationVirtualBaseA(ArrayVA,LengthVA), CMoveOperationBaseA(ArrayA,LengthA), MArrayB1(new wchar_t[LengthB1]), MLengthB1(LengthB1)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperationBaseB1 CALLED !" << std::endl;

			for(std::size_t Index=0;Index<LengthB1;Index++)
			{
				MArrayB1[Index]=ArrayB1[Index];
			}
		}

		CMoveOperationBaseB1(CMoveOperationBaseB1&& Value)
			: CMoveOperationVirtualBaseA(std::move(Value)), CMoveOperationBaseA(std::move(Value)), MArrayB1(Value.GetArrayB1()), MLengthB1(Value.GetLengthB1())
		{
			std::wcout << L"MOVE CONSTRUCTOR CMoveOperationBaseB1 CALLED !" << std::endl;

			Value.MArrayB1=nullptr;
			Value.MLengthB1=0;
		}

		virtual ~CMoveOperationBaseB1(void)
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperationBaseB1 CALLED !" << std::endl;

			if (MArrayB1!=nullptr)
			{
				delete[](MArrayB1);
				MArrayB1=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------