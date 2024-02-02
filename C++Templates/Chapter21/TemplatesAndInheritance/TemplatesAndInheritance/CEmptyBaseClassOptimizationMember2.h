//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CEmptyBaseClassOptimizationMember2Empty
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
class CEmptyBaseClassOptimizationMember2Helper final : private TBaseField
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TLocalField												MLocalField;

	public:
		const TBaseField& GetBaseField(void) const noexcept;
		const TLocalField& GetLocalField(void) const noexcept;

	public:
		CEmptyBaseClassOptimizationMember2Helper(const TBaseField& BaseField, const TLocalField& LocalField);
		~CEmptyBaseClassOptimizationMember2Helper(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>::CEmptyBaseClassOptimizationMember2Helper(const TBaseField& BaseField, const TLocalField& LocalField)
	: TBaseField(BaseField)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>::~CEmptyBaseClassOptimizationMember2Helper(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
const TBaseField& CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>::GetBaseField(void) const noexcept
{
	const TBaseField&											BaseField=static_cast<const TBaseField&>(*this);

	return(BaseField);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
const TLocalField& CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>::GetLocalField(void) const noexcept
{
	return(MLocalField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
class CEmptyBaseClassOptimizationMember2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>	MField;

	public:
		const CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>& GetField(void) const noexcept;

	public:
		CEmptyBaseClassOptimizationMember2(const CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>& Field);
		~CEmptyBaseClassOptimizationMember2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
CEmptyBaseClassOptimizationMember2<TBaseField,TLocalField>::CEmptyBaseClassOptimizationMember2(const CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
CEmptyBaseClassOptimizationMember2<TBaseField,TLocalField>::~CEmptyBaseClassOptimizationMember2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TBaseField, typename TLocalField>
const CEmptyBaseClassOptimizationMember2Helper<TBaseField,TLocalField>& CEmptyBaseClassOptimizationMember2<TBaseField,TLocalField>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------