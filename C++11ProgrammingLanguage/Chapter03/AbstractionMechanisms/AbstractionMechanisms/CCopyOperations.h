//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CCopyOperations final
{
//-----------------------------------------------------------------------------
	private:
		int*													MArray;
		int														MLength;

	public:
		CCopyOperations& operator=(const CCopyOperations& Value)
		{
			std::wcout << L"COPY OPERATOR= CCopyOperations CALLED !" << std::endl;

			int*												Array=nullptr;

			try
			{
				Array=new int[Value.GetLength()];

				for(int Index=0;Index<Value.GetLength();Index++)
				{
					Array[Index]=Value.GetArray()[Index];
				}

				if (MArray!=nullptr)
				{
					delete[](MArray);
					MArray=nullptr;
				}

				MArray=Array;
				MLength=Value.GetLength();
			}
			catch(...)
			{
				if (Array!=nullptr)
				{
					delete[](Array);
					Array=nullptr;
				}
			}

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
		CCopyOperations(int* Array, int Length)
			: MArray(new int[Length]), MLength(Length)
		{
			std::wcout << L"CONSTRUCTOR CCopyOperations CALLED !" << std::endl;

			for(int Index=0;Index<Length;Index++)
			{
				MArray[Index]=Array[Index];
			}
		}

		CCopyOperations(const CCopyOperations& Value)
			: MArray(new int[Value.GetLength()]), MLength(Value.GetLength())
		{
			std::wcout << L"COPY CONSTRUCTOR CCopyOperations CALLED !" << std::endl;

			for(int Index=0;Index<Value.GetLength();Index++)
			{
				MArray[Index]=Value.GetArray()[Index];
			}
		}

		~CCopyOperations(void)
		{
			std::wcout << L"DESTRUCTOR ~CCopyOperations CALLED !" << std::endl;

			if (MArray!=nullptr)
			{
				delete[](MArray);
				MArray=nullptr;
			}
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------