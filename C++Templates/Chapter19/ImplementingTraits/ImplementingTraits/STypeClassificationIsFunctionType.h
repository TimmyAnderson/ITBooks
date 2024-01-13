//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "STypeFunctionBoolConstant.h"
#include "STypeList.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct STypeClassificationIsFunctionType final : TypeFunctionFalseType
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS.
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...)> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS.
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...)> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [const].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) const> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [volatile].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) volatile> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [const volatile].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) const volatile> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [const].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) const> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [volatile].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) volatile> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [const volatile].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) const volatile> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) &> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [const &].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) const&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [&&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) &&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre NON-VARIADIC FUNCTIONS s MODIFIER [const &&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters...) const&&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=false;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) &> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [const &].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) const&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [&&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) &&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION pre VARIADIC FUNCTIONS s MODIFIER [const &&].
template<typename TReturnValue, typename... TParameters>
struct STypeClassificationIsFunctionType<TReturnValue(TParameters..., ...) const&&> final : TypeFunctionTrueType
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													RETURN_VALUE=TReturnValue;
		using													PARAMETERS=STypeList<TParameters...>;

	public:
		static constexpr bool									IS_VARIADIC=true;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------