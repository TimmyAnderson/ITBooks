//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <future>
#include <cassert>
#include <iterator>
#include <stack>
#include "MyDebug.h"
#include "CException.h"
#include "CException1.h"
#include "CException2.h"
#include "CException3.h"
#include "CObject1.h"
#include "CObject2.h"
#include "CCustomErrorCategory.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
exception														STLException;
exception_ptr													STLExceptionPtr;
const char*														STLWhat=nullptr;
//-----------------------------------------------------------------------------
CException														MyException;
exception_ptr													MyExceptionPtr;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInitializerList(void)
{
	PrintLineSeparator();

	// Inicializacia VECTOR pomocou CLASS [initializer_list].
	initializer_list<wstring>									InitializerList{L"AAA",L"BBB",L"CCC"};
	vector<wstring>												Strings(InitializerList);

	for(wstring String : Strings)
	{
		wcout << L"STRING [" << String << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForRange(void)
{
	PrintLineSeparator();

	int															Values[]{1,2,3};

	for(int Value : Values)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! FUNCTION begin() je definovana v LIBRARY <iterator>.
	const int*													Iterator1=begin(Values);

	// !!! FUNCTION end() je definovana v LIBRARY <iterator>.
	while(Iterator1!=end(Values))
	{
		wcout << L"VALUE [" << *Iterator1 << L"] !" << endl;
		Iterator1++;
	}

	PrintLineSeparator();

	vector<wstring>												Strings({L"AAA",L"BBB",L"CCC"});

	// !!! FUNCTION begin() je definovana v LIBRARY <iterator>.
	vector<wstring>::iterator									Iterator2=begin(Strings);

	// !!! FUNCTION end() je definovana v LIBRARY <iterator>.
	while(Iterator2!=end(Strings))
	{
		wcout << L"STRING [" << *Iterator2 << L"] !" << endl;
		Iterator2++;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOutOfRangeException(void)
{
	PrintLineSeparator(false);

	try
	{
		vector<int>												Items;

		int														Item=Items.at(100);

		printf_s("ITEM [%d] !",Item);
	}
	catch(const out_of_range& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SetSTLException(void)
{
	try
	{
		throw(logic_error("Some ERROR !"));
	}
	catch(const exception& E)
	{
		STLException=E;
		STLExceptionPtr=current_exception();

		// !!! POINTER na CHAR vrateny FUNCTION what() je validny IBA v CATCH BLOCK.
		STLWhat=E.what();

		printf_s("EXCEPTION [%s] !\n",STLException.what());
		printf_s("WHAT [%s] !\n",STLWhat);
	}

	printf_s("ERROR [%s] !\n",STLException.what());

	// !!!!! Tu uz je POINTER na CHAR NEVALIDNY a PROGRAM skonci vo FATAL ERROR.
	//printf_s("WHAT [%s] !\n",What);
}
//-----------------------------------------------------------------------------
void SetMyException(void)
{
	try
	{
		throw(CException("Some MY ERROR !"));
	}
	catch(const CException& E)
	{
		MyException=E;
		MyExceptionPtr=current_exception();

		printf_s("EXCEPTION [%s] !\n",MyException.GetMessage().c_str());
	}

	printf_s("ERROR [%s] !\n",MyException.GetMessage().c_str());
}
//-----------------------------------------------------------------------------
void TestExceptionPtrClass(void)
{
	PrintLineSeparator(false);

	SetSTLException();

	PrintLineSeparator(false);

	try
	{
		// EXCEPTION vytvorena v INEJ FUNCTION sa znova hodi.
		throw(STLException);
	}
	catch(const exception& E)
	{
		printf_s("THROW EXCEPTION [%s] !\n",E.what());
	}

	try
	{
		// Iny sposob hodenia EXCEPTION.
		rethrow_exception(STLExceptionPtr);
	}
	catch(const exception& E)
	{
		printf_s("rethrow_exception() - EXCEPTION [%s] !\n",E.what());
	}

	// !!! CLASS [exception_ptr] je mozne pouzit aj na CUSTOM EXCEPTION CLASSES, ktore NIE SU DERIVED z CLASS [EXCEPTION].

	PrintLineSeparator(false);

	SetMyException();

	PrintLineSeparator(false);

	try
	{
		// EXCEPTION vytvorena v INEJ FUNCTION sa znova hodi.
		throw(MyException);
	}
	catch(const CException& E)
	{
		printf_s("THROW EXCEPTION [%s] !\n",E.GetMessage().c_str());
	}

	try
	{
		// Iny sposob hodenia EXCEPTION.
		rethrow_exception(MyExceptionPtr);
	}
	catch(const CException& E)
	{
		printf_s("rethrow_exception() - EXCEPTION [%s] !\n",E.GetMessage().c_str());
	}

	PrintLineSeparator(false);

	try
	{
		// Alternativny sposob vytvorenia instancie CLASS [exception_ptr].
		exception_ptr											EP=make_exception_ptr<logic_error>(logic_error("Another ERROR !"));

		rethrow_exception(EP);
	}
	catch(const exception& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThrowNestedException(void)
{
	try
	{
		try
		{
			throw(CException1("EXCEPTION 1 !"));
		}
		catch(...)
		{
			// !!! CURRENT EXCEPTION je WRAPPED do NESTED EXCEPTION 'CException2'.
			// !!!!! Hodena EXCEPTION je DERIVED z CException2 a ZAROVEN DERIVED z CLASS [nested_exception].
			throw_with_nested<CException2>(CException2("EXCEPTION 2 !"));
		}
	}
	catch(...)
	{
		// !!! CURRENT EXCEPTION je WRAPPED do NESTED EXCEPTION 'CException3'.
		// !!!!! Hodena EXCEPTION je DERIVED z CException3 a ZAROVEN DERIVED z CLASS [nested_exception].
		throw_with_nested<CException3>(CException3("EXCEPTION 3 !"));
	}
}
//-----------------------------------------------------------------------------
void PrintNestedException(const CException& E)
{
	// Vypise sa obsah EXCEPTION.
	cout << "EXCEPTION [" << E.GetMessage().c_str() << "] !" << endl;

	try
	{
		// !!!!! Ak je EXCEPTION v 'E' zaroven DERIVED z CLASS [nested_exception], tak sa spravi RETHROW tejto EXCEPTION.
		rethrow_if_nested(E);

		// !!! Sem sa PROGRAM dostane VTEDY, ak OBJECT 'E' NEBOL DERIVED z CLASS [nested_exception] co v tomto priklade je pri OBJECT 'CException1', pretoze tato EXCEPTION SAMA o SEBE NIE JE DERIVED z CLASS [nested_exception]. Az OBALOVACIE EXCEPTIONS 'CException2' a 'CException3', ktorych instancie boli vytvorene cez FUNCTION throw_with_nested<TException> su OBJECTS, ktore su DERIVED z CLASS [nested_exception] a ZAROVEN su DERIVED z TYPE 'TException'.
		cout << "MESSAGE [" << E.GetMessage() << "] !" << endl;
	}
	catch(const CException& NE)
	{
		// !!!!! Pokial bola v 'E' zabalena CLASS [nested_exception], tak sa CURRENT FUNCTION ZNOVA REKURZIVNE zavola a to pre pripad, ze by EXCEPTION zabalovala dalsiu NESTED EXCEPTION.
		PrintNestedException(NE);
	}
}
//-----------------------------------------------------------------------------
void TestNestedExceptions(void)
{
	PrintLineSeparator(false);

	try
	{
		// !!!!! Hodena EXCEPTION je DERIVED z CUSTOM EXCEPTION a ZAROVEN DERIVED z CLASS [nested_exception].
		ThrowNestedException();
	}
	catch(const CException &E)
	{
		PrintNestedException(E);
	}

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyTerminateHandler(void)
{
	cout << "MY TERMINATION HANDLER !\n";
}
//-----------------------------------------------------------------------------
// !!!!! TEST skonci vykonanim PROGRAM TERMINATE.
void TestTerminate1(void)
{
	PrintLineSeparator(false);

	set_terminate(MyTerminateHandler);

	// !!! Zavola sa TERMINATE HANDLER.
	terminate();

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TEST skonci vykonanim PROGRAM TERMINATE.
void TestTerminate2(void)
{
	PrintLineSeparator(false);

	set_terminate(MyTerminateHandler);

	// !!! Zavola sa TERMINATE HANDLER, ale NIE z DEBUGGER, ale az pri spusteni .EXE FILE.
	throw(CException("My EXCEPTION !"));

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void UncaughtExceptions1(void)
{
	CObject1													Object("OBJECT 1");

	throw(CException("My EXCEPTION !"));

	cout << "MESSAGE [" << Object.GetMessage() << "] !\n";
}
//-----------------------------------------------------------------------------
void UncaughtExceptions2(void)
{
	CObject2													Object("OBJECT 2");

	UncaughtExceptions1();

	cout << "MESSAGE [" << Object.GetMessage() << "] !\n";
}
//-----------------------------------------------------------------------------
void TestUncaughtExceptions(void)
{
	PrintLineSeparator(false);

	try
	{
		UncaughtExceptions2();
	}
	catch(...)
	{
#ifdef _MSC_VER
		// Tu uz EXCEPTION je CAUGHT.
		bool													IsUncaughtException=uncaught_exception();
		int														NumberOfUncaughtExceptions=uncaught_exceptions();

		cout << "MAIN - IsUncaughtException [" << IsUncaughtException << "], NumberOfUncaughtExceptions [" << NumberOfUncaughtExceptions << "] !\n";
#else
		// Tu uz EXCEPTION je CAUGHT.
		bool													IsUncaughtException=uncaught_exception();

		cout << "MAIN - IsUncaughtException [" << IsUncaughtException << "] !\n";
#endif
	}

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssertion(void)
{
	PrintLineSeparator();

	// Kedze CONDITION je TRUE, tak sa NIC NEVYPISE a COMPILER NEHODI ERROR.
	static_assert(true,"Some TEXT 1 !");

	// !!! Kedze CONDITION je FALSE, tak sa NEVYPISE ERROR a COMPILATION skonci hodenim ERROR.
	//static_assert(false,"Some TEXT 2 !");

	// Neurobi NIC, pretoze CONDITION je TRUE.
	assert(true);

	// !!! Kedze CONDITION je TRUE, tak sa v RUNTIME vypise ERROR a PROGRAM je ABORTED.
	//assert(false);

	wcout << L"TESTS PASSED !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErrorCodesAndConditions(void)
{
	PrintLineSeparator(false);

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
		printf_s("EXCEPTION [%s] !\n",E.what());

		const error_code&										ErrorCode=E.code();
		const error_condition&									ErrorCondition=ErrorCode.default_error_condition();
		const error_category&									ErrorCategory=ErrorCode.category();

		printf_s("ErrorCode.value() [%d] !\n",ErrorCode.value());
		printf_s("ErrorCode.message() [%s] !\n",ErrorCode.message().c_str());
		printf_s("ErrorCondition.value() [%d] !\n",ErrorCondition.value());
		printf_s("ErrorCondition.message() [%s] !\n",ErrorCondition.message().c_str());
		printf_s("ErrorCategory.name() [%s] !\n",ErrorCategory.name());
	}
	// !!! G++ ma ERROR, pretoze EXCEPTION [ios_base::failure] NIE JE DERIVED z CLASS [system_error], aj ked podla specifikacie by mala byt.
	catch(const exception& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator(false);

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

		printf_s("ErrorCode.value() [%d] !\n",ErrorCode.value());
		printf_s("ErrorCode.message() [%s] !\n",ErrorCode.message().c_str());
		printf_s("ErrorCondition.value() [%d] !\n",ErrorCondition.value());
		printf_s("ErrorCondition.message() [%s] !\n",ErrorCondition.message().c_str());
		printf_s("ErrorCategory.name() [%s] !\n",ErrorCategory.name());

		// !!! CLASS [errc] je mozne pouzit na identifikaciu EXCEPTIONS.
        if (errc(ErrorCode.value())==errc::invalid_argument)
		{
			printf_s("ERROR [INVALID ARGUMENT] DETECTED !\n");
		}
		else
		{
			printf_s("OTHER ERROR [%s] DETECTED !\n",E.what());
		}
    }

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCreationErrorCodesAndConditions(void)
{
	PrintLineSeparator(false);

	try
	{
		// !!! Vytvorenie instancie CLASS [error_code] pomocou FUNCTION make_error_code().
		throw(system_error(make_error_code(errc::bad_address),"Some ERROR !"));
	}
	catch(const system_error& E)
	{
		printf_s("EXCEPTION [%s], CODE [%d], CODE MESSAGE [%s], CATEGORY MESSAGE [%s] !\n",E.what(),E.code().value(),E.code().message().c_str(),E.code().category().name());
	}

	PrintLineSeparator(false);

	error_code													ErrorCode1=make_error_code(errc::bad_address);
	
	cout << "ERROR CODE [" << ErrorCode1.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode1.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode1.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode1.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode1.default_error_condition().message() << "] !\n";

#ifdef _MSC_VER
	PrintLineSeparator(false);

	error_code													ErrorCode2=make_error_code(io_errc::stream);

	cout << "ERROR CODE [" << ErrorCode2.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode2.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode2.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode2.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode2.default_error_condition().message() << "] !\n";
#endif

	PrintLineSeparator(false);

	error_code													ErrorCode3=make_error_code(future_errc::broken_promise);

	cout << "ERROR CODE [" << ErrorCode3.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode3.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode3.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode3.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode3.default_error_condition().message() << "] !\n";

	PrintLineSeparator(false);

	const error_category&										Category=future_category();
	error_code													ErrorCode4(987,Category);

	cout << "ERROR CODE [" << ErrorCode4.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode4.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode4.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode4.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode4.default_error_condition().message() << "] !\n";

	PrintLineSeparator(false);

	error_condition												ErrorCondition1=make_error_condition(errc::cross_device_link);

	cout << "ERROR CONDITION [" << ErrorCondition1.value() << "] !\n";
	cout << "ERROR CONDITION MESSAGE [" << ErrorCondition1.message() << "] !\n";
	cout << "ERROR CONDITION CATEGORY NAME [" << ErrorCondition1.category().name() << "] !\n";

#ifdef _MSC_VER
	PrintLineSeparator(false);

	error_condition												ErrorCondition2=make_error_condition(io_errc::stream);

	cout << "ERROR CONDITION [" << ErrorCondition2.value() << "] !\n";
	cout << "ERROR CONDITION MESSAGE [" << ErrorCondition2.message() << "] !\n";
	cout << "ERROR CONDITION CATEGORY NAME [" << ErrorCondition2.category().name() << "] !\n";
#endif

	PrintLineSeparator(false);

	error_condition												ErrorCondition3=make_error_condition(future_errc::broken_promise);

	cout << "ERROR CONDITION [" << ErrorCondition3.value() << "] !\n";
	cout << "ERROR CONDITION MESSAGE [" << ErrorCondition3.message() << "] !\n";
	cout << "ERROR CONDITION CATEGORY NAME [" << ErrorCondition3.category().name() << "] !\n";

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErrorCategory(void)
{
	PrintLineSeparator(false);

	// !!! Podla ERROR CATEGORY sa interpretuje hodnota ERROR CODE.
	error_code													ErrorCode1(1,generic_category());

	cout << "ERROR CODE [" << ErrorCode1.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode1.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode1.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode1.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode1.default_error_condition().message() << "] !\n";

	PrintLineSeparator(false);

	// !!! Podla ERROR CATEGORY sa interpretuje hodnota ERROR CODE.
	error_code													ErrorCode2(1,future_category());

	cout << "ERROR CODE [" << ErrorCode2.value() << "] !\n";
	cout << "ERROR CODE MESSAGE [" << ErrorCode2.message() << "] !\n";
	cout << "ERROR CODE CATEGORY NAME [" << ErrorCode2.category().name() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode2.default_error_condition().value() << "] !\n";
	cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode2.default_error_condition().message() << "] !\n";

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomCategory(void)
{
	PrintLineSeparator(false);

	try
	{
		throw(system_error(make_error_code(ECustomErrorCode::E_ERROR_CODE_B)));
	}
	catch(const system_error& E)
	{
		const error_code&										ErrorCode=E.code();

		cout << "ERROR CODE [" << ErrorCode.value() << "] !\n";
		cout << "ERROR CODE MESSAGE [" << ErrorCode.message() << "] !\n";
		cout << "ERROR CODE CATEGORY NAME [" << ErrorCode.category().name() << "] !\n";
		cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode.default_error_condition().value() << "] !\n";
		cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode.default_error_condition().message() << "] !\n";
	}

	PrintLineSeparator(false);

	try
	{
		throw(system_error(make_error_code(ECustomErrorCode::E_ERROR_CODE_PLATFORM_DEPENDENT)));
	}
	catch(const system_error& E)
	{
		const error_code&										ErrorCode=E.code();

		cout << "ERROR CODE [" << ErrorCode.value() << "] !\n";
		cout << "ERROR CODE MESSAGE [" << ErrorCode.message() << "] !\n";
		cout << "ERROR CODE CATEGORY NAME [" << ErrorCode.category().name() << "] !\n";
		cout << "ERROR CODE DEFAULT ERROR CONDITION VALUE [" << ErrorCode.default_error_condition().value() << "] !\n";
		cout << "ERROR CODE DEFAULT ERROR CONDITION MESSAGE [" << ErrorCode.default_error_condition().message() << "] !\n";
	}

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestInitializerList();
	TestForRange();
	//TestOutOfRangeException();
	//TestExceptionPtrClass();
	//TestNestedExceptions();
	//TestTerminate1();
	//TestTerminate2();
	//TestUncaughtExceptions();
	//TestAssertion();
	//TestErrorCodesAndConditions();
	//TestCreationErrorCodesAndConditions();
	//TestErrorCategory();
	//TestCustomCategory();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------