//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Store.h"
//-------------------------------------------------------------------------------------------------------
// !!! SPECIALIZATION pre VOID*.
template<>
class CStore<void*>
{
	private:
		void*													MValue;

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		void* GetValue(void)
		{
			wprintf_s(L"void* GetValue(void) CALLED !\n");

			return(MValue);
		}

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		CStore(void* Value)
			: MValue(Value)
		{
		}

		virtual ~CStore(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------