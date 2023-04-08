using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ICallbackFaultsCallback))]
	public interface ICallbackFaultsContract : ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void SynchroNonFaultException(string Message, int Timeout);
        [OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void AsynchroNonFaultException(string Message, int Timeout);
        [OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void SynchroFaultException(string Message, int Timeout);
        [OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void AsynchroFaultException(string Message, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------