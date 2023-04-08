//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CVirtualTemplateBase
{
	public:
		void DummyNonVirtualFunction(TType Value)
		{
			wprintf_s(L"DummyNonVirtualFunction() CALLED with parameter [%d] !\n",Value);
		}

	public:
		// !!! C++ UMOZNUJE, aby TEMPLATE FUNCTIONS (pozor NEJEDNA sa o TEMPLATE METHODS) boli VIRTUALNE.
		template<typename TLocalType>
		void DummyNonVirtualTemplateFunction(TLocalType Value)
		{
			wprintf_s(L"DummyVirtualTemplateFunction() CALLED with parameter [%f] !\n",Value);
		}

	public:
		virtual void DummyVirtualFunction(TType Value)
		{
			wprintf_s(L"DummyVirtualFunction() CALLED with parameter [%d] !\n",Value);
		}

	public:
		// !!!!! C++ NEUMOZNUJE, aby TEMPLATE FUNCTIONS (pozor NEJEDNA sa o TEMPLATE METHODS) boli VIRTUALNE.
		/*
		template<typename TLocalType>
		virtual void DummyVirtualTemplateFunction(TLocalType Value)
		{
			wprintf_s(L"DummyVirtualTemplateFunction() CALLED with parameter [%d] !\n",Value);
		}
		*/

	public:
		virtual void DummyAbstractFunction(TType Value)=0;
};
//-------------------------------------------------------------------------------------------------------