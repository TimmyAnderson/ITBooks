//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CDeferEvalution final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! POINTER TYPE FIELD je mozne definovat aj pre INCOMPLETE TYPES.
		TType*													MField;

	public:
		const TType* GetField(void) const noexcept;

	/*
	public:
		// !!!!! Ak je tato METHOD definovana, tak CLASS [CDeferEvalution] NIE JE mozne pouzit pre TEMPLATE PARAMETER typu INCOMPLETE TYPE.
		// !!!!! Dovodom preco sa neda pouzit TEMPLATE PARAMETER typu INCOMPLETE TYPE je v tom, ze METHOD NIE JE TEMPLATE METHOD a RETURN VALUE TYPE tejto METHOD je vyhodnocovany v pri INSTANTIATION celej CLASS, a nie pri INSTANTIATION tejto METHOD.
		typename std::conditional<std::is_constructible<TType,int>::value,TType,TType>::type CreateValue(void) const;
	*/

	public:
		// !!!!! TEMPLATE METHOD sposobi DEFERRED EVALUATION. To znamena, ze RETURN VALUE TYPE tejto METHOD je vyhodnocovany az pri INSTANTIATION tejto METHOD a NIE pri INSTANTIATION CLASS.
		template<typename TLocalType>
		typename std::conditional<std::is_constructible<TLocalType,int>::value,TType,TType>::type TemplateCreateValue(void) const;

	public:
		CDeferEvalution(TType* Field);
		virtual ~CDeferEvalution(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CDeferEvalution<TType>::CDeferEvalution(TType* Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CDeferEvalution<TType>::~CDeferEvalution(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType* CDeferEvalution<TType>::GetField(void) const noexcept
{
	return(MField);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! Ak je tato METHOD definovana, tak CLASS [CDeferEvalution] NIE JE mozne pouzit pre TEMPLATE PARAMETER typu INCOMPLETE TYPE.
// !!!!! Dovodom preco sa neda pouzit TEMPLATE PARAMETER typu INCOMPLETE TYPE je v tom, ze METHOD NIE JE TEMPLATE METHOD a RETURN VALUE TYPE tejto METHOD je vyhodnocovany v pri INSTANTIATION celej CLASS, a nie pri INSTANTIATION tejto METHOD.
template<typename TType>
typename std::conditional<std::is_constructible<TType,int>::value,TType,TType>::type CDeferEvalution<TType>::CreateValue(void) const
{
	TType														Value{};

	return(Value);
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE METHOD sposobi DEFERRED EVALUATION. To znamena, ze RETURN VALUE TYPE tejto METHOD je vyhodnocovany az pri INSTANTIATION tejto METHOD a NIE pri INSTANTIATION CLASS.
template<typename TType>
template<typename TLocalType>
typename std::conditional<std::is_constructible<TLocalType,int>::value,TType,TType>::type CDeferEvalution<TType>::TemplateCreateValue(void) const
{
	TType														Value{};

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------