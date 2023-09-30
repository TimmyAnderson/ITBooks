//----------------------------------------------------------------------------------------------------------------------
#include "CExplicitInstantiationDeclaration.h"
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Nasledujuci CODE obsahuje EXPLICIT INSTANTIATION pre EXPLICIT INSTANTIATION DECLARATION definovanu v HEADER FILE. EXPLICIT INSTANTIATION sposobi, ze pre danu TEMPLATE a TEMPLATE ARGUMENTS sa vytvori BINARY CODE iba v tejto TRANSLATION UNIT.
template class CExplicitInstantiationDeclaration<int>;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Nasledujuci CODE obsahuje EXPLICIT INSTANTIATION pre EXPLICIT INSTANTIATION DECLARATION definovanu v HEADER FILE. EXPLICIT INSTANTIATION sposobi, ze pre danu TEMPLATE a TEMPLATE ARGUMENTS sa vytvori BINARY CODE iba v tejto TRANSLATION UNIT.
template void ExplicitInstantiationDeclarationFunction<int>(const int& Value);
//----------------------------------------------------------------------------------------------------------------------