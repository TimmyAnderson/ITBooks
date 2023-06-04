//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
using															MyFunctionType1=void(double Value1, int Value2, int Value3);
using															MyFunctionType2=void(double Value1, int Value2, std::wstring Value3);
using															MyFunctionType3=void(double Value1, int Value2);
//----------------------------------------------------------------------------------------------------------------------
class CFunctionObjectAndSurrogate final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		static void SomeFunction1(double Value1, int Value2, int Value3);
		static void SomeFunction2(double Value1, int Value2, std::wstring Value3);
		static void SomeFunction3(double Value1, int Value2);

	public:
		void operator()(double Value1, double Value2) const;
		operator MyFunctionType1*(void) const;
		// !!! OPERATOR vracia REFERENCE na FUNCTION.
		operator MyFunctionType2&(void) const;
		operator MyFunctionType3*(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------