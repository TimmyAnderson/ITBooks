//-------------------------------------------------------------------------------------------------------
#include <locale>
#include <iostream>
#include "ISeasonFacet.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
ostream& operator<<(ostream& Stream, ESeason Season)
{
	// Ziska sa LOCALE zo STREAMU.
	const locale&												Locale=Stream.getloc();

	if (has_facet<ISeasonFacet>(Locale))
	{
		return(Stream << use_facet<ISeasonFacet>(Locale).ToString(Season));
	}
	else
	{
		return(Stream << int(Season));
	}
}
//-------------------------------------------------------------------------------------------------------
istream& operator>>(istream& Stream, ESeason& Season)
{
	// Ziska sa LOCALE zo STREAMU.
	const locale&												Locale=Stream.getloc();

	// Zo STREAMU sa nacita TEXTOVA REPREZENTACIA ESeason.
	if (has_facet<ISeasonFacet>(Locale)==true)
	{
		const ISeasonFacet&										Facet=use_facet<ISeasonFacet>(Locale);
		string													Buffer;

		if (!(Stream >> Buffer && Facet.FromString(Buffer,Season)==true))
		{
			Stream.setstate(ios_base::failbit);
		}

		return(Stream);
	}
	else
	{
		// Zo STREAMU sa nacita CISELNA REPREZENTACIA ESeason.
		int														Number;

		Stream >> Number;

		Season=ESeason(Number);

		return(Stream);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
locale::id														ISeasonFacet::id;
//-------------------------------------------------------------------------------------------------------
ISeasonFacet::ISeasonFacet(size_t InitRefs)
	: locale::facet(InitRefs)
{
}
//-------------------------------------------------------------------------------------------------------
ISeasonFacet::~ISeasonFacet(void)
{
}
//-------------------------------------------------------------------------------------------------------