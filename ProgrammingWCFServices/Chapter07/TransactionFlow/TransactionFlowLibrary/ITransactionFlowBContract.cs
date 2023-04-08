using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ITransactionFlowBContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Dummy();
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFAllowed(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.NotAllowed)]
		[FaultContract(typeof(Exception))]
		void TFNotAllowed(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Mandatory)]
		[FaultContract(typeof(Exception))]
		void TFMandatory(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFImplicitVoting(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFImplicitVotingWithException(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFExplicitVoting(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFExplicitVotingWithEnd(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFExplicitVotingStartTransaction(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TFExplicitVotingEndTransaction(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------