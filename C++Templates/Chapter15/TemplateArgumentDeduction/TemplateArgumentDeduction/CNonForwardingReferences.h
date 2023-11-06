//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonForwardingReferences final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		// !!!!! CONSTRUCTOR NIE je TEMPLATE METHOD, a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES.
		CNonForwardingReferences(TType&& Value);
		// !!!!! CONSTRUCTOR JE TEMPLATE METHOD, ale PARAMETER NIE JE FORWARDING REFERENCE, a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES.
		template<typename TLocalType>
		CNonForwardingReferences(CNonForwardingReferences<TLocalType>&& Value);
		virtual ~CNonForwardingReferences(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR NIE je TEMPLATE METHOD a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES.
template<typename TType>
CNonForwardingReferences<TType>::CNonForwardingReferences(TType&& Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CONSTRUCTOR JE TEMPLATE METHOD, ale PARAMETER NIE JE FORWARDING REFERENCE, a preto sa NEAPLIKUJE RULE pre TEMPLATE ARGUMENT DEDUCTION FORWARDING REFERENCES.
template<typename TType>
template<typename TLocalType>
CNonForwardingReferences<TType>::CNonForwardingReferences(CNonForwardingReferences<TLocalType>&& Value)
	: MValue(Value.GetValue())
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CNonForwardingReferences<TType>::~CNonForwardingReferences(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CNonForwardingReferences<TType>::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------