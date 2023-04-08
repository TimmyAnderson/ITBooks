//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <locale>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Definuje INTERFACE pre CUSTOM FACET.
class CMySuperFacet : public std::locale::facet
{
//-----------------------------------------------------------------------------
	public:
		// !!! ID MUSI byt definovany v BASE FACET, pretoze VSETKY FACETS, ktore su DERIVED z BASE FACET MUSIA mat ROVNAKY ID.
		static std::locale::id									id;

	public:
		virtual std::wstring GetYesString(void) const=0;
		virtual std::wstring GetNoString(void) const=0;

	public:
		CMySuperFacet(void);
		virtual ~CMySuperFacet(void) override;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------