//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CDereferencingOperatorsPointerToClass.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDereferencingOperatorsClass
{
//-----------------------------------------------------------------------------
	private:
		CDereferencingOperatorsPointerToClass					MValue;

	public:
		CDereferencingOperatorsPointerToClass operator->(void)
		{
			std::wcout << "MEMBER CDereferencingOperatorsClass::OPERATOR-> CALLED !" << std::endl;

			return(MValue);
		}

	public:
		CDereferencingOperatorsClass(const CDereferencingOperatorsPointerToClass& Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------