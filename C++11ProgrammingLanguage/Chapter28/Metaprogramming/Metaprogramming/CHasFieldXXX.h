//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! CLASS zistuje ci TYPE [TType] ma definovany PUBLIC FIELD 'XXX'.
template <typename TType>
class CHasFieldXXX
{
//-------------------------------------------------------------------------------------------------------
	private:
		// !!! Pomocne STRUCTURES. Klucove je, ze MUSIA mat ROZLICNU DLZKU, kedze sa testuje ich SIZEOF.
		struct SOperatorYes
		{
			char												MField[1];
		};

		struct SOperatorNo
		{
			char												MField[2];
		};

	private:
		// !!! Pomocna STRUCTURE, ktora ma definovany FIELD lubovolneho TYPE, ktory vsak MUSI mat NAME 'XXX'.
		struct CBaseClass
		{
			void*												XXX;
		};

		// !!! Pomocna STRUCTURE, ktora dedi z TYPE 'CBaseClass' a TYPE [TType].
		// !!!!! Jediny zmysel tejto STRUCTURE je v tom, ze zistuje ci je FIELD 'XXX' v TYPE [TType] uz definovany.
		// !!!!! Ak FIELD 'XXX' v TYPE [TType] NIE JE DEFINOVANY, potom ho tam prida STRUCTURE 'CBaseClass'. Vysledkom bude, ze STRUCTURE [CDerivedClass] bude mat PRESNE 1 FIELD 'XXX'.
		// !!!!! Ak FIELD 'XXX' v TYPE [TType] UZ JE DEFINOVANY, potom DALSI prida STRUCTURE 'CBaseClass'. Vysledkom bude, ze STRUCTURE [CDerivedClass] bude mat 2 FIELDS 'XXX'.
		struct CDerivedClass : public TType, CBaseClass
		{
		};

	private:
		// !!! Za TYPE [TLocalType] CONSTANT definovana nizsie dosadi pomocny TYPE [CDerivedClass].
		// !!!!! COMPILER pri zvazovani tejto verzie OVERLOADED METHOD HasFieldXXX<CDerivedClass>() sa pokusi definovat POINTER typu [CDerivedClass::XXX*]. Ak STRUCTURE 'CDerivedClass' ma VIAC ako JEDEN FIELD pomenovany ako 'XXX' (jeden mala z TYPE [TType] a dalsi zdedila z TYPE 'CBaseClass'), tak COMPILER bude mat CHYBNU AMBIGUOUS DEKLARACIU, pretoze sa NEBUDE VEDIET ROZHODNUT, ktoru VERZIU FIELD 'XXX' ma POUZIT. COMPILER aplikuje mechanizmus SFINAE vdaka comu ODMIETNE TUTO VERZIU OVERLOADED METHOD HasFieldXXX<CDerivedClass>() a vyskusa 2. verziu.
		template <typename TLocalType>
		static SOperatorNo HasFieldXXX(decltype(TLocalType::XXX)*);

		// !!! Za TYPE [TLocalType] CONSTANT definovana nizsie dosadi pomocny TYPE [CDerivedClass].
		// !!!!! Ak nebolo mozne pouzit prvu verziu OVERLOADED METHOD HasFieldXXX<CDerivedClass>() potom to znamena, ze POVODNY TYPE [TType] UZ MAL DEFINOVANY FIELD 'XXX', a preto METHOD vrati TYPE 'SOperatorYes' signalizujuc, ze TYPE [TType] MA DEFINOVANY FIELD 'XXX'.
		template <typename TLocalType>
		static SOperatorYes HasFieldXXX(TLocalType*);

	public:
		static const bool										IfFieldDefined=(sizeof(HasFieldXXX<CDerivedClass>(0))==sizeof(SOperatorYes));
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------