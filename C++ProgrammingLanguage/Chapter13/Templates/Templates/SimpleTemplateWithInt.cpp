//-------------------------------------------------------------------------------------------------------
#include "SimpleTemplateWithInt.h"
#include <string>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template<typename TVariable, int INT>
CSimpleTemplateWithInt<typename TVariable,INT>::CSimpleTemplateWithInt(TVariable Variable)
	: MVariable(Variable)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TVariable, int INT>
CSimpleTemplateWithInt<typename TVariable,INT>::~CSimpleTemplateWithInt(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TVariable, int INT>
const TVariable& CSimpleTemplateWithInt<typename TVariable,INT>::GetVariable(void) const
{
	return(MVariable);
}
//-------------------------------------------------------------------------------------------------------
template<typename TVariable, int INT>
void CSimpleTemplateWithInt<typename TVariable,INT>::PrintINTParameter(void) const
{
	wprintf_s(L"INT: [%d] !\n",INT);
}
//-------------------------------------------------------------------------------------------------------