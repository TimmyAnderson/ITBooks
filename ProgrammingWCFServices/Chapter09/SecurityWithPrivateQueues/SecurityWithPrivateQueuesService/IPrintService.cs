using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.Net.Security;
//-------------------------------------------------------------------------------------------------------
namespace SecurityWithPrivateQueuesService
{
//-------------------------------------------------------------------------------------------------------
	//[ServiceContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
	[ServiceContract(ProtectionLevel=ProtectionLevel.None)]
	public interface IPrintService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsOneWay=true)]
		void PrintText(string Text);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------