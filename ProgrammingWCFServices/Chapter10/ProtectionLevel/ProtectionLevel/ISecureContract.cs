using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ProtectionLevel
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(ProtectionLevel=System.Net.Security.ProtectionLevel.EncryptAndSign)]
	public interface ISecureContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=System.Net.Security.ProtectionLevel.EncryptAndSign)]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------