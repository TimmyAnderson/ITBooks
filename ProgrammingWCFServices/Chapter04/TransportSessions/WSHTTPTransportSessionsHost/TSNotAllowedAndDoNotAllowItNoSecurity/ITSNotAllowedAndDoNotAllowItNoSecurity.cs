using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransportSessionsSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace WSHTTPTransportSessionsHost
{
//-------------------------------------------------------------------------------------------------------
	// !!! Zakazem TS.
	[ServiceContract(SessionMode=SessionMode.NotAllowed)]
	public interface ITSNotAllowedAndDoNotAllowItNoSecurity : ISimpleService
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------