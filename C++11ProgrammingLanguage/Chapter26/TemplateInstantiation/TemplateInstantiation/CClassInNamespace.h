//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
namespace SomeNamespace
{
//-------------------------------------------------------------------------------------------------------
	class CClassInNamespace
	{
//-------------------------------------------------------------------------------------------------------
		private:
			std::wstring										MValue;

		public:
			std::wstring GetValue(void)
			{
				return(MValue);
			}

		public:
			CClassInNamespace(std::wstring Value)
			{
				MValue=Value;
			}
//-------------------------------------------------------------------------------------------------------
	};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	// GLOBAL FUNCTION.
	void PrintClassInNamespace(CClassInNamespace Value)
	{
		wprintf_s(L"VALUE [%ls] !\n",Value.GetValue().c_str());
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------