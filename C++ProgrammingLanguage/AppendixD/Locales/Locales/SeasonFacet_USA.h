//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "ISeasonFacet.h"
//-------------------------------------------------------------------------------------------------------
class CSeasonFacet_USA : public ISeasonFacet
{
	// !!! Kedze CSeasonFacet_USA ma TEN ISTY INTERFACE ako ISeasonFacet, NESMIE MAT VLASTNE ID. Musi mat ROVNAKE ako ma ISeasonFacet.

	private:
		static const std::string								MSeasons[];

	public:
		// DERIVED METHODS, ktore su implementaciou FACET INTERFACE ISeasonFacet.
		virtual const std::string& ToString(ESeason Season) const;
		virtual bool FromString(const std::string& String, ESeason& ParsedSeason) const;

	public:
		CSeasonFacet_USA(void);
		virtual ~CSeasonFacet_USA(void);
};
//-------------------------------------------------------------------------------------------------------