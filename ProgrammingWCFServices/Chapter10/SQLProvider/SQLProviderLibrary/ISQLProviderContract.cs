using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
namespace SQLProviderLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ISQLProviderContract
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