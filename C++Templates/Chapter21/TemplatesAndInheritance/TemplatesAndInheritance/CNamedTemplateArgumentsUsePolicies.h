//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNamedTemplateArgumentsDefaultPolicies.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS nahradza DEFAULT POLICY definovanu v CLASS [CNamedTemplateArgumentsDefaultPolicies] za CUSTOM POLICY v TYPE TEMPLATE PARAMETER [TPolicy].
template<typename TPolicy>
class CNamedTemplateArgumentsUsePolicy1 : virtual public CNamedTemplateArgumentsDefaultPolicies
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! USING sa musi volat ROVNAKO ako USING v TYPE [CNamedTemplateArgumentsDefaultPolicies].
		using													Policy1=TPolicy;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS nahradza DEFAULT POLICY definovanu v CLASS [CNamedTemplateArgumentsDefaultPolicies] za CUSTOM POLICY v TYPE TEMPLATE PARAMETER [TPolicy].
template<typename TPolicy>
class CNamedTemplateArgumentsUsePolicy2 : virtual public CNamedTemplateArgumentsDefaultPolicies
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! USING sa musi volat ROVNAKO ako USING v TYPE [CNamedTemplateArgumentsDefaultPolicies].
		using													Policy2=TPolicy;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS nahradza DEFAULT POLICY definovanu v CLASS [CNamedTemplateArgumentsDefaultPolicies] za CUSTOM POLICY v TYPE TEMPLATE PARAMETER [TPolicy].
template<typename TPolicy>
class CNamedTemplateArgumentsUsePolicy3 : virtual public CNamedTemplateArgumentsDefaultPolicies
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! USING sa musi volat ROVNAKO ako USING v TYPE [CNamedTemplateArgumentsDefaultPolicies].
		using													Policy3=TPolicy;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS nahradza DEFAULT POLICY definovanu v CLASS [CNamedTemplateArgumentsDefaultPolicies] za CUSTOM POLICY v TYPE TEMPLATE PARAMETER [TPolicy].
template<typename TPolicy>
class CNamedTemplateArgumentsUsePolicy4 : virtual public CNamedTemplateArgumentsDefaultPolicies
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! USING sa musi volat ROVNAKO ako USING v TYPE [CNamedTemplateArgumentsDefaultPolicies].
		using													Policy4=TPolicy;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------