using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using LCChannel;
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	interface ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsInitiating=true, IsOneWay=true)]
		void SomeOperation(string Input);
		[OperationContract(IsTerminating=true, IsOneWay=true)]
		void SomeOtherOperation(string Input);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------