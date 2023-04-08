using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ICallbackContractHierarchyCallback1))]
	public interface ICallbackContractHierarchyContract1 : ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void CallCallback1(string Message, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------