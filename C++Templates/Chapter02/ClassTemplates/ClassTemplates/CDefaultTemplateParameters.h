//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS ma DEFAULT TEMPLATE ARGUMENT za 2. TEMPLATE PARAMETER.
template<typename TType, typename TCollection=std::vector<TType>>
class CDefaultTemplateParameters
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TCollection												MElements;

	public:
		void Push(const TType& Element);
		void Pop(void);
		const TType& Top(void) const;

		// !!! METHOD je definovana INLINE.
		bool IsEmpty(void) const
		{
			bool												IsEmpty=MElements.empty();

			return(IsEmpty);
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
void CDefaultTemplateParameters<TType,TCollection>::Push(const TType& Element)
{
	MElements.push_back(Element);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
void CDefaultTemplateParameters<TType,TCollection>::Pop(void)
{
	if (MElements.empty()==false)
	{
		MElements.pop_back();
	}
	else
	{
		throw(CException(L"COLLECTION is EMPTY !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TCollection>
const TType& CDefaultTemplateParameters<TType,TCollection>::Top(void) const
{
	if (MElements.empty()==false)
	{
		const TType&											Element=MElements.back();

		return(Element);
	}
	else
	{
		throw(CException(L"COLLECTION is EMPTY !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------