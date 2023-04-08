using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SimpleTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ISimpleTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void OneDBTwoTables(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void TwoDBOneTableInEach(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void TwoDBOneTableInEachExcplicitVoting(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TwoDBOneTableInEachExcplicitVotingWithException(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		[FaultContract(typeof(Exception))]
		void TwoDBOneTableInEachWithException(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------