using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DeliveryFailuresLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IDeliveryFailuresContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void PrintText(string Message);
        [OperationContract(IsOneWay=true)]
		void ThrowExceptionWithTransaction(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------