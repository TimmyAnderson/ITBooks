using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(CallbackContract=typeof(ICallbackContract))]
	interface ISomeContractDuplex
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsOneWay=true)]
		void SomeOperation(string Input);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------