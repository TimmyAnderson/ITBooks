//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "VirtualTemplateBase.h"
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CVirtualTemplateDerived : public CVirtualTemplateBase<TType>
{
	public:
		virtual void DummyAbstractFunction(TType Value)
		{
			wprintf_s(L"DummyAbstractFunction() CALLED with parameter [%d] !\n",Value);
		}
};
//-------------------------------------------------------------------------------------------------------