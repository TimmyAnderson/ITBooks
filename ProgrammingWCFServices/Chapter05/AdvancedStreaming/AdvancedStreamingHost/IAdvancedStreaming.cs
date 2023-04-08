using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace AdvancedStreamingHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IAdvancedStreaming
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CMyTestStream GetNotFullyFilledStream();
		[OperationContract]
		CMyTestStream GetAlreadyFilledStream();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------