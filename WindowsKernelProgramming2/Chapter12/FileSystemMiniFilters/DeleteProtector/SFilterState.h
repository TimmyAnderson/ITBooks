//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fltKernel.h>
#include "Helpers\CExecutiveResourceGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct SFilterState final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CExecutiveResourceGlobal								MLock;
		UNICODE_STRING											MExtentions;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------