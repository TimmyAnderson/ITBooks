//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionObjectTypeConversionToReferenceToFunction.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CFunctionObjectTypeConversionToReferenceToFunction::operator CallableType(void) const
{
	// !!! CONVERSION na REFERENCE na FUNCTION je NUTNA, pretoze ak sa nepouzije, tak COMPILER spravi DECAY FUNCTION TYPE na POINTER NA FUNCTION TYPE.
	return(static_cast<CallableType>(MyCallback));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CFunctionObjectTypeConversionToReferenceToFunction::MyCallback(size_t Index, double Value)
{
	wcout << L"CONVERSION OPERATOR TO REFERENCE TO FUNCTION - INDEX [" << Index << "] VALUE [" << Value << "]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------