using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyModesLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(IConcurrencyModesCallback))]
	public interface IConcurrencyModesContract : ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void SlowMethod(string Message, int Timeout);
        [OperationContract]
		void DoSynchroCallbackToJustSender(string Message, int Timeout);
        [OperationContract]
		void DoSynchroCallbackForAllClients(string Message, int Timeout);
        [OperationContract]
		void DoAsynchroCallback(string Message, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------