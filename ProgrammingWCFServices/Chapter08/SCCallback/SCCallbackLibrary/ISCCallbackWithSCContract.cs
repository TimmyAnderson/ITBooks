using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ISCCallbackWithSCCallback))]
	public interface ISCCallbackWithSCContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Connect(string ClientName);
        [OperationContract]
        void Disconnect();
        [OperationContract]
		void DoCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------