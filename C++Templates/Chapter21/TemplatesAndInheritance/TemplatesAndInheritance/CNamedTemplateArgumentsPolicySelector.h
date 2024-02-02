//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNamedTemplateArgumentsDiscriminator.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS je DERIVED vo vsetkych POLICY CLASSES. Vdaka pouzitiu INHERITANCE je mozne nahradit lubovolnu POLICY CLASS za inu, bez ohladu na to v akom poradi sa POLICY CLASS nachadza.
// !!!!! CLASS [CNamedTemplateArgumentsDiscriminator<TBase,ID>] sa pouziva iba na to, aby CLASS [CNamedTemplateArgumentsPolicySelector] mohla byt DERIVED z viacerych TYPES [CNamedTemplateArgumentsDiscriminator<TBase,ID>], aj ked TYPE TEMPLATE PARAMETER [TBase]. V takom pripade sa pouziva VALUE [ID] na definovanie z hladiska C++ unikatneho TYPE, z ktoreho CLASS [CNamedTemplateArgumentsPolicySelector] moze byt DERIVED.
template<typename TPolicy1, typename TPolicy2, typename TPolicy3, typename TPolicy4>
class CNamedTemplateArgumentsPolicySelector : public CNamedTemplateArgumentsDiscriminator<TPolicy1,1>, public CNamedTemplateArgumentsDiscriminator<TPolicy2,2>, public CNamedTemplateArgumentsDiscriminator<TPolicy3,3>, public CNamedTemplateArgumentsDiscriminator<TPolicy4,4>
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------