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
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ITSRequiredAndBindingIsDefault : ISimpleService
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------