//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------------
class CFunctionObjectTypeConversionToReferenceToFunction final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													CallableType=void(&)(size_t Index, double Value);

	private:
		static void MyCallback(size_t Index, double Value);

	public:
		operator CallableType(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------