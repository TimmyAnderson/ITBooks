//------------------------------------------------------------------------------------------------------
#include "BagFileRecords.h"
#include "BagFileRecords.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CBagFileRecords::CBagFileRecords(void)
	: MBagExecutable(), MRunnableType()
{
}
//------------------------------------------------------------------------------------------------------
CBagFileRecords::~CBagFileRecords(void)
{
	for (vector<CBagFileRecord*>::iterator Iterator=MBagFileRecords.begin();Iterator!=MBagFileRecords.end();Iterator++)
	{
		delete(*Iterator);
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
wstring CBagFileRecords::GetBagExecutable(void)
{
	return(MBagExecutable);
}
//------------------------------------------------------------------------------------------------------
wstring CBagFileRecords::GetRunnableType(void)
{
	return(MRunnableType);
}
//------------------------------------------------------------------------------------------------------
vector<CBagFileRecord*>& CBagFileRecords::GetBagFileRecords(void)
{
	return(MBagFileRecords);
}
//------------------------------------------------------------------------------------------------------
void CBagFileRecords::SetBagExecutable(std::wstring Value)
{
	MBagExecutable=Value;
}
//------------------------------------------------------------------------------------------------------
void CBagFileRecords::SetRunnableType(std::wstring Value)
{
	MRunnableType=Value;
}
//------------------------------------------------------------------------------------------------------