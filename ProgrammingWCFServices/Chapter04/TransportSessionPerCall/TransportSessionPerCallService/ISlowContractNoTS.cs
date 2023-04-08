using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace TransportSessionPerCallService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.NotAllowed)]
	public interface ISlowContractNoTS
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void SlowOperation(string ID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------