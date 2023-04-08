//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <locale>
#include <iostream>
#include "ESeason.h"
//-------------------------------------------------------------------------------------------------------
// !!! Definujem INTERACE pre CUSTOM FACET.
class ISeasonFacet : public std::locale::facet
{
	public:
		// !!! Kedze sa jedna o NOVY FACET INTERFACE, tak MUSIM DEFINOVAT INE ID.
		static std::locale::id									id;

	public:
		// INTERFACE METHODS.
		virtual const std::string& ToString(ESeason Season) const=0;
		virtual bool FromString(const std::string& String, ESeason& ParsedSeason) const=0;

	public:
		ISeasonFacet(size_t InitRefs=0);
		virtual ~ISeasonFacet(void);
};
//-------------------------------------------------------------------------------------------------------
// !!! GLOBALNE OPERATORS.
std::ostream& operator<<(std::ostream& Stream, ESeason Season);
std::istream& operator>>(std::istream& Stream, ESeason& Season);
//-------------------------------------------------------------------------------------------------------