//-------------------------------------------------------------------------------------------------------
#include "SeasonFacet_SK.h"
#include <algorithm>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
const string													CSeasonFacet_SK::MSeasons[]={"JAR","LETO","JESEN","ZIMA"};
//-------------------------------------------------------------------------------------------------------
CSeasonFacet_SK::CSeasonFacet_SK(void)
{
}
//-------------------------------------------------------------------------------------------------------
CSeasonFacet_SK::~CSeasonFacet_SK(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
const std::string& CSeasonFacet_SK::ToString(ESeason Season) const
{
	if (Season<E_SPRING || E_WINTER<Season)
	{
		// Vrati hodnotu indikujucu CHYBU.
		static const string										Error="NEPLATNA HODNOTA";

		return(Error);
	}
	else
	{
		return(MSeasons[Season]);
	}
}
//-------------------------------------------------------------------------------------------------------
bool CSeasonFacet_SK::FromString(const std::string& String, ESeason& ParsedSeason) const
{
	const string*												Begin=&MSeasons[E_SPRING];
	const string*												End=&MSeasons[E_WINTER]+1;
	const string*												Pointer=find(Begin,End,String);

	if (Pointer==End)
	{
		return(false);
	}
	else
	{
		ParsedSeason=ESeason(Pointer-Begin);
		return(true);
	}
}
//-------------------------------------------------------------------------------------------------------