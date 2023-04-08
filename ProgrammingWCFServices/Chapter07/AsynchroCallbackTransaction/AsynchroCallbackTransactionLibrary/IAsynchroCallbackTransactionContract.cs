using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace AsynchroCallbackTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(IAsynchroCallbackTransactionCallback))]
	public interface IAsynchroCallbackTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Connect(string ClientName);
        [OperationContract]
        void Disconnect();
        [OperationContract]
		void DoTransaction(string Message, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------