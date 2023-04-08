//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "ISeasonFacet.h"
//-------------------------------------------------------------------------------------------------------
class CSeasonFacet_SK : public ISeasonFacet
{
	// !!! Kedze CSeasonFacet_SK ma TEN ISTY INTERFACE ako ISeasonFacet, NESMIE MAT VLASTNE ID. Musi mat ROVNAKE ako ma ISeasonFacet.

	private:
		static const std::string								MSeasons[];

	public:
		// DERIVED METHODS, ktore su implementaciou FACET INTERFACE ISeasonFacet.
		virtual const std::string& ToString(ESeason Season) const;
		virtual bool FromString(const std::string& String, ESeason& ParsedSeason) const;

	public:
		CSeasonFacet_SK(void);
		virtual ~CSeasonFacet_SK(void);
};
//-------------------------------------------------------------------------------------------------------