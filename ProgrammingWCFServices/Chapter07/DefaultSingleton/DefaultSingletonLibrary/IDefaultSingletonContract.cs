using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DefaultSingletonLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IDefaultSingletonContract
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