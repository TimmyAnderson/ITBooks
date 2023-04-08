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
	[ServiceContract(ProtectionLevel=System.Net.Security.ProtectionLevel.None)]
	public interface INonSecureContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=System.Net.Security.ProtectionLevel.None)]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------