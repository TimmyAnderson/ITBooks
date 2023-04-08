using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace StatefulSingletonLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IStatefulSingletonContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void DoTransaction(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void NonTransaction();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------