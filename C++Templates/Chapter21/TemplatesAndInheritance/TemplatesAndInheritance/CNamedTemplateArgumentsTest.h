//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNamedTemplateArgumentsPolicies.h"
#include "CNamedTemplateArgumentsDefaultPolicies.h"
#include "CNamedTemplateArgumentsPolicySelector.h"
#include "CNamedTemplateArgumentsDefaultPolicyArguments.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS umoznuje, aby zo vsetkych TEMPLATE PARAMETERS, ktore maju DEFAULT VALUES boli nastavene bez ohladu na ich poradie v TEMPLATE PARAMETER LIST.
template<typename TPolicySetter1=CNamedTemplateArgumentsDefaultPolicyArguments, typename TPolicySetter2=CNamedTemplateArgumentsDefaultPolicyArguments, typename TPolicySetter3=CNamedTemplateArgumentsDefaultPolicyArguments, typename TPolicySetter4=CNamedTemplateArgumentsDefaultPolicyArguments>
class CNamedTemplateArgumentsTest final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! HELPER USING sluziaci na pristup k jednotlivym POLICIES.
		using													Policies=CNamedTemplateArgumentsPolicySelector<TPolicySetter1,TPolicySetter2,TPolicySetter3,TPolicySetter4>;

	public:
		void Print1(void) const;
		void Print2(void) const;
		void Print3(void) const;
		void Print4(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPolicySetter1, typename TPolicySetter2, typename TPolicySetter3, typename TPolicySetter4>
void CNamedTemplateArgumentsTest<TPolicySetter1,TPolicySetter2,TPolicySetter3,TPolicySetter4>::Print1(void) const
{
	// !!!!! Volanie STATIC METHOD danej POLICY.
	Policies::Policy1::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPolicySetter1, typename TPolicySetter2, typename TPolicySetter3, typename TPolicySetter4>
void CNamedTemplateArgumentsTest<TPolicySetter1,TPolicySetter2,TPolicySetter3,TPolicySetter4>::Print2(void) const
{
	// !!!!! Volanie STATIC METHOD danej POLICY.
	Policies::Policy2::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPolicySetter1, typename TPolicySetter2, typename TPolicySetter3, typename TPolicySetter4>
void CNamedTemplateArgumentsTest<TPolicySetter1,TPolicySetter2,TPolicySetter3,TPolicySetter4>::Print3(void) const
{
	// !!!!! Volanie STATIC METHOD danej POLICY.
	Policies::Policy3::Print();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPolicySetter1, typename TPolicySetter2, typename TPolicySetter3, typename TPolicySetter4>
void CNamedTemplateArgumentsTest<TPolicySetter1,TPolicySetter2,TPolicySetter3,TPolicySetter4>::Print4(void) const
{
	// !!!!! Volanie STATIC METHOD danej POLICY.
	Policies::Policy4::Print();
}
//----------------------------------------------------------------------------------------------------------------------