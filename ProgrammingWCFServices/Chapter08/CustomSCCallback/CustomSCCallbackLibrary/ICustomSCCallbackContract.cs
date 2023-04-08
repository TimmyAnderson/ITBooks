using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ICustomSCCallbackCallback))]
	public interface ICustomSCCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Connect(string ClientName);
        [OperationContract]
        void Disconnect();
        [OperationContract]
		void CallCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------