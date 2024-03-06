//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TYPE reprezentuje TUPLE ELEMENT do ktoreho je ulozeny TUPLE FIELD.
// !!!!! 1. TEMPLATE PARAMETER je unikatne ID daneho TUPLE ELEMENT, aby do TUPLE bolo mozne ukladat viacero FIELDS rovnakeho TYPE.
// !!!!! 2. TEMPLATE PARAMETER je TYPE daneho TUPLE FIELD.
// !!!!! 3. TEMPLATE PARAMETER urcuje ci TYPE [TType] moze byt pouzity ako BASE CLASS pre TUPLE ELEMENT. To je mozne vtedy, ak TYPE je CLASS a zaroven NIE JE oznaceny pomocou KEYWORD [final].
template<size_t ELEMENT_ID, typename TType, bool = std::is_class<TType>::value==true && std::is_final<TType>::value==false>
class CTupleEBCOElement;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CASE, kedy TUPLE ELEMENT NEMOZE byt pouzity ako BASE CLASS.
template<size_t ELEMENT_ID, typename TType>
class CTupleEBCOElement<ELEMENT_ID,TType,false>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& Get(void) const;

	public:
		TType& Get(void);

	public:
		CTupleEBCOElement(void);
		CTupleEBCOElement(const TType& Other);
		CTupleEBCOElement(TType&& Other);
		//virtual ~CTupleEBCOElement(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,false>::CTupleEBCOElement(void)
	: MValue()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,false>::CTupleEBCOElement(const TType& Other)
	: MValue(Other)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,false>::CTupleEBCOElement(TType&& Other)
	: MValue(std::forward<TType>(Other))
{
}
//----------------------------------------------------------------------------------------------------------------------
/*
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,false>::~CTupleEBCOElement(void) noexcept
{
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
const TType& CTupleEBCOElement<ELEMENT_ID,TType,false>::Get(void) const
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
TType& CTupleEBCOElement<ELEMENT_ID,TType,false>::Get(void)
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CASE, kedy TUPLE ELEMENT MOZE byt pouzity ako BASE CLASS.
template<size_t ELEMENT_ID, typename TType>
class CTupleEBCOElement<ELEMENT_ID,TType,true> : private TType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		const TType& Get(void) const;

	public:
		TType& Get(void);

	public:
		CTupleEBCOElement(void);
		CTupleEBCOElement(const TType& Other);
		CTupleEBCOElement(TType&& Other);
		//virtual ~CTupleEBCOElement(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,true>::CTupleEBCOElement(void)
	: TType()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,true>::CTupleEBCOElement(const TType& Other)
	: TType(Other)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,true>::CTupleEBCOElement(TType&& Other)
	: TType(std::forward<TType>(Other))
{
}
//----------------------------------------------------------------------------------------------------------------------
/*
template<size_t ELEMENT_ID, typename TType>
CTupleEBCOElement<ELEMENT_ID,TType,true>::~CTupleEBCOElement(void) noexcept
{
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
const TType& CTupleEBCOElement<ELEMENT_ID,TType,true>::Get(void) const
{
	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<size_t ELEMENT_ID, typename TType>
TType& CTupleEBCOElement<ELEMENT_ID,TType,true>::Get(void)
{
	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------