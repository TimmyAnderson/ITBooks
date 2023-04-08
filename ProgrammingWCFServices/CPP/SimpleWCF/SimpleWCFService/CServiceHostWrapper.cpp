#include "StdAfx.h"
#include "CServiceHostWrapper.h"
//-------------------------------------------------------------------------------------------------------
namespace SimpleWCFService
{
//-------------------------------------------------------------------------------------------------------
generic<typename T>
CServiceHostWrapper<T>::CServiceHostWrapper(void)
{
	MSyn=gcnew Object();
	MHost=gcnew ServiceHost(T::typeid);

	MHost->OpenTimeout=TimeSpan(0,0,10);
	MHost->CloseTimeout=TimeSpan(0,0,10);
}
//-------------------------------------------------------------------------------------------------------
generic<typename T>
CServiceHostWrapper<T>::~CServiceHostWrapper(void)
{
	StopService();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
generic<typename T>
ServiceHost^ CServiceHostWrapper<T>::Host::get(void)
{
	return(MHost);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
generic<typename T>
generic<typename TL>
void CServiceHostWrapper<T>::AddServiceEndpoint(Binding^ EndpointBinding, String^ Address)
{
	lock			LockRoot(MSyn);
	{
		try
		{
			MHost->AddServiceEndpoint(TL::typeid,EndpointBinding,Address);
		}
		catch(Exception^ E)
		{
			Console::WriteLine(String::Format("CServiceHostWrapper.AddServiceEndpoint() - Exception: {0} !",E->Message));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
generic<typename T>
void CServiceHostWrapper<T>::StartService(void)
{
	lock			LockRoot(MSyn);
	{
		try
		{
			MHost->Open();
		}
		catch(Exception^ E)
		{
			Console::WriteLine(String::Format("CServiceHostWrapper.StartService() - Exception: {0} !",E->Message));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
generic<typename T>
void CServiceHostWrapper<T>::StopService(void)
{
	lock			MLockRoot(MSyn);
	{
		try
		{
			if (MHost->State==CommunicationState::Opened==true || MHost->State==CommunicationState::Opening==true)
				MHost->Close();
		}
		catch(Exception^ E)
		{
			Console::WriteLine(String::Format("CServiceHostWrapper.StopService() - Exception: {0} !",E->Message));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
generic<typename T>
void CServiceHostWrapper<T>::AddTCPMEXEndpoint(String^ MEXEndpoindName)
{
	lock			MLockRoot(MSyn);
	{
		try
		{
			BindingElement^				BE=gcnew TcpTransportBindingElement();
			CustomBinding^				CB=gcnew CustomBinding(BE);
			ServiceMetadataBehavior^	SMB;

			if ((SMB=Host->Description->Behaviors->Find<ServiceMetadataBehavior^>())==nullptr)
			{
				SMB=gcnew ServiceMetadataBehavior();
				Host->Description->Behaviors->Add(SMB);
			}

			MHost->AddServiceEndpoint(IMetadataExchange::typeid,CB,MEXEndpoindName);
		}
		catch(Exception^ E)
		{
			Console::WriteLine(String::Format("CServiceHostWrapper.AddServiceEndpoint() - Exception: {0} !",E->Message));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------