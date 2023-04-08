using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace FaultContractsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IFaultContractsContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IsAlive();
		[OperationContract]
        [FaultContract(typeof(CFaultDetails))]
		void ThrowCFaultDetailsException();
		[OperationContract]
        [FaultContract(typeof(InvalidOperationException))]
		void ThrowInvalidOperationException();
		[OperationContract]
        [FaultContract(typeof(InvalidOperationException))]
		void ThrowInvalidOperationAsFaultException();
		[OperationContract]
		void ThrowFaultException();
		[OperationContract]
		void ThrowExceptionDetail();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------