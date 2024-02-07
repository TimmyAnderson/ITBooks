//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include <functional>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "MyFunctionType.h"
#include "CFunctionObjectOperatorBrackets.h"
#include "CFunctionObjectOperatorConversionToPointerToFunction.h"
#include "CFunctionObjectOperatorConversionToReferenceToFunction.h"
#include "CTypeErasureCallbackWrapper.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TFunction, typename TType1, typename TType2, typename TType3>
void CallCallbackFunction(TFunction CallbackFunction, TType1 Value1, TType2 Value2, TType3 Value3)
{
	wcout << L"CALLBACK TYPE [" << GetTypeInfoName<TFunction>() << L"] !" << endl;

	CallbackFunction(Value1,Value2, Value3);
}
//----------------------------------------------------------------------------------------------------------------------
void MyCallbackFunction(const CString& Value1, int Value2, double Value3)
{
	wcout << L"FUNCTION [void MyCallbackFunction(const CString& Value1, int Value2, double Value3))(const CString& Value1, int Value2, double Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCallbackFunctions(void)
{
	PrintLineSeparator();

	{
		// !!! Pouziva sa POINTER na FUNCTION.
		MyFunctionType*											CallbackFunction=&MyCallbackFunction;
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa REFERENCE na FUNCTION.
		MyFunctionType&											CallbackFunction=MyCallbackFunction;
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa LAMBDA FUNCTION.
		auto													CallbackFunction=[](const CString& Value1, int Value2, double Value3){wcout << L"FUNCTION [void MyCallbackFunction(const CString& Value1, int Value2, double Value3))(const CString& Value1, int Value2, double Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;};
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s OPERATOR [OPERATOR()].
		CFunctionObjectOperatorBrackets							CallbackFunction;
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s CONVERTION OPERATOR na POINTER na FUNCTION.
		CFunctionObjectOperatorConversionToPointerToFunction	CallbackFunction;
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s CONVERTION OPERATOR na REFERENCE na FUNCTION.
		CFunctionObjectOperatorConversionToReferenceToFunction	CallbackFunction;
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		function<void (const CString& Value1, int Value2, double Value3)>	CallbackFunction(MyCallbackFunction);
		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCallbackFunctionsViaFunctionPointer(void)
{
	PrintLineSeparator();

	{
		// !!! Pouziva sa POINTER na FUNCTION.
		MyFunctionType*											InternalCallbackFunction=&MyCallbackFunction;

		CTypeErasureCallbackWrapper<MyFunctionType>						CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa REFERENCE na FUNCTION.
		MyFunctionType&											InternalCallbackFunction=MyCallbackFunction;

		CTypeErasureCallbackWrapper<MyFunctionType>				CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa LAMBDA FUNCTION.
		auto													InternalCallbackFunction=[](const CString& Value1, int Value2, double Value3){wcout << L"FUNCTION [void MyCallbackFunction(const CString& Value1, int Value2, double Value3))(const CString& Value1, int Value2, double Value3)] CALLED with VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] !" << endl;};

		CTypeErasureCallbackWrapper<MyFunctionType>				CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s OPERATOR [OPERATOR()].
		CFunctionObjectOperatorBrackets							InternalCallbackFunction;

		CTypeErasureCallbackWrapper<MyFunctionType>				CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s CONVERTION OPERATOR na POINTER na FUNCTION.
		CFunctionObjectOperatorConversionToPointerToFunction	InternalCallbackFunction;

		CTypeErasureCallbackWrapper<MyFunctionType>				CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();

	{
		// !!! Pouziva sa FUNCTION OBJECT s CONVERTION OPERATOR na REFERENCE na FUNCTION.
		CFunctionObjectOperatorConversionToReferenceToFunction	InternalCallbackFunction;

		CTypeErasureCallbackWrapper<MyFunctionType>				CallbackFunction(InternalCallbackFunction);

		CString													Value1=L"Timmy";
		int														Value2=12;
		double													Value3=123.456;

		CallCallbackFunction(CallbackFunction,Value1,Value2,Value3);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestCallbackFunctions();
	TestCallbackFunctionsViaFunctionPointer();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------