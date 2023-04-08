//-------------------------------------------------------------------------------------------------------
#include "SimpleTemplate.h"
#include <string>
//-------------------------------------------------------------------------------------------------------
// !!!!! Tento HACK sluzi na to, aby LINKER VLOZIL DEFINICIE (tela) TEMPLATE metod do generovaneho suboru. Lepsim riesenim je vsak vlozit CPP subor do CPP suboru, kde sa TEMPLATE POUZIVA.
//template CSimpleTemplate<int>;
//template CSimpleTemplate<std::wstring>;
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
CSimpleTemplate<typename TVariable>::CSimpleTemplate(TVariable Variable)
	: MVariable(Variable)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
CSimpleTemplate<typename TVariable>::~CSimpleTemplate(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
const TVariable& CSimpleTemplate<typename TVariable>::GetVariable(void) const
{
	return(MVariable);
}
//-------------------------------------------------------------------------------------------------------