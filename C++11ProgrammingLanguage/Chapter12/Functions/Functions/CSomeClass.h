//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
class CSomeClass
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		void Test1(int) const noexcept
		{
		}

		/*
		// !!! COMPILER hodi ERROR, pretoze C++ IGNORUJE CONST SPECIFIERS aplikovane na PARAMETERS ako rozlisujuce kriterium pre FUNCTION OVERLOADING.
		void Test1(const int) const noexcept
		{
		}
		*/

		void Test2(int) const noexcept
		{
		}

		void Test3(const int) const noexcept
		{
		}

		void Test4(short) const noexcept
		{
		}

		void Test5(int&) const noexcept
		{
		}

		// !!!!! METHOD Test5() a METHOD Test6() maju ROZLICNE TYPES, pretoze CONST SPECIFIERS su aplikovane na REFERENCE PARAMETERS a nie na BY-VALUE PARAMETERS.
		void Test6(const int&) const noexcept
		{
		}

		void Test7(int&) const noexcept
		{
		}

		// !!!!! METHOD Test7() a METHOD Test8() maju ROZLICNE TYPES, pretoze CONST SPECIFIERS su aplikovane na POINTER PARAMETERS a nie na BY-VALUE PARAMETERS.
		void Test8(const int&) const noexcept
		{
		}

		// !!!!! METHOD Test8() a METHOD Test9() maju ROZLICNE TYPES, pretoze METHOD Test8() je CONST METHOD, zatial co METHOD Test9() je NON-CONST METHOD.
		void Test9(const int&) noexcept
		{
		}

		// !!!!! METHOD Test8() a METHOD Test10() maju ROZLICNE TYPES, pretoze METHOD Test8() je NOEXCEPT METHOD, zatial co METHOD Test10() moze hadzat EXCEPTIONS.
		void Test10(const int&) const
		{
		}

	public:
		CSomeClass& operator=(const CSomeClass& Other)
		{
			std::wcout << L"CSomeClass COPY OPERATOR= - VALUE [" << MValue << L"] !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CSomeClass& operator=(CSomeClass&& Other)
		{
			std::wcout << L"CSomeClass MOVE OPERATOR= - VALUE [" << MValue << L"] !" << std::endl;

			MValue=std::move(Other.MValue);

			return(*this);
		}

	public:
		CSomeClass(const std::wstring& Value)
			: MValue(Value)
		{
		}

		CSomeClass(const CSomeClass& Other)
			: MValue(Other.MValue)
		{
			std::wcout << L"CSomeClass COPY CONSTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}

		CSomeClass(CSomeClass&& Other)
			: MValue(std::move(Other.MValue))
		{
			std::wcout << L"CSomeClass MOVE CONSTRUCTOR - VALUE [" << MValue << L"] !" << std::endl;
		}

		~CSomeClass(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------