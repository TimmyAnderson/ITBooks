//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Store.h"
//-------------------------------------------------------------------------------------------------------
// !!! SPECIALIZATION pre DOUBLE.
template<>
class CStore<double>
{
	private:
		double													MValue;

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		double GetValue(void)
		{
			wprintf_s(L"double GetValue(void) CALLED !\n");

			return(MValue);
		}

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		CStore(double Value)
			: MValue(Value)
		{
		}

		virtual ~CStore(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------