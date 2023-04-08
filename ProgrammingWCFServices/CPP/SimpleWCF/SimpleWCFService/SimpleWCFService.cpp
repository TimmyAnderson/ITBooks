#include "stdafx.h"
#include "CServiceHostWrapper.h"
#include "CServiceHostWrapperCollection.h"
//-------------------------------------------------------------------------------------------------------
using namespace System;
using namespace SimpleWCFLibrary;
using namespace SimpleWCFService;
//-------------------------------------------------------------------------------------------------------
int main(array<System::String ^> ^args)
{
	CServiceHostWrapperCollection^				ServiceHostWrapperCollection=gcnew CServiceHostWrapperCollection();
	CServiceHostWrapper<CSimpleWCFService^>^	Service=gcnew CServiceHostWrapper<CSimpleWCFService^>();

	ServiceHostWrapperCollection->AddServiceHostWrapper(Service);

	// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
	Binding^								TCPBinding=gcnew NetTcpBinding();

	Service->AddServiceEndpoint<ISimpleWCFContract^>(TCPBinding,"net.tcp://localhost:9001/ISimpleWCFContract");

	Service->AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

	ServiceHostWrapperCollection->StartServices();

	Console::WriteLine("Press any key to STOP services !");
	Console::ReadLine();

	ServiceHostWrapperCollection->StopServices();

	Console::WriteLine("Press any key to EXIT !");
	Console::ReadLine();
    return(0);
}
//-------------------------------------------------------------------------------------------------------