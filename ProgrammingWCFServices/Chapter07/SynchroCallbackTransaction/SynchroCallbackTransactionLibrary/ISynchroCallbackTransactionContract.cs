using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SynchroCallbackTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ISynchroCallbackTransactionCallback))]
	public interface ISynchroCallbackTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Connect(string ClientName);
        [OperationContract]
        void Disconnect();
        [OperationContract]
		void DoTransaction(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------