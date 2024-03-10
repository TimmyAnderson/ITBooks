//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <utility>
#include "CTypeList.h"
#include "CTypeListFindIndexOfType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CVariant;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS sa nachadza N-krat v CLASS [CVariant], kde VALUE 'N' je pocet TYPES, ktore mozu byt ulozene do CLASS [CVariant].
template<typename TType, typename... TTypes>
class CVariantChoice
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		using													DerivedType=CVariant<TTypes...>;

	protected:
		// !!! VALUES su indexovane od 1.
		constexpr static size_t									Discriminator=(CTypeListFindIndexOfType<CTypeList<TTypes...>,TType>::VALUE+1);

	public:
		DerivedType& operator=(const TType& Value);
		DerivedType& operator=(TType&& Value);

	private:
		const DerivedType& GetDerived(void) const;
		DerivedType& GetDerived(void);

	public:
		bool Destroy(void);

	public:
		CVariantChoice(void);
		CVariantChoice(const TType& Value);
		CVariantChoice(TType&& Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CVariantChoice<TType,TTypes...>::CVariantChoice(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CVariantChoice<TType,TTypes...>::CVariantChoice(const TType& Value)
{
	// !!!!! Pouzije sa PLACEMENT CALL OPERATOR [OPERATOR new].
	new(GetDerived().GetRawBuffer()) TType(Value);

	GetDerived().SetDiscriminator(Discriminator);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
CVariantChoice<TType,TTypes...>::CVariantChoice(TType&& Value)
{
	// !!!!! Pouzije sa PLACEMENT CALL OPERATOR [OPERATOR new].
	new(GetDerived().GetRawBuffer()) TType(std::move(Value));

	GetDerived().SetDiscriminator(Discriminator);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
typename CVariantChoice<TType,TTypes...>::DerivedType& CVariantChoice<TType,TTypes...>::operator=(const TType& Value)
{
	// !!!!! Ak je TYPE rovnaky ako uz ulozeny TYPE, NESMIE sa volat DESTRUCTOR SOURCE OBJECT, pretoze by to znemoznilo SELF-ASSIGNMENT.
	if (GetDerived().GetDiscriminator()==Discriminator)
	{
		// !!! Priradi sa VALUE ROVNAKEHO TYPE, ako ten co je ulozeny.

		*GetDerived().template GetBufferAs<TType>()=Value;
	}
	else
	{
		// !!! Priradi sa VALUE INEHO TYPE, ako ten co je ulozeny.

		GetDerived().Destroy();

		// !!!!! Pouzije sa PLACEMENT CALL OPERATOR [OPERATOR new].
		new(GetDerived().GetRawBuffer()) TType(Value);

		GetDerived().SetDiscriminator(Discriminator);
	}

	DerivedType&												Result=GetDerived();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
typename CVariantChoice<TType,TTypes...>::DerivedType& CVariantChoice<TType,TTypes...>::operator=(TType&& Value)
{
	// !!!!! Ak je TYPE rovnaky ako uz ulozeny TYPE, NESMIE sa volat DESTRUCTOR SOURCE OBJECT, pretoze by to znemoznilo SELF-ASSIGNMENT.
	if (GetDerived().GetDiscriminator()==Discriminator)
	{
		// !!! Priradi sa VALUE ROVNAKEHO TYPE, ako ten co je ulozeny.

		*GetDerived().template GetBufferAs<TType>()=std::move(Value);
	}
	else
	{
		// !!! Priradi sa VALUE INEHO TYPE, ako ten co je ulozeny.

		GetDerived().Destroy();

		// !!!!! Pouzije sa PLACEMENT CALL OPERATOR [OPERATOR new].
		new(GetDerived().GetRawBuffer()) TType(std::move(Value));

		GetDerived().SetDiscriminator(Discriminator);
	}

	DerivedType&												Result=GetDerived();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
const typename CVariantChoice<TType,TTypes...>::DerivedType& CVariantChoice<TType,TTypes...>::GetDerived(void) const
{
	const DerivedType&											Result=*static_cast<const DerivedType*>(this);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
typename CVariantChoice<TType,TTypes...>::DerivedType& CVariantChoice<TType,TTypes...>::GetDerived(void)
{
	DerivedType&												Result=*static_cast<DerivedType*>(this);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename... TTypes>
bool CVariantChoice<TType,TTypes...>::Destroy(void)
{
	if (GetDerived().GetDiscriminator()==Discriminator)
	{
		// !!!!! Vykonava sa PLACEMENT CALL OPERATOR [OPERATOR delete].
		
	    GetDerived().template GetBufferAs<TType>()->~TType();

		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------