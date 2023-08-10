//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionObjectTypeNonStaticMethod.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectTypeNonStaticMethod::CFunctionObjectTypeNonStaticMethod(int Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectTypeNonStaticMethod::~CFunctionObjectTypeNonStaticMethod(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CFunctionObjectTypeNonStaticMethod::NonStaticMethod(wstring Value1, wstring Value2, size_t Index, double Value)
{
	wcout << L"NON-STATIC METHOD - FIELD [" << MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"] INDEX [" << Index << "] VALUE [" << Value << "]." << endl;

	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------