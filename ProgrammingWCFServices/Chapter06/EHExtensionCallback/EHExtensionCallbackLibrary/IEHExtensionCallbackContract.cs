using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required, CallbackContract=typeof(IEHExtensionCallbackCallback))]
	public interface IEHExtensionCallbackContract : ICallbackRegister
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract]
		void DoCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------