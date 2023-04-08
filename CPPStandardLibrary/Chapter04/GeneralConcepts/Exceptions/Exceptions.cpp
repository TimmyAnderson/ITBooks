//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <system_error>
#include <future>
#include <fstream>
#include <iostream>
#include "MyDebug.h"
#include "CCustomException.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
exception														Exception;
exception_ptr													ExceptionPtr;
const char*														What=nullptr;
//-----------------------------------------------------------------------------
void TestBadAllocException(void)
{
	PrintLineSeparator();

	/**/
	vector<int*>												Items;

	try
	{
		int														Counter=0;

		while(true)
		{
			int*												Item=new int[1024*1024*1024];

			Items.push_back(Item);

			wcout << L"COUNTER [" << ++Counter << L"] !";
		}
	}
	catch(const bad_alloc& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	for(int* Array : Items)
	{
		delete[](Array);
	}
	/**/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOutOfRangeException(void)
{
	PrintLineSeparator();

	try
	{
		vector<int>												Items;

		int														Item=Items.at(100);

		wcout << L"ITEM [" << Item << L"] !";
	}
	catch(const out_of_range& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErrorCodesAndConditions(void)
{
	PrintLineSeparator();

	try
	{
		fstream													FS;

		FS.exceptions(ifstream::failbit | ifstream::badbit);

		// Neexistujuci FILE.
		FS.open("XX:\\!!!");

		FS.close();
	}
	catch(const system_error& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		const error_code&										ErrorCode=E.code();
		const error_condition&									ErrorCondition=ErrorCode.default_error_condition();
		const error_category&									ErrorCategory=ErrorCode.category();

		wcout << "ErrorCode.value() [" << ErrorCode.value() << L"] !" << endl;
		wcout << "ErrorCode.message() [" << ConvertStringToWideString(ErrorCode.message().c_str()) << L"] !" << endl;
		wcout << "ErrorCondition.value() [" << ErrorCondition.value() << L"] !" << endl;
		wcout << "ErrorCondition.message() [" << ConvertStringToWideString(ErrorCondition.message().c_str()) << L"] !" << endl;
		wcout << "ErrorCategory.name() [" << ConvertStringToWideString(ErrorCategory.name()) << L"] !" << endl;
	}

	PrintLineSeparator();

    try
	{
		// Simulacia EXCEPTION.
        thread().detach();
    }
	catch (const system_error& E)
	{
		const error_code&										ErrorCode=E.code();
		const error_condition&									ErrorCondition=ErrorCode.default_error_condition();
		const error_category&									ErrorCategory=ErrorCode.category();

		wcout << "ErrorCode.value() [" << ErrorCode.value() << L"] !" << endl;
		wcout << "ErrorCode.message() [" << ConvertStringToWideString(ErrorCode.message().c_str()) << L"] !" << endl;
		wcout << "ErrorCondition.value() [" << ErrorCondition.value() << L"] !" << endl;
		wcout << "ErrorCondition.message() [" << ConvertStringToWideString(ErrorCondition.message().c_str()) << L"] !" << endl;
		wcout << "ErrorCategory.name() [" << ConvertStringToWideString(ErrorCategory.name()) << L"] !" << endl;

		// !!! CLASS [errc] je mozne pouzit na identifikaciu EXCEPTIONS.
        if (errc(ErrorCode.value())==errc::invalid_argument)
		{
			wcout << "ERROR [INVALID ARGUMENT] DETECTED !" << endl;
		}
		else
		{
			wcout << "OTHER ERROR [" << ConvertStringToWideString(E.what()) << L"] DETECTED !" << endl;
		}
    }

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SetException(void)
{
	try
	{
		throw(logic_error("Some ERROR !"));
	}
	catch(const exception& E)
	{
		Exception=E;
		ExceptionPtr=current_exception();

		// !!! POINTER na CHAR vrateny FUNCTION what() je validny IBA v CATCH BLOCK.
		What=E.what();

		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
		wcout << "WHAT [" << ConvertStringToWideString(What) << L"] !" << endl;
	}

	wcout << "ERROR [" << ConvertStringToWideString(Exception.what()) << L"] !" << endl;

	// !!!!! Tu uz je POINTER na CHAR NEVALIDNY a PROGRAM skonci vo FATAL ERROR.
	//wcout << L"WHAT [" << ConvertStringToWideString(What) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestExceptionPtrClass(void)
{
	PrintLineSeparator();

	SetException();

	PrintLineSeparator();

	try
	{
		// EXCEPTION vytvorena v INEJ FUNCTION sa znova hodi.
		throw(Exception);
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	try
	{
		// Iny sposob hodenia EXCEPTION.
		rethrow_exception(ExceptionPtr);
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	try
	{
		// Alternativny sposob vytvorenia instancie CLASS [exception_ptr].
		exception_ptr											EP=make_exception_ptr<logic_error>(logic_error("Another ERROR !"));

		rethrow_exception(EP);
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardException(void)
{
	PrintLineSeparator();

	try
	{
		throw(system_error(make_error_code(errc::bad_address),"Some ERROR !"));
	}
	catch(const system_error& E)
	{
		wcout << "EXCEPTION [" << ConvertStringToWideString(E.what()) << L"], CODE [" << E.code().value() << L"] !" << endl;
	}

	try
	{
		throw(logic_error("Some ERROR !"));
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	try
	{
		// !!! VC++ umoznuje hodit EXCEPTION CLASS [bad_exception], avsak C++ a ani G++ to NEUMOZNUJE.
		throw(bad_exception());
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomException(void)
{
	PrintLineSeparator();

	try
	{
		throw(CException("Some ERROR !"));
	}
	catch(const exception& E)
	{
		wcout << L"EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestBadAllocException();
	//TestOutOfRangeException();
	//TestErrorCodesAndConditions();
	//TestExceptionPtrClass();
	//TestStandardException();
	TestCustomException();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------