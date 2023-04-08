using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessageHeadersHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IService2
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Operation2(ref string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------