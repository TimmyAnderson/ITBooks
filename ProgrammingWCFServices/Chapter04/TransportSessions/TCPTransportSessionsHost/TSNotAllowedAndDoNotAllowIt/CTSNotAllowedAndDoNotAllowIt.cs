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
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CTSNotAllowedAndDoNotAllowIt : ITSNotAllowedAndDoNotAllowIt
	{
//-------------------------------------------------------------------------------------------------------
		public string SomeServiceMethod(string Param)
		{
			return(CTestHelper.SomeServiceMethod(Param));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------