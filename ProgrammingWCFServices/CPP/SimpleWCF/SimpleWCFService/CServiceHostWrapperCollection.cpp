#include "StdAfx.h"
#include "CServiceHostWrapperCollection.h"
//-------------------------------------------------------------------------------------------------------
namespace SimpleWCFService
{
//-------------------------------------------------------------------------------------------------------
CServiceHostWrapperCollection::CServiceHostWrapperCollection(void)
{
	MSyn=gcnew Object();
	MList=gcnew List<IServiceHostWrapper^>;
}
//-------------------------------------------------------------------------------------------------------
CServiceHostWrapperCollection::~CServiceHostWrapperCollection(void)
{
	StopServices();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CServiceHostWrapperCollection::StartServices(void)
{
	lock			MLockRoot(this);
	{
		for each(IServiceHostWrapper^ ServiceHostWrapper in MList)
			ServiceHostWrapper->StartService();
	}
}
//-------------------------------------------------------------------------------------------------------
void CServiceHostWrapperCollection::StopServices(void)
{
	lock			MLockRoot(this);
	{
		for each(IServiceHostWrapper^ ServiceHostWrapper in MList)
			ServiceHostWrapper->StopService();
	}
}
//-------------------------------------------------------------------------------------------------------
void CServiceHostWrapperCollection::AddServiceHostWrapper(IServiceHostWrapper^ ServiceHostWrapper)
{
	lock			MLockRoot(this);
	{
		MList->Add(ServiceHostWrapper);
	}
}
//-------------------------------------------------------------------------------------------------------
bool CServiceHostWrapperCollection::RemoveServiceHostWrapper(int Index)
{
	lock			MLockRoot(this);
	{
		if (Index>=MList->Count)
			return(false);

		MList->RemoveAt(Index);
		return(true);
	}
}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------