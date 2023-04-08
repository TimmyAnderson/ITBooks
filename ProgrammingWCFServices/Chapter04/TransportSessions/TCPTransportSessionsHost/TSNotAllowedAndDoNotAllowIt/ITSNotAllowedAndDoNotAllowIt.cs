using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransportSessionsSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TCPTransportSessionsHost
{
//-------------------------------------------------------------------------------------------------------
	// !!! Zakazem TS.
	[ServiceContract(SessionMode=SessionMode.NotAllowed)]
	public interface ITSNotAllowedAndDoNotAllowIt : ISimpleService
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------