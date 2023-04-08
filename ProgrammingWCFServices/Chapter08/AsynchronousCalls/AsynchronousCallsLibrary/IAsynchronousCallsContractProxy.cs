using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Specializovany PROXY INTERFACE pouzivany IBA NA STRANE CLIENTA.
	[ServiceContract(Name="IAsynchronousCallsContract",SessionMode=SessionMode.Required)]
	public interface IAsynchronousCallsContractProxy
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void IsAlive();
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		string SlowMethod(string Message, ref string RefMessage, out string OutMessage);

		// Asynchronna verzia metody SlowMethod().
        [OperationContract(AsyncPattern=true)]
		IAsyncResult BeginSlowMethod(string Message, ref string RefMessage, AsyncCallback Callback, object AsyncState);
		string EndSlowMethod(ref string RefMessage, out string OutMessage, IAsyncResult Result);
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
        [FaultContract(typeof(Exception))]
		void SlowMethodWithException(string Message);

		// Asynchronna verzia metody SlowMethodWithException().
        [OperationContract(AsyncPattern=true)]
		IAsyncResult BeginSlowMethodWithException(string Message, AsyncCallback Callback, object AsyncState);
		void EndSlowMethodWithException(IAsyncResult Result);
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void SlowMethodWithUnexpectedException(string Message);

		// Asynchronna verzia metody SlowMethodWithUnexpectedException().
        [OperationContract(AsyncPattern=true)]
		IAsyncResult BeginSlowMethodWithUnexpectedException(string Message, AsyncCallback Callback, object AsyncState);
		void EndSlowMethodWithUnexpectedException(IAsyncResult Result);
//-------------------------------------------------------------------------------------------------------
        [OperationContract(AsyncPattern=true)]
		IAsyncResult BeginServerAsynchroSlowMethod(string Message, AsyncCallback CB, object AS);
		string EndServerAsynchroSlowMethod(IAsyncResult AR);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------