//-------------------------------------------------------------------------------------------------------
#include "TemplateWithTemplateAsParameter.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
CTemplateWithTemplateAsParameter<TType, TTemplate>::CTemplateWithTemplateAsParameter(void)
{
}
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
CTemplateWithTemplateAsParameter<TType, TTemplate>::~CTemplateWithTemplateAsParameter(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
TTemplate<TType> CTemplateWithTemplateAsParameter<TType, TTemplate>::GetTemplateValues(void)
{
	wprintf_s(L"GET VALUES TEMPLATE !\n");

	return(MTemplateValues);
}
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
TTemplate<TType*> CTemplateWithTemplateAsParameter<TType, TTemplate>::GetTemplatePointers(void)
{
	wprintf_s(L"GET POINTERS TEMPLATE !\n");

	return(MTemplatePointers);
}
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
void CTemplateWithTemplateAsParameter<TType, TTemplate>::SetTemplateValues(TTemplate<TType> Param)
{
	wprintf_s(L"SET VALUES TEMPLATE !\n");

	MTemplateValues=Param;
}
//-------------------------------------------------------------------------------------------------------
template <typename TType, template<typename TType> class TTemplate>
void CTemplateWithTemplateAsParameter<TType, TTemplate>::SetTemplatePointers(TTemplate<TType*> Param)
{
	wprintf_s(L"SET POINTERS TEMPLATE !\n");

	MTemplatePointers=Param;
}
//-------------------------------------------------------------------------------------------------------