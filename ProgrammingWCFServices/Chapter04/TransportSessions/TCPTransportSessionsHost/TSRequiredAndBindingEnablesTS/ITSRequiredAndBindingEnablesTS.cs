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
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ITSRequiredAndBindingEnablesTS : ISimpleService
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------