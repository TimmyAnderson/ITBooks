//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CSpecialTemplateArgumentDeduction final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		double													MValue;

	public:
		template<typename TType>
		operator TType(void) const;

	public:
		double GetValue(void) const noexcept;

	public:
		CSpecialTemplateArgumentDeduction(double Value);
		virtual ~CSpecialTemplateArgumentDeduction(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CSpecialTemplateArgumentDeduction::operator TType(void) const
{
	TType														ReturnValue=static_cast<TType>(MValue);

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------