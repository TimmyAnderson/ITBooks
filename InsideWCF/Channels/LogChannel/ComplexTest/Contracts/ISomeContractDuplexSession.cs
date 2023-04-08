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
	[ServiceContract(CallbackContract=typeof(ICallbackContract), SessionMode=SessionMode.Required)]
	interface ISomeContractDuplexSession
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsInitiating=true)]
		void SomeOperation(string Input);
		[OperationContract(IsTerminating=true)]
		void SomeOtherOperation(string Input);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------