//-------------------------------------------------------------------------------------------------------
#include "SeasonFacet_USA.h"
#include <algorithm>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
const string													CSeasonFacet_USA::MSeasons[]={"SPRING","SUMMER","FALL","WINTER"};
//-------------------------------------------------------------------------------------------------------
CSeasonFacet_USA::CSeasonFacet_USA(void)
{
}
//-------------------------------------------------------------------------------------------------------
CSeasonFacet_USA::~CSeasonFacet_USA(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
const std::string& CSeasonFacet_USA::ToString(ESeason Season) const
{
	if (Season<E_SPRING || E_WINTER<Season)
	{
		// Vrati hodnotu indikujucu CHYBU.
		static const string										Error="INVALID SEASON";

		return(Error);
	}
	else
	{
		return(MSeasons[Season]);
	}
}
//-------------------------------------------------------------------------------------------------------
bool CSeasonFacet_USA::FromString(const std::string& String, ESeason& ParsedSeason) const
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