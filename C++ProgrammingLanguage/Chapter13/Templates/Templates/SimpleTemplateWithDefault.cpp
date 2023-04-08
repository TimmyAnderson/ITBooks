//-------------------------------------------------------------------------------------------------------
#include "SimpleTemplateWithDefault.h"
#include <string>
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
CSimpleTemplateWithDefault<typename TVariable>::CSimpleTemplateWithDefault(TVariable Variable)
	: MVariable(Variable)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
CSimpleTemplateWithDefault<typename TVariable>::~CSimpleTemplateWithDefault(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
const TVariable& CSimpleTemplateWithDefault<typename TVariable>::GetVariable(void) const
{
	return(MVariable);
}
//-------------------------------------------------------------------------------------------------------