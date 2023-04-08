//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include "MyDebug.h"
#include "CException.h"
#include "CExceptionBase.h"
#include "CExceptionDerived1.h"
#include "CExceptionDerived2.h"
#include "CExceptionCopyMove.h"
#include "CExceptionCopy.h"
#include "CExceptionMove.h"
#include "EExceptionType1.h"
#include "EExceptionType2.h"
#include "CObject.h"
#include "CThrowExceptionInCopy.h"
#include "CFuctionTryBlocksBase.h"
#include "CFuctionTryBlocksDerived.h"
#include "CFuctionTryBlocks.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CalledFunction(bool ThrowException)
{
	if (ThrowException==true)
	{
		throw(CException(L"EXCEPTION in CALLED FUNCTION !"));
	}

	wcout << L"FUNCTION [" << __func__ << L"()] SUCCESSFULLY FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void CallerFunction(void)
{
	try
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 STARTED !" << endl;

		CalledFunction(false);

		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 SUCCESSFULLY FINISHED !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 STARTED !" << endl;

		CalledFunction(true);

		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 SUCCESSFULLY FINISHED !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestCallerCalledException(void)
{
	PrintLineSeparator();

	CallerFunction();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Method2(EExceptionType2 ExceptionType)
{
	CObject														Object(L"OBJECT in METHOD [Method2()] !");

	Object.GetValue();

	if (ExceptionType==EExceptionType2::E_EXCEPTION_COPY_MOVE)
	{
		throw(CExceptionCopyMove(L"EXCEPTION [CExceptionCopyMove] !"));
	}
	else if (ExceptionType==EExceptionType2::E_EXCEPTION_COPY)
	{
		throw(CExceptionCopy(L"EXCEPTION [CExceptionCopy] !"));
	}
	else if (ExceptionType==EExceptionType2::E_EXCEPTION_MOVE)
	{
		throw(CExceptionMove(L"EXCEPTION [CExceptionMove] !"));
	}
	else
	{
		throw(CException(L"UNSUPPORTED EXCEPTION TYPE !"));
	}
}
//-----------------------------------------------------------------------------
void Method1(EExceptionType2 ExceptionType)
{
	CObject														Object1(L"OBJECT 1 in METHOD [Method1()] !");
	CObject														Object2(L"OBJECT 2 in METHOD [Method1()] !");

	Object1.GetValue();
	Object2.GetValue();

	try
	{
		Method2(ExceptionType);
	}
	catch(const CExceptionCopyMove& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION [CExceptionCopyMove] CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
		throw;
	}
	catch(const CExceptionCopy& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION [CExceptionCopy] CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
		throw;
	}
	catch(const CExceptionMove& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION [CExceptionMove] CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
		throw;
	}
}
//-----------------------------------------------------------------------------
void TestCopyMoveExceptions(void)
{
	PrintLineSeparator();

	try
	{
		CObject													Object(L"OBJECT in TRY 1 BLOCK of METHOD [TestCopyMoveExceptions()] !");

		Object.GetValue();

		Method1(EExceptionType2::E_EXCEPTION_COPY_MOVE);
	}
	catch(const CExceptionCopyMove& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [CExceptionCopyMove] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		CObject													Object(L"OBJECT in TRY 2 BLOCK of METHOD [TestCopyMoveExceptions()] !");

		Object.GetValue();

		Method1(EExceptionType2::E_EXCEPTION_COPY);
	}
	catch(const CExceptionCopy& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [CExceptionCopy] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		CObject													Object(L"OBJECT in TRY 3 BLOCK of METHOD [TestCopyMoveExceptions()] !");

		Object.GetValue();

		Method1(EExceptionType2::E_EXCEPTION_MOVE);
	}
	catch(const CExceptionMove& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 FAILED with EXCEPTION [CExceptionMove] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void NoExceptFunction(void) noexcept
{
	wcout << L"FUNCTION [" << __func__ << L"()] is CALLED !" << endl;

	// !!! Ak by doslo k hodeniu EXCEPTION, PROGRAM je OKAMZITE TERMINATED.
	//throw(CException(L"FATAL EXCEPTION !"));
}
//-----------------------------------------------------------------------------
void TestNoExceptKeyword(void)
{
	PrintLineSeparator();

	// !!! FUNCTION NIKDY nehodi EXCEPTION.
	NoExceptFunction();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! METHOD obsahuje CONDITIONAL KEYWORD [noexcept].
// !!!!! METHOD vykonava COPY svojho PARAMETER, pricom na zaklade toho ci PARAMETER TYPE ma CUSTOM COPY CONSTRUCTOR a CUSTOM COPY OPERATOR moze hodit EXCEPTION, alebo NIE.
template<typename TType>
TType ExceptOrNoExceptFunction(const TType& Parameter) noexcept(is_trivially_copyable<TType>())
{
	bool														IsPod=is_trivially_copyable<TType>();

	wcout << L"FUNCTION [" << __func__ << L"()] is CALLED for OBJECT that IS TRIVIALLY COPYABLE has VALUE [" << IsPod << L"] !" << endl;

	// !!!!! Ak PARAMETER NIE JE PLAIN OLD OBJECT, tak COPY OPERATOR= MOZE hodit EXCEPTION.
	TType														CopiedObject=Parameter;

	return(CopiedObject);
}
//-----------------------------------------------------------------------------
void TestNoExceptKeywordConditional(void)
{
	PrintLineSeparator();

	// !!! FUNCTION NIKDY nehodi EXCEPTION pre TYPE [int].
	int															CopiedValue1=ExceptOrNoExceptFunction(100);

	wcout << L"In FUNCTION [" << __func__ << L"()] COPIED VALUE 1 has VALUE [" << CopiedValue1 << L"] !" << endl;

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION HODI nehodi EXCEPTION pre TYPE [CThrowExceptionInCopy], pretoze COPY CONSTRUCTOR i COPY OPERATOR= hadzu EXCEPTIONS.
		CThrowExceptionInCopy									CopiedValue2=ExceptOrNoExceptFunction(CThrowExceptionInCopy(L"MY OBJECT !!!"));
	
		wcout << L"In FUNCTION [" << __func__ << L"()] COPIED VALUE 2 has VALUE [" << CopiedValue2.GetValue() << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [CException] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION NEHADZE EXCEPTION.
void DoPrint(int Value) noexcept
{
	wcout << L"FUNCTION [" << __func__ << L"()] is CALLED for VALUE [" << Value << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! FUNCTION HADZE EXCEPTION.
void DoPrint(const CObject& Value)
{
	wcout << L"FUNCTION [" << __func__ << L"()] is CALLED for VALUE [" << Value.GetValue() << L"] !" << endl;

	throw(CException(L"Some EXCEPTION !!!"));
}
//-----------------------------------------------------------------------------
// !!!!! METHOD obsahuje CONDITIONAL KEYWORD [noexcept] i OPERATOR KEYWORD [noexcept].
template<typename TType>
void ExceptOrNoExceptOperatorFunction(const TType& Parameter) noexcept(noexcept(DoPrint(Parameter)))
{
	wcout << L"FUNCTION [" << __func__ << L"()] is CALLED !" << endl;

	// !!!!! Ak PARAMETER NIE JE PLAIN OLD OBJECT, tak COPY OPERATOR= MOZE hodit EXCEPTION.
	DoPrint(Parameter);
}
//-----------------------------------------------------------------------------
void TestNoExceptOperator(void)
{
	PrintLineSeparator();

	// !!! FUNCTION NEHODI nehodi EXCEPTION pre TYPE [int], pretoze FUNCTION [" << __func__ << L"void DoPrint(int)] JE oznacena KEYWORD [noexcept].
	ExceptOrNoExceptOperatorFunction(100);

	PrintLineSeparator();

	try
	{
		// !!! FUNCTION HODI EXCEPTION pre TYPE [CObject], pretoze FUNCTION [" << __func__ << L"void DoPrint(void)] NIE JE oznacena KEYWORD [noexcept] a zaroven HADZE EXCEPTION.
		ExceptOrNoExceptOperatorFunction(CObject(L"MY OBJECT !!!"));
	
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK SUCCEEDED !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [CException] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCatchExceptions(void)
{
	PrintLineSeparator();

	try
	{
		CException												Exception(L"EXCEPTION CAUGHT by VALUE !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY VALUE.
	catch(CException E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		CExceptionDerived1										Exception(L"EXCEPTION CAUGHT by VALUE of BASE TYPE !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY VALUE of BASE TYPE.
	catch(CExceptionBase E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		CException*												Exception=new CException(L"EXCEPTION CAUGHT by POINTER !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY POINTER.
	catch(const CException* E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E->GetTextMessage() << L"] !" << endl;

		// !!!!! EXCEPTIONS zachytavane pomocou POINTER TYPES je nutne MANUALNE ODSTRANIT z MEMORY.
		delete(E);
	}

	PrintLineSeparator();

	try
	{
		CExceptionDerived1*										Exception=new CExceptionDerived1(L"EXCEPTION CAUGHT by POINTER of BASE TYPE !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY POINTER of BASE TYPE.
	catch(const CExceptionBase* E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E->GetTextMessage() << L"] !" << endl;

		// !!!!! EXCEPTIONS zachytavane pomocou POINTER TYPES je nutne MANUALNE ODSTRANIT z MEMORY.
		delete(E);
	}

	PrintLineSeparator();

	try
	{
		CException												Exception(L"EXCEPTION CAUGHT by REFERENCE !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY REFERENCE.
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		CExceptionDerived1										Exception(L"EXCEPTION CAUGHT by REFERENCE of BASE TYPE !");

		throw(Exception);
	}
	// !!! EXCEPTION je chytena BY REFERENCE of BASE TYPE.
	catch(const CExceptionBase& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThrowException(void)
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	throw(CException(L"Some EXCEPTION !!!"));
}
//-----------------------------------------------------------------------------
void RethrowExceptionIndirectly(void)
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	// !!! EXCEPTION je RETHROWN NEPRIAMO vo FUNCTION, ktora je volana z CATCH BLOCK.
	throw;
}
//-----------------------------------------------------------------------------
void RethrowException1(void)
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	try
	{
		ThrowException();
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;

		// !!! EXCEPTION je RETHROWN.
		throw;
	}
}
//-----------------------------------------------------------------------------
void RethrowException2(void)
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	try
	{
		ThrowException();
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;

		// !!! EXCEPTION je RETHROWN NEPRIAMO vo FUNCTION, ktora je volana z CATCH BLOCK.
		RethrowExceptionIndirectly();
	}
}
//-----------------------------------------------------------------------------
void TestRethrowExceptions(void)
{
	PrintLineSeparator();

	/*
	try
	{
		// !!!!! EXCEPTION je RETHROWN aj ked nie je ZIADNA EXCEPTION AKTUALNE SPRACOVANA. Takyto EXCEPTION RETHROWN vedie k PROGRAM TERMINATION.
		throw;
	}
	catch(...)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT !" << endl;
	}

	PrintLineSeparator();
	*/

	try
	{
		RethrowException1();
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		RethrowException2();
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT with MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCatchAllExceptions(void)
{
	PrintLineSeparator();

	try
	{
		throw(CException(L"Some EXCEPTION !!!"));
	}
	// !!! CATCH BLOCK zachyti KAZDU EXCEPTION.
	catch(...)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] EXCEPTION CAUGHT !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThrowException(EExceptionType1 ExceptionType)
{
	if (ExceptionType==EExceptionType1::E_BASE)
	{
		throw(CExceptionBase(L"EXCEPTION [CExceptionBase] !"));
	}
	else if (ExceptionType==EExceptionType1::E_DERIVED_1)
	{
		throw(CExceptionDerived1(L"EXCEPTION [CExceptionDerived1] !"));
	}
	else if (ExceptionType==EExceptionType1::E_DERIVED_2)
	{
		throw(CExceptionDerived2(L"EXCEPTION [CExceptionDerived2] !"));
	}
	else
	{
		throw(CException(L"UNSUPPORTED EXCEPTION TYPE !"));
	}
}
//-----------------------------------------------------------------------------
void TestMultipleCatchBlocksException(void)
{
	PrintLineSeparator();

	try
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 STARTED !" << endl;

		ThrowException(EExceptionType1::E_BASE);

		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 SUCCESSFULLY FINISHED !" << endl;
	}
	catch(const CExceptionDerived1& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [CExceptionDerived1] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CExceptionDerived2& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [CExceptionDerived2] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	// !!! CATCH BLOCK pre BASE EXCEPTION CLASS MUSI byt az za CATCH BLOCK pre DERIVED EXCEPTION CLASSES.
	catch(const CExceptionBase& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [CExceptionBase] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [CException] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 STARTED !" << endl;

		ThrowException(EExceptionType1::E_DERIVED_1);

		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 SUCCESSFULLY FINISHED !" << endl;
	}
	catch(const CExceptionDerived1& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [CExceptionDerived1] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CExceptionDerived2& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [CExceptionDerived2] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	// !!! CATCH BLOCK pre BASE EXCEPTION CLASS MUSI byt az za CATCH BLOCK pre DERIVED EXCEPTION CLASSES.
	catch(const CExceptionBase& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [CExceptionBase] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [CException] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 STARTED !" << endl;

		ThrowException(EExceptionType1::E_DERIVED_2);

		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 SUCCESSFULLY FINISHED !" << endl;
	}
	catch(const CExceptionDerived1& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 FAILED with EXCEPTION [CExceptionDerived1] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CExceptionDerived2& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 FAILED with EXCEPTION [CExceptionDerived2] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	// !!! CATCH BLOCK pre BASE EXCEPTION CLASS MUSI byt az za CATCH BLOCK pre DERIVED EXCEPTION CLASSES.
	catch(const CExceptionBase& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 FAILED with EXCEPTION [CExceptionBase] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 3 FAILED with EXCEPTION [CException] and MESSAGE [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION obsahuje IBA TRY CATCH BLOCK.
void TryBlockFunction(void)
try
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	throw(CException(L"Some EXCEPTION !!!"));
}
catch(const CException&E)
{
	wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestFuctionTryBlocksOnFunctions(void)
{
	PrintLineSeparator();

	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	TryBlockFunction();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFuctionTryBlocksOnBaseClassInitializers(void)
{
	PrintLineSeparator();

	try
	{
		wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

		CFuctionTryBlocksDerived								Object(L"Some TEXT !!!");

		Object.GetValue();
	}
	catch(const CException&E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFuctionTryBlocksOnMemberClassInitializers(void)
{
	PrintLineSeparator();

	try
	{
		wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

		CFuctionTryBlocks										Object(L"Some TEXT !!!");

		Object.GetValue();
	}
	catch(const CException&E)
	{
		wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestExceptionThreadTransfer(void)
{
	PrintLineSeparator();

	{
		wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

		// !!!!! SHARED VARIABLE medzi THREAD 1 a THREAD 2.
		exception_ptr											ThreadSharedException;

		// !!!!! Tento CODE by mal bezat v THREAD 1.

		try
		{
			throw(CException(L"EXCEPTION in ANOTHER THREAD !!!"));
		}
		catch(const CException&E)
		{
			wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 1 FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;

			// !!! Ulozi sa CURRENT EXCEPTION.
			ThreadSharedException=current_exception();
		}

		PrintLineSeparator();

		// !!!!! Tento CODE by mal bezat v THREAD 2.

		try
		{
			// !!!!! Ulozena EXCEPTION je hodena v INOM THREAD.
			rethrow_exception(ThreadSharedException);
		}
		catch(const CException&E)
		{
			wcout << L"In FUNCTION [" << __func__ << L"()] TRY BLOCK 2 FAILED with EXCEPTION [" << E.GetTextMessage() << L"] !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! CUSTOM TERMINATE HANDLER sa zavola IBA ak PROGRAM NIE je volany z VISUAL STUDIO.
void CustomTerminateHandler(void)
{
	wcout << L"FUNCTION [" << __func__ << L"()] CALLED !" << endl;

	wcout << L"FUNCTION [" << __func__ << L"()] PROGRAM is EXITING !" << endl;

	PrintLineSeparator();

	// !!! PROGRAM sa ukonci vratenim ERROR CODE.
	exit(100);
}
//-----------------------------------------------------------------------------
void TestTerminateHandler(void)
{
	PrintLineSeparator();

	terminate_handler											OldTerminateHandler=set_terminate(CustomTerminateHandler);

	throw(CException(L"UNHANDLED EXCEPTION !!!"));

	// !!! Vrati sa povodny TERMINATE HANDLER. Pouziva sa vtedy, ak nedojde k vzniku PROGRAM TERMINATION.
	set_terminate(OldTerminateHandler);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestCallerCalledException();
	//TestCopyMoveExceptions();
	//TestNoExceptKeyword();
	//TestNoExceptKeywordConditional();
	//TestNoExceptOperator();
	//TestCatchExceptions();
	//TestRethrowExceptions();
	//TestCatchAllExceptions();
	//TestMultipleCatchBlocksException();
	//TestFuctionTryBlocksOnFunctions();
	//TestFuctionTryBlocksOnBaseClassInitializers();
	//TestFuctionTryBlocksOnMemberClassInitializers();
	//TestExceptionThreadTransfer();
	TestTerminateHandler();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------