//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "MyFunctionType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFunctionObjectOperatorConversionToPointerToFunction final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		static void CallbackFunction(const CString& Value1, int Value2, double Value3);

	public:
		operator MyFunctionType*(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------