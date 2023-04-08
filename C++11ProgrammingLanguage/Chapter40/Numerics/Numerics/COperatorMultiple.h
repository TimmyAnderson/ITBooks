//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
template<typename TType>
class COperatorMultiple final
{
	public:
		TType operator()(TType Value1, TType Value2)
		{
			return(Value1*Value2);
		}
};
//-----------------------------------------------------------------------------