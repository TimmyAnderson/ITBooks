//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers\CMemoryOperators.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CTestClass1 : public CMemoryOperators
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MValue1;
		short int												MValue2;
		long int												MValue3;
		unsigned __int64										MValue4;

	public:
		bool GetValue1(void) const noexcept;
		short int GetValue2(void) const noexcept;
		long int GetValue3(void) const noexcept;
		unsigned __int64 GetValue4(void) const noexcept;

	public:
		CTestClass1(bool Value1, short int Value2, long int Value3, unsigned __int64 Value4);
		~CTestClass1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------