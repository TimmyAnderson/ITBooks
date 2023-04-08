using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultBindingHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
	public interface IService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=ProtectionLevel.EncryptAndSign)]
		string ToUpper(string Text);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------