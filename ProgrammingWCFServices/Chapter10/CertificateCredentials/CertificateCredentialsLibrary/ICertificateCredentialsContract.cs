using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
namespace CertificateCredentialsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ICertificateCredentialsContract
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