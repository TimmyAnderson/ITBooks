//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBase
{
//-------------------------------------------------------------------------------------------------------
	protected:
		std::wstring											MValue;

	public:
		virtual void VirtualMethod(void)=0;

	public:
		CBase(std::wstring Value)
			: MValue(Value)
		{
		}

		virtual ~CBase(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------