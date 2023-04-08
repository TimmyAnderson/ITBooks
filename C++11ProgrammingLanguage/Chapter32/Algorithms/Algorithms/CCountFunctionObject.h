//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
//-----------------------------------------------------------------------------
template<typename TType>
class CCountFunctionObject
{
//-----------------------------------------------------------------------------
	private:
		std::size_t												MSum;

	public:
		CCountFunctionObject& operator=(const CCountFunctionObject& Other)
		{
			std::wcout << L"COPY OPERATOR= CCountFunctionObject CALLED !" << std::endl;

			MSum=Other.MSum;

			return(*this);
		}

		CCountFunctionObject& operator=(CCountFunctionObject&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CCountFunctionObject CALLED !" << std::endl;

			MSum=Other.MSum;

			return(*this);
		}

	public:
		void operator()(const TType& Value)
		{
			MSum+=Value;
		}

	public:
		std::size_t GetSum(void) const noexcept
		{
			return(MSum);
		}

	public:
		CCountFunctionObject(void)
			: MSum(0)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CCountFunctionObject CALLED !" << std::endl;
		}

		CCountFunctionObject(const CCountFunctionObject& Other)
			: MSum(Other.MSum)
		{
			std::wcout << L"COPY CONSTRUCTOR CCountFunctionObject CALLED !" << std::endl;
		}

		CCountFunctionObject(CCountFunctionObject&& Other)
			: MSum(Other.MSum)
		{
			std::wcout << L"MOVE CONSTRUCTOR CCountFunctionObject CALLED !" << std::endl;
		}

		~CCountFunctionObject(void)
		{
			std::wcout << L"DESTRUCTOR CCountFunctionObject CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------