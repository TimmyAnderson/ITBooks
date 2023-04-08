//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMoveOperations final
{
//-----------------------------------------------------------------------------
	private:
		int*													MArray;
		int														MLength;

	public:
		CMoveOperations& operator=(CMoveOperations&& Value)
		{
			std::wcout << L"MOVE OPERATOR= CMoveOperations CALLED !" << std::endl;

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

	public:
		int* GetArray(void) const noexcept
		{
			return(MArray);
		}

		int GetLength(void) const noexcept
		{
			return(MLength);
		}

	public:
		void Print(const std::wstring& Prefix) const noexcept
		{
			std::wcout << Prefix << L" [";

			for(int Index=0;Index<MLength;Index++)
			{
				if (Index>0)
				{
					std::wcout << L",";
				}

				std::wcout << MArray[Index];
			}

			std::wcout << "] !" << std::endl;
		}

	public:
		CMoveOperations(int* Array, int Length)
			: MArray(new int[Length]), MLength(Length)
		{
			std::wcout << L"CONSTRUCTOR CMoveOperations CALLED !" << std::endl;

			for(int Index=0;Index<Length;Index++)
			{
				MArray[Index]=Array[Index];
			}
		}

		CMoveOperations(CMoveOperations&& Value)
			: MArray(Value.GetArray()), MLength(Value.GetLength())
		{
			std::wcout << L"MOVE CONSTRUCTOR CMoveOperations CALLED !" << std::endl;

			Value.MArray=nullptr;
			Value.MLength=0;
		}

		~CMoveOperations(void)
		{
			std::wcout << L"DESTRUCTOR ~CMoveOperations CALLED !" << std::endl;

			if (MArray!=nullptr)
			{
				delete[](MArray);
				MArray=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------