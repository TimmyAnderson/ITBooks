//-----------------------------------------------------------------------------
#include "CCustomErrorCategory.h"
//-----------------------------------------------------------------------------
const CCustomErrorCategory										CCustomErrorCategory::CATEGORY;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CCustomErrorCategory::CCustomErrorCategory(void)
{
}
//-----------------------------------------------------------------------------
CCustomErrorCategory::~CCustomErrorCategory(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION pouziva CONSTRUCTOR CLASS [error_code], preto je ju NUTNE definovat.
error_code make_error_code(ECustomErrorCode ErrorCode)
{
	error_code													ErrorCodeObject(static_cast<int>(ErrorCode),CCustomErrorCategory::CATEGORY);

	return(ErrorCodeObject);
}
//-----------------------------------------------------------------------------
// !!! FUNCTION pouziva CONSTRUCTOR CLASS [error_condition], preto je ju NUTNE definovat.
error_condition make_error_condition(ECustomErrorCondition ErrorCondition)
{
	error_condition												ErrorConditionObject(static_cast<int>(ErrorCondition),CCustomErrorCategory::CATEGORY);

	return(ErrorConditionObject);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const char* CCustomErrorCategory::name(void) const noexcept
{
	return("CUSTOM CATEGORY");
}
//-----------------------------------------------------------------------------
string CCustomErrorCategory::message(int ErrorCondition) const
{
	ECustomErrorCondition										TypedErrorCondition=static_cast<ECustomErrorCondition>(ErrorCondition);

	if (TypedErrorCondition==ECustomErrorCondition::E_ERROR_CONDITION_A)
	{
		return("CONDITION A");
	}
	else if (TypedErrorCondition==ECustomErrorCondition::E_ERROR_CONDITION_B)
	{
		return("CONDITION B");
	}
	else if (TypedErrorCondition==ECustomErrorCondition::E_ERROR_CONDITION_C)
	{
		return("CONDITION C");
	}
	else
	{
		return(string());
	}
}
//-----------------------------------------------------------------------------
// Mapuje ERROR CODE na ERROR CONDITION.
error_condition CCustomErrorCategory::default_error_condition(int Code) const noexcept
{
	ECustomErrorCode											TypedErrorCode=static_cast<ECustomErrorCode>(Code);

	if (TypedErrorCode==ECustomErrorCode::E_ERROR_CODE_A)
	{
		// !!! INTERNE CONSTRUCTOR pouziva FUNCTION make_error_condition().
		return(error_condition(ECustomErrorCondition::E_ERROR_CONDITION_A));
	}
	else if (TypedErrorCode==ECustomErrorCode::E_ERROR_CODE_B)
	{
		// !!! INTERNE CONSTRUCTOR pouziva FUNCTION make_error_condition().
		return(error_condition(ECustomErrorCondition::E_ERROR_CONDITION_B));
	}
	else if (TypedErrorCode==ECustomErrorCode::E_ERROR_CODE_C)
	{
		// !!! INTERNE CONSTRUCTOR pouziva FUNCTION make_error_condition().
		return(error_condition(ECustomErrorCondition::E_ERROR_CONDITION_C));
	}
	else
	{
		return(error_condition());
	}
}
//-----------------------------------------------------------------------------
bool CCustomErrorCategory::equivalent(int Code, const error_condition& Condition) const noexcept
{
	return(error_category::equivalent(Code,Condition));
}
//-----------------------------------------------------------------------------
bool CCustomErrorCategory::equivalent(const error_code& Code, int Condition) const noexcept
{
	return(error_category::equivalent(Code,Condition));
}
//-----------------------------------------------------------------------------