//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------------
class CFunctionObjectTypeOperator final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! FUNCTION OBJECT ma definovany OPERATOR [OPERATOR()], ktory sluzi ako CALLBACK.
		void operator()(size_t Index, double Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------