//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDelegatingConstructor final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue1;
		int														MValue2;

	public:
		int GetValue1(void) const noexcept
		{
			return(MValue1);
		}

		int GetValue2(void) const noexcept
		{
			return(MValue2);
		}

	public:
		CDelegatingConstructor(void)
			: CDelegatingConstructor(0,0)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CDelegatingConstructor CALLED !" << std::endl;
		}

		CDelegatingConstructor(int Value)
			: CDelegatingConstructor(Value,0)
			// DELEGATING CONSTRUCTOR NEMOZE mat v MEMBER INITIALIZER LIST INE INITIALIZERS okrem volania ineho CONSTRUCTOR aktualnej CLASS.
			//: CDelegatingConstructor(Value1,0), MValue2(0)
		{
			MValue2=Value;

			std::wcout << L"CONSTRUCTOR CDelegatingConstructor with 1 PARAMETER CALLED !" << std::endl;
		}

		CDelegatingConstructor(int Value1, int Value2)
			: MValue1(Value1), MValue2(Value2)
		{
			std::wcout << L"CONSTRUCTOR CDelegatingConstructor with 2 PARAMETERS CALLED !" << std::endl;
		}

		virtual ~CDelegatingConstructor(void)
		{
			std::wcout << L"DESTRUCTOR ~CDelegatingConstructor CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------