//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDeletedMethods final
{
//-----------------------------------------------------------------------------
	public:
		// !!! DELETED METHOD.
		void operator()(int)=delete;

		void operator()(long)
		{
			std::wcout << "METHOD OPERATOR()(LONG) CALLED !" << std::endl;
		}

		void operator()(double)
		{
			std::wcout << "METHOD OPERATOR()(DOUBLE) CALLED !" << std::endl;
		}


	public:
		void Overload1(int)
		{
			std::wcout << "METHOD Overload1(INT) CALLED !" << std::endl;
		}

		void Overload1(long)
		{
			std::wcout << "METHOD Overload1(LONG) CALLED !" << std::endl;
		}

		void Overload1(double)
		{
			std::wcout << "METHOD Overload1(DOUBLE) CALLED !" << std::endl;
		}

		// !!! DELETED METHOD.
		void Overload2(int)=delete;

		void Overload2(long)
		{
			std::wcout << "METHOD Overload2(LONG) CALLED !" << std::endl;
		}

		void Overload2(double)
		{
			std::wcout << "METHOD Overload2(DOUBLE) CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------