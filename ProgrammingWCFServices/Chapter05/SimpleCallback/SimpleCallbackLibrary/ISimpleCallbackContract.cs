using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SimpleCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ISimpleCallbackCallback))]
	public interface ISimpleCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Connect(string ClientName);
        [OperationContract]
        void Disconnect();
        [OperationContract]
		void DoSomething(string ClientName, string Message, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------