//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <coroutine>
#include <thread>
#include <syncstream>
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers/MyDebug.h"
#include "Helpers/CString.h"
#include "Helpers/CException.h"
#include "CSimpleCoroutineObject.h"
#include "CClassWithCoroutineMethod.h"
#include "CValue.h"
#include "CTracingCoroutineObject.h"
#include "CTracingAwaiter.h"
#include "CCoroutineObjectPromiseTypeWithParameters.h"
#include "CCoroutineObjectMultiYield.h"
#include "CCoroutineObjectMultiReturn.h"
#include "CCoroutineObjectUnhandledException.h"
#include "CCoroutineObjectPromiseTypeVoid.h"
#include "CCoroutineObjectHandledException1.h"
#include "CCoroutineObjectHandledException2.h"
#include "CCoroutineObjectCustomAllocation.h"
#include "CCoroutineObjectCustomAllocationWithParameters.h"
#include "CCoroutineObjectCustomAllocationSection.h"
#include "CCoroutineObjectCustomAllocationFailure.h"
#include "CCoroutineObjectStandardAwaiter.h"
#include "CCoroutineObjectWithAwaiterInterface.h"
#include "CCoroutineObjectWithAwaiterInterfaceFaulty.h"
#include "CCoroutineObjectScheduling1.h"
#include "CCoroutineObjectScheduling2.h"
#include "CCoroutineObjectSymmetricTransfer.h"
#include "CCoroutineObjectAwaitTransform.h"
#include "CCoroutineObjectCustomOperatorCoAwait.h"
#include "CCoroutineObjectThreadPool.h"
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
using namespace this_thread;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineMethodNonStatic(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CClassWithCoroutineMethod								Object(123);
		CSimpleCoroutineObject									MyCoroutineTask=Object.CoroutineMethodNonStatic();

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineMethodStatic(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CSimpleCoroutineObject									MyCoroutineTask=CClassWithCoroutineMethod::CoroutineMethodStatic();

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineLambda(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		auto													LambdaCoroutine=[](void)->CSimpleCoroutineObject
		{
			wcout << L"\tLambdaCoroutine() - PART 1." << endl;

			suspend_always										Awaiter1{};

			co_await Awaiter1;

			wcout << L"\tLambdaCoroutine() - PART 2." << endl;

			suspend_always										Awaiter2{};

			co_await Awaiter2;

			wcout << L"\tLambdaCoroutine() - PART 3." << endl;
		};

		CSimpleCoroutineObject									MyCoroutineTask=LambdaCoroutine();

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
auto ReturnCorutineLambdaWithCaptureOK(void)
{
	CValue														Value(L"XYZ");

	auto														LambdaCoroutine=[Value](void)->CSimpleCoroutineObject
	{
		wcout << L"\tLambdaCoroutine() - PART 1. VALUE [" << Value.GetValue() << L"]." << endl;

		suspend_always											Awaiter1{};

		co_await Awaiter1;

		wcout << L"\tLambdaCoroutine() - PART 2. VALUE [" << Value.GetValue() << L"]." << endl;

		suspend_always											Awaiter2{};

		co_await Awaiter2;

		wcout << L"\tLambdaCoroutine() - PART 3. VALUE [" << Value.GetValue() << L"]." << endl;
	};

	return(LambdaCoroutine);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineLambdaWithCaptureOK(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		wcout << L"Test() - BEFORE COROUTINE STARTED." << endl;

		// !!!!! CODE NESPOSOBI PROBLEM, ani pri pouziti LAMBDA FUNCTION CAPTURE, pretoze LAMBDA OBJECT je ulozeny v LOCAL VARIABLE, ktorej zivotnost trva pocas celeho behu LAMBDA COROUTINE.
		auto													LambdaCoroutine=ReturnCorutineLambdaWithCaptureOK();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		CSimpleCoroutineObject									MyCoroutineTask=LambdaCoroutine();

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
auto ReturnCorutineLambdaWithCaptureError(void)
{
	CValue														Value(L"XYZ");

	auto														LambdaCoroutine=[Value](void)->CSimpleCoroutineObject
	{
		wcout << L"\tLambdaCoroutine() - PART 1. VALUE [" << Value.GetValue() << L"]." << endl;

		suspend_always											Awaiter1{};

		co_await Awaiter1;

		wcout << L"\tLambdaCoroutine() - PART 2. VALUE [" << Value.GetValue() << L"]." << endl;

		suspend_always											Awaiter2{};

		co_await Awaiter2;

		wcout << L"\tLambdaCoroutine() - PART 3. VALUE [" << Value.GetValue() << L"]." << endl;
	};

	return(LambdaCoroutine);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CODE sposobi UNDEFINED BEHAVIOR.
void TestCoroutineLambdaWithCaptureError(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		wcout << L"Test() - BEFORE COROUTINE STARTED." << endl;

		// !!!!! CODE sposobi UNDEFINED BEHAVIOR, pretoze CODE [ReturnCorutineLambdaWithCaptureError()] vracia TEMPORARY LAMBDA FUNCTION OBJECT reprezentujuci LAMBDA FUNCTION, ktory hned po skonceni celeho CODE [ReturnCorutineLambdaWithCaptureError()()] bude uvolneny z MEMORY. Tym padom sa aj uvolni OBJECT TYPE [CValue], ktoru LAMBDA COROUTINE ziskala z CONTEXT pomocou LAMBDA FUNCTION CAPTURE. A pri volani LAMBDA FUNCTION dojde k pristupu k uz uvolnenej MEMORY.
		CSimpleCoroutineObject									MyCoroutineTask=ReturnCorutineLambdaWithCaptureError()();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTracingCoroutineObject<suspend_always> CoroutineTracingLazyStart(void)
{
	wcout << L"\tCoroutineTracingLazyStart() - PART 1." << endl;

	CTracingAwaiter											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineTracingLazyStart() - PART 2." << endl;

	CTracingAwaiter											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineTracingLazyStart() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineTracingLazyStart(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CTracingCoroutineObject<suspend_always>					MyCoroutineTask=CoroutineTracingLazyStart();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTracingCoroutineObject<suspend_never> CoroutineTracingEagerStart(void)
{
	wcout << L"\tCoroutineTracingEagerStart() - PART 1." << endl;

	CTracingAwaiter											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineTracingEagerStart() - PART 2." << endl;

	CTracingAwaiter											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineTracingEagerStart() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineTracingEagerStart(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CTracingCoroutineObject<suspend_never>					MyCoroutineTask=CoroutineTracingEagerStart();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectPromiseTypeWithParameters CoroutinePromiseTypeWithParameters(int Value1, double Value2)
{
	wcout << L"\tCoroutinePromiseTypeWithParameters() - PART 1. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutinePromiseTypeWithParameters() - PART 2. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutinePromiseTypeWithParameters() - PART 3. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutinePromiseTypeWithParameters(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectPromiseTypeWithParameters				MyCoroutineTask=CoroutinePromiseTypeWithParameters(100,123.456);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectMultiYield<int,double> CoroutineMultiYield(void)
{
	wcout << L"\tCoroutineMultiYield() - PART 1." << endl;

	// !!!!! OPERATOR [OPERATOR co_yield] moze v ramci 1 COROUTINE vracat ROZNE TYPES, ake PROMISE TYPE obsahuje OVERLOADED VERSIONS METHOD [TAWaiterType yield_value(TYieldValue Value)].
	co_yield 100;

	wcout << L"\tCoroutineMultiYield() - PART 2." << endl;

	// !!!!! OPERATOR [OPERATOR co_yield] moze v ramci 1 COROUTINE vracat ROZNE TYPES, ake PROMISE TYPE obsahuje OVERLOADED VERSIONS METHOD [TAWaiterType yield_value(TYieldValue Value)].
	co_yield 123.456;

	wcout << L"\tCoroutineMultiYield() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineMultiYield(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectMultiYield<int,double>					MyCoroutineTask=CoroutineMultiYield();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. VALUE 1 [" << MyCoroutineTask.GetValue1() << L"] VALUE 2 [" << MyCoroutineTask.GetValue2() << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED. VALUE 1 [" << MyCoroutineTask.GetValue1() << L"] VALUE 2 [" << MyCoroutineTask.GetValue2() << L"]." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectMultiReturn<int,double> CoroutineMultiReturn(bool ReturnInt)
{
	wcout << L"\tCoroutineMultiReturn() - PART 1." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineMultiReturn() - PART 2." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineMultiReturn() - PART 3." << endl;

	if (ReturnInt==true)
	{
		// !!!!! OPERATOR [OPERATOR co_return] moze v ramci 1 COROUTINE vracat ROZNE TYPES, ake PROMISE TYPE obsahuje OVERLOADED VERSIONS METHOD [void return_value(TYieldValue Value)].
		co_return(100);
	}
	else
	{
		// !!!!! OPERATOR [OPERATOR co_return] moze v ramci 1 COROUTINE vracat ROZNE TYPES, ake PROMISE TYPE obsahuje OVERLOADED VERSIONS METHOD [void return_value(TYieldValue Value)].
		co_return(123.456);
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineMultiReturn(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectMultiReturn<int,double>					MyCoroutineTask=CoroutineMultiReturn(true);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED. VALUE 1 [" << MyCoroutineTask.GetValue1() << L"] VALUE 2 [" << MyCoroutineTask.GetValue2() << L"]." << endl;

				break;
			}
		}
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CCoroutineObjectMultiReturn<int,double>					MyCoroutineTask=CoroutineMultiReturn(false);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED. VALUE 1 [" << MyCoroutineTask.GetValue1() << L"] VALUE 2 [" << MyCoroutineTask.GetValue2() << L"]." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectUnhandledException CoroutineUnhandledException(bool ThrowException)
{
	wcout << L"\tCoroutineUnhandledException() - PART 1." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineUnhandledException() - PART 2." << endl;

	if (ThrowException==true)
	{
		throw(CException(L"Some EXCEPTION."));
	}

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineUnhandledException() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineUnhandledException(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectUnhandledException						MyCoroutineTask=CoroutineUnhandledException(false);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CCoroutineObjectUnhandledException						MyCoroutineTask=CoroutineUnhandledException(true);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectPromiseTypeVoid CoroutinePromiseTypeVoid(void)
{
	wcout << L"\tCoroutinePromiseTypeVoid() - PART 1." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutinePromiseTypeVoid() - PART 2." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutinePromiseTypeVoid() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutinePromiseTypeVoid(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectPromiseTypeVoid							MyCoroutineTask=CoroutinePromiseTypeVoid();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectHandledException1 CoroutineObjectHandledException1(bool ThrowExceptionInCoroutineBody, bool ThrowExceptionInPromiseTypeMethodInitialSuspend, bool ThrowExceptionInPromiseTypeMethodReturnVoid)
{
	(void)ThrowExceptionInPromiseTypeMethodInitialSuspend;
	(void)ThrowExceptionInPromiseTypeMethodReturnVoid;

	wcout << L"\tCoroutineObjectHandledException1() - PART 1." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectHandledException1() - PART 2." << endl;

	if (ThrowExceptionInCoroutineBody==true)
	{
		throw(CException(L"Some EXCEPTION."));
	}

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectHandledException1() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectHandledException1(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	try
	{
		// !!! EXCEPTION sa hodi v COROUTINE.
		CCoroutineObjectHandledException1						MyCoroutineTask=CoroutineObjectHandledException1(true,false,false);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}

		MyCoroutineTask.ThrowUnhandledException();
	}
	catch(const CException& E)
	{
		wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
	}
	catch(...)
	{
		wcout << L"UNKNOWN EXCEPTION CAUGHT." << endl;
	}

	/*
	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		// !!!!! EXCEPTION v METHOD [TAwaiter initial_suspend(void)] sposobi UNDEFINED BEHAVIOR.
		// !!! EXCEPTION sa hodi v PROMISE TYPE METHOD.
		CCoroutineObjectHandledException1						MyCoroutineTask=CoroutineObjectHandledException1(false,true,false);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}

		MyCoroutineTask.ThrowUnhandledException();
	}
	catch(const CException& E)
	{
		wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
	}
	catch(...)
	{
		wcout << L"UNKNOWN EXCEPTION CAUGHT." << endl;
	}
	*/

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	try
	{
		// !!! EXCEPTION sa hodi v PROMISE TYPE METHOD.
		CCoroutineObjectHandledException1						MyCoroutineTask=CoroutineObjectHandledException1(false,false,true);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}

		MyCoroutineTask.ThrowUnhandledException();
	}
	catch(const CException& E)
	{
		wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
	}
	catch(...)
	{
		wcout << L"UNKNOWN EXCEPTION CAUGHT." << endl;
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectHandledException2 CoroutineObjectHandledException2(bool ThrowExceptionInCoroutineBody)
{
	wcout << L"\tCoroutineObjectHandledException2() - PART 1." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectHandledException2() - PART 2." << endl;

	if (ThrowExceptionInCoroutineBody==true)
	{
		throw(CException(L"Some EXCEPTION."));
	}

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectHandledException2() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectHandledException2(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	try
	{
		// !!! EXCEPTION sa hodi v COROUTINE.
		CCoroutineObjectHandledException2						MyCoroutineTask=CoroutineObjectHandledException2(true);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}
	catch(const CException& E)
	{
		wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
	}
	catch(...)
	{
		wcout << L"UNKNOWN EXCEPTION CAUGHT." << endl;
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocation CoroutineObjectCustomAllocation1(int Value)
{
	wcout << L"\tCoroutineObjectCustomAllocation1() - PART 1. VALUE [" << Value << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectCustomAllocation1() - PART 2. VALUE [" << Value << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectCustomAllocation1() - PART 3. VALUE [" << Value << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocation CoroutineObjectCustomAllocation2(int Value1, double Value2)
{
	wcout << L"\tCoroutineObjectCustomAllocation2() - PART 1. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectCustomAllocation2() - PART 2. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectCustomAllocation2() - PART 3. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectCustomAllocation(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectCustomAllocation						MyCoroutineTask=CoroutineObjectCustomAllocation1(100);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	{
		CCoroutineObjectCustomAllocation						MyCoroutineTask=CoroutineObjectCustomAllocation2(100,123.456);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationWithParameters CoroutineObjectCustomAllocationWithParameters(int Value1, double Value2)
{
	wcout << L"\tCoroutineObjectCustomAllocationWithParameters() - PART 1. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectCustomAllocationWithParameters() - PART 2. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectCustomAllocationWithParameters() - PART 3. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectCustomAllocationWithParameters(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectCustomAllocationWithParameters			MyCoroutineTask=CoroutineObjectCustomAllocationWithParameters(100,123.456);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationSection CoroutineObjectCustomAllocationSection(int Value1, double Value2)
{
	wcout << L"\tCoroutineObjectCustomAllocationSection() - PART 1. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectCustomAllocationSection() - PART 2. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectCustomAllocationSection() - PART 3. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectCustomAllocationSection(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectCustomAllocationSection					MyCoroutineTask=CoroutineObjectCustomAllocationSection(100,123.456);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationFailure CoroutineObjectCustomAllocationFailure(int Value1, double Value2)
{
	wcout << L"\tCoroutineObjectCustomAllocationFailure() - PART 1. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineObjectCustomAllocationFailure() - PART 2. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	suspend_always											Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineObjectCustomAllocationFailure() - PART 3. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectCustomAllocationFailure(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectCustomAllocationFailure					MyCoroutineTask=CoroutineObjectCustomAllocationFailure(100,123.456);

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectStandardAwaiter CoroutineCoroutineObjectStandardAwaiter2(void)
{
	wcout << L"\t\tCoroutineCoroutineObjectStandardAwaiter2() - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t\tCoroutineCoroutineObjectStandardAwaiter2() - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t\tCoroutineCoroutineObjectStandardAwaiter2() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectStandardAwaiter CoroutineCoroutineObjectStandardAwaiter1(void)
{
	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 2." << endl;

	CCoroutineObjectStandardAwaiter								MyCoroutineObject=CoroutineCoroutineObjectStandardAwaiter2();

	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 3." << endl;

	int															Index=0;

	while(true)
	{
		wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

		// !!!!! Ak COROUTINE vola inu COROUTINE tak CALLER COROUTINE je zodpovedna za volanie METHOD [void coroutine_handle<TPromiseType>::resume(void) const].
		bool													CanResume=MyCoroutineObject.Resume();

		if (CanResume==true)
		{
			wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
		}
		else
		{
			wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - AFTER COROUTINE FINISHED." << endl;

			break;
		}
	}

	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 4." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 5." << endl;

	suspend_always												Awaiter3{};

	co_await Awaiter3;

	wcout << L"\tCoroutineCoroutineObjectStandardAwaiter2() - PART 6." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectStandardAwaiter(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectStandardAwaiter							MyCoroutineObject=CoroutineCoroutineObjectStandardAwaiter1();
		int														Index=0;

		while(true)
		{
			wcout << L"Test() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterface CoroutineObjectWithAwaiterInterface2(wstring CoroutineName)
{
	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterface CoroutineObjectWithAwaiterInterface1(wstring CoroutineName)
{
	wcout << L"\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 2." << endl;

	CCoroutineObjectWithAwaiterInterface						MyCoroutineObject=CoroutineObjectWithAwaiterInterface2(L"COROUTINE 2");

	wcout << L"\t" << CoroutineName << L" CALLED - PART 3." << endl;

	co_await MyCoroutineObject;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 4." << endl;

	suspend_always												Awaiter3{};

	co_await Awaiter3;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 5." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectWithAwaiterInterface(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectWithAwaiterInterface					MyCoroutineObject=CoroutineObjectWithAwaiterInterface1(L"COROUTINE 1");
		int														Index=0;

		while(true)
		{
			wcout << L"Test() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterfaceFaulty CoroutineObjectWithAwaiterInterfaceFaulty2(wstring CoroutineName)
{
	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t\t" << CoroutineName << L" CALLED - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterfaceFaulty CoroutineObjectWithAwaiterInterfaceFaulty1(wstring CoroutineName)
{
	wcout << L"\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 2." << endl;

	// !!!!! COROUTINE [CoroutineObjectWithAwaiterInterfaceFaulty2()] nebude NIKDY ZAVOLANA, pretoze METHOD [Resume()] vykonava RESUME iba pre NAJVYSSI LEVEL COROUTINES, ale nie pre vnorene COROUTINES.
	CCoroutineObjectWithAwaiterInterfaceFaulty					MyCoroutineObject=CoroutineObjectWithAwaiterInterfaceFaulty2(L"COROUTINE 2");

	wcout << L"\t" << CoroutineName << L" CALLED - PART 3." << endl;

	co_await MyCoroutineObject;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 4." << endl;

	suspend_always												Awaiter3{};

	co_await Awaiter3;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 5." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectWithAwaiterInterfaceFaulty(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectWithAwaiterInterfaceFaulty				MyCoroutineObject=CoroutineObjectWithAwaiterInterfaceFaulty1(L"COROUTINE 1");
		int														Index=0;

		while(true)
		{
			wcout << L"Test() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling1 CoroutineObjectScheduling1(int ID, int Counter)
{
	wcout << L"\tCOROUTINE [" << ID << L"] STARTED." << endl;

	for (int Index=1;Index<=Counter;++Index)
	{
		wcout << L"\tCOROUTINE [" << ID << L"] STEP [" << Index << L"]." << endl;

		ECoroutineSchedulingMode								SchedulingMode=ECoroutineSchedulingMode::E_LESS;
		CCoroutineObjectSchedulingAwaiter1						CustomAwaiter(SchedulingMode);

		co_await CustomAwaiter;
	}

	wcout << L"\tCOROUTINE [" << ID << L"] FINISHED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectScheduling1(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectSchedulingScheduler1					CoroutineScheduler;

		wcout << L"Test() - BEFORE COROUTINES SCHEDULED." << endl;

		// !!!!! Do SCHEDULER sa vlozia COROUTINES.
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling1(1,5));
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling1(2,2));
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling1(3,4));

		wcout << L"Test() - AFTER COROUTINES SCHEDULED." << endl;

		while(true)
		{
			bool												HaveCoroutinesToResume=CoroutineScheduler.ResumeCoroutine();

			if (HaveCoroutinesToResume==false)
			{
				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectScheduling2 CoroutineObjectScheduling2(int ID, int Counter)
{
	wcout << L"\tCOROUTINE [" << ID << L"] STARTED." << endl;

	for (int Index=1;Index<=Counter;++Index)
	{
		wcout << L"\tCOROUTINE [" << ID << L"] STEP [" << Index << L"]." << endl;

		ECoroutineSchedulingMode								SchedulingMode=ECoroutineSchedulingMode::E_LESS;

		wcout << L"\tCOROUTINE [" << ID << L"] is CALLING OPERATOR [OPERATOR co_await]." << endl;

		// !!!!! Ak ked EMUM [ECoroutineSchedulingMode] neimplementuje AWAITER INTERFACE, C++ vola METHOD [std::suspend_always await_transform(ECoroutineSchedulingMode SchedulingMode)], ktora vrati AWAITER OBJECT.
		co_await SchedulingMode;
	}

	wcout << L"\tCOROUTINE [" << ID << L"] FINISHED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectScheduling2(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectSchedulingScheduler2					CoroutineScheduler;

		wcout << L"Test() - BEFORE COROUTINES SCHEDULED." << endl;

		// !!!!! Do SCHEDULER sa vlozia COROUTINES.
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling2(1,5));
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling2(2,2));
		CoroutineScheduler.StartCoroutine(CoroutineObjectScheduling2(3,4));

		wcout << L"Test() - AFTER COROUTINES SCHEDULED." << endl;

		while(true)
		{
			bool												HaveCoroutinesToResume=CoroutineScheduler.ResumeCoroutine();

			if (HaveCoroutinesToResume==false)
			{
				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSymmetricTransfer CoroutineObjectSymmetricTransfer1(wstring CoroutineName)
{
	wcout << L"\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSymmetricTransfer CoroutineObjectSymmetricTransfer2(wstring CoroutineName)
{
	wcout << L"\t" << CoroutineName << L" CALLED - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t" << CoroutineName << L" CALLED - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectSymmetricTransfer(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectSymmetricTransfer						MyCoroutineObject1=CoroutineObjectSymmetricTransfer1(L"COROUTINE 1");
		CCoroutineObjectSymmetricTransfer						MyCoroutineObject2=CoroutineObjectSymmetricTransfer1(L"COROUTINE 2");

		coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>>	Coroutine2Handle=MyCoroutineObject2.GetCurrentHandle();

		// !!!!! Pre COROUTINE 1 sa nastavi COROUTINE HANDLE na COROUTINE 2, aby pokracovala po skonceni COROUTINE 1 okamzite bez vykonania SUSPEND pokracovala COROUTINE 2.
		// !!!!! Ak by sa v COROUTINE 1 nenastavil COROUTINE HANDLE na COROUTINE 2, tak medzi ukoncenim COROUTINE 1 a spustenim COROUTINE 2 bude vykonany SUSPEND.
		MyCoroutineObject1.SetNextCoroutineHandle(Coroutine2Handle);

		int														Index=0;

		while(true)
		{
			wcout << L"Test() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

			bool												CanResume=MyCoroutineObject1.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}

		while(true)
		{
			wcout << L"Test() - BEFORE COROUTINE RESUMED. INDEX [" << ++Index << L"]." << endl;

			bool												CanResume=MyCoroutineObject2.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED. INDEX [" << ++Index << L"]." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaitTransform CoroutineObjectAwaitTransform(void)
{
	wcout << L"\tCOROUTINE - PART 1." << endl;

	// !!! Pouzije sa CUSTOM TYPE, namiesto AWAITER TYPE. Konverziu na AWAITER TYPE vykonava METHOD [TAwaiter await_transform(TType Awaiter)].
	// !!! Pouzije CUSTOM VALUE, ktora je ulozena v METHOD [TAwaiter await_transform(TType Awaiter)] do FIELD PROMISE TYPE emuluje funkcionalitu OPERATOR [OPERATOR co_yield].
	co_await 100;

	wcout << L"\tCOROUTINE - PART 2." << endl;

	// !!! Pouzije sa CUSTOM TYPE, namiesto AWAITER TYPE. Konverziu na AWAITER TYPE vykonava METHOD [TAwaiter await_transform(TType Awaiter)].
	// !!! Pouzije CUSTOM VALUE, ktora je ulozena v METHOD [TAwaiter await_transform(TType Awaiter)] do FIELD PROMISE TYPE emuluje funkcionalitu OPERATOR [OPERATOR co_yield].
	co_await 123.456;

	wcout << L"\tCOROUTINE - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectAwaitTransform(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectAwaitTransform							MyCoroutineTask=CoroutineObjectAwaitTransform();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED. VALUE 1 [" << MyCoroutineTask.GetValue1() << L"] VALUE 2 [" << MyCoroutineTask.GetValue2() << L"]." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomOperatorCoAwait CoroutineObjectCustomOperatorCoAwait(void)
{
	wcout << L"\tCOROUTINE - PART 1." << endl;

	// !!!!! TYPE ma OVERLOADED OPERATOR [OPERATOR co_await], a preto OBJECT tohto TYPE moze byt pouzity ako PARAMETER OPERATOR [OPERATOR co_await].
	CCoroutineObjectCustomOperatorCoAwaitAwaiter				Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE - PART 2." << endl;

	// !!!!! TYPE ma OVERLOADED OPERATOR [OPERATOR co_await], a preto OBJECT tohto TYPE moze byt pouzity ako PARAMETER OPERATOR [OPERATOR co_await].
	CCoroutineObjectCustomOperatorCoAwaitAwaiter				Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCOROUTINE - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectCustomOperatorCoAwait(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectCustomOperatorCoAwait					MyCoroutineTask=CoroutineObjectCustomOperatorCoAwait();

		wcout << L"Test() - AFTER COROUTINE STARTED." << endl;

		while(true)
		{
			bool												CanResume=MyCoroutineTask.Resume();

			if (CanResume==true)
			{
				wcout << L"Test() - AFTER COROUTINE SUSPENDED." << endl;
			}
			else
			{
				wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;

				break;
			}
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool CoroutineObjectThreadPoolLevel2(int ID, int Step)
{
	wosyncstream												Stream{wcout};

	Stream << L"\t\tLEVEL 2 - ID [" << ID << L"] THREAD ID [" << get_id() << L"] STEP [" << Step << L"]." << endl;

	// !!! Pouzitie OPERATOR [OPERATOR co_return] spravi z FUNCTION COROUTINE.
	co_return;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool CoroutineObjectThreadPoolLevel1(int ID)
{
	{
		wosyncstream											Stream{wcout};

		Stream << L"\tLEVEL 1 - ID [" << ID << L"] THREAD ID [" << get_id() << L"] COROUTINE STARTED." << endl;
	}

	co_await CoroutineObjectThreadPoolLevel2(ID,1);

	{
		wosyncstream											Stream{wcout};

		Stream << L"\tLEVEL 1 - ID [" << ID << L"] THREAD ID [" << get_id() << L"] RESUME AFTER STEP 1." << endl;
	}

	co_await CoroutineObjectThreadPoolLevel2(ID,2);

	{
		wosyncstream											Stream{wcout};

		Stream << L"\tLEVEL 1 - ID [" << ID << L"] THREAD ID [" << get_id() << L"] RESUME AFTER STEP 2." << endl;
	}

	{
		wosyncstream											Stream{wcout};

		Stream << L"\tLEVEL 1 - ID [" << ID << L"] THREAD ID [" << get_id() << L"] COROUTINE FINISHED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectThreadPool(int NumberOfCoroutines)
{
	{
		wosyncstream											Stream{wcout};

		Stream << L"TEST - THREAD ID [" << get_id() << L"] TEST STARTED." << endl;
	}

	CCoroutineObjectThreadPoolThreadPool						ThreadPool(4);

	for(int Index=0;Index<NumberOfCoroutines;Index++)
	{
		{
			wosyncstream										Stream{wcout};

			Stream << L"TEST - THREAD ID [" << get_id() << L"] TASK [" << (Index+1) << L"] STARTING." << endl;
		}

		CCoroutineObjectThreadPool								CoroutineObject=CoroutineObjectThreadPoolLevel1(Index+1);

		ThreadPool.RunTask(move(CoroutineObject));
	}

	{
		wosyncstream											Stream{wcout};

		Stream << L"TEST - THREAD ID [" << get_id() << L"] TEST WAITING for COROUTINES to FINISH." << endl;
	}

	ThreadPool.WaitUntilAllCoroutinesFinished();

	{
		wosyncstream											Stream{wcout};

		Stream << L"TEST - THREAD ID [" << get_id() << L"] TEST FINISHED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectThreadPool1(void)
{
	PrintLineSeparator();

	TestCoroutineObjectThreadPool(1);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectThreadPool2(void)
{
	PrintLineSeparator();

	TestCoroutineObjectThreadPool(4);

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();
    
	//TestCoroutineMethodNonStatic();
	//TestCoroutineMethodStatic();
	//TestCoroutineLambda();
	//TestCoroutineLambdaWithCaptureOK();
	//TestCoroutineLambdaWithCaptureError();
	//TestCoroutineTracingLazyStart();
	//TestCoroutineTracingEagerStart();
	//TestCoroutinePromiseTypeWithParameters();
	//TestCoroutineMultiYield();
	//TestCoroutineMultiReturn();
	//TestCoroutineUnhandledException();
	//TestCoroutinePromiseTypeVoid();
	//TestCoroutineObjectHandledException1();
	//TestCoroutineObjectHandledException2();
	//TestCoroutineObjectCustomAllocation();
	//TestCoroutineObjectCustomAllocationWithParameters();
	//TestCoroutineObjectCustomAllocationSection();
	//TestCoroutineObjectCustomAllocationFailure();
	//TestCoroutineObjectStandardAwaiter();
	//TestCoroutineObjectWithAwaiterInterface();
	//TestCoroutineObjectWithAwaiterInterfaceFaulty();
	//TestCoroutineObjectScheduling1();
	//TestCoroutineObjectScheduling2();
	//TestCoroutineObjectSymmetricTransfer();
	//TestCoroutineObjectAwaitTransform();
	//TestCoroutineObjectCustomOperatorCoAwait();
	//TestCoroutineObjectThreadPool1();
	TestCoroutineObjectThreadPool2();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------