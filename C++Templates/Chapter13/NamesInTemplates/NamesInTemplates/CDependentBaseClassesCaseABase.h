//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDependentBaseClassesCaseABase
{
//----------------------------------------------------------------------------------------------------------------------
	protected:
		// !!!!! FIELD ma ROVNAKY NAME ako nazov ENUM v TEMPLATE CLASS SPECIALIZATION [CDependentBaseClassesCaseABase<bool>].
		int														MBaseField;

	public:
		int GetBaseField(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
int CDependentBaseClassesCaseABase<TType>::GetBaseField(void) const noexcept
{
	return(MBaseField);
}
//----------------------------------------------------------------------------------------------------------------------