using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
namespace MySecurityProviderLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IMySecurityProviderContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void IsAlive();
        [OperationContract]
		void AutoAuthorization();
        [OperationContract]
		[FaultContract(typeof(SecurityAccessDeniedException))]
		void ManualAuthorization();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------