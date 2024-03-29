//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace ParsingADL
{
//----------------------------------------------------------------------------------------------------------------------
	class CParsingADL final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MValue;

		public:
			const CString& GetValue(void) const noexcept;

		public:
			CParsingADL(const CString& Value);
			virtual ~CParsingADL(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CParsingADL::CParsingADL(const CString& Value)
		: MValue(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParsingADL::~CParsingADL(void) noexcept
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CParsingADL::GetValue(void) const noexcept
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<int VALUE>
	void ParsingADLTemplateFunction1(CParsingADL Value)
	{
		std::wcout << L"FUNCTION 1 - CParsingADL.Value [" << Value.GetValue() << L"] VALUE [" << VALUE << L"]." << std::endl;
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	void ParsingADLTemplateFunction1(void)
	{
		// !!!!! DUMMY. Sluzi iba na to, aby C++ COMPILER dokazal rozlisit, ze CODE [ParsingADLTemplateFunction1()] je volanie FUNCTION.
	}
//----------------------------------------------------------------------------------------------------------------------
	template<int VALUE>
	void ParsingADLTemplateFunction2(CParsingADL Value)
	{
		std::wcout << L"FUNCTION 2 - CParsingADL.Value [" << Value.GetValue() << L"] VALUE [" << VALUE << L"]." << std::endl;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------