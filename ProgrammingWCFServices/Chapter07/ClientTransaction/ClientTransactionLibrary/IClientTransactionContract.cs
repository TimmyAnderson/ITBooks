using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ClientTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IClientTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------