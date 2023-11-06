//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
class CTemplateAlias final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													SizeType=typename TCollection::size_type;

	private:
		TCollection												MCollection;

	public:
		typename TCollection::size_type GetSize(void) const noexcept;
		const TType& GetItem(typename TCollection::size_type Index) const;

	public:
		CTemplateAlias(const TCollection& Collection);
		virtual ~CTemplateAlias(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
CTemplateAlias<TType,TCollection>::CTemplateAlias(const TCollection& Collection)
	: MCollection(Collection)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
CTemplateAlias<TType,TCollection>::~CTemplateAlias(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
typename TCollection::size_type CTemplateAlias<TType,TCollection>::GetSize(void) const noexcept
{
	typename TCollection::size_type								Size=MCollection.size();

	return(Size);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
const TType& CTemplateAlias<TType,TCollection>::GetItem(typename TCollection::size_type Index) const
{
	const TType&												Item=MCollection[Index];

	return(Item);
}
//----------------------------------------------------------------------------------------------------------------------