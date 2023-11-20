//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CTemplateAndNonTemplateFunctionOverloading final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int GetValue(void) const noexcept;

	public:
		CTemplateAndNonTemplateFunctionOverloading(int Value);
		CTemplateAndNonTemplateFunctionOverloading(const CTemplateAndNonTemplateFunctionOverloading& Other);
		CTemplateAndNonTemplateFunctionOverloading(CTemplateAndNonTemplateFunctionOverloading&& Other) noexcept;
		template<typename TType>
		CTemplateAndNonTemplateFunctionOverloading(TType&& Other);
		virtual ~CTemplateAndNonTemplateFunctionOverloading(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CTemplateAndNonTemplateFunctionOverloading::CTemplateAndNonTemplateFunctionOverloading(TType&& Other)
	: MValue(Other.GetValue())
{
	std::wcout << L"TEMPLATE CONSTRUCTOR CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------