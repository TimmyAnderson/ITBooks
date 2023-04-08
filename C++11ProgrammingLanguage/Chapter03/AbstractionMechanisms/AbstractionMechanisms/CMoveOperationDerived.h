//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CMoveOperationBaseB1.h"
#include "CMoveOperationBaseB2.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMoveOperationDerived final : public CMoveOperationBaseB1, public CMoveOperationBaseB2
{
//-----------------------------------------------------------------------------
	private:
		wchar_t*												MArray;
		std::size_t												MLength;

	public:
		CMoveOperationDerived& operator=(CMoveOperationDerived&& Value)
		{
			std::wcout << L"COPY OPERATOR= CMoveOperationDerived CALLED !" << std::endl;

			CMoveOperationBaseB1::operator=(std::move(Value));
			CMoveOperationBaseB2::operator=(std::move(Value));

			if (MArray!=nullptr)
			{
				delete[](MArray);
				MArray=nullptr;
			}

			MArray=Value.MArray;
			MLength=Value.MLength;

			Value.MArray=nullptr;
			Value.MLength=0;

			return(*this);
		}

	private:
		void PrintValue(const std::wstring& Prefix, const wchar_t* Array, std::size_t Length) const
		{
			std::wcout << L" " << Prefix << L" [";

			for(std::size_t Index=0;Index<Length;Index++)
			{
				std::wcout << Array[Index];
			}

			std::wcout << "]";
		}

	public:
		wchar_t* GetArray(void) const noexcept
		{
			return(MArray);
		}

		std::size_t GetLength(void) const noexcept
		{
			return(MLength);
		}

		void Print(const std::wstring& Prefix) const
		{
			std::wcout << Prefix;

			PrintValue(L"ArrayVA",GetArrayVA(),GetLengthVA());
			PrintValue(L"ValueA via B1",static_cast<const CMoveOperationBaseB1*>(this)->GetArrayA(),static_cast<const CMoveOperationBaseB1*>(this)->GetLengthA());
			PrintValue(L"ValueA via B2",static_cast<const CMoveOperationBaseB2*>(this)->GetArrayA(),static_cast<const CMoveOperationBaseB2*>(this)->GetLengthA());
			PrintValue(L"ArrayB1",GetArrayB1(),GetLengthB1());
			PrintValue(L"ArrayB2",GetArrayB2(),GetLengthB2());
			PrintValue(L"Array",GetArray(),GetLength());

			std::wcout << L"] !" << std::endl;
		}

	public:
		CMoveOperationDerived(const wchar_t* ArrayVA, std::size_t LengthVA, const wchar_t* ArrayB1VA, std::size_t LengthB1VA, const wchar_t* ArrayB1A, std::size_t LengthB1A, const wchar_t* ArrayB1, std::size_t LengthB1, const wchar_t* ArrayB2VA, std::size_t LengthB2VA, const wchar_t* ArrayB2A, std::size_t LengthB2A, const wchar_t* ArrayB2, std::size_t LengthB2, const wchar_t* Array, std::size_t Length)
			: CMoveOperationVirtualBaseA(ArrayVA,LengthVA), CMoveOperationBaseB1(ArrayB1VA,LengthB1VA,ArrayB1A,LengthB1A,ArrayB1,LengthB1), CMoveOperationBaseB2(ArrayB2VA,LengthB2VA,ArrayB2A,LengthB2A,ArrayB2,LengthB2), MArray(new wchar_t[Length]), MLength(Length)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperationDerived CALLED !" << std::endl;

			for(std::size_t Index=0;Index<Length;Index++)
			{
				MArray[Index]=Array[Index];
			}
		}

		CMoveOperationDerived(CMoveOperationDerived&& Value)
			: CMoveOperationVirtualBaseA(std::move(Value)), CMoveOperationBaseB1(std::move(Value)), CMoveOperationBaseB2(std::move(Value)), MArray(Value.GetArray()), MLength(Value.GetLength())
		{
			std::wcout << L"COPY CONSTRUCTOR CMoveOperationDerived CALLED !" << std::endl;

			Value.MArray=nullptr;
			Value.MLength=0;
		}

		virtual ~CMoveOperationDerived(void) override
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperationDerived CALLED !" << std::endl;

			if (MArray!=nullptr)
			{
				delete[](MArray);
				MArray=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------