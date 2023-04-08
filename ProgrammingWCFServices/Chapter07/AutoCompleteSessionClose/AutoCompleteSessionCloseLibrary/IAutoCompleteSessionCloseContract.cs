using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace AutoCompleteSessionCloseLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IAutoCompleteSessionCloseContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void DoTransaction(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void ThrowException();
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void FinishTransaction(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------