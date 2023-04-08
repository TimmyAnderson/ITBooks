//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Store.h"
//-------------------------------------------------------------------------------------------------------
// !!! SPECIALIZATION pre POINTER.
template<typename TType>
class CStore<TType*>
{
	private:
		// !!! TType NIE JE POINTER.
		TType*													MValue;

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		TType* GetValue(void)
		{
			wprintf_s(L"TType* GetValue(void) CALLED !\n");

			return(MValue);
		}

	public:
		// !!! Musel som to definovat INLINE, pretoze Visual C++ FUNCTION NEMOZE BYT EXPLICITNE SPECIALIZED (hodi ERROR C2910).
		CStore(TType* Value)
			: MValue(Value)
		{
		}

		virtual ~CStore(void)
		{
		}
};
//-------------------------------------------------------------------------------------------------------