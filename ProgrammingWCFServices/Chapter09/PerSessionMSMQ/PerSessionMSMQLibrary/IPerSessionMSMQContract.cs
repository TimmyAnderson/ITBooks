using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionMSMQLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IPerSessionMSMQContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void TransactionStart(string Message);
        [OperationContract(IsOneWay=true)]
		void TransactionFinishAuto(string Message);
        [OperationContract(IsOneWay=true)]
		void TransactionFinishManual(string Message);
        [OperationContract(IsOneWay=true)]
		void FailTransaction(string Message);
        [OperationContract(IsOneWay=true)]
		void NonTransaction(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------