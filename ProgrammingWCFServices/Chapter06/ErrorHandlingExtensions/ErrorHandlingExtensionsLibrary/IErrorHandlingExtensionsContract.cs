using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ErrorHandlingExtensionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IErrorHandlingExtensionsContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IsAlive();
		[OperationContract]
		void CaughtException();
		[OperationContract]
        [FaultContract(typeof(ObjectDisposedException))]
		void PromoteAllException();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------