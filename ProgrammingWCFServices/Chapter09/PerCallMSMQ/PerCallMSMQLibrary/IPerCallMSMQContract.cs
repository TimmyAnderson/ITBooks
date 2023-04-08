using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerCallMSMQLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IPerCallMSMQContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void PrintText(string Message);
        [OperationContract(IsOneWay=true)]
		void ThrowException(string Message);
        [OperationContract(IsOneWay=true)]
		void PrintTextWithTransaction(string Message);
        [OperationContract(IsOneWay=true)]
		void ThrowExceptionWithTransaction(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------