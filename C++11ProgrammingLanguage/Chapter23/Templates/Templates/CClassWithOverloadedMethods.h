//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CClassWithOverloadedMethods
{
//-------------------------------------------------------------------------------------------------------
	public:
		template<typename TType>
		void TemplateOverride(TType, typename TType::value_type)
		{
			wprintf_s(L"TEMPLATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, TType::value_type)] CALLED !\n");
		}

		template<typename TType>
		void TemplateOverride(TType, TType)
		{
			wprintf_s(L"TEMPLATE FUNCTION [void CClassWithOverloadedMethods::TemplateOverride(TType, TType)] CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------