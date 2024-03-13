//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CNonExpressionTemplateArray.h"
#include "CDouble.h"
#include "CExpressionTemplateAdd.h"
#include "CExpressionTemplateMultiple.h"
#include "CExpressionTemplateScalar.h"
#include "CExpressionTemplateArray.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestNonExpressionTemplateArray(void)
{
	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CNonExpressionTemplateArray<double>						X(SIZE);
		CNonExpressionTemplateArray<double>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		X=((1.2*X)+(X*Y));

		wcout << L"BINARY OPERATORS <double>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CNonExpressionTemplateArray<double>						X(SIZE);
		CNonExpressionTemplateArray<double>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		CNonExpressionTemplateArray<double>						Temp(X);

		Temp*=Y;
		X*=1.2;
		X+=Temp;

		wcout << L"UNARY OPERATORS <double>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CDouble::ResetCounter();

		CNonExpressionTemplateArray<CDouble>					X(SIZE);
		CNonExpressionTemplateArray<CDouble>					Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		X=((CDouble(1.2)*X)+(X*Y));

		wcout << L"BINARY OPERATORS <CDouble>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"COUNTER [" << CDouble::GetCounter() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CDouble::ResetCounter();

		CNonExpressionTemplateArray<CDouble>					X(SIZE);
		CNonExpressionTemplateArray<CDouble>					Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		CNonExpressionTemplateArray<CDouble>					Temp(X);

		Temp*=Y;
		X*=1.2;
		X+=Temp;

		wcout << L"UNARY OPERATORS <CDouble>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"COUNTER [" << CDouble::GetCounter() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestExpressionTemplateArray(void)
{
	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CExpressionTemplateArray<double>						X(SIZE);
		CExpressionTemplateArray<double>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		X=((1.2*X)+(X*Y));

		wcout << L"EXPRESSION TEMPLATE <double>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CDouble::ResetCounter();

		CExpressionTemplateArray<CDouble>						X(SIZE);
		CExpressionTemplateArray<CDouble>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(Index+20);
		}

		X=((CDouble(1.2)*X)+(X*Y));

		wcout << L"EXPRESSION TEMPLATE <double>:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tRESULT [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"COUNTER [" << CDouble::GetCounter() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CExpressionTemplateArray<double>						X(SIZE);
		CExpressionTemplateArray<double>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(SIZE-Index-1);
		}

		wcout << L"EXPRESSION TEMPLATE <double> BEFORE:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tX [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"EXPRESSION TEMPLATE <double> BEFORE:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tY [" << (Index) << L"] - [" << Y[Index] << L"]." << endl;
		}

		X[Y]=(2.0*X[Y]);

		wcout << L"EXPRESSION TEMPLATE <double> AFTER:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tX [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"EXPRESSION TEMPLATE <double> AFTER:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tY [" << (Index) << L"] - [" << Y[Index] << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		constexpr size_t										SIZE=5;

		CDouble::ResetCounter();

		CExpressionTemplateArray<CDouble>						X(SIZE);
		CExpressionTemplateArray<CDouble>						Y(SIZE);

		for(size_t Index=0;Index<SIZE;Index++)
		{
			X[Index]=(Index+10);
			Y[Index]=(SIZE-Index-1);
		}

		wcout << L"EXPRESSION TEMPLATE <double> BEFORE:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tX [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"EXPRESSION TEMPLATE <double> BEFORE:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tY [" << (Index) << L"] - [" << Y[Index] << L"]." << endl;
		}

		X[Y]=(CDouble(2.0)*X[Y]);

		wcout << L"EXPRESSION TEMPLATE <double> AFTER:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tX [" << (Index) << L"] - [" << X[Index] << L"]." << endl;
		}

		wcout << L"EXPRESSION TEMPLATE <double> AFTER:" << endl;

		for(size_t Index=0;Index<SIZE;Index++)
		{
			wcout << L"\tY [" << (Index) << L"] - [" << Y[Index] << L"]." << endl;
		}

		wcout << L"COUNTER [" << CDouble::GetCounter() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestNonExpressionTemplateArray();
	TestExpressionTemplateArray();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------