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
class CMoveOperationBaseB2 : public virtual CMoveOperationVirtualBaseA, public CMoveOperationBaseA
{
//-----------------------------------------------------------------------------
	private:
		wchar_t*												MArrayB2;
		std::size_t												MLengthB2;

	public:
		CMoveOperationBaseB2& operator=(CMoveOperationBaseB2&& Value)
		{
			std::wcout << L"MOVE OPERATOR= CMoveOperationBaseB2 CALLED !" << std::endl;

			CMoveOperationVirtualBaseA::operator=(std::move(Value));
			CMoveOperationBaseA::operator=(std::move(Value));

			if (MArrayB2!=nullptr)
			{
				delete[](MArrayB2);
				MArrayB2=nullptr;
			}

			MArrayB2=Value.MArrayB2;
			MLengthB2=Value.MLengthB2;

			Value.MArrayB2=nullptr;
			Value.MLengthB2=0;

			return(*this);
		}

	public:
		wchar_t* GetArrayB2(void) const noexcept
		{
			return(MArrayB2);
		}

		std::size_t GetLengthB2(void) const noexcept
		{
			return(MLengthB2);
		}

	public:
		CMoveOperationBaseB2(const wchar_t* ArrayVA, std::size_t LengthVA, const wchar_t* ArrayA, std::size_t LengthA, const wchar_t* ArrayB2, std::size_t LengthB2)
			: CMoveOperationVirtualBaseA(ArrayVA,LengthVA), CMoveOperationBaseA(ArrayA,LengthA), MArrayB2(new wchar_t[LengthB2]), MLengthB2(LengthB2)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperationBaseB2 CALLED !" << std::endl;

			for(std::size_t Index=0;Index<LengthB2;Index++)
			{
				MArrayB2[Index]=ArrayB2[Index];
			}
		}

		CMoveOperationBaseB2(CMoveOperationBaseB2&& Value)
			: CMoveOperationVirtualBaseA(std::move(Value)), CMoveOperationBaseA(std::move(Value)), MArrayB2(Value.GetArrayB2()), MLengthB2(Value.GetLengthB2())
		{
			std::wcout << L"MOVE CONSTRUCTOR CMoveOperationBaseB2 CALLED !" << std::endl;

			Value.MArrayB2=nullptr;
			Value.MLengthB2=0;
		}

		virtual ~CMoveOperationBaseB2(void)
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperationBaseB2 CALLED !" << std::endl;

			if (MArrayB2!=nullptr)
			{
				delete[](MArrayB2);
				MArrayB2=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------