using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ISimpleFaultsPerSessionContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IsAlive();
		[OperationContract]
		void ThrowSimpleException();
		[OperationContract]
        [FaultContract(typeof(CFaultDetails))]
		void ThrowFaultException();
		[OperationContract]
        [FaultContract(typeof(CFaultDetails))]
		void ThrowCMyFaultException();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------