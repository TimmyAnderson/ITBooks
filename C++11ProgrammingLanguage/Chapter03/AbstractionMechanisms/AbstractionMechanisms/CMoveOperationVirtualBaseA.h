//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMoveOperationVirtualBaseA
{
//-----------------------------------------------------------------------------
	private:
		wchar_t*												MArrayVA;
		std::size_t												MLengthVA;

	public:
		CMoveOperationVirtualBaseA& operator=(CMoveOperationVirtualBaseA&& Value)
		{
			std::wcout << L"MOVE OPERATOR= CMoveOperationVirtualBaseA CALLED !" << std::endl;

			if (MArrayVA!=nullptr)
			{
				delete[](MArrayVA);
				MArrayVA=nullptr;
			}

			MArrayVA=Value.MArrayVA;
			MLengthVA=Value.MLengthVA;

			Value.MArrayVA=nullptr;
			Value.MLengthVA=0;

			return(*this);
		}

	public:
		wchar_t* GetArrayVA(void) const noexcept
		{
			return(MArrayVA);
		}

		std::size_t GetLengthVA(void) const noexcept
		{
			return(MLengthVA);
		}

	public:
		CMoveOperationVirtualBaseA(const wchar_t* ArrayVA, std::size_t LengthVA)
			: MArrayVA(new wchar_t[LengthVA]), MLengthVA(LengthVA)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperationVirtualBaseA CALLED !" << std::endl;

			for(std::size_t Index=0;Index<LengthVA;Index++)
			{
				MArrayVA[Index]=ArrayVA[Index];
			}
		}

		CMoveOperationVirtualBaseA(CMoveOperationVirtualBaseA&& Value)
			: MArrayVA(Value.GetArrayVA()), MLengthVA(Value.GetLengthVA())
		{
			std::wcout << L"MOVE CONSTRUCTOR CMoveOperationVirtualBaseA CALLED !" << std::endl;

			Value.MArrayVA=nullptr;
			Value.MLengthVA=0;
		}

		virtual ~CMoveOperationVirtualBaseA(void)
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperationVirtualBaseA CALLED !" << std::endl;

			if (MArrayVA!=nullptr)
			{
				delete[](MArrayVA);
				MArrayVA=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------