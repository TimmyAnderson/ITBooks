using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
namespace AuthorizationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IAuthorizationContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void IsAlive();
        [OperationContract]
		void AutoAuthorization1();
        [OperationContract]
		void AutoAuthorization2();
        [OperationContract]
		void AutoAuthorization3();
        [OperationContract]
		[FaultContract(typeof(SecurityAccessDeniedException))]
		void ManualAuthorization1();
        [OperationContract]
		[FaultContract(typeof(SecurityAccessDeniedException))]
		void ManualAuthorization2();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------