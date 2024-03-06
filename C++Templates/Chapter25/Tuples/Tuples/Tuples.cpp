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
#include "CTuple.h"
#include "CDumpType.h"
#include "CTupleTypeListInterface.h"
#include "CTuplePushFront.h"
#include "CTuplePushBack.h"
#include "CTuplePopFront.h"
#include "CTupleReverse.h"
#include "CTuplePopBack.h"
#include "CCopyCounter.h"
#include "CValueList.h"
#include "CMakeIndexListType.h"
#include "CTupleReverseIndexList.h"
#include "CTupleSelect.h"
#include "CReplicatedIndexListType.h"
#include "CTupleSplat.h"
#include "SOperationSmallerThan.h"
#include "CTupleSort.h"
#include "CTupleApply.h"
#include "CEmptyClass1.h"
#include "CEmptyClass2.h"
#include "CTupleEBCO.h"
#include "CTupleEBCOGet.h"
#include "CTupleEBCOOperatorPrint.h"
#include "CTupleEBCOGetFast.h"
#include "CCompileTimeValueOperatorLiteral.h"
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
void TestTuple(void)
{
	PrintLineSeparator();

	{
		CTuple<>												HelperObject1;
		CTuple<double>											HelperObject2(123.456,HelperObject1);
		CTuple<int,double>										HelperObject3(100,HelperObject2);
		CTuple<CString,int,double>								Object(L"Timmy",HelperObject3);

		wcout << L"HEAD [" << Object.GetHead() << L"]." << endl;
		wcout << L"TAIL.HEAD [" << Object.GetTail().GetHead() << L"]." << endl;
		wcout << L"TAIL.TAIL.HEAD [" << Object.GetTail().GetTail().GetHead() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleGet(void)
{
	PrintLineSeparator();

	{
		CTuple<>												HelperObject1;
		CTuple<double>											HelperObject2(123.456,HelperObject1);
		CTuple<int,double>										HelperObject3(100,HelperObject2);
		CTuple<CString,int,double>								Object(L"Timmy",HelperObject3);

		wcout << L"GET 0 [" << TupleGet<0>(Object) << L"]." << endl;
		wcout << L"GET 1 [" << TupleGet<1>(Object) << L"]." << endl;
		wcout << L"GET 2 [" << TupleGet<2>(Object) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<>												HelperObject1;
		CTuple<double>											HelperObject2(123.456,HelperObject1);
		CTuple<int,double>										HelperObject3(100,HelperObject2);
		CTuple<CString,int,double>								Object(L"Timmy",HelperObject3);

		wcout << L"GET 0 [" << Object.Get<0>() << L"]." << endl;
		wcout << L"GET 1 [" << Object.Get<1>() << L"]." << endl;
		wcout << L"GET 2 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleConstructors(void)
{
	PrintLineSeparator();

	{
		CTuple<>												HelperObject1;
		CTuple<double>											HelperObject2(123.456,HelperObject1);
		CTuple<int,double>										HelperObject3(100,HelperObject2);
		CTuple<CDumpType,int,double>							Object(CDumpType(L"Timmy"),HelperObject3);

		wcout << L"CONSTRUCTOR 1 - VALUE 1 [" << Object.Get<0>() << L"] VALUE 2 [" << Object.Get<1>() << L"] VALUE 3 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CDumpType,int,double>							Object(CString(L"Timmy"),100,123.456);

		wcout << L"CONSTRUCTOR 2 - VALUE 1 [" << Object.Get<0>() << L"] VALUE 2 [" << Object.Get<1>() << L"] VALUE 3 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CDumpType,int,double>							OriginalObject(CString(L"Timmy"),100,123.456);
		CTuple<CDumpType,int,double>							Object(OriginalObject);

		wcout << L"CONSTRUCTOR 3 - VALUE 1 [" << Object.Get<0>() << L"] VALUE 2 [" << Object.Get<1>() << L"] VALUE 3 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CDumpType,int,double>							Object=MakeTuple(CDumpType(CString(L"Timmy")),100,123.456);

		wcout << L"MAKE TUPLE 1 - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE 1 [" << Object.Get<0>() << L"] VALUE 2 [" << Object.Get<1>() << L"] VALUE 3 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! Pretoze sa robi DECAY z LITARAL STRING sa stane POINTER na STRING.
		CTuple<const wchar_t*,int,double>						Object=MakeTuple(L"Timmy",100,123.456);

		wcout << L"MAKE TUPLE 2 - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE 1 [" << Object.Get<0>() << L"] VALUE 2 [" << Object.Get<1>() << L"] VALUE 3 [" << Object.Get<2>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleOperatorEqual(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								Object1(CString(L"Timmy"),100,123.456);
		CTuple<CString,int,double>								Object2(CString(L"Timmy"),100,123.456);
		bool													Result=(Object1==Object2);

		wcout << L"OBJECT 1 - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] - VALUE 1 [" << Object1.Get<0>() << L"] VALUE 2 [" << Object1.Get<1>() << L"] VALUE 3 [" << Object1.Get<2>() << L"]." << endl;
		wcout << L"OBJECT 2 - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] - VALUE 1 [" << Object2.Get<0>() << L"] VALUE 2 [" << Object2.Get<1>() << L"] VALUE 3 [" << Object2.Get<2>() << L"]." << endl;
		wcout << L"RESULT - TYPE [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double>								Object1(CString(L"Timmy"),100,123.456);
		CTuple<CString,int,double>								Object2(CString(L"Timmy"),200,123.456);
		bool													Result=(Object1==Object2);

		wcout << L"OBJECT 1 - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] - VALUE 1 [" << Object1.Get<0>() << L"] VALUE 2 [" << Object1.Get<1>() << L"] VALUE 3 [" << Object1.Get<2>() << L"]." << endl;
		wcout << L"OBJECT 2 - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] - VALUE 1 [" << Object2.Get<0>() << L"] VALUE 2 [" << Object2.Get<1>() << L"] VALUE 3 [" << Object2.Get<2>() << L"]." << endl;
		wcout << L"RESULT - TYPE [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double>								Object1(CString(L"Timmy"),100,123.456);
		CTuple<CString,double,double>							Object2(CString(L"Timmy"),100,123.456);
		bool													Result=(Object1==Object2);

		wcout << L"OBJECT 1 - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"] - VALUE 1 [" << Object1.Get<0>() << L"] VALUE 2 [" << Object1.Get<1>() << L"] VALUE 3 [" << Object1.Get<2>() << L"]." << endl;
		wcout << L"OBJECT 2 - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"] - VALUE 1 [" << Object2.Get<0>() << L"] VALUE 2 [" << Object2.Get<1>() << L"] VALUE 3 [" << Object2.Get<2>() << L"]." << endl;
		wcout << L"RESULT - TYPE [" << Result << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<>												Object1;
		CTuple<>												Object2;
		bool													Result=(Object1==Object2);

		wcout << L"OBJECT 1 - TYPE [" << GetTypeInfoName<decltype(Object1)>() << L"]." << endl;
		wcout << L"OBJECT 2 - TYPE [" << GetTypeInfoName<decltype(Object2)>() << L"]." << endl;
		wcout << L"RESULT - TYPE [" << Result << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleOperatorPrint(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								Object(CString(L"Timmy"),100,123.456);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString>											Object(CString(L"Timmy"));

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<>												Object;

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [" << Object << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleTypeListInterface(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTuple<>;

		constexpr bool											VALUE=CTupleTypeListIsEmpty<InputType>::VALUE;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] VALUE [" << VALUE << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTuple<CString,int,double>;

		constexpr bool											VALUE=CTupleTypeListIsEmpty<InputType>::VALUE;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] VALUE [" << VALUE << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTuple<CString,int,double>;
		using													OutputType=CTupleTypeListFrontType<InputType>::TYPE;

		wcout << L"FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTuple<CString,int,double>;
		using													OutputType=CTupleTypeListPushFrontType<InputType,bool>::TYPE;

		wcout << L"PUSH FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTuple<CString,int,double>;
		using													OutputType=CTupleTypeListPushBackType<InputType,bool>::TYPE;

		wcout << L"PUSH BACK - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTuple<CString,int,double>;
		using													OutputType=CTupleTypeListPopFrontType<InputType>::TYPE;

		wcout << L"POP FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTuplePushFront(void)
{
	PrintLineSeparator();

	{
		CTuple<>												InputObject;
		CTuple<bool>											OutputObject=TuplePushFront(InputObject,true);

		wcout << L"PUSH FRONT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<bool,CString,int,double>							OutputObject=TuplePushFront(InputObject,true);

		wcout << L"PUSH FRONT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTuplePushBack(void)
{
	PrintLineSeparator();

	{
		CTuple<>												InputObject;
		CTuple<bool>											OutputObject=TuplePushBack(InputObject,true);

		wcout << L"PUSH BACK - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<CString,int,double,bool>							OutputObject=TuplePushBack(InputObject,true);

		wcout << L"PUSH BACK - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTuplePopFront(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<int,double>										OutputObject=TuplePopFront(InputObject);

		wcout << L"POP FRONT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<bool>											InputObject(true);
		CTuple<>												OutputObject=TuplePopFront(InputObject);

		wcout << L"POP FRONT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleReverse(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<double,int,CString>								OutputObject=TupleReverse(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<>												InputObject;
		CTuple<>												OutputObject=TupleReverse(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CCopyCounter<0>,CCopyCounter<1>,CCopyCounter<2>,CCopyCounter<3>,CCopyCounter<4>>	InputObject;
		CTuple<CCopyCounter<4>,CCopyCounter<3>,CCopyCounter<2>,CCopyCounter<1>,CCopyCounter<0>>	OutputObject=TupleReverse(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"]." << endl;

		wcout << L"CCopyCounter<0> - NUMBER OF COPIES [" << CCopyCounter<0>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<1> - NUMBER OF COPIES [" << CCopyCounter<1>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<2> - NUMBER OF COPIES [" << CCopyCounter<2>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<3> - NUMBER OF COPIES [" << CCopyCounter<3>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<4> - NUMBER OF COPIES [" << CCopyCounter<4>::GetCopies() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTuplePopBack(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<CString,int>										OutputObject=TuplePopBack(InputObject);

		wcout << L"POP BACK - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString>											InputObject(CString(L"Timmy"));
		CTuple<>												OutputObject=TuplePopBack(InputObject);

		wcout << L"POP BACK - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleReverseIndexList(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double>								InputObject(CString(L"Timmy"),100,123.456);
		CTuple<double,int,CString>								OutputObject=TupleReverseIndexList(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<>												InputObject;
		CTuple<>												OutputObject=TupleReverse(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CCopyCounter<0>,CCopyCounter<1>,CCopyCounter<2>,CCopyCounter<3>,CCopyCounter<4>>	InputObject;
		CTuple<CCopyCounter<4>,CCopyCounter<3>,CCopyCounter<2>,CCopyCounter<1>,CCopyCounter<0>>	OutputObject=TupleReverse(InputObject);

		wcout << L"REVERSE - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"]." << endl;

		wcout << L"CCopyCounter<0> - NUMBER OF COPIES [" << CCopyCounter<0>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<1> - NUMBER OF COPIES [" << CCopyCounter<1>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<2> - NUMBER OF COPIES [" << CCopyCounter<2>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<3> - NUMBER OF COPIES [" << CCopyCounter<3>::GetCopies() << L"]." << endl;
		wcout << L"CCopyCounter<4> - NUMBER OF COPIES [" << CCopyCounter<4>::GetCopies() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleSelect(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							InputObject(CString(L"Timmy"),100,123.456,false);
		CTuple<CString,double>									OutputObject=TupleSelect(InputObject,CValueList<size_t,0,2>{});

		wcout << L"SELECT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							InputObject(CString(L"Timmy"),100,123.456,false);
		CTuple<bool,int,double,CString,CString>					OutputObject=TupleSelect(InputObject,CValueList<size_t,3,1,2,0,0>{});

		wcout << L"SELECT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleSplat(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							InputObject(CString(L"Timmy"),100,123.456,false);
		CTuple<CString,CString,CString,CString>					OutputObject=TupleSplat<0,4>(InputObject);

		wcout << L"SPLAT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							InputObject(CString(L"Timmy"),100,123.456,false);
		CTuple<double,double,double,double,double>				OutputObject=TupleSplat<2,5>(InputObject);

		wcout << L"SPLAT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleSort(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							InputObject(CString(L"Timmy"),100,123.456,false);
		CTuple<bool,int,double,CString>							OutputObject=TupleSort<SOperationSmallerThanType>(InputObject);

		wcout << L"SORT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<long double,double,long,int,bool>				InputObject(123.456,78.9,1000,100,false);
		CTuple<bool,int,long,double,long double>				OutputObject=TupleSort<SOperationSmallerThanType>(InputObject);

		wcout << L"SORT - INPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(InputObject)>() << L"] - VALUE [" << InputObject << L"] - OUTPUT OBJECT - TYPE [" << GetTypeInfoName<decltype(OutputObject)>() << L"] - VALUE [" << OutputObject << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
void TuplePrintInternal(size_t Index, wstringstream& Stream, TType Value, TTypes... Values)
{
	if (Index>1)
	{
		Stream << L' ';
	}

	Stream << L"INDEX [";

	Stream << Index;

	Stream << L"] VALUE [";

	Stream << Value;

	Stream << L"]";

	if constexpr (sizeof...(TTypes)>0)
	{
		TuplePrintInternal(Index+1,Stream,Values...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void TuplePrint(TTypes... Values)
{
	wstringstream												Stream;

	Stream << L"PRINT - OBJECT - [";

	if constexpr (sizeof...(Values)>0)
	{
		TuplePrintInternal(1,Stream,Values...);
	}
	
	Stream << L"].";

	wcout << Stream.str() << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void TestTupleApply(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							Object(CString(L"Timmy"),100,123.456,false);

		TupleApply<void(*)(CString,int,double,bool)>(TuplePrint,Object);
	}

	PrintLineSeparator();

	{
		CTuple<>												Object;

		TupleApply<void(*)(void)>(TuplePrint,Object);
	}

	/*
	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze nevie vykonat DEDUCTION CALLBACK FUNCTION z VARIADIC TEMPLATE FUNCTION.
	{
		CTuple<CString,int,double,bool>							Object(CString(L"Timmy"),100,123.456,false);

		TupleApply(TuplePrint,Object);
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleEBCO(void)
{
	PrintLineSeparator();

	{
		CTupleEBCO<CEmptyClass1,CEmptyClass1,CEmptyClass2,CEmptyClass2>	Object;

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] SIZEOF [" << sizeof(Object) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTupleEBCO<CEmptyClass1,CEmptyClass1,CEmptyClass2,CEmptyClass2,int,double>	Object;

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] SIZEOF [" << sizeof(Object) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTupleEBCO<CString,int,double,bool>						Object(CString(L"Timmy"),100,123.456,false);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] SIZEOF [" << sizeof(Object) << L"] - VALUE [" << Object << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleEBCOGetFast(void)
{
	PrintLineSeparator();

	{
		CTupleEBCO<CString,int,double,bool>						Object(CString(L"Timmy"),100,123.456,false);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [0] [" << TupleGetFast<0>(Object) << L"] VALUE [1] [" << TupleGetFast<1>(Object) << L"] VALUE [2] [" << TupleGetFast<2>(Object) << L"] VALUE [3] [" << TupleGetFast<3>(Object) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTupleEBCO<CString,CString,int>							Object(L"Timmy",L"Anderson",12);

		wcout << L"OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE [0] [" << TupleGetFast<0>(Object) << L"] VALUE [1] [" << TupleGetFast<1>(Object) << L"] VALUE [2] [" << TupleGetFast<2>(Object) << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTupleOperatorSubscript(void)
{
	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							Object(CString(L"Timmy"),100,123.456,false);
		auto													Value1=Object[CCompileTimeValue<size_t,0>{}];
		auto													Value2=Object[CCompileTimeValue<size_t,1>{}];
		auto													Value3=Object[CCompileTimeValue<size_t,2>{}];
		auto													Value4=Object[CCompileTimeValue<size_t,3>{}];

		wcout << L"OPERATOR[] - OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] VALUE 4 [" << Value4 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,CString,int>								Object(L"Timmy",L"Anderson",12);
		auto													Value1=Object[CCompileTimeValue<size_t,0>{}];
		auto													Value2=Object[CCompileTimeValue<size_t,1>{}];
		auto													Value3=Object[CCompileTimeValue<size_t,2>{}];

		wcout << L"OPERATOR[] - OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CTuple<CString,int,double,bool>							Object(CString(L"Timmy"),100,123.456,false);

		// !!!!! Pouzije sa LITERAL OPERATOR.
		auto													Value1=Object[0_c];
		auto													Value2=Object[1_c];
		auto													Value3=Object[2_c];
		auto													Value4=Object[3_c];

		wcout << L"OPERATOR[] - OBJECT - TYPE [" << GetTypeInfoName<decltype(Object)>() << L"] - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] VALUE 3 [" << Value3 << L"] VALUE 4 [" << Value4 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTuple();
	//TestTupleGet();
	//TestTupleConstructors();
	//TestTupleOperatorEqual();
	//TestTupleOperatorPrint();
	//TestTupleTypeListInterface();
	//TestTuplePushFront();
	//TestTuplePushBack();
	//TestTuplePopFront();
	//TestTupleReverse();
	//TestTuplePopBack();
	//TestTupleReverseIndexList();
	//TestTupleSelect();
	//TestTupleSplat();
	//TestTupleSort();
	//TestTupleApply();
	//TestTupleEBCO();
	//TestTupleEBCOGetFast();
	TestTupleOperatorSubscript();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------