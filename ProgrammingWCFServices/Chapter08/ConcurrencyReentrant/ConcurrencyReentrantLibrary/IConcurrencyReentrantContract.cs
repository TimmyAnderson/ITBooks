using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyReentrantLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(IConcurrencyReentrantCallback))]
	public interface IConcurrencyReentrantContract : ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void SlowMethod(string Message);
        [OperationContract]
		void DoCallback(string Message);
        [OperationContract]
		void DoSlowCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------