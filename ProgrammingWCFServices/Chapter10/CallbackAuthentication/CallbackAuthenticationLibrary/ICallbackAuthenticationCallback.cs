using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Security.Principal;
using System.Net.Security;
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ICallbackAuthenticationCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
		void OnCallback();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------