using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-----------------------------------------------------------------------------------------------------------
namespace ReliableSession_FaultEvent_Shared
{
//-----------------------------------------------------------------------------------------------------------
	// Vypol som SECURITY, aby som sa nemusel babrat pri HTTP s HTTPS kanalom.
	[ServiceContract(ProtectionLevel=ProtectionLevel.None,SessionMode=SessionMode.Allowed)]
	public interface ISimpleTestInterface
	{
//-----------------------------------------------------------------------------------------------------------
		[OperationContract(ProtectionLevel=ProtectionLevel.None)]
		string ToUpper(string Param);
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------