using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(ICallbackContractHierarchyCallback2))]
	public interface ICallbackContractHierarchyContract2 : ICallbackContractHierarchyContract1, ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void CallCallback2(string MessagePart1, string MessagePart2, int Timeout);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------