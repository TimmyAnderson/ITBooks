using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IEHExtensionHostContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void IsAlive();
		[OperationContract]
        [FaultContract(typeof(ObjectDisposedException))]
		void ThrowException();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------