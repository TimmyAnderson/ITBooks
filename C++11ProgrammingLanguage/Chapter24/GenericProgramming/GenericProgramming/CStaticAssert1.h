//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE umoznuje, aby TEMPLATE PARAMETER [TCallback] bol CLASS, alebo POINTER na FUNCTION s 1. PARAMETER typu [TValue].
template<typename TValue, typename TCallback>
class CStaticAssert1
{
//-------------------------------------------------------------------------------------------------------
	private:
		TCallback												MCallback;
		TValue													MValue;

	public:
		void CallCallback(void)
		{
			MCallback(MValue);
		}

	public:
		CStaticAssert1(TCallback Callback, TValue Value)
			: MCallback(Callback), MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------