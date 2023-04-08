//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
template<typename TValue, typename TCallback>
class CStaticAssert2
{
//-------------------------------------------------------------------------------------------------------
	private:
		TCallback												MCallback;
		TValue													MValue;

	// !!!!! KEYWORD [static_assert()] moze byt pouzity aj na urovni CLASSES.
	// !!!!! STATIC ASSERT vyzaduje, aby TEMPLATE PARAMETER [TCallback] bol CLASS. PARAMETER TYPU POINTER na FUNCTION teda NEAKCEPTUJE, ak ked by v skutocnosti mohol.
	static_assert(std::is_class<TCallback>::value,"TCallback MUST be CLASS !");

	public:
		void CallCallback(void)
		{
			MCallback(MValue);
		}

	public:
		CStaticAssert2(TCallback Callback, TValue Value)
			: MCallback(Callback), MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------