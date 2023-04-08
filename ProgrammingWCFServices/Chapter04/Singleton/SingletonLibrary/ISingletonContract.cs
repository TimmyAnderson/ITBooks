using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SingletonLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Pri singleton nemusi tu byt Required.
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface ISingletonContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CState GetState();
		[OperationContract]
		void SetState(CState State);
		[OperationContract]
		void PrintActualState();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------