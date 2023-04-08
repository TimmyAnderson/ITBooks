//-------------------------------------------------------------------------------------------------------
#include <utility>
#include <string>
#include "MyDebug.h"
#include "CThrowClass.h"
#include "CException.h"
//-------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4297)
#endif
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void ExceptionFunction(bool ThrowException)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION ExceptionFunction() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION ExceptionFunction() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestException(void)
{
	PrintLineSeparator();

	try
	{
		ExceptionFunction(false);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		ExceptionFunction(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void NoExceptionFunction(bool ThrowException) noexcept
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptionFunction() will THROW EXCEPTION !" << endl;

		// !!! Ak je z FUNCTION, ktora je deklarovana ako [noexcept] hodena EXCEPTION, dojde k PADU PROGRAMU.
		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptionFunction() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! Sposobi PAD PROGRAMU.
void TestNoException(void)
{
	PrintLineSeparator();

	try
	{
		NoExceptionFunction(false);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		NoExceptionFunction(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void InnerNoExceptionFunction(void)
{
	throw(CException(L"This is a very SERIOUS ERROR !"));
}
//-------------------------------------------------------------------------------------------------------
void OuterNoExceptionFunction(bool ThrowException) noexcept
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION ExceptionFunction() will THROW EXCEPTION !" << endl;

		InnerNoExceptionFunction();
	}
	else
	{
		wcout << L"FUNCTION ExceptionFunction() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestInnerException(void)
{
	PrintLineSeparator();

	try
	{
		OuterNoExceptionFunction(false);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		OuterNoExceptionFunction(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION NESMIE hodit EXCEPTION za ZIADNYCH OKOLNOSTI.
void NoExceptCondition1(bool ThrowException) noexcept(true)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition1() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition1() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions1(void)
{
	PrintLineSeparator();

	NoExceptCondition1(false);

	PrintLineSeparator();

	try
	{
		// !!! Sposobi PAD PROGRAMU, pretoze FUNCTION hodi EXCEPTION, aj ked by nemala za ziadnych okolnosti.
		NoExceptCondition1(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION moze hodit EXCEPTION za lubovolnych OKOLNOSTI.
void NoExceptCondition2(bool ThrowException) noexcept(false)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition2() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition2() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions2(void)
{
	PrintLineSeparator();

	NoExceptCondition2(false);

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION sa KOREKTNE zavola a EXCEPTION bude zachytena, pretoze FUNCTION moze hodit EXCEPTION za LUBOVOLNYCH podmienok.
		NoExceptCondition2(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/*
// !!! COMPILER hodi ERROR, pretoze v CONDITION NEMOZE byt VARIABLE, ktora je MIMO FUNCTION BODY.
void NoExceptCondition3(bool ThrowException) noexcept(ThrowException==false)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition3() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition3() will NOT THROW EXCEPTION !" << endl;
	}
}
*/
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions3(void)
{
	PrintLineSeparator();

/*
	NoExceptCondition3(false);

	PrintLineSeparator();

	try
	{
		NoExceptCondition3(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << << L"] was DETECTED !" << endl;,Exception.GetMessage().c_str());
	}
*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/*
bool															NonConstantGlobalVariable=true;
//-------------------------------------------------------------------------------------------------------
// !!! COMPILER hodi ERROR, pretoze v CONDITION NEMOZE odkaz na NON-CONSTAT VARIABLE.
void NoExceptCondition4(bool ThrowException) noexcept(NonConstantGlobalVariable==false)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition4() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition4() will NOT THROW EXCEPTION !" << endl;
	}
}
*/
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions4(void)
{
	PrintLineSeparator();

/*
	NoExceptCondition4(false);

	PrintLineSeparator();

	try
	{
		NoExceptCondition4(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << << L"] was DETECTED !" << endl;,Exception.GetMessage().c_str());
	}
*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
const bool														ConstantGlobalVariable=true;
//-------------------------------------------------------------------------------------------------------
// !!! COMPILER CONDITION AKCEPTUJE, pretoze referovana VARIABLE je CONSTANT.
void NoExceptCondition5(bool ThrowException) noexcept(ConstantGlobalVariable==false)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition5() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition5() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions5(void)
{
	PrintLineSeparator();

	NoExceptCondition5(false);

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION sa KOREKTNE zavola a EXCEPTION bude zachytena, pretoze FUNCTION moze hodit EXCEPTION za LUBOVOLNYCH podmienok.
		NoExceptCondition5(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void NoExceptFunction1() noexcept
{
	wcout << L"FUNCTION NoExceptFunction1() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze NoExceptFunction1() NIE JE OZNACENA pomocou KEYWORD [constexpr].
void NoExceptCondition6(bool ThrowException) noexcept(NoExceptFunction1())
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition6() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition6() will NOT THROW EXCEPTION !" << endl;
	}
}
*/
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions6(void)
{
	PrintLineSeparator();

/*
	NoExceptCondition6(false);

	PrintLineSeparator();

	try
	{
		NoExceptCondition6(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << << L"] was DETECTED !" << endl;,Exception.GetMessage().c_str());
	}
*/

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTIONS oznacene KEYWORD [constexpr] MUSIA mat IBA RETURN STATEMENT a ZIADEN iny CODE.
constexpr int NoExceptFunction2(int Value) noexcept
{
	return(Value);
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPILER CONDITION akceptuje, pretoze NoExceptFunction2() JE OZNACENA pomocou KEYWORD [constexpr].
void NoExceptCondition7(bool ThrowException) noexcept(NoExceptFunction2(1))
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition7() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition7() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions7(void)
{
	PrintLineSeparator();

	NoExceptCondition7(false);

	PrintLineSeparator();

	try
	{
		// !!! Sposobi PAD PROGRAMU, pretoze FUNCTION hodi EXCEPTION, aj CONDITION to nepovoluje.
		NoExceptCondition7(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void NoExceptFunction3(void) noexcept
{
	wcout << L"FUNCTION NoExceptFunction3() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPILER CONDITION akceptuje, pretoze NoExceptFunction3() JE OZNACENA pomocou KEYWORD [noexcept].
void NoExceptCondition8(bool ThrowException) noexcept(noexcept(NoExceptFunction3()))
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition8() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition8() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions8(void)
{
	PrintLineSeparator();

	NoExceptCondition8(false);

	PrintLineSeparator();

	try
	{
		// !!! Sposobi PAD PROGRAMU, pretoze FUNCTION hodi EXCEPTION, aj CONDITION to nepovoluje.
		NoExceptCondition8(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void NoExceptFunction4(void) noexcept
{
	wcout << L"FUNCTION NoExceptFunction4() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! COMPILER CONDITION akceptuje, pretoze NoExceptFunction4() JE OZNACENA pomocou KEYWORD [noexcept].
void NoExceptCondition9(bool ThrowException) noexcept(!noexcept(NoExceptFunction3()))
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition9() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition9() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions9(void)
{
	PrintLineSeparator();

	NoExceptCondition9(false);

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION sa KOREKTNE zavola a EXCEPTION bude zachytena, pretoze CONDITION umoznuje hodit EXCEPTION.
		NoExceptCondition9(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! PARAMETERS je MOZNE pouzit v CONDITIONS, ak sa aplikuje OPERATOR [noexcept()].
void NoExceptCondition10(bool ThrowException, CThrowClass ThrowClass) noexcept(noexcept(ThrowClass.CanThrowException()))
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition10() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition10() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions10(void)
{
	PrintLineSeparator();

	CThrowClass													ThrowClass;

	NoExceptCondition10(false,ThrowClass);

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION sa KOREKTNE zavola a EXCEPTION bude zachytena, pretoze CONDITION umoznuje hodit EXCEPTION.
		NoExceptCondition10(true,ThrowClass);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! PARAMETERS je MOZNE pouzit v CONDITIONS, ak sa aplikuje OPERATOR [noexcept()].
void NoExceptCondition11(bool ThrowException, CThrowClass ThrowClass) noexcept(noexcept(ThrowClass.CanNotThrowException()))
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION NoExceptCondition11() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION NoExceptCondition11() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNoExceptConditions11(void)
{
	PrintLineSeparator();

	CThrowClass													ThrowClass;

	NoExceptCondition11(false,ThrowClass);

	PrintLineSeparator();

	try
	{
		// !!! Sposobi PAD PROGRAMU, pretoze FUNCTION hodi EXCEPTION, aj CONDITION to nepovoluje.
		NoExceptCondition11(true,ThrowClass);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ExceptInnerFunction(bool ThrowException)
{
	if (ThrowException==true)
	{
		wcout << L"FUNCTION ExceptInnerFunction() will THROW EXCEPTION !" << endl;

		throw(CException(L"This is a very SERIOUS ERROR !"));
	}
	else
	{
		wcout << L"FUNCTION ExceptInnerFunction() will NOT THROW EXCEPTION !" << endl;
	}
}
//-------------------------------------------------------------------------------------------------------
void NoExceptOuterFunction(bool ThrowException) noexcept
{
	wcout << L"FUNCTION NoExceptOuterFunction() CALLED !" << endl;

	ExceptInnerFunction(ThrowException);
}
//-------------------------------------------------------------------------------------------------------
void TestInnerFunctionException(void)
{
	PrintLineSeparator();

	NoExceptOuterFunction(false);

	PrintLineSeparator();

	try
	{
		// !!! Sposobi PAD PROGRAMU, pretoze FUNCTION hodi INNER EXCEPTION, aj ked OUTER FUNCTION to neumoznuje.
		NoExceptOuterFunction(true);
	}
	catch(CException& Exception)
	{
		wcout << L"EXCEPTION [" << Exception.GetMessage() << L"] was DETECTED !" << endl;
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestException();
	//TestNoException();
	//TestInnerException();
	//TestNoExceptConditions1();
	//TestNoExceptConditions2();
	//TestNoExceptConditions3();
	//TestNoExceptConditions4();
	//TestNoExceptConditions5();
	//TestNoExceptConditions6();
	//TestNoExceptConditions7();
	//TestNoExceptConditions8();
	//TestNoExceptConditions9();
	//TestNoExceptConditions10();
	//TestNoExceptConditions11();
	TestInnerFunctionException();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------