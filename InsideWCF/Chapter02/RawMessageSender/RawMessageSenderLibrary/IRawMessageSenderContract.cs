using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace RawMessageSenderLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(Namespace="http://wintellect.com/RawMessageSenderContract")]
	public interface IRawMessageSenderContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(Action="urn:SubmitOrder")]
		void SubmitOrder(Message Order);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------