//----------------------------------------------------------------------------------------------------------------------
#include "COverloadingSignatures1.h"
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void TemplateOverloadingSignaturesShared(TType1 Value1, TType2 Value2)
{
	wcout << L"FUNCTION in TRANSLATION UNIT 1 CALLED. TYPE 1 [" << GetTypeInfoName<decltype(Value1)>() << L"] VALUE 1 [" << Value1 << L"] TYPE 2 [" << GetTypeInfoName<decltype(Value2)>() << L"] VALUE 2 [" << Value2 << L"]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void OverloadingSignaturesTest1(void)
{
	TemplateOverloadingSignaturesShared<int,int>(100,200);
}
//----------------------------------------------------------------------------------------------------------------------