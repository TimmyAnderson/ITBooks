using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace CustomHeadersInConfigHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpperEndpointHeader(string Value);
		[OperationContract]
		string ToUpperAddressHeader(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------