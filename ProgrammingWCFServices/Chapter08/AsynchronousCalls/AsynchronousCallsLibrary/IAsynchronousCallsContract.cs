using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IAsynchronousCallsContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void IsAlive();
        [OperationContract]
		string SlowMethod(string Message, ref string RefMessage, out string OutMessage);
        [OperationContract]
        [FaultContract(typeof(Exception))]
		void SlowMethodWithException(string Message);
        [OperationContract]
		void SlowMethodWithUnexpectedException(string Message);
//-------------------------------------------------------------------------------------------------------
		// !!! Tato OPERATION je ASYNCHRONNE REALIZOVANA na SERVICE.
        [OperationContract(AsyncPattern=true)]
		IAsyncResult BeginServerAsynchroSlowMethod(string Message, AsyncCallback CB, object AS);
		string EndServerAsynchroSlowMethod(IAsyncResult AR);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------