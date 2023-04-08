//-------------------------------------------------------------------------------------------------------
#include "CustomIntputIterator.h"
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType& operator*(CCustomIntputIterator<TType>& Iterator)
{
	TType*														ActualPosition=Iterator.GetActualPosition();

	return(*ActualPosition);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
CCustomIntputIterator<TType>& operator++(CCustomIntputIterator<TType>& Iterator)
{
	TType*														ActualPosition=Iterator.GetActualPosition();

	ActualPosition++;

	Iterator.SetActualPosition(ActualPosition);

	return(Iterator);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
bool operator==(CCustomIntputIterator<TType>& Iterator1, CCustomIntputIterator<TType>& Iterator2)
{
	TType*														ActualPosition1=Iterator1.GetActualPosition();
	TType*														ActualPosition2=Iterator2.GetActualPosition();

	if (ActualPosition1==ActualPosition2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
bool operator!=(CCustomIntputIterator<TType>& Iterator1, CCustomIntputIterator<TType>& Iterator2)
{
	TType*														ActualPosition1=Iterator1.GetActualPosition();
	TType*														ActualPosition2=Iterator2.GetActualPosition();

	if (ActualPosition1!=ActualPosition2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
CCustomIntputIterator<TType>::CCustomIntputIterator(TType* ActualPosition)
	: MActualPosition(ActualPosition)
{
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
CCustomIntputIterator<TType>::~CCustomIntputIterator(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType* CCustomIntputIterator<TType>::GetActualPosition(void)
{
	return(MActualPosition);
}
//-------------------------------------------------------------------------------------------------------
template<typename TType>
void CCustomIntputIterator<TType>::SetActualPosition(TType* ActualPosition)
{
	MActualPosition=ActualPosition;
}
//-------------------------------------------------------------------------------------------------------