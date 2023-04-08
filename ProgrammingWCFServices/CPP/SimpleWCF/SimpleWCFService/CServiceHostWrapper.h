#pragma once
//-----------------------------------------------------------------------------
#include <msclr/lock.h>
#include "IServiceHostWrapper.h"
//-----------------------------------------------------------------------------
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::ServiceModel;
using namespace System::ServiceModel::Channels;
using namespace System::ServiceModel::Description;
using namespace msclr;
//-------------------------------------------------------------------------------------------------------
namespace SimpleWCFService
{
//-------------------------------------------------------------------------------------------------------
	generic<typename T>
	public ref class CServiceHostWrapper : IServiceHostWrapper
	{
		private:
			Object^					MSyn;
			ServiceHost^			MHost;
//-------------------------------------------------------------------------------------------------------
		public:
			property ServiceHost^	Host
			{
				virtual ServiceHost^ get(void);
			}
//-------------------------------------------------------------------------------------------------------
		public:
			generic<typename TL> void AddServiceEndpoint(Binding^ EndpointBinding, String^ Address);
//-------------------------------------------------------------------------------------------------------
		public:
			virtual void StartService(void);
			virtual void StopService(void);
			virtual void AddTCPMEXEndpoint(String^ MEXEndpoindName);
//-------------------------------------------------------------------------------------------------------
		public:
			CServiceHostWrapper(void);
			~CServiceHostWrapper(void);
//-------------------------------------------------------------------------------------------------------
	};
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------