//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateAndNonTemplateFunctionOverloading.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTemplateAndNonTemplateFunctionOverloading::CTemplateAndNonTemplateFunctionOverloading(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
CTemplateAndNonTemplateFunctionOverloading::CTemplateAndNonTemplateFunctionOverloading(const CTemplateAndNonTemplateFunctionOverloading& Other)
	: MValue(Other.GetValue())
{
	wcout << L"COPY CONSTRUCTOR CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CTemplateAndNonTemplateFunctionOverloading::CTemplateAndNonTemplateFunctionOverloading(CTemplateAndNonTemplateFunctionOverloading&& Other) noexcept
	: MValue(Other.GetValue())
{
	wcout << L"NOVE CONSTRUCTOR CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CTemplateAndNonTemplateFunctionOverloading::~CTemplateAndNonTemplateFunctionOverloading(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int CTemplateAndNonTemplateFunctionOverloading::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------