using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ICallbackFaultsCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void NonFaultCallback(string Message);
		[OperationContract]
		[FaultContract(typeof(CFaultDetails))]
		void FaultCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------