//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <new>
#include <cstdint>
#include "CTypeList.h"
#include "CTypeListGetLargestType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE TYPE PARAMETERS su TYPES, ktore mozu byt do daneho VARIANT ulozene.
template<typename... TTypes>
class CVariantStorage
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													LargestType=CTypeListGetLargestType<CTypeList<TTypes...>>;
		
	public:
		alignas(TTypes...) uint8_t								MBuffer[sizeof(LargestType)]{};
		uint8_t													MDiscriminator=0;

	public:
		template<typename TType>
		const TType* GetBufferAs(void) const;
		template<typename TType>
		TType* GetBufferAs(void);

	public:
		const void* GetRawBuffer(void) const;
		void* GetRawBuffer(void);

	public:
		std::uint8_t GetDiscriminator(void) const;
		void SetDiscriminator(std::uint8_t Discriminator);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TType>
const TType* CVariantStorage<TTypes...>::GetBufferAs(void) const
{
	const TType*												Result=std::launder(reinterpret_cast<const TType*>(MBuffer));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TType>
TType* CVariantStorage<TTypes...>::GetBufferAs(void)
{
	TType*														Result=std::launder(reinterpret_cast<TType*>(MBuffer));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
const void* CVariantStorage<TTypes...>::GetRawBuffer(void) const
{
	return(MBuffer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void* CVariantStorage<TTypes...>::GetRawBuffer(void)
{
	return(MBuffer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
uint8_t CVariantStorage<TTypes...>::GetDiscriminator(void) const
{
	return(MDiscriminator);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void CVariantStorage<TTypes...>::SetDiscriminator(uint8_t Discriminator)
{
	MDiscriminator=Discriminator;
}
//----------------------------------------------------------------------------------------------------------------------