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
#include "SOperationAddConst.h"
#include "SOperationSmallerThan.h"
#include "CTypeList.h"
#include "CTypeListPushFront.h"
#include "CTypeListPopFront.h"
#include "CTypeListFront.h"
#include "CTypeListFindElement.h"
#include "CTypeListIsEmpty.h"
#include "CTypeListGetLargestType.h"
#include "CTypeListPushBack1.h"
#include "CTypeListPushBack2.h"
#include "CTypeListReverse.h"
#include "CTypeListPopBack.h"
#include "CTypeListTransform.h"
#include "CTypeListAccumulate.h"
#include "CTypeListAccumulateGetLargestType.h"
#include "CTypeListInsertionSort.h"
#include "CCompileTimeValue1.h"
#include "CCompileTimeValue2.h"
#include "CCompileTimeValueMultiply1.h"
#include "CCompileTimeValueMultiply2.h"
#include "CValueList1.h"
#include "CValueList2.h"
#include "CCompileTimeValueGreaterThan1.h"
#include "CCompileTimeValueGreaterThan2.h"
#include "CTypeListPackExpansionTransform.h"
#include "CTypeListPackExpansionSelect.h"
#include "CConsTypeList.h"
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
void TestTypeListPushFront(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListPushFront<InputType,int>;

		wcout << L"PUSH FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int>;
		using													OutputType=CTypeListPushFront<InputType,double>;

		wcout << L"PUSH FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPopFront(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<int>;
		using													OutputType=CTypeListPopFront<InputType>;

		wcout << L"POP FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListPopFront<InputType>;

		wcout << L"POP FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;

		// !!!!! COMPILER hodi ERROR.
		using													OutputType=CTypeListPopFront<InputType>;

		wcout << L"POP FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListFront(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<int>;
		using													OutputType=CTypeListFront<InputType>;

		wcout << L"FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListFront<InputType>;

		wcout << L"FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;

		// !!!!! COMPILER hodi ERROR.
		using													OutputType=CTypeListFront<InputType>;

		wcout << L"FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListFindElement(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;

		constexpr unsigned int									INDEX=0;

		using													OutputType=CTypeListFindElement<InputType,INDEX>;

		wcout << L"FIND ELEMENT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] INDEX [" << INDEX << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;

		constexpr unsigned int									INDEX=1;

		using													OutputType=CTypeListFindElement<InputType,INDEX>;

		wcout << L"FIND ELEMENT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] INDEX [" << INDEX << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;

		constexpr unsigned int									INDEX=2;

		using													OutputType=CTypeListFindElement<InputType,INDEX>;

		wcout << L"FIND ELEMENT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] INDEX [" << INDEX << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;

		constexpr unsigned int									INDEX=2;

		// !!!!! COMPILER hodi ERROR.
		using													OutputType=CTypeListFindElement<InputType,INDEX>;

		wcout << L"FIND ELEMENT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] INDEX [" << INDEX << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}
	*/

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListIsEmpty(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;

		constexpr bool											IsEmpty=CTypeListIsEmpty<InputType>;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] IS EMPTY [" << IsEmpty << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;

		constexpr bool											IsEmpty=CTypeListIsEmpty<InputType>;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] IS EMPTY [" << IsEmpty << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListGetLargestType(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<int,CString,double>;
		using													OutputType=CTypeListGetLargestType<InputType>;

		wcout << L"GET LARGEST TYPE - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,long double,int>;
		using													OutputType=CTypeListGetLargestType<InputType>;

		wcout << L"GET LARGEST TYPE - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<long double,bool,int>;
		using													OutputType=CTypeListGetLargestType<InputType>;

		wcout << L"GET LARGEST TYPE - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPushBack1(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListPushBack1<InputType,int>;

		wcout << L"PUSH BACK 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int>;
		using													OutputType=CTypeListPushBack1<InputType,double>;

		wcout << L"PUSH BACK 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPushBack2(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListPushBack2<InputType,int>;

		wcout << L"PUSH BACK 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int>;
		using													OutputType=CTypeListPushBack2<InputType,double>;

		wcout << L"PUSH BACK 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListReverse(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListReverse<InputType>;

		wcout << L"REVERSE - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListReverse<InputType>;

		wcout << L"REVERSE - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPopBack(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<int>;
		using													OutputType=CTypeListPopBack<InputType>;

		wcout << L"POP BACK - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListPopBack<InputType>;

		wcout << L"POP BACK - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListTransform(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListTransform<InputType,SOperationAddConstType>;

		wcout << L"TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<const CString,int,const double>;
		using													OutputType=CTypeListTransform<InputType,SOperationAddConstType>;

		wcout << L"TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListTransform<InputType,SOperationAddConstType>;

		wcout << L"TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListAccumulate(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;

		// !!!!! Vykona REVERSE vsetkych TYPES.
		using													OutputType=CTypeListAccumulate<InputType,CTypeListPushFrontType,CTypeList<>>;

		wcout << L"ACCUMULATE (REVERSE) - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListAccumulateGetLargestType<InputType>;

		wcout << L"ACCUMULATE (GET LARGEST TYPE) - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,int,long double,double>;
		using													OutputType=CTypeListAccumulateGetLargestType<InputType>;

		wcout << L"ACCUMULATE (GET LARGEST TYPE) - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListInsertionSort(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,int,long double,double>;
		using													OutputType=CTypeListInsertionSort<InputType,SOperationSmallerThanType>;

		wcout << L"INSERATION SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<long double,double,bool,int>;
		using													OutputType=CTypeListInsertionSort<InputType,SOperationSmallerThanType>;

		wcout << L"INSERATION SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<long double,double,int,bool>;
		using													OutputType=CTypeListInsertionSort<InputType,SOperationSmallerThanType>;

		wcout << L"INSERATION SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListCompileTimeValues(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CCompileTimeValue1<int,2>,CCompileTimeValue1<int,3>,CCompileTimeValue1<int,5>,CCompileTimeValue1<int,7>,CCompileTimeValue1<int,11>>;
		using													OutputType=CTypeListAccumulate<InputType,CCompileTimeValueMultiplyType1,CCompileTimeValue1<int,1>>;

		wcout << L"COMPILE TIME VALUES 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<CCompileTimeValue2<2>,CCompileTimeValue2<3>,CCompileTimeValue2<5>,CCompileTimeValue2<7>,CCompileTimeValue2<11>>;
		using													OutputType=CTypeListAccumulate<InputType,CCompileTimeValueMultiplyType2,CCompileTimeValue2<1>>;

		wcout << L"COMPILE TIME VALUES 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestValueList(void)
{
	PrintLineSeparator();

	{
		using													InputType=CValueList1<int,6,2,4,9,5,2,1,7>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType1>;

		wcout << L"VALUE LIST 1 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList1<int,1,2,3,4,5,6,7,8,9>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType1>;

		wcout << L"VALUE LIST 1 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList1<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType1>;

		wcout << L"VALUE LIST 1 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList1<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListPushBack1<InputType,CCompileTimeValue1<int,10>>;

		wcout << L"VALUE LIST 1 - PUSH BACK 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList1<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListPushBack2<InputType,CCompileTimeValue1<int,10>>;

		wcout << L"VALUE LIST 1 - PUSH BACK 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList2<int,6,2,4,9,5,2,1,7>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType2>;

		wcout << L"VALUE LIST 2 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList2<int,1,2,3,4,5,6,7,8,9>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType2>;

		wcout << L"VALUE LIST 2 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList2<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListInsertionSort<InputType,CCompileTimeValueGreaterThanType2>;

		wcout << L"VALUE LIST 2 - SORT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList2<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListPushBack1<InputType,CCompileTimeValue2<10>>;

		wcout << L"VALUE LIST 2 - PUSH BACK 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CValueList2<int,9,8,7,6,5,4,3,2,1>;
		using													OutputType=CTypeListPushBack2<InputType,CCompileTimeValue2<10>>;

		wcout << L"VALUE LIST 2 - PUSH BACK 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPackExpansionTransform(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<CString,int,double>;
		using													OutputType=CTypeListPackExpansionTransform<InputType,SOperationAddConstType>;

		wcout << L"PACK EXPANSION TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<const CString,int,const double>;
		using													OutputType=CTypeListPackExpansionTransform<InputType,SOperationAddConstType>;

		wcout << L"PACK EXPANSION TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<>;
		using													OutputType=CTypeListPackExpansionTransform<InputType,SOperationAddConstType>;

		wcout << L"PACK EXPANSION TRANSFORM - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTypeListPackExpansionSelect(void)
{
	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,short,int,long,double,long double,CString>;
		using													OutputType=CTypeListPackExpansionSelect<InputType,CValueList1<unsigned int,0,2,4,6>>;

		wcout << L"PACK EXPANSION SELECT 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,short,int,long,double,long double,CString>;
		using													OutputType=CTypeListPackExpansionSelect<InputType,CValueList1<unsigned int,6,5,4,3,2,1,0>>;

		wcout << L"PACK EXPANSION SELECT 1 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,short,int,long,double,long double,CString>;
		using													OutputType=CTypeListPackExpansionSelect<InputType,CValueList2<unsigned int,0,2,4,6>>;

		wcout << L"PACK EXPANSION SELECT 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CTypeList<bool,short,int,long,double,long double,CString>;
		using													OutputType=CTypeListPackExpansionSelect<InputType,CValueList2<unsigned int,6,5,4,3,2,1,0>>;

		wcout << L"PACK EXPANSION SELECT 2 - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestConsTypeList(void)
{
	PrintLineSeparator();

	{
		using													InputType=CConsTypeList<int,CConsTypeList<char,CConsTypeList<short,CConsTypeList<double>>>>;
		using													OutputType=CConsTypeListPushFront<InputType,CString>;

		wcout << L"PUSH FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CConsTypeList<int,CConsTypeList<char,CConsTypeList<short,CConsTypeList<double>>>>;
		using													OutputType=CConsTypeListPopFront<InputType>;

		wcout << L"POP FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CConsTypeList<int,CConsTypeList<char,CConsTypeList<short,CConsTypeList<double>>>>;
		using													OutputType=CConsTypeListFront<InputType>;

		wcout << L"FRONT - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] OUTPUT TYPE [" << GetTypeInfoName<OutputType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CConsTypeList<int,CConsTypeList<char,CConsTypeList<short,CConsTypeList<double>>>>;
		constexpr bool											Value=CConsTypeListIsEmptyType<InputType>::VALUE;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] IS EMPTY [" << Value << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													InputType=CConsTypeListNull;
		constexpr bool											Value=CConsTypeListIsEmptyType<InputType>::VALUE;

		wcout << L"IS EMPTY - INPUT TYPE [" << GetTypeInfoName<InputType>() << L"] IS EMPTY [" << Value << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypeListPushFront();
	//TestTypeListPopFront();
	//TestTypeListFront();
	//TestTypeListFindElement();
	//TestTypeListIsEmpty();
	//TestTypeListGetLargestType();
	//TestTypeListPushBack1();
	//TestTypeListPushBack2();
	//TestTypeListReverse();
	//TestTypeListPopBack();
	//TestTypeListTransform();
	//TestTypeListAccumulate();
	//TestTypeListInsertionSort();
	//TestTypeListCompileTimeValues();
	//TestValueList();
	//TestTypeListPackExpansionTransform();
	//TestTypeListPackExpansionSelect();
	TestConsTypeList();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------