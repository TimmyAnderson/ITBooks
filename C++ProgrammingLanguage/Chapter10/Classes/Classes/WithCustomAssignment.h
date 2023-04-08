//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CWithCustomAssignment
{
	private:
		std::wstring											MStringValue;
		int														MIntValue;

	public:
		CWithCustomAssignment& operator=(const CWithCustomAssignment& OriginalObject);

	public:
		void PrintValue(void);

	public:
		CWithCustomAssignment(void);
		CWithCustomAssignment(std::wstring StringValue, int IntValue);
		CWithCustomAssignment(const CWithCustomAssignment& OrginalObject);
		virtual ~CWithCustomAssignment(void);
};
//-------------------------------------------------------------------------------------------------------