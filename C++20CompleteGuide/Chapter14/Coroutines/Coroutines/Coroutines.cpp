//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <coroutine>
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers/MyDebug.h"
#include "Helpers/CString.h"
#include "Helpers/CException.h"
#include "CValue.h"
#include "CResumeCoroutineTask.h"
#include "CCoroutineObject1.h"
#include "CCoroutineObject2.h"
#include "CCoroutineObject3.h"
#include "CMovableCoroutineObject.h"
#include "CCoroutineObjectYield.h"
#include "CCoroutineObjectYieldIterator.h"
#include "CCoroutineObjectReturn.h"
#include "CAwaiterLog.h"
#include "CCoroutineObjectAwaiter.h"
#include "CCoroutineObjectAwaiterAutoStart.h"
#include "CCoroutineObjectDuplexCommunication.h"
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
// !!!!! COROUTINES MUSIA ako RETURN TYPE vracat TYPE COROUTINE OBJECT.
CResumeCoroutineTask SimpleCoroutine(int NumberOfIterations)
{
	wcout << L"\tSimpleCoroutine() - STARTED." << endl;

	for(int Index=1;Index<=NumberOfIterations;++Index)
	{
		wcout << L"\tSimpleCoroutine() - STEP [" << Index << L"] of STEPS [" << NumberOfIterations << L"]." << endl;

		// !!! CLASS [suspend_always] reprezentuje AWAITER OBJECT.
		suspend_always											Awaiter{};

		// !!! COROUTINE vykona cakanie na skoncenie AWAITER.
		co_await Awaiter;
	}

	wcout << L"\tSimpleCoroutine() - FINISHED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestSimpleCoroutine(void)
{
	PrintLineSeparator();

	wcout << L"Test() - BEFORE COROUTINE INITIALIZED." << endl;

	CResumeCoroutineTask										MyCoroutineTask=SimpleCoroutine(3);

	wcout << L"Test() - AFTER COROUTINE INITIALIZED." << endl;

	while(true)
	{
		wcout << L"Test() - BEFORE RESUME CALLED." << endl;

		// !!!!! CUSTOM METHOD COROUTINE OBJECT vykona RESUME a vracia informaciu ci COROUTINE uz skoncila.
		bool													CanResume=MyCoroutineTask.Resume();

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

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CResumeCoroutineTask MultipleCoroutines(int ID, int NumberOfIterations)
{
	wcout << L"\tMultipleCoroutines() ID [" << ID << L"] - STARTED." << endl;

	for(int Index=1;Index<=NumberOfIterations;++Index)
	{
		wcout << L"\tMultipleCoroutines() ID [" << ID << L"] - STEP [" << Index << L"] of STEPS [" << NumberOfIterations << L"]." << endl;

		suspend_always											Awaiter{};

		co_await Awaiter;
	}

	wcout << L"\tMultipleCoroutines() ID [" << ID << L"] - FINISHED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestMultipleCoroutines(void)
{
	PrintLineSeparator();

	wcout << L"Test() - BEFORE COROUTINES INITIALIZED." << endl;

	CResumeCoroutineTask										MyCoroutineTask1=MultipleCoroutines(1,2);
	CResumeCoroutineTask										MyCoroutineTask2=MultipleCoroutines(2,4);

	wcout << L"Test() - AFTER COROUTINES INITIALIZED." << endl;

	bool														Coroutine1Finished=false;
	bool														Coroutine2Finished=false;

	while(true)
	{
		wcout << L"Test() - BEFORE RESUME 1 CALLED." << endl;

		bool													CanResume1=MyCoroutineTask1.Resume();

		if (CanResume1==true)
		{
			wcout << L"Test() - AFTER COROUTINE 1 SUSPENDED." << endl;
		}
		else
		{
			if (Coroutine1Finished==false)
			{
				wcout << L"Test() - COROUTINE 1 FINISHED." << endl;
				Coroutine1Finished=true;
			}
		}

		wcout << L"Test() - BEFORE RESUME 2 CALLED." << endl;

		bool													CanResume2=MyCoroutineTask2.Resume();

		if (CanResume2==true)
		{
			wcout << L"Test() - AFTER COROUTINE 2 SUSPENDED." << endl;
		}
		else
		{
			if (Coroutine2Finished==false)
			{
				wcout << L"Test() - COROUTINE 2 FINISHED." << endl;
				Coroutine2Finished=true;
			}
		}

		if (Coroutine1Finished==true && Coroutine2Finished==true)
		{
			break;
		}
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETERS sa prenasaju BY-REFERENCE.
CResumeCoroutineTask CoroutineParametersByReference(const int& NumberOfIterations, const CValue& Value)
{
	wcout << L"\tCoroutineParametersByReference() - VALUE [" << Value.GetValue() << L"] - STARTED." << endl;

	for(int Index=1;Index<=NumberOfIterations;++Index)
	{
		wcout << L"\tCoroutineParametersByReference() - VALUE [" << Value.GetValue() << L"] - STEP [" << Index << L"] of STEPS [" << NumberOfIterations << L"]." << endl;

		suspend_always											Awaiter{};

		co_await Awaiter;
	}

	wcout << L"\tCoroutineParametersByReference() - VALUE [" << Value.GetValue() << L"] - FINISHED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineParametersByReferenceOK(void)
{
	PrintLineSeparator();

	wcout << L"Test() - BEFORE COROUTINE INITIALIZED." << endl;

	{
		int														NumberOfIterations=2;
		CValue													Value(L"TIMMY");

		// !!!!! Aj ked je PARAMETER COROUTINE TYPE [const int&] NESMIE SA pouzit LITERAL VALUE, pretoze jej platnost konci OKAMZITE po ukonceni prvej casti COROUTINE a pri volaniach dalsich casti COROUTINE by doslo k pristupu k neplatnej REFERENCE.
		CResumeCoroutineTask									MyCoroutineTask=CoroutineParametersByReference(NumberOfIterations,Value);

		wcout << L"Test() - AFTER COROUTINE INITIALIZED." << endl;

		while(true)
		{
			wcout << L"Test() - BEFORE RESUME CALLED." << endl;

			// !!!!! CUSTOM METHOD COROUTINE OBJECT vykona RESUME a vracia informaciu ci COROUTINE uz skoncila.
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
// !!!!! CODE sposobi RUNTIME ERROR.
/*
void TestCoroutineParametersByReferenceError(void)
{
	PrintLineSeparator();

	wcout << L"Test() - BEFORE COROUTINE INITIALIZED." << endl;

	// !!!!! CODE sposobi RUNTIME ERROR, pretoze LITERAL ARGUMENT [2] i ARGUMENT [CValue(L"TIMMY")] sa prenasaju ako BY-REFERENCE PARAMETERS, ktorych platnost skonci OKAMZITE po prvom volani COROUTINE. Dalsie volania COROUTINE uz budu pristupovat k NEPLATNYM REFERENCES.
	CResumeCoroutineTask										MyCoroutineTask=CoroutineParametersByReference(2,CValue(L"TIMMY"));

	wcout << L"Test() - AFTER COROUTINE INITIALIZED." << endl;

	while(true)
	{
		wcout << L"Test() - BEFORE RESUME CALLED." << endl;

		// !!!!! CUSTOM METHOD COROUTINE OBJECT vykona RESUME a vracia informaciu ci COROUTINE uz skoncila.
		bool													CanResume=MyCoroutineTask.Resume();

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

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CResumeCoroutineTask InnerCoroutine(void)
{
	wcout << L"\t\tInnerCoroutine() - PART 1." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\t\tInnerCoroutine() - PART 2." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CResumeCoroutineTask OuterCoroutineCallingCoroutineNotToFinish(void)
{
	wcout << L"\tOuterCoroutineCallingCoroutineNotToFinish() - START." << endl;

	CResumeCoroutineTask										MyCoroutineTask=InnerCoroutine();

	bool														CanResume=MyCoroutineTask.Resume();

	if (CanResume==true)
	{
		wcout << L"\tOuterCoroutineCallingCoroutineNotToFinish() - AFTER INNER COROUTINE SUSPENDED." << endl;
	}
	else
	{
		wcout << L"\tOuterCoroutineCallingCoroutineNotToFinish() - AFTER INNER COROUTINE FINISHED." << endl;
	}
	
	// !!!!! INNER COROUTINE ostane NEUKONCENA, pretoze sa nevolal dostatocny pocet RESUME.

	wcout << L"\tOuterCoroutineCallingCoroutineNotToFinish() - BEFORE SUSPEND." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tOuterCoroutineCallingCoroutineNotToFinish() - END." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineCallingCoroutineNotToFinish(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CResumeCoroutineTask									MyCoroutineTask=OuterCoroutineCallingCoroutineNotToFinish();

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
CResumeCoroutineTask OuterCoroutineCallingCoroutineToFinish(void)
{
	wcout << L"\tOuterCoroutineCallingCoroutineToFinish() - START." << endl;

	CResumeCoroutineTask										MyCoroutineTask=InnerCoroutine();

	while(true)
	{
		bool													CanResume=MyCoroutineTask.Resume();

		if (CanResume==true)
		{
			wcout << L"\tOuterCoroutineCallingCoroutineToFinish() - AFTER INNER COROUTINE SUSPENDED." << endl;
		}
		else
		{
			wcout << L"\tOuterCoroutineCallingCoroutineToFinish() - AFTER INNER COROUTINE FINISHED." << endl;

			break;
		}
	}
	
	wcout << L"\tOuterCoroutineCallingCoroutineToFinish() - BEFORE SUSPEND." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tOuterCoroutineCallingCoroutineToFinish() - END." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineCallingCoroutineToFinish(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CResumeCoroutineTask									MyCoroutineTask=OuterCoroutineCallingCoroutineToFinish();

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
CCoroutineObject1 CoroutineForCoroutineObject1(void)
{
	wcout << L"\tCoroutineForCoroutineObject1() - PART 1." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tCoroutineForCoroutineObject1() - PART 2." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObject1(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	CCoroutineObject1											MyCoroutineObject=CoroutineForCoroutineObject1();

	while(true)
	{
		bool													CanResume=MyCoroutineObject.Resume();

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

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObject2 CoroutineForCoroutineObject2(void)
{
	wcout << L"\tCoroutineForCoroutineObject2() - PART 1." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tCoroutineForCoroutineObject2() - PART 2." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObject2(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	CCoroutineObject2											MyCoroutineObject=CoroutineForCoroutineObject2();

	while(true)
	{
		bool													CanResume=MyCoroutineObject.Resume();

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

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObject3 CoroutineForCoroutineObject3(void)
{
	wcout << L"\tCoroutineForCoroutineObject3() - PART 1." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tCoroutineForCoroutineObject3() - PART 2." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObject3(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	CCoroutineObject3											MyCoroutineObject=CoroutineForCoroutineObject3();

	while(true)
	{
		bool													CanResume=MyCoroutineObject.Resume();

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

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CMovableCoroutineObject CoroutineForMovableCoroutineObject(void)
{
	wcout << L"\tCoroutineForMovableCoroutineObject() - PART 1." << endl;

	suspend_always												Awaiter{};

	co_await Awaiter;

	wcout << L"\tCoroutineForMovableCoroutineObject() - PART 2." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestMovableCoroutineObject(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CMovableCoroutineObject									MyCoroutineObject1=CoroutineForMovableCoroutineObject();

		// !!! Vola sa MOVE CONSTRUCTOR.
		CMovableCoroutineObject									MyCoroutineObject2=move(MyCoroutineObject1);

		// !!! Vola sa MOVE OPERATOR [OPERATOR=].
		MyCoroutineObject1=move(MyCoroutineObject2);

		// !!! Vola sa MOVE CONSTRUCTOR.
		CMovableCoroutineObject									MyCoroutineObject=move(MyCoroutineObject1);

		while(true)
		{
			bool												CanResume=MyCoroutineObject.Resume();

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
CCoroutineObjectYield<int> CoroutineReturningValues(void)
{
	wcout << L"\tCoroutineReturningValues() - PART 1." << endl;

	// !!! VALUE [10] je vratena do CALLER FUNCTION.
	co_yield 10;

	wcout << L"\tCoroutineReturningValues() - PART 2." << endl;

	// !!! VALUE [20] je vratena do CALLER FUNCTION.
	co_yield 20;

	wcout << L"\tCoroutineReturningValues() - PART 3." << endl;

	// !!! VALUE [30] je vratena do CALLER FUNCTION.
	co_yield 30;

	wcout << L"\tCoroutineReturningValues() - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineReturningValues(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectYield<int>								MyCoroutineObject=CoroutineReturningValues();

		while(true)
		{
			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				int												Value=MyCoroutineObject.GetValue();

				wcout << L"Test() - AFTER COROUTINE SUSPENDED. VALUE [" << Value << L"]." << endl;
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
CCoroutineObjectYieldIterator<int> CoroutineReturningValuesIterator(void)
{
	wcout << L"\tCoroutineReturningValuesIterator() - PART 1." << endl;

	co_yield 10;

	wcout << L"\tCoroutineReturningValuesIterator() - PART 2." << endl;

	co_yield 20;

	wcout << L"\tCoroutineReturningValuesIterator() - PART 3." << endl;

	co_yield 30;

	wcout << L"\tCoroutineReturningValuesIterator() - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineReturningValuesIterator(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectYieldIterator<int>						MyCoroutineObject=CoroutineReturningValuesIterator();

		for(const int& Value : MyCoroutineObject)
		{
			wcout << L"Test() - AFTER COROUTINE SUSPENDED. VALUE [" << Value << L"]." << endl;
		}

		wcout << L"Test() - AFTER COROUTINE FINISHED." << endl;
	}

	wcout << L"Test() - FINISHED." << endl;

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectReturn<int,double> CoroutineYieldingAndReturningValues(void)
{
	wcout << L"\tCoroutineYieldingAndReturningValues() - PART 1." << endl;

	co_yield 10;

	wcout << L"\tCoroutineYieldingAndReturningValues() - PART 2." << endl;

	co_yield 20;

	wcout << L"\tCoroutineYieldingAndReturningValues() - PART 3." << endl;

	co_yield 30;

	wcout << L"\tCoroutineYieldingAndReturningValues() - PART 4." << endl;

	co_return(123.456);
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineYieldingAndReturningValues(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectReturn<int,double>						MyCoroutineObject=CoroutineYieldingAndReturningValues();

		while(true)
		{
			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				int												Value=MyCoroutineObject.GetYieldValue();

				wcout << L"Test() - AFTER COROUTINE SUSPENDED. VALUE [" << Value << L"]." << endl;
			}
			else
			{
				double											Value=MyCoroutineObject.GetReturnValue();

				wcout << L"Test() - AFTER COROUTINE FINISHED. VALUE [" << Value << L"]." << endl;

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
CMovableCoroutineObject CoroutineWithCustomAwaiter(void)
{
	wcout << L"\tCoroutineWithCustomAwaiter() - PART 1." << endl;

	CAwaiterLog													Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCoroutineWithCustomAwaiter() - PART 2." << endl;

	CAwaiterLog													Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCoroutineWithCustomAwaiter() - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineWithCustomAwaiter(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CMovableCoroutineObject									MyCoroutineObject=CoroutineWithCustomAwaiter();

		while(true)
		{
			bool												CanResume=MyCoroutineObject.Resume();

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
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterOneLevel(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectAwaiterOneLevel(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		int														Index=0;
		CCoroutineObjectAwaiter									MyCoroutineObject=CoroutineCoroutineObjectWithAwaiterOneLevel(1);

		while(true)
		{
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
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterTwoLevels2(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterTwoLevels1(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	// !!! Vykona sa standardny SUSPEND.
	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	// !!!!! Zavola sa CUSTOM COROUTINE a vykona sa SUSPEND na CUSTOM AWAITER, ktory je zaroven aj SUB COROUTINE OBJECT.
	CCoroutineObjectAwaiter										Awaiter2=CoroutineCoroutineObjectWithAwaiterTwoLevels2(2);

	// !!!!! Vola sa METHOD [Awaiter2::await_suspend(CURRENT_COROUTINE)]. Teda vola sa METHOD [Awaiter2::await_suspend(CoroutineCoroutineObjectWithAwaiterTwoLevels1)].
	// !!!!! Cize, v tomto pripade sa vola METHOD [await_suspend()] COROUTINE OBJECT, ktory vytvorina SUB COROUTINE [CoroutineCoroutineObjectWithAwaiterTwoLevels2()], a ako PARAMETER je HANDLE na CURRENT COROUTINE, teda HANDLE na COROUTINE [CoroutineCoroutineObjectWithAwaiterTwoLevels1()].
	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;

	suspend_always												Awaiter3{};

	// !!! Vykona sa standardny SUSPEND.
	co_await Awaiter3;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectAwaiterTwoLevels(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		int														Index=0;
		CCoroutineObjectAwaiter									MyCoroutineObject=CoroutineCoroutineObjectWithAwaiterTwoLevels1(1);

		while(true)
		{
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
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterThreeLevels3(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterThreeLevels2(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	CCoroutineObjectAwaiter										Awaiter2=CoroutineCoroutineObjectWithAwaiterThreeLevels3(3);

	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;

	suspend_always												Awaiter3{};

	co_await Awaiter3;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter CoroutineCoroutineObjectWithAwaiterThreeLevels1(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	CCoroutineObjectAwaiter										Awaiter2=CoroutineCoroutineObjectWithAwaiterThreeLevels2(2);

	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;

	suspend_always												Awaiter3{};

	co_await Awaiter3;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectAwaiterThreeLevels(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		int														Index=0;
		CCoroutineObjectAwaiter									MyCoroutineObject=CoroutineCoroutineObjectWithAwaiterThreeLevels1(1);

		while(true)
		{
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
CCoroutineObjectAwaiterAutoStart CoroutineCoroutineObjectWithAwaiterAutoStart2(int ID)
{
	wcout << L"\t\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	co_await Awaiter1;

	wcout << L"\t\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	suspend_always												Awaiter2{};

	co_await Awaiter2;

	wcout << L"\t\tCOROUTINE [" << ID << L"] - PART 3." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiterAutoStart CoroutineCoroutineObjectWithAwaiterAutoStart1(int ID)
{
	wcout << L"\tCOROUTINE [" << ID << L"] - PART 1." << endl;

	suspend_always												Awaiter1{};

	// !!! Vykona sa standardny SUSPEND.
	co_await Awaiter1;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 2." << endl;

	// !!!!! Zavola sa CUSTOM COROUTINE a vykona sa SUSPEND na CUSTOM AWAITER, ktory je zaroven aj SUB COROUTINE OBJECT.
	CCoroutineObjectAwaiterAutoStart							Awaiter2=CoroutineCoroutineObjectWithAwaiterAutoStart2(2);

	// !!!!! Vola sa METHOD [Awaiter2::await_suspend(CURRENT_COROUTINE)]. Teda vola sa METHOD [Awaiter2::await_suspend(CoroutineCoroutineObjectWithAwaiterTwoLevels1)].
	// !!!!! Cize, v tomto pripade sa vola METHOD [await_suspend()] COROUTINE OBJECT, ktory vytvorila SUB COROUTINE [CoroutineCoroutineObjectWithAwaiterTwoLevels2()], a ako PARAMETER je HANDLE na CURRENT COROUTINE, teda HANDLE na COROUTINE [CoroutineCoroutineObjectWithAwaiterTwoLevels1()].
	// !!!!! COROUTINE NEBUDE SUSPENDED, pretoze METHOD [coroutine_handle<CCoroutineObjectAwaiterAutoStart::promise_type> CCoroutineObjectAwaiterAutoStart::await_suspend(coroutine_handle<TPromiseType> Handle)] vracia COROUTINE HANDLE, a ak METHOD vracia COROUTINE HANDLE, tak COROUTINE nie je SUSPENDED, ale spusti sa COROUTINE, ktore HANDLE bol vrateny v RETURN VALUE.
	co_await Awaiter2;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 3." << endl;

	suspend_always												Awaiter3{};

	// !!! Vykona sa standardny SUSPEND.
	co_await Awaiter3;

	wcout << L"\tCOROUTINE [" << ID << L"] - PART 4." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineObjectAwaiterAutoStart(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		int														Index=0;
		CCoroutineObjectAwaiterAutoStart						MyCoroutineObject=CoroutineCoroutineObjectWithAwaiterAutoStart1(1);

		while(true)
		{
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
CCoroutineObjectDuplexCommunication<int,double> CoroutineDuplexCommunication(void)
{
	wcout << L"\tCoroutineDuplexCommunication() - PART 1." << endl;

	// !!! VALUE [10] je vratena do CALLER FUNCTION.
	// !!!!! RETURN VALUE obsahuje VALUE, ktoru CALLER FUNCTION zaslala do COROUTINE.
	double														Value1=co_yield 10;

	wcout << L"\tCoroutineDuplexCommunication() - PART 2. VALUE [" << Value1 << L"]." << endl;

	// !!! VALUE [20] je vratena do CALLER FUNCTION.
	// !!!!! RETURN VALUE obsahuje VALUE, ktoru CALLER FUNCTION zaslala do COROUTINE.
	double														Value2=co_yield 20;

	wcout << L"\tCoroutineDuplexCommunication() - PART 3. VALUE [" << Value2 << L"]." << endl;

	// !!! VALUE [30] je vratena do CALLER FUNCTION.
	// !!!!! RETURN VALUE obsahuje VALUE, ktoru CALLER FUNCTION zaslala do COROUTINE.
	double														Value3=co_yield 30;

	wcout << L"\tCoroutineDuplexCommunication() - PART 4. VALUE [" << Value3 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestCoroutineDuplexCommunication(void)
{
	PrintLineSeparator();

	wcout << L"Test() - STARTED." << endl;

	{
		CCoroutineObjectDuplexCommunication<int,double>			MyCoroutineObject=CoroutineDuplexCommunication();
		int														Counter=1;

		while(true)
		{
			bool												CanResume=MyCoroutineObject.Resume();

			if (CanResume==true)
			{
				int												Value=MyCoroutineObject.GetValueFromCoroutine();

				wcout << L"Test() - AFTER COROUTINE SUSPENDED. VALUE [" << Value << L"]." << endl;

				// !!!!! CALLER FUNCTION zasle do COROUTINE VALUE.
				MyCoroutineObject.SetValueToCoroutine(double(Value+(Counter*0.111)));

				Counter++;
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
int main(void)
{
	SafeMain();

	//TestSimpleCoroutine();
	//TestMultipleCoroutines();
	//TestCoroutineParametersByReferenceOK();
	//TestCoroutineParametersByReferenceError();
	//TestCoroutineCallingCoroutineNotToFinish();
	//TestCoroutineCallingCoroutineToFinish();
	//TestCoroutineObject1();
	//TestCoroutineObject2();
	//TestCoroutineObject3();
	//TestMovableCoroutineObject();
	//TestCoroutineReturningValues();
	//TestCoroutineReturningValuesIterator();
	//TestCoroutineYieldingAndReturningValues();
	//TestCoroutineWithCustomAwaiter();
	//TestCoroutineObjectAwaiterOneLevel();
	//TestCoroutineObjectAwaiterTwoLevels();
	TestCoroutineObjectAwaiterThreeLevels();
	//TestCoroutineObjectAwaiterAutoStart();
	//TestCoroutineDuplexCommunication();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------