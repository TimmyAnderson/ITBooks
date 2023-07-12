//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TValue>
class CPlusFunctor
{
//-------------------------------------------------------------------------------------------------------
	public:
		TValue operator()(TValue Value1, TValue Value2)
		{
			wprintf_s(L"CPlusFunctor::operator() CALLED !\n");

			return(Value1+Value2);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------