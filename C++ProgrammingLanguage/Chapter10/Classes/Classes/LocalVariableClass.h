//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CLocalVariableClass
{
	private:
		std::wstring											MValue;

	public:
		void PrintValue(void);

	public:
		CLocalVariableClass(std::wstring Value);
		virtual ~CLocalVariableClass(void);
};
//-------------------------------------------------------------------------------------------------------