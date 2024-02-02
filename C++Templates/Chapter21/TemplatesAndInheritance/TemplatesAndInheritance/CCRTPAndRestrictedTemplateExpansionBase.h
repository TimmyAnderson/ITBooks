//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS implementuje BASE CLASS v CURIOUSLY RECURRING TEMPLATE PATTERN.
// !!!!! CLASS implementuje OPERATOR [OPERATOR !=] na zaklade existencie OPERATOR [OPERATOR ==] v DERIVED CLASS, ktory bude zaslany ako TEMPLATE PARAMETER.
// !!!!! CLASS vyuziva RESTRICTED TEMPLATE EXPANSION PATTERN, ked OPERATOR [OPERATOR !=] implementuje ako FRIEND OPERATOR.
// !!!!! Nutnost pouzitia RESTRICTED TEMPLATE EXPANSION PATTERN je nasledovna.
// !!! A. CLASS DEFINUJE OPERATOR [OPERATOR!=] ako FRIEND OPERATOR co je aplikacia RESTRICTED TEMPLATE EXPANSION PATTERN.
// !!! B. CLASS MUSI definovat OPERATOR [OPERATOR!=] FRIEND OPERATOR, aby tento OPERATOR bol viditelny na GLOBAL NAMESPACE, pretoze CODE pouzivajuci CLASS, chce pouzivat OPERATOR [OPERATOR!=] na GLOBAL NAMESPACE.
// !!! C. Vdaka tomu, ze OPERATOR [OPERATOR!=] je implementovany ako FRIEND OPERATOR, tak je za pouzitia ARGUMENT DEPENDENT LOOKUP viditelny aj na GLOBAL NAMESPACE.
// !!!!! D. Alternativou by bolo definovat OPERATOR [OPERATOR!=] nie ako FRIEND OPERATOR, ale ako GLOBAL OPERATOR. Problem tejto implementacie je vsak v tom, ze takyto OPERATOR [OPERATOR!=] by bol aplikovany prakticky na LUBOVOLNY TYPE, kedze by sa jednalo o TEMPLATE OPERATOR. To znamena, ze by mohol byt aplikovany na hocijaky USER DERIVED TYPE. Avsak definovanie OPERATOR [OPERATOR!=] ako FRIEND OPERATOR sposobi, ze tento OPERATOR je pouzitelny iba na TYPE [TDerivedObject], ktory je TEMPLATE PARAMETER CLASS [CCRTPAndRestrictedTemplateExpansionBase] a na ziaden iny TYPE.
template<typename TDerivedObject>
class CCRTPAndRestrictedTemplateExpansionBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! CODE tohto OPERATOR [OPERATOR!=] vyzaduje, aby CLASS [TDerivedObject] mala impelementovany OPERATOR [OPERATOR==].
		// !!!!! FRIEND FUNCTION vyuziva RESTRICTED TEMPLATE EXPANSION PATTERN, kedy je OPERATOR [OPERATOR!=] definovany ako DEFINITION FRIEND OPERATOR [OPERATOR!=] v CLASS [CCRTPAndRestrictedTemplateExpansionBase].
		// !!!!! Vdaka tomu, ze OPERATOR [OPERATOR!=] je DEFINED ako FRIEND OPERATOR [OPERATOR!=], tak C++ umozni, aby tento FRIEND OPERATOR [OPERATOR!=] bola viditelny aj v PARENT SCOPE co je v tomto pripade NAMESPACE SCOPE. To znamena, ze OPERATOR [OPERATOR!=] bude viditelny aj v NAMESPACE SCOPE.
		// !!!!! Na to, aby bol FRIEND OPERATOR [OPERATOR!=] bol viditelny v NAMESPACE SCOPE, musi ho C++ vediet najst pomocou ARGUMENT DEPENDENT LOOKUP. C++ najde FRIEND OPERATOR [OPERATOR!=] vdaka ARGUMENT DEPENDENT LOOKUP tak, zoberie vsetky ARGUMENTS FRIEND OPERATOR [OPERATOR!=] a hlada v ich TYPES ci bol definovany FRIEND OPERATOR [OPERATOR!=]. Ak je ARGUMENT OPERATOR [OPERATOR!=] bud TYPE [CCRTPAndRestrictedTemplateExpansionDerived], alebo TYPE [CCRTPAndRestrictedTemplateExpansionBase<TDerivedObject>], tak C++ FRIEND OPERATOR [OPERATOR!=] najde.
		// !!!!! Este podstatnejsi je sposob akym sa v FRIEND OPERATOR [OPERATOR!=] najde OPERATOR [OPERATOR==]. C++ ho najde vdaka ARGUMENT DEPENDENT LOOKUP. C++ zoberie vsetky ARGUMENTS OPERATOR [OPERATOR==] a ziska ich TYPES. Kedze obe ARUMENTS OPERATOR [OPERATOR==] maju rovnaky TYPE [TDerivedObject], tak tento TYPE sa pouzije na ARGUMENT DEPENDENT LOOKUP. C++ pozrie do DEFINITION TYPE [TDerivedObject] ci sa tam nenachadza OPERATOR [OPERATOR==]. Ak je TYPE [TDerivedObject] nahradeny za TYPE [CCRTPAndRestrictedTemplateExpansionDerived] tak C++ najde FRIEND OPERATOR [OPERATOR==], ktory TYPE [CCRTPAndRestrictedTemplateExpansionDerived] implementuje a zavola ho.
		friend bool operator!=(const TDerivedObject& Value1, const TDerivedObject& Value2)
		{
			// !!!!! CODE vyzaduje, aby TYPE [TDerivedObject] mal implementovany OPERATOR [OPERATOR ==].
			bool												Result=(!(Value1==Value2));

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------