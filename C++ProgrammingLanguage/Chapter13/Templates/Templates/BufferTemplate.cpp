//-------------------------------------------------------------------------------------------------------
#include "BufferTemplate.h"
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
template<typename TType, TType DefaultValue, int SIZE>
CBufferTemplate<typename TType, DefaultValue, SIZE>::CBufferTemplate(void)
{
	for (int i=0;i<SIZE;i++)
	{
		MBuffer[i]=DefaultValue;
	}
}
//-------------------------------------------------------------------------------------------------------
template<typename TType, TType DefaultValue, int SIZE>
CBufferTemplate<typename TType, DefaultValue, SIZE>::~CBufferTemplate(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType, TType DefaultValue, int SIZE>
const TType& CBufferTemplate<typename TType, DefaultValue, SIZE>::GetValue(int Index) const
{
	if (Index<0 || Index>=SIZE)
	{
		throw(wstring(L"Index is OUT of BOUNDS !"));
	}

	return(MBuffer[Index]);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType, TType DefaultValue, int SIZE>
void CBufferTemplate<typename TType, DefaultValue, SIZE>::SetValue(int Index, const TType& Value)
{
	if (Index<0 || Index>=SIZE)
	{
		throw(wstring(L"Index is OUT of BOUNDS !"));
	}

	MBuffer[Index]=Value;
}
//-------------------------------------------------------------------------------------------------------