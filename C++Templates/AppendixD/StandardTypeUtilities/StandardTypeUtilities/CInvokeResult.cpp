//----------------------------------------------------------------------------------------------------------------------
#include "CInvokeResult.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wstring CInvokeResult::operator()(int Value1, double Value2) const
{
	wcout << "METHOD [void operator()(int Value1, double Value2) const] CALLED. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << endl;

	return(L"TIMMY");
}
//----------------------------------------------------------------------------------------------------------------------