//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <utility>
//-----------------------------------------------------------------------------
/*
   Princip fungovania detekcie ci TYPE ma METHOD XXX().

   A. Hodnotu [SFunctionXXXCheck<CTypeWithMethodXXX>::RESULT] bude C++ interpretovat nasledovne.
      1. C++ sa pokusi vytvorit TEMPLATE INSTANCE [SFunctionXXXCheck<CTypeWithMethodXXX>].
	  2. Kedze TEMPLATE STRUCTURE [SFunctionXXXCheck] dedi z TEMPLATE STRUCTURE [SConditionResult], C++ sa pokusi vytvorit TEMPLATE INSTANCING [SConditionResult<decltype(SFunctionXXXCheckMethods::CheckIfHasMethodXXX(std::declval<CTypeWithMethodXXX>()))>].
	  3. Kedze STRUCTURE [SFunctionXXXCheckMethods] ma 2 verzie STATIC METHOD CheckIfHasMethodXXX(), C++ musi vybrat, ktoru z nich zavola na zistenie TYPE, ktory ma substituovat do TEMPLATE STRUCTURE [SConditionResult].
	  4. C++ sa pokusi vykonat substituciu TYPE [CTypeWithMethodXXX] pre METHOD [auto CheckIfHasMethodXXX(TType Value) -> decltype(Value.XXX())].
	  !!! 5. Pri vykonavani EXPRESSION [decltype(Value.XXX())] sa C++ pokusi zavolat METHOD XXX() CLASS [CTypeWithMethodXXX]. Kedze CLASS [CTypeWithMethodXXX] MA METHOD XXX(), tak toto volanie prebehne USPESNE a C++ vyberie tuto verziu METHOD CheckIfHasMethodXXX().
	  !!!!! 6. C++ z DEKLRACIE METHOD [auto CheckIfHasMethodXXX(CTypeWithMethodXXX Value) -> decltype(Value.XXX())] urci jej TYPE. Kedze FUNCTION CTypeWithMethodXXX.XXX() NEMA RETURN VALUE, C++ urci TYPE [void] ako TYPE DEKLRACIE FUNCTION [auto CheckIfHasMethodXXX(CTypeWithMethodXXX Value) -> decltype(Value.XXX())].
	  !!!!! 7. C++ vytvori TEMPLATE INSTANCE [SFunctionXXXCheck], ktora je DERIVED z TEMPLATE INSTANCE [SConditionResult<void>].
	  !!!!! 8. Kedze TYPE [void] je ODLISNY od TYPE [SFalseValue], C++ pouzije 1. VERZIU TEMPLATE STRUCTURE [SConditionResult].
	  !!!!! 9. Kedze 1. VERZIA TEMPLATE STRUCTURE [SConditionResult] definuje MEMBER [RESULT] ako TRUE, hodnota [SFunctionXXXCheck::RESULT] bude TRUE.

   B. Hodnotu [SFunctionXXXCheck<wstring>::RESULT] bude C++ interpretovat nasledovne.
      1. C++ sa pokusi vytvorit TEMPLATE INSTANCE [SFunctionXXXCheck<wstring>].
	  2. Kedze TEMPLATE STRUCTURE [SFunctionXXXCheck] dedi z TEMPLATE STRUCTURE [SConditionResult], C++ sa pokusi vytvorit TEMPLATE INSTANCING [SConditionResult<decltype(SFunctionXXXCheckMethods::CheckIfHasMethodXXX(std::declval<wstring>()))>].
	  3. Kedze STRUCTURE [SFunctionXXXCheckMethods] ma 2 verzie STATIC METHOD CheckIfHasMethodXXX(), C++ musi vybrat, ktoru z nich zavola na zistenie TYPE, ktory ma substituovat do TEMPLATE STRUCTURE [SConditionResult].
	  4. C++ sa pokusi vykonat substituciu TYPE [wstring] pre METHOD [auto CheckIfHasMethodXXX(TType Value) -> decltype(Value.XXX())].
	  !!!!! 5. Pri vykonavani EXPRESSION [decltype(Value.XXX())] sa C++ pokusi zavolat METHOD XXX() CLASS [CTypeWithMethodXXX]. Kedze CLASS [wstring] MA METHOD XXX(), tak toto volanie ZLYHA a C++ tuto verziu METHOD CheckIfHasMethodXXX() vdaka mechanizmu SFINAE IGNORUJE.
	  !!! 6. C++ sa pokusi pouzit 2. VERZIU METHOD [SFalseValue CheckIfHasMethodXXX(TTypes...)]. Kedze ta nema ziaden EXPRESSION na vyhodnotenie, C++ vyhodnoti METHOD ako sposobilu pre substituciu do TEMPLATE STRUCTURE [SConditionResult].
	  !!!!! 7. C++ z DEKLRACIE METHOD [SFalseValue CheckIfHasMethodXXX(TTypes...)] urci jej TYPE. Kedze METHOD ma ako RETURN VALUE TYPE [SFalseValue], tento TYPE sa pouzije ako TYPE celej EXPRESSION.
	  !!! 8. C++ vytvori TEMPLATE INSTANCE [SFunctionXXXCheck], ktora je DERIVED z TEMPLATE INSTANCE [SConditionResult<SFalseValue>].
	  !!!!! 9. Kedze TYPE [SFalseValue] je ROVNAKY ako TYPE [SFalseValue], C++ pouzije 2. VERZIU TEMPLATE STRUCTURE, ktora reprezentuje TEMPLATE SPECIALIZATION [SConditionResult<SFalseValue>].
	  !!!!! 10. Kedze 2. VERZIA TEMPLATE STRUCTURE, TEMPLATE SPECIALIZATION [SConditionResult<SFalseValue>] definuje MEMBER [RESULT] ako FALSE, hodnota [SFunctionXXXCheck::RESULT] bude FALSE.
*/
//-----------------------------------------------------------------------------
// !!! Tento FILE je ANALOGIOU FILE [HasMethodXXX2.h]. Jediny rozdiel je, ze sa z FUNCTIONS CheckIfHasMethodXXX() stali STATIC METHODS STRUCTURE STestFunctionXXXCheckMethodsStructure.
//-----------------------------------------------------------------------------
// !!! STRUCTURE [SErrorStructure] je pomocna STRUCTRUE, ktora sluzi ako identifikator FALSE hodnoty pri COMPILE-TIME testoch. STRUCTURE je preto prazdna a nema ziadne MEMBERS.
struct SFalseValue
{
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! STRUCTURE [SConditionResult] reprezentuje vysledok COMPILE-TIME testu, ktory moze nadobudat TRUE, alebo FALSE hodnotu.
// !!! Tato verzia TEMPLATE STRUCTURE [SConditionResult] reprezentuje TRUE vysledok COMPILE-TIME testu.
template<typename TType>
struct SConditionResult
{
//-----------------------------------------------------------------------------
	public:
		// MEMBER [RESULT] nadobuda hodnotu TRUE.
		static const bool										RESULT=true;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION pre TYPE [SFalseValue] je SPECIALIZATION TEMPLATE STRUCTURE [SConditionResult].
// !!! Tato verzia TEMPLATE STRUCTURE [SConditionResult] reprezentuje FALSE vysledok COMPILE-TIME testu.
template<>
// !!!!! STRUCTURE [SFalseValue] tu sluzi ako IDENTIFIKATOR FALSE hodnoty. Namiesto STRUCTURE [SFalseValue] by mohol byt pouzity LUBOVOLNY TYPE, vratane PRIMITIVE TYPES. Podstatne je iba to, aby ak COMPILE-TIME test vrati TRUE, vysledkom bola [SConditionResult<XXX>], kde 'XXX' je INY TYPE ako TYPE [SFalseValue]. Naopak, ak COMPILE-TIME test vrati hodnotu FALSE, potom jeho vysledkom musi byt [SConditionResult<SFalseValue>].
struct SConditionResult<SFalseValue>
{
//-----------------------------------------------------------------------------
	public:
		// MEMBER [RESULT] nadobuda hodnotu FALSE.
		static const bool										RESULT=false;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! STRUCTURE [SFunctionXXXCheckMethods] je NON-TEMPLATE STRUCTURE, ktora sluzi iba ako WRAPPER na ulozenie STATIC METHODS, ktore kontroluju ci CLASS 
// !!!!! STRUCTURE [SFunctionXXXCheckMethods] obsahuje IBA DEKLARACIE METHODS CheckIfHasMethodXXX(). Ich DEFINICIE (BODIES) NIE SU POTREBNE, pretoze COMPILER pouziva iba ich DEKLARACIE na vykonanie COMPILE-TIME testov a ich INSTANCIE NIKDY NEVYTVORI a tym padom ani NEPOTREBUJE ich BODIES.
struct SFunctionXXXCheckMethods
{
//-----------------------------------------------------------------------------
	public:
		// !!!!! Klucova TEMPLATE METHOD, ktora kontroluje ci TYPE [TType] ma METHOD XXX().
		// !!!!! METHOD NEMA BODY, pretoze sa pouziva iba v COMPILE-TIME na vyhodnotenie podmienky. Nevola sa v RUN-TIME a teda jej BODY NIE JE POTREBNE.
		template <typename TType>
		static auto CheckIfHasMethodXXX(TType Value) -> decltype(Value.XXX());

