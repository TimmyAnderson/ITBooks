//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNoCustomAssignment
{
	private:
		std::wstring											MStringValue;
		int														MIntValue;

	public:
		void PrintValue(void);

	public:
		CNoCustomAssignment(void);
		CNoCustomAssignment(std::wstring StringValue, int IntValue);
		virtual ~CNoCustomAssignment(void);
};
//-------------------------------------------------------------------------------------------------------