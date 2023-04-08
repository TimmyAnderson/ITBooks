//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMultipleDestructorCallsField final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CMultipleDestructorCallsField(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CMultipleDestructorCallsFieldField CALLED !" << std::endl;
		}

		~CMultipleDestructorCallsField(void)
		{
			std::wcout << L"DESTRUCTOR CMultipleDestructorCallsFieldField CALLED !" << std::endl;

			MValue=0;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------