		// !!!!! OVERLOADED METHOD, ktoru C++ pouzije vtedy, ak [TType] NEMA METHOD XXX(). V takom pripade pokus o substituciu v TYPE v TEMPLATE METHOD CheckIfHasMethodXXX() ZLYHA a kedze sa aplikuje mechanizmus SFINAE, C++ pouzije tuto OVERLOADED METHOD.
		// !!!!! METHOD NEMA BODY, pretoze sa pouziva iba v COMPILE-TIME na vyhodnotenie podmienky. Nevola sa v RUN-TIME a teda jej BODY NIE JE POTREBNE.
		template <typename... TTypes>
		static SFalseValue CheckIfHasMethodXXX(TTypes...);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Zakladna STRUCTURE, ktora sluzi na kontrolu ci TYPE [TType] ma METHOD XXX().
// !!!!! Klucovym atributom TEMPLATE STRUCTURE [SFunctionXXXCheck] je fakt, ze je DERIVED zo TEMPLATE STRUCTURE [SConditionResult]. Vdaka tejto INHERITANCE C++ moze vytvorit z TEMPLATE [SFunctionXXXCheck] 2 rozlicne TEMPLATE INSTANTION.
//    1. TEMPLATE je DERIVED zo STRUCTURE [SConditionResult<ABC>], kde 'ABC' je INY TYPE, ako TYPE [SFalseValue]. K tomuto INSTANCING dochadza vtedy, ked C++ sa rozhodne pre 1. VERZIU METHOD SFunctionXXXCheckMethods::CheckIfHasMethodXXX(). A pre nu sa C++ rozhodne vtedy, ak TYPE 'ABC' dokaze substituovat za TEMPLATE PARAMETER [TType], co sa podari vtedy, ake TYPE 'ABC' ma METHOD XXX().
//    2. TEMPLATE je DERIVED zo STRUCTURE [SConditionResult<SFalseValue>]. K tomuto INSTANCING dochadza vtedy, ked C++ sa rozhodne pre 2. VERZIU METHOD SFunctionXXXCheckMethods::CheckIfHasMethodXXX(). A pre nu sa C++ rozhodne vtedy, ak TYPE 'ABC' NEDOKAZE substituovat za TEMPLATE PARAMETER [TType] 1. VERZIE METHOD SFunctionXXXCheckMethods::CheckIfHasMethodXXX(), k comu dojde vtedy, ked TYPE 'ABC' NEMA METHOD XXX().
template<typename TType>
struct SFunctionXXXCheck : public SConditionResult<decltype(SFunctionXXXCheckMethods::CheckIfHasMethodXXX(std::declval<TType>()))>
{
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------