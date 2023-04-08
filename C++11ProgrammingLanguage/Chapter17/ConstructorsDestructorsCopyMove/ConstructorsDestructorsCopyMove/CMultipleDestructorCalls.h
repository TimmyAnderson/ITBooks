//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CMultipleDestructorCallsField.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMultipleDestructorCalls final
{
//-----------------------------------------------------------------------------
	private:
		CMultipleDestructorCallsField							MValue;

	public:
		int GetValue(void) const noexcept
		{
			return(MValue.GetValue());
		}

	public:
		CMultipleDestructorCalls(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CMultipleDestructorCalls CALLED !" << std::endl;
		}

		~CMultipleDestructorCalls(void)
		{
			std::wcout << L"DESTRUCTOR CMultipleDestructorCalls CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